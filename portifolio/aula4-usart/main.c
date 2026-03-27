#define F_CPU 16000000
#include <xc.h>

#include "util/delay.h"

// Table 19-12. Examples of UBRRn Settings for Commonly Used Oscillator
// Frequencies Asynchronous normal mode (U2Xn = 0) -> [f_osc / (16BAUD)]-1
#define BAUDRATE_9600 103  // (16*10^6) / (16*9600) -1
#define BAUDRATE_115200 8  // (16*10^6) / (16*115200) -1

void baud9600_1bitstop() {
  UBRR0 = BAUDRATE_9600;  // BAUDRATE de 9600 (U2X0 = 0)

  UCSR0A = (0 << U2X0);  // U2Xn: Double the USART Transmission Speed

  UCSR0B = (0 << UCSZ02) |  // UCSZn2: Character Size 8bits;
           (1 << TXEN0);    // TXENn: Transmitter Enable 0

  UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) |  // Bits 7:6 – UMSELn1:0 USART Mode
                                              // Select Asynchronous USART
           (1 << UPM01) | (0 << UPM00) |   // UPMn1:0: Parity Mode even parity
           (0 << USBS0) |                  // USBSn: Stop Bit Select 1-bit
           (1 << UCSZ01) | (1 << UCSZ00);  // UCSZn1:0: Character Size 8bits
}

void baud115200_2bitstop() {
  UBRR0 = BAUDRATE_115200;
  UCSR0A = (0 << U2X0);     // U2Xn: Double the USART Transmission Speed
  UCSR0B = (0 << UCSZ02) |  // UCSZn2: Character Size 8bits;
           (1 << TXEN0);    // TXENn: Transmitter Enable 0
  UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) |  // Bits 7:6 – UMSELn1:0 USART Mode
                                              // Select Asynchronous USART
           (0 << UPM01) | (0 << UPM00) |   // UPMn1:0: Parity Mode even parity
           (1 << USBS0) |                  // USBSn: Stop Bit Select 2-bit
           (1 << UCSZ01) | (1 << UCSZ00);  // UCSZn1:0: Character Size 8bits
}

int main() {
  baud115200_2bitstop();
  while (1) {
    UDR0 = 0x5B;
    _delay_ms(10);
  }
}