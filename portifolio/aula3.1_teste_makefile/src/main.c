
#include <xc.h>
#include "gpio.h"

int main(void) {
    GPIO_initialize();
    GPIO_blinkLED();
    while(1) {
        //
    }
}