#define F_CPU 16000000
#include "avr/interrupt.h"
#include "usart.h"
#include "util/delay.h"
#include <xc.h>

// le os comandos e aciona os leds
void parseMessage(uint8_t *pMessage) {
  if (USART_integrityCheck()) { // valida o checksum
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
  DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
  USART_initialize();
  sei(); // habilita as interrupções para o rx
  while (1) {
    if (USART_hasBytes()) { // verifica se recebeu os 3 bytes
      PORTB &= ~(1 << PORTB3);
      
      uint8_t tBytes[3];
      USART_readBytes(tBytes);
      
      parseMessage(tBytes); // lê os bytes
      
    } else {
      _delay_ms(100);
      PORTB |= (1 << PORTB3);
    }
  }
}
