#define F_CPU 16000000
#include <xc.h>

#include "util/delay.h"

#define BUFFER_SIZE 3
// uint8_t gMessage[BUFFER_SIZE] = {200, 100, 50, 94};  // ultimo byte eh
// checksum (soma todos
//  e modulo (resto) por 256) 350mod256
uint8_t gMessage[BUFFER_SIZE] = {200, 100, 50};

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

void UART_sendMessage(uint8_t* pData, int pSize) {
  uint8_t* tMsgPtr = pData;  // aponta para o endereço da mensagem
  uint8_t tChecksum = 0;
  for (int i = 0; i < pSize; i++) {
    while ((UCSR0A & (1 << UDRE0)) == 0);  // espera a liberação
    uint8_t tMessageByte = *tMsgPtr;
    tChecksum += tMessageByte;  // soma os bytes (quando estoura o tamanho, reinicia a contagem, por isso calcula manualmente o "mod")
    UDR0 = tMessageByte;        // transmite a mensagem
    tMessageByte++;             // move o ponteiro
  }
  while ((UCSR0A & (1 << UDRE0)) == 0);  // espera a liberação
  UDR0 = tChecksum;
}

int main(void) {
  USART_initialize();
  while (1) {
    UART_sendMessage(gMessage, BUFFER_SIZE);
    _delay_ms(10);
  }
}