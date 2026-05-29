#include "avr/io.h"
#include <xc.h>

#define F_CPU 16000000

#define VREF 5
// objetivo:    medir a tensão de uma bateria, e acender um LED amarelo
//              se ela estiver abaixo de 3.0v ou um LED vermelho se estiver
//              acima de 3.8v
//
// OBS: bateria no pino ADC7, utilizar vref=avcc 5v

void ADC_config() {
  ADMUX = (0 << REFS1) | (1 << REFS0) | // vref=avcc (5v)
          (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0); // pino adc7

  ADCSRA = (1 << ADEN) | (0 << ADATE) |
           (0 << ADIE) | // liga adc, modo single conversion, sem interrupção
           (1 << ADPS2) | (1 << ADPS1) |
           (1 << ADPS0); // prescaler 128 @ 16MHz, f_adc=125kHz, sampling rate

  // (125/13) = 9615 SPS
  ADCSRB = 0; // não será usado o auto-trigger
  DIDR0 = 0;  // nao está usando adc0-adc5;
}

void GPIO_config() {
    DDRB = (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
}

int main(void) {
    
  ADC_config();
  GPIO_config();
  
  while (1) {
      
    ADCSRA |= (1 << ADSC); // dispara conversão
    while ((ADCSRA & (1 << ADSC))); // espera conclusão, ADSC retorna para 0

    uint16_t tResult = ADC; // armazena conversão
    PORTB = 0;
    
    if(tResult < 614) {
        PORTB |= (1<<PORTB2); // amarelo
    } else if(tResult > 778) { // 0-1023
        PORTB |= (1<<PORTB0); // vermelho
    } else {
        PORTB |= (1<<PORTB1); // verde
    }
    
  }
}
