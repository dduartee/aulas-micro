/*
 * main.c
 *
 * Created: 3/6/2026 2:36:31 PM
 *  Author: Aluno
 */

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <xc.h>

#include "util/delay.h"

/**
 * @brief Piscar um led no pino PC2 enquanto a chave ligada ao pino PD3 estiver
 * pressionada
 */

void atividade1() {
  DDRC |= (1 << DDC2);   // define o Data Direction do PC2 como saida
  DDRD &= ~(1 << DDD3);  // define o Data Direction do PD3 como entrada

  while (1) {
    // ler valor da chave
    if (PIND & (1 << PIND3)) {  // filtra o PIND para comparar com PIND3, e
                                // retorna o valor do D3
      PORTC |= (1 << PORTC2);
      _delay_ms(300);
      PORTC &= ~(1 << PORTC2);
      _delay_ms(700);
    } else {
      PORTC &= ~(1 << PORTC2);
    }
  }
}

/**
 * @brief controla 6 leds em uma lógica de pinheirinho de natal (PC0 a PC5)
 */

void atividade2() {
  DDRC |= (1 << DDC5) | (1 << DDC4) | (1 << DDC3) | (1 << DDC2) | (1 << DDC1) |
          (1 << DDC0);
  DDRD &= ~(1 << DDD3);  // define o Data Direction do PD3 como entrada

  uint8_t tState = 1;

  while (1) {
    // se o tState estiver para o C6 reinicia a contagem
    if (tState & (1 << PORTC6)) {
      tState = 1;
    }
    // ler valor da chave
    if (PIND & (1 << PIND3)) {  // filtra o PIND para comparar com PIND3, e
                                // retorna o valor do D3
      PORTC = tState;
      tState = tState << 1;  // shift do 1 para a esquerda
    } else {
      PORTC = 0;
    }

    _delay_ms(500);
  }
}

int main(void) { atividade2(); }