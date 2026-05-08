#include "avr/io.h"
#define F_CPU 16000000
#include "avr/interrupt.h"
#include "util/delay.h"
#include <xc.h>

uint8_t gTWIData = 5;

ISR(TWI_vect) {
  uint8_t tState = (TWSR & 0b11111000);
  switch (tState) {
  case 0x60: { // slave recever
    gTWIData = TWDR;
    TWCR = (1 << TWINT) | (1 << TWEN) | (1<< TWEA);
  } break;
  case 0xA8: { // slave transmitter
    TWDR = gTWIData;
    TWCR = (1 << TWINT) | (1 << TWEN);
  } break;
  default:
    TWCR = (1 << TWINT) | (1 << TWEN);
    break;
  }
}

void TWI_config() {
  TWBR = 12; // twbr*PR = (f_cpu/2scl)-8 | scl = 400khz
  TWSR = ((0 << TWPS1) | (0 << TWPS0)); // pr = 1
  TWCR = (1 << TWEN) | (1 << TWIE) ;
  TWAR = (0x55 << 1); // shift para o offset
  sei();
}

int main(void) {
  TWI_config();
  while (1) {
    _delay_ms(1000);
  }
}
