#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdlib.h>

void UART_putch(unsigned char data);
unsigned char UART_getch(void);

void UART_putchar(unsigned char data, FILE *stream);
unsigned UART_getchar(FILE *stream);


void InitUART(unsigned long iBaudrate);

/* http://www.ermicro.com/blog/?p=325 */

FILE uart_output = FDEV_SETUP_STREAM(UART_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, UART_getchar, _FDEV_SETUP_READ);

#endif // UART_H 

