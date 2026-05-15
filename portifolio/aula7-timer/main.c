#define F_CPU 8000000
#include "avr/io.h"
#include <xc.h>
#include "avr/interrupt.h"

ISR(TIMER0_COMPA_vect) {
    PORTB |= (1<<PORTB0); // eleva PB0
}

ISR(TIMER0_COMPB_vect) {
    PORTB &= ~(1<<PORTB0); // baixa PB0
}

int main(void) {
    DDRB = (1<<DDB0);
    TCCR0A = (1<<WGM01) | (0<<WGM00); // WGM00 WGM01 WGM02 = modo CTC conta até OCR0A
    TCCR0B = (0<<WGM02) | (0<<CS02) | (1<<CS01) | (0<<CS00); // prescaler de /8
    OCR0A = 249; // contagem até 250 us (para F_clk @ 1MHz)
    OCR0B = 99; // 100us transição da onda com duty cycle 40%
    TIMSK0 = (1<<OCIE0A) | (1<<OCIE0B); // interrupções A e B de comparação de saída
    sei();
    
    while(1) {}
}