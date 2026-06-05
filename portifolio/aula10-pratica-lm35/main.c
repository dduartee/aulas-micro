#include "avr/interrupt.h"
#include "avr/io.h"
#include "util/delay.h"
#include <xc.h>

#define F_CPU 8000000

#define VREF 1
#define FREQ 4 // 4hz
#define PERI 1/FREQ

void ADC_config() {
  ADMUX = (0 << REFS1) | (0 << REFS0) | // vref=AREF (pino externo)  ← alternativo: (1<<REFS1)|(1<<REFS0) = 1.1v interno
          (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (1 << MUX0); // pino ADC5

  ADCSRA = (1 << ADEN) | (1 << ADATE) |
           (1 << ADIE) | // liga adc, com interrupção
           (1 << ADPS2) | (1 << ADPS1) |
           (1 << ADPS0); // prescaler 128 @ 16MHz, f_adc=125kHz, sampling rate

  ADCSRB = (1 << ADTS2) | (1 << ADTS1) | (0 << ADTS0); // ADTS=110: Timer1 Overflow (ok p/ Normal)
  // Alternativo p/ CTC: (1<<ADTS2)|(0<<ADTS1)|(1<<ADTS0) = Compare Match B
  DIDR0 = (1<<ADC5D); // desabilita buffer digital do ADC5
}

void GPIO_config() { DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2); }

/*
 * Objetivo: Realizar leituras do LM35 com ADC, com taxa de amostragem de 4 Hz,
 * utilizando TIMER1 como fonte de disparo do ADC (modo auto-trigger).
 * vref interno (1.1v)
 */
uint16_t ADC_Result;
ISR(ADC_vect) {
    ADC_Result = ADC; // armazena conversão
}

ISR(TIMER1_OVF_vect) { PORTB ^= (1 << PORTB0); }

int main(void) {
  // timer com prescaler (SIMULADOR ACIONA O OVF COM CTC, MAS NO ARDUINO FISICO NAO)
  TCCR1A = (0 << WGM11) | (0 << WGM10); // WGM00 WGM01 WGM02 = modo CTC conta até OCR0A
  TCCR1B =
      (0 << WGM12) | (0 << CS12) | (1 << CS11) | (0 << CS10); // prescaler de /64
  // Modo Normal (WGM12=0): conta até 65535, overflow a ~1.9 Hz c/ 8MHz+64
  // Alternativo CTC: WGM12=1, ADTS=101 (Compare Match B), OCR1A=31249 → 4 Hz
  
  OCR1A = 62500; // ((1/4hz) * F_CPU)/PRE_SCALER
  //  ^-- 8M/64=125k ticks/s; 125k/2=62.5k → overflow a ~2 Hz (não 4)
  //  Alternativo 4 Hz: OCR1A = 8M/64/4 - 1 = 31249 (modo CTC)
  OCR1B = 62500; // ((1/4hz) * F_CPU)/PRE_SCALER (não usado c/ ADTS=Overflow)
  TIMSK1 = (1<<TOIE1);
  sei();
  GPIO_config();
  ADC_config();
  while (1) {
  }
}
