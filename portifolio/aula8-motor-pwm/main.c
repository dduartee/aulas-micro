#define F_CPU 8000000
#include "avr/io.h"
#include "util/delay.h"
#include <xc.h>
#include "avr/interrupt.h"

#define PWM_INICIAL 200
#define PWM_PERIODO 255

uint8_t gPWM = PWM_INICIAL;
uint8_t gBuzzer = 0;

ISR(INT1_vect) { // interrupção externa acionada pelo encoder a cada rotação do motor.
    _delay_ms(70); // gambiarra pois o encoder contava repetidas vezes
    uint16_t contagem = TCNT1; // contagem de tempo entre cada acionamento do encoder
    TCNT1 = 0;

    gBuzzer = 1;

    uint8_t rotacoes_segundo = 3;
    if (contagem < (F_CPU/256)/rotacoes_segundo) { // prescaler 256
        // chegou mais rápido → reduz PWM
        if (gPWM > 0) gPWM--;
    } else {
        // chegou mais devagar → aumenta PWM
        if (gPWM < 254) gPWM++;
    }
}

void EXTINT_config() {
    EICRA = (1 << ISC11) | (1 << ISC10); // apenas borda de SUBIDA
    EIMSK = (1 << INT1);
}
void GPIO_config() {
    DDRD = (1 << DDD6) | (1 << DDD5) | (0 << DDD1) | (0 << DDD2);
}
int main(void) {
  GPIO_config();

  TCCR0A = (1 << WGM01) |
           (1 << WGM00) // modo FAST PWM com TOP=0xFF, OC0A PWM não-inversor
           | (0 << COM0B0) | (1 << COM0B1) | (0 << COM0A0) | (1 << COM0A1);

  TCCR0B =
      (1 << WGM02) | (0 << CS02) | (1 << CS01) | (0 << CS00); // prescaler de /8
  
  OCR0A = PWM_PERIODO; // periodo do ciclo

  TCCR1A = (0 << WGM11) |
           (0 << WGM10); // modo FAST PWM com TOP=0xFF, OC0A PWM não-inversor
           TCCR1B = (0 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10); // /256
           
  OCR1A = 249; // contagem até 250 us (para F_clk @ 1MHz)
  OCR1B = 99; // 100us transição da onda com duty cycle 40%
  
  EXTINT_config();
  
  sei();
  while (1) {
    if (!(PIND & (1 << PIND2))) {
      gPWM += 2;
      while (!(PIND & (1 << PIND2))) {}
    } else if(!(PIND & (1 << PIND1))) {
     gPWM -= 2;
     while(!(PIND & (1 << PIND1))) {}
    }
    _delay_ms(50);
    OCR0B = gPWM; // largura do pulso

    if (gBuzzer) {
        gBuzzer = 0;
        PORTD |= (1 << PORTD7);
        _delay_ms(50);
        PORTD &= ~(1 << PORTD7);
    }
  }
}
