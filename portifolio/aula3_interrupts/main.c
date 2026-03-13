/*
 * main.c
 *
 * Created: 3/13/2026 2:22:21 PM
 *  Author: Aluno
 */ 

#define F_CPU 16000000

#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

ISR(INT0_vect) {
	PORTC = (1<<PORTC0); // alterna LED
	_delay_ms(100);
	PORTC = 0;
	_delay_ms(10);
}

// rising edge no INT0


int main(void)
{
	DDRC = (1<<DDC0); // configura C0 como saida
	// EICRA = (1<<ISC01) | (1<<ISC00); // configura ISC01 ISC00 para combinação de rising edge (pressionando botao)
	EICRA = (1<<ISC01) | (0<<ISC00); // configura ISC01 ISC00 para combinação de falling edge (soltando botao)
	EIMSK = (0<<INT1) | (1<<INT0); // habilita INT0
	
	sei();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}