

#include "avr/io.h"
#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"


void USART_initialize() {
  UBRR0 = 103;              // 9600bps U2Xn = 0
  UCSR0A = (0 << U2X0);     // mantem velocidade normal
  UCSR0B = (0 << UCSZ02) |  // COMBINAÇÃO UCSZ para character size 8bits frames
                            // de 8bits
           (1 << TXEN0);    // habilita o TX0

  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) |  // combinação UCSZ para character
                                            // size 8bits frames de 8bits
           (0 << UMSEL01) |
           (0 << UMSEL00) |               // combinação UMSEL para USART async
           (1 << UPM01) | (1 << UPM00) |  // habilita paridade par
           (0 << USBS0);                  // 1 stop bit
}

int main(void) {
    USART_initialize();
    DDRB = (1<<DDB5);

    while(1) {
        UDR0 = 't';
        _delay_ms(10);
        UDR0 = 'e';
        _delay_ms(10);
        UDR0 = 's';
        _delay_ms(10);
        UDR0 = 't';
        _delay_ms(10);
        UDR0 = 'e';
        _delay_ms(10);
        UDR0 = '\n';
        PORTB |= (1<<PORTB5);
        _delay_ms(200);
        PORTB &= ~(1<<PORTB5);
        _delay_ms(300);
    }
}
