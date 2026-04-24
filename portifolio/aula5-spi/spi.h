#ifndef SPI_H
#define SPI_H

#include <xc.h>

void SPI_config();
uint8_t SPI_transceiveByte(uint8_t pTransmittedByte);
void SPI_transceiveBuffer(uint8_t *pTransmitBuffer, uint8_t *pReceiveBuffer,
                          uint16_t pSize);

#endif
