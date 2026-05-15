#define F_CPU 8000000
#include "avr/io.h"
#include <xc.h>

int main(void) {
    DDRB = (1<<DDB6);
    DDRD = (1<<DDD6);
    
    TCCR0A = (1<<WGM01) | (0<<WGM00) | (1<<COM0A0) | (0<<COM0A1); // modo ctc, toggle do OC0A
    TCCR0B = (0<<WGM02) | (0<<CS02) | (1<<CS01) | (0<<CS00); // prescaler de /8
    OCR0A = 249; // contagem até 250 us (para F_clk @ 1MHz)
    //OCR0B = 99; // 100us transição da onda com duty cycle 40%
    
    while(1) {}
}