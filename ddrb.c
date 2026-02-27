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
	DDRB = (1<<DDB6)|(1<<DDB7); // direciona os pinos da porta B, 6 e 7 como saida.
	while(1) {
		PORTB ^= (1<<PORTB7); // alterna o bit portb7
	}
    
}