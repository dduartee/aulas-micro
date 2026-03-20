#define F_CPU 16000000
#include <xc.h>

#include "util/delay.h"

int main() {
  UBRR0 = 103;  // BAUDRATE de 9600 (U2X0 = 0)

  UCSR0A = (0 << U2X0);  // U2Xn: Double the USART Transmission Speed

  UCSR0B = (0 << UCSZ02) |  // UCSZn2: Character Size 8bits;
           (1 << TXEN0);    // TXENn: Transmitter Enable 0

  UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) |  // Bits 7:6 – UMSELn1:0 USART Mode
                                              // Select Asynchronous USART
           (1 << UPM01) | (0 << UPM00) |   // UPMn1:0: Parity Mode even parity
           (0 << USBS0) |                  // USBSn: Stop Bit Select 1-bit
           (1 << UCSZ01) | (1 << UCSZ00);  // UCSZn1:0: Character Size 8bits

  while (1) {
    UDR0 = 0x5B;
    _delay_ms(10);
  }
}