
#include "avr/interrupt.h"
#include <xc.h>

const float VREF = 1.1f;

// parametros do filtro notch com rejeição em w = 0.12pi
const float coeff_a[3] = {1.000, -1.414, 1.000};
const float coeff_b[3] = {1.000, -1.273, 0.810};

float x[3]; // x[0] = x(n) , x[1] = x(n-1), x[2] = x(n-2)
float y[3];

ISR(ADC_vect) {
  uint16_t tADCValue = ADC;
  x[2] = x[1];
  x[1] = x[0];
  x[0] = VREF * ((float)tADCValue / 1.024); // saida em milivolts
  
  y[2] = y[1];
  y[1] = y[0];
  y[0] = coeff_a[0] * x[0] + coeff_a[1] * x[1] + coeff_a[2] * x[2] +
         coeff_b[1] * y[1] + coeff_b[2] * y[2];

  // joga o resultado no pwm como saida processada
  OCR1A = (uint16_t)(y[0] * 65355);
}

int main(void) {
    //configurar adc com interrupção
    // configurar pwm
}
