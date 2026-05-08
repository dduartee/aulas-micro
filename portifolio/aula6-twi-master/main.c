#include "avr/io.h"
#define F_CPU 16000000
#include "util/delay.h"
#include <xc.h>

void TWI_master_config() {
    // DDRC = (1<<DDC4) | (1<<DDC5);
  TWBR = 12; // twbr*PR = (f_cpu/2scl)-8 | scl = 400khz
  TWSR = ((0 << TWPS1) | (0 << TWPS0)); // pr = 1
  TWCR = (1 << TWEN);
}

void TWI_master_write_byte(uint8_t pAddress, uint8_t pData) {
  TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // become a master

  while ((TWCR & (1 << TWINT)) == 0); // espera conclusão
  
  TWDR = (pAddress<<1) | 0; // coloca 0 para WRITE e envia address
  TWCR = (1 << TWINT) | (1 << TWEN); // limpa o twint cada vez que se transmite
  
  while ((TWCR & (1 << TWINT)) == 0); // espera conclusão
  
  uint8_t tState = TWSR & 0b11111000; // Bits 7..3 – TWS: TWI Status

  switch (tState) {
  case 0x18: // ack recebido
    break;
  case 0x20:
    break;
  default:
    break;
  }
  TWCR |= (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

int main(void) {
  TWI_master_config();
  while (1) {
    TWI_master_write_byte(55, 'a');
    _delay_ms(1000);
  }
}
