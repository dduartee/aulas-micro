#include <xc.h>
#include "gpio.h"

void GPIO_initialize() {
    DDRB = 1<<DDB0;
}
void GPIO_blinkLED() {
    PORTB |= 1<<PORTB0;
}