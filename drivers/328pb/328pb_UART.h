#ifndef _328PB_UART_H
#define _328PB_UART_H

#include <avr/io.h>

void UART_Init(unsigned int baud);
void UART_Transmit(unsigned char data);
void UART_Transmit_String(const char* str);

#endif
