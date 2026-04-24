
#include "spi.h"
#include "avr/io.h"

void SPI_config() {
  DDRB |= (1 << PB3) | (1 << PB5); // define o SCK e MISO para saida

  SPCR = (0 << SPIE) |               // nao habilita interrupt
         (1 << SPE) |                // habilita o spi
         (0 << DORD) |               // ordem msb
         (1 << MSTR) |               // modo mestre
         (0 << CPOL) | (0 << CPHA) | // SPI no modo 0
         (0 << SPR1) | (1 << SPR0);  // 1 MHz

  SPSR = (0 << SPI2X);
}

uint8_t SPI_transceiveByte(uint8_t pTransmittedByte) {
  uint8_t rReceivedByte;
  SPDR = pTransmittedByte; // transmite
  
  // pool do SPIF, aguarda a flag para leitura
  while ((SPSR & (1 << SPIF)) == 0); 

  rReceivedByte = SPDR;
  return rReceivedByte;
}

void SPI_transceiveBuffer(uint8_t *pTransmitBuffer, uint8_t *pReceiveBuffer,
                          uint16_t pSize) {

  uint8_t *tTransmitPtr = pTransmitBuffer;
  uint8_t *tReceivePtr = pReceiveBuffer;
  uint16_t tCounter;

  for (tCounter = 0; tCounter < pSize; tCounter++) {
    *tReceivePtr = SPI_transceiveByte(*tTransmitPtr);
    tReceivePtr++;
    tTransmitPtr++;
  }
}
