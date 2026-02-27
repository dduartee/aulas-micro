/*
 * main.c
 *
 * Created: 2/27/2026 1:45:55 PM
 *  Author: Aluno
 */ 

#include <xc.h>
#include "gpio.h"
#include "usart.h"


int main(void) {
	GPIO_initialize();
	USART_initialize();
	
    while(1) {
        GPIO_blinkLED();
		USART_sendMessage();
    }
}