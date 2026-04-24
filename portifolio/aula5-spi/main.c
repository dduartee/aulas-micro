
#define F_CPU 16000000
#include "spi.h"
#include "util/delay.h"
#include <xc.h>

#define SPI_BUFFER_SIZE 4

uint8_t gTransmitBuffer[SPI_BUFFER_SIZE] = {0x0A,0x3B,0x33,0x24};
uint8_t gReceiveBuffer[SPI_BUFFER_SIZE];

int main(void) {
  SPI_config();

  while (1) {
    SPI_transceiveBuffer(gTransmitBuffer, gReceiveBuffer, SPI_BUFFER_SIZE);
    _delay_ms(100);
  }
}
