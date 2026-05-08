

#include "sm28vlt32.h"

void SM28VLT32_config() {
  DDRB |= (1 << PB0); // configura PB0 como saida (chip select)
}

uint8_t SM28VLT32_writeWord(uint32_t pAddress, uint16_t pData) {
  uint8_t tTransmitBuffer[7];
  uint8_t tReceiveBuffer[7];

  PORTB &= ~(1 << PORTB0); // baixa o chip select

  // command byte
  tTransmitBuffer[0] = 0x17; // write word command

  // address bytes
  tTransmitBuffer[1] = (pAddress & 0x00FF0000) >> 16; // seleciona os bits e desliza para primeiro byte
  tTransmitBuffer[2] = (pAddress & 0x0000FF00) >> 8; // >> 8, desliza para o primeiro byte
  tTransmitBuffer[3] = (pAddress & 0x000000FF) >> 0; // seleciona os ultimos 8 bits

  // data bytes
  tTransmitBuffer[4] = (pData & 0xFF00) >> 8;
  tTransmitBuffer[5] = (pData & 0x00FF) >> 0;

  // dummy byte
  tTransmitBuffer[6] = 0x00;

  SPI_transceiveBuffer(tTransmitBuffer, tReceiveBuffer, 7);

  PORTB |= (1 << PORTB0); // chip select alto

  return tReceiveBuffer[0]; // quick status byte
}
