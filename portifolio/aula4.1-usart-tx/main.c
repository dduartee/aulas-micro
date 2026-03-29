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

/**
 * transmite a mensagem {0x20, 0x0n, 0xCS} dados com checksum
 */
void UART_sendMessage(uint8_t* pData, int pSize) {
  uint8_t* tMsgPtr = pData;  // aponta para o endereço da mensagem
  uint8_t tChecksum = 0;
  for (int i = 0; i < pSize; i++) {
    while ((UCSR0A & (1 << UDRE0)) == 0);  // espera a liberação
    uint8_t tMessageByte = *tMsgPtr;
    tChecksum +=
        tMessageByte;     // soma os bytes (quando estoura o tamanho, reinicia a
                          // contagem, por isso calcula manualmente o "mod")
    UDR0 = tMessageByte;  // transmite a mensagem
    tMsgPtr++;            // move o ponteiro
  }
  while ((UCSR0A & (1 << UDRE0)) == 0);  // espera a liberação
  // UDR0 = tChecksum++; // para falhar o checksum
  UDR0 = tChecksum;
}

// ultimo estado dos botões b0 e b1
uint8_t gStateB0 = 0x00;
uint8_t gStateB1 = 0x00;
/**
 * objetivo: enviar o estado atual dos botões a cada mudança
 */
int main(void) {
  USART_initialize();
  while (1) {
    uint8_t tStateB0 = (PINB & (1 << PINB0)) == 0 ? 0x01 : 0x00;
    if (tStateB0 != gStateB0) { // verifica estado atual x anterior
      uint8_t tMessageB0[2] = {0x20, tStateB0};
      UART_sendMessage(tMessageB0, 2);
      _delay_ms(10);
      gStateB0 = tStateB0; // substitui
    }

    uint8_t tStateB1 = (PINB & (1 << PINB1)) == 0 ? 0x01 : 0x00;
    if (tStateB1 != gStateB1) {
      uint8_t tMessageB1[2] = {0x21, tStateB1};
      UART_sendMessage(tMessageB1, 2);
      _delay_ms(10);
      gStateB1 = tStateB1;
    }
  }
}