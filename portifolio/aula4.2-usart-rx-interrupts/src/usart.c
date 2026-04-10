#include "usart.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include <stdint.h>
#include <xc.h>

volatile uint8_t gReceivedBytes[3]; // 2 dados + 1 checksum
volatile uint8_t gReadyToRead = 0;
volatile uint8_t gByteCounter = 0;

ISR(USART_RX_vect) { // interrupção dispara uma vez por byte
  gReceivedBytes[gByteCounter] = UDR0;
  gByteCounter++;
  if (gByteCounter >= 3) { // recebido 3 bytes.
    gReadyToRead = 1; // pronto para leitura
    gByteCounter = 0; // reinicia a contagem.
  } else {
    gReadyToRead = 0; // caso ainda não tenha recebido os 3 bytes, ou receba mais, reinicia a flag de leitura.
  }
}

void USART_initialize() {
  UBRR0 = 103;
  UCSR0A = (0 << U2X0);                   // velocidade normal (nao double)
  UCSR0B = (1 << RXEN0) |                 // habilita rx
           (0 << UCSZ02) | (1 << RXCIE0); //
  UCSR0C = (0 << UCSZ00) | (0 << UCSZ01) | (0 << USBS0) | (1 << UPM00) |
           (1 << UPM01) | (0 << UMSEL00) | (0 << UMSEL01);
}

// retorna a flag para leitura
uint8_t USART_hasBytes() { return gReadyToRead; }

// remove a flag para leitura
void USART_flush() { gReadyToRead = 0; }

// se estiver pronto para ler, copia os bytes
void USART_readBytes(uint8_t* pBytes) {
  if (gReadyToRead) {
      for (int i = 0; i < 3; i++) {
          pBytes[i] = gReceivedBytes[i];
      }
  }
  USART_flush();
}

// calcula o checksum
uint8_t USART_integrityCheck() {
  uint8_t tChecksum = 0;
  for (int i = 0; i < 2; i++) {
    tChecksum += gReceivedBytes[i]; // calcula o checksum dos dados
  }
  return gReceivedBytes[2] == tChecksum;
}
