/*
 * gpio.c
 *
 * Created: 27/02/2026 14:02:23
 *  Author: Aluno
 */ 


#include <xc.h>
#include "gpio.h"

// inicializa gpio
void GPIO_initialize() {
	DDRB = 1<<DDB7;
}

// pisca o led
void GPIO_blinkLED() {
	PORTB ^= 1<<PORTB7;
}