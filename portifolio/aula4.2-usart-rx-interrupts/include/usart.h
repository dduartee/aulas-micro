#ifndef USART_H_
#define USART_H_
#include <xc.h>

void USART_initialize();
uint8_t USART_hasBytes();
void USART_readBytes(uint8_t* pBytes);
void USART_flush();
uint8_t USART_integrityCheck();
#endif /* USART_H_ */
