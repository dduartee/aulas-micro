#define F_CPU 8000000
#include "avr/io.h"
#include <xc.h>
#include "util/delay.h"

uint8_t gPWM = 0;

int main(void) {
  DDRD = (1 << DDD6) | (1<<DDD5);

  TCCR0A = (1 << WGM01) | (1 << WGM00) // modo FAST PWM com TOP=0xFF, OC0A PWM não-inversor
         | (0 << COM0B0) | (1 << COM0B1)
         | (0 << COM0A0) | (1 << COM0A1); 
  
  TCCR0B = (1 << WGM02) | (0 << CS02) | (1 << CS01) | (0 << CS00); // prescaler de /8
  OCR0A = 99;
  while (1) {
      gPWM++;
      if(gPWM>99) gPWM = 0;
      OCR0B = gPWM;
      _delay_ms(100);
  }
}
