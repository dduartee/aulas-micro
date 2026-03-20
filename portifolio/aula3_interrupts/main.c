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

int flag_set_led = 0;
int gPD2_prev_state = 0;
int gPD3_prev_state = 0;
ISR(INT0_vect) {
	flag_set_led = 1;
}

ISR(INT1_vect) {
	flag_set_led = 1; // incrementa a contagem de clock para acionar o LED
}

ISR(PCINT2_vect) {
	// rising edge
	int PD2_state = PIND & (1<<PIND2);
	if(PD2_state) {
		if(gPD2_prev_state == 0) {
			// houve mudan�a de estado	
			flag_set_led = 1;
		}
		gPD2_prev_state = 1;
	} else {
		gPD2_prev_state = 0;
	}
	
	int PD3_state = PIND & (1<<PIND3);
	if(PD3_state) {
		if(gPD3_prev_state == 0) {
			// houve mudan�a de estado
			flag_set_led = 1;
		}
			gPD3_prev_state = 1;
		} else {
			gPD3_prev_state = 0;
		}
}

void EXTINT_config() {
		EICRA = // configura interrup��es
		(0<<ISC01) | (1<<ISC00) | // ambas as bordas
		(1<<ISC11) | (1<<ISC10); // rising edge
		
		EIMSK = (1<<INT1) | (1<<INT0); // habilita INT0 e INT1
		
}


void PCINT_config() {
	PCMSK2 |= (1<<PCINT18) | (1<<PCINT19); // habilita o 18 e 19 do PCIE2 (D2, D3)
	PCICR |= (1<<PCIE2); // habilita grupo E2
}

int main(void)
{
	DDRC = (1<<DDC0); // configura C0 como saida
	PCINT_config();
	sei();

    while(1)
    {
        if(flag_set_led) { // centraliza o acionamento do LED
	        PORTC = (1<<PORTC0); // alterna LED
	        _delay_ms(100);
	        PORTC = 0;
	        flag_set_led = 0;
        }
    }
}