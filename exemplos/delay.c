#ifndef F_CPU
#define F_CPU 16000000UL // 16MHz - UL = unsigned long 
#endif

#include <util/delay.h>

void GPIO_blinkLED() {
	PORTB |= (1<<PORTB0); // ATIVA B7
	_delay_ms(300); // delay de 300ms em ALTO
	PORTB &= ~(1<<PORTB0); // DESATIVA B7
	_delay_ms(700); // delay de 300ms em ALTO
}