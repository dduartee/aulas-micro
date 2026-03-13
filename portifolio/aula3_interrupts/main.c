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

int gCount = 0;

ISR(INT0_vect) {
	/*
	PORTC = (1<<PORTC0); // alterna LED
	_delay_ms(100);
	PORTC = 0;
	_delay_ms(10);
	*/
	gCount = 3; // acionamento manual do LED, faz com que reinicie a contagem do clock após acionar o LED
}

ISR(INT1_vect) {
	gCount++; // incrementa a contagem de clock para acionar o LED
}

int main(void)
{
	DDRC = (1<<DDC0); // configura C0 como saida
	EICRA = 
		(0<<ISC01) | (1<<ISC00) | // ambas as bordas
		(1<<ISC11) | (1<<ISC10); // rising edge
		
	EIMSK = (1<<INT1) | (1<<INT0); // habilita INT0 e INT1
	
	sei();
    while(1)
    {
        if(gCount >= 3) { // centraliza o acionamento do LED
	        PORTC = (1<<PORTC0); // alterna LED
	        _delay_ms(100);
	        PORTC = 0;
	        gCount = 0;
        }
    }
}