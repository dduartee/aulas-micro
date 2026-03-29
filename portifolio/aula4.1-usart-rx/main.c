#define F_CPU 16000000
#include <xc.h>

#include "util/delay.h"

uint8_t gReceivedByte[3];  // 2 dados + 1 checksum

void USART_initialize() {
  UBRR0 = 103;              // 9600bps U2Xn = 0
  UCSR0A = (0 << U2X0);     // mantem velocidade normal
  UCSR0B = (0 << UCSZ02) |  // COMBINAÇÃO UCSZ para character size 8bits frames
                            // de 8bits
           (1 << RXEN0);    // habilita RX0

  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) |  // combinação UCSZ para character
                                            // size 8bits frames de 8bits
           (0 << UMSEL01) |
           (0 << UMSEL00) |               // combinação UMSEL para USART async
           (1 << UPM01) | (1 << UPM00) |  // habilita paridade par
           (0 << USBS0);                  // 1 stop bit
}
void USART_receiveMessage(uint8_t* pBuffer, int pSize) {
  uint8_t* tBufferPtr = pBuffer;
  for (int i = 0; i < pSize; i++) {
    while ((UCSR0A & (1 << RXC0)) == 0);  // espera receber alguma coisa
    uint8_t tReceivedByte = UDR0;
    *tBufferPtr = tReceivedByte;
    tBufferPtr++;
  }
}

void USART_parseMessage(uint8_t* pMessage) {
  uint8_t tChecksum = 0;
  for (int i = 0; i < 2; i++) {
    tChecksum += pMessage[i]; // calcula o checksum dos dados
  }
  if (pMessage[2] == tChecksum) { // valida
    PORTB &= ~(1 << PORTB2);
    switch (pMessage[0]) {
      case 0x20: // comando para o led B0
        if (pMessage[1] == 0x01) {  
          PORTB |= (1 << PORTB0);
        } else {
          PORTB &= ~(1 << PORTB0);
        }
        _delay_ms(10);

        break;
      case 0x21: // comando para o led B1
        if (pMessage[1] == 0x01) {  
          PORTB |= (1 << PORTB1);
        } else {
          PORTB &= ~(1 << PORTB1);
        }
        _delay_ms(10);
        break;
      default:
        break;
    }
  } else {
    PORTB |= (1 << PORTB2); // acusa erro de checksum
  }
}

int main(void) {
  DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2);
  USART_initialize();
  while (1) {
    USART_receiveMessage(gReceivedByte, 3);
    USART_parseMessage(gReceivedByte);
    _delay_ms(1);
  }
}