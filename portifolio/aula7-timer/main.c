#define F_CPU 8000000
#include "avr/io.h"
#include <xc.h>
#include "avr/interrupt.h"

ISR(TIMER0_OVF_vect) {
    PORTB ^= (1<<PORTB0); // alterna porta, duas interrupções para gerar a onda
}

int main(void) {
    DDRB = (1<<DDB0);
    TCCR0A = (1<<WGM01) | (0<<WGM00); // WGM00 WGM01 WGM02 = modo CTC conta até OCR0A
    TCCR0B = (0<<WGM02) | (0<<CS02) | (1<<CS01) | (0<<CS00); // prescaler de /8
    OCR0A = 249; // contagem até 250 uS (para F_clk @ 1MHz)

    TIMSK0 = (1<<TOIE0); // interrupção de overflow
    sei();
    
    while(1) {}
}