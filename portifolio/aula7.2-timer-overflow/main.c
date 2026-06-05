#define F_CPU 8000000
#include "avr/io.h"
#include <xc.h>
#include "avr/interrupt.h"

ISR(TIMER1_OVF_vect) {
    PORTB ^= (1<<PORTB0); // alterna porta, duas interrupções para gerar a onda
}

int main(void) {
    DDRB = (1<<DDB0);
    TCCR1A = (0<<WGM11) | (0<<WGM10); // WGM00 WGM01 WGM02 = modo CTC conta até OCR0A
    TCCR1B = (1<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10); // prescaler de /8
    OCR1A = 65535;

    TIMSK1 = (1<<TOIE1); // interrupção de overflow
    sei();
    
    while(1) {}
}