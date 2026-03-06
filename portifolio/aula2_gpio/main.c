/*
 * main.c
 *
 * Created: 3/6/2026 2:36:31 PM
 *  Author: Aluno
 */ 

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <xc.h>
#include "util/delay.h"


/**
 * @brief Piscar um led no pino PC2 enquanto a chave ligada ao pino PD3 estiver pressionada
 */

void atividade1() {
	DDRC |= (1<<DDC2); // define o Data Direction do PC2 como saida
	DDRD &= ~(1<<DDD3); // define o Data Direction do PD3 como saida
	
	while(1) {
		// ler valor da chave
		if(PIND & (1<<PIND3)) { // filtra o PIND para comparar com PIND3, e retorna o valor do D3
			PORTC |= (1<<PORTC2);
			_delay_ms(300);
			PORTC &= ~(1<<PORTC2);
			_delay_ms(700);
			} else {
			PORTC &= ~(1<<PORTC2);
		}
	}
}

int main(void) {
	
	
}