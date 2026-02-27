/*
 * main.c
 *
 * Created: 2/20/2026 2:24:44 PM
 *  Author: Aluno
 */ 

#include <xc.h>

// const uint8_t *PORTB_ptr = 0x25; // ponteiro constante para escrever no PORTB

/*
~ - not
& - and
| - or
^ - xor

usando and

01011100
11001100
=========
01001100 

usando or
01011100
11001100
=========
11011100

usando or
00010110
01000000 // liga um bit
=========
01010110

operação shift

>> -> rotacao a direita
<< -> rotacao a esquerda


>> 0 01011100
>> 1 00101110
>> 2 00010111 


PORTB [b7][b6][b5][b4][b3][b2][b1][b0]
  OR  [0 ][0 ][0 ][0 ][1 ][0 ][0 ][0 ]
	  [b7][b6][b5][b4][1 ][b2][b1][b0]
	  
PORTB [b7][b6][b5][b4][b3][b2][b1][b0]
  XOR [0 ][0 ][0 ][0 ][1 ][0 ][0 ][0 ]
	  [b7][b6][b5][b4][~b3][b2][b1][b0]

PORTB [b7][b6][b5][b4][b3][b2][b1][b0]
 AND  [0 ][0 ][0 ][0 ][1 ][0 ][0 ][0 ]
	  [0 ][0 ][0 ][0 ][b3][0 ][0 ][0 ]

PORTB [b7][b6][b5][b4][b3][b2][b1][b0]
 AND~ [1 ][1 ][1 ][1 ][0 ][1 ][1 ][1 ]
      [b7][b6][b5][b4][0 ][b2][b1][b0]
*/

int main(void) {
	
	while(1) {
		
		// *PORTB_ptr = 0; // usa o ponteiro para escrever 0 no endereço 0x25
		// *PORTB_ptr = 0b00001000; // liga o terceiro bit -> PORTB3
		
		// operações resolvidas em tempo de compilação
		
		// PORTB = PORTB | 0b00001000; // seta o bit 3 preserva o restante
		// PORTB |= 0b00001000;
		// PORTB |= 1<<3; // shift 3x pra esquerda -> 1 << 3 = 1000)
		
		PORTB |= (1<<PORTB3); // forma preferida para setar bits, seta 1 para b3
		PORTB &= ~(1<<PORTB3); // seta 0 para b3
		PORTB ^= (1<<PORTB3); // alterna o bit (util para onda quadrada)
		
		PORTB = 0;
		
	}
    
}