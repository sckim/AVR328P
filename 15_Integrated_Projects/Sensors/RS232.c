#include <avr/io.h>
#include "RS232.h"


void UART0_INIT(unsigned int ubrr)
{
	// Set baud rate 
	UBRR0H = ubrr>>8;
	UBRR0L = ubrr;
	
	// Enable receiver and transmitter 
	UCSR0A = (1<<U2X0);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	// Set frame format: 8 bit, no parity, 1 stop bit,   
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}


// UART0 데이터 수신 프로그램
unsigned char UART0_GetChar(void)
 { 
     while(!(UCSR0A & 0x80)) ; 
      return UDR0; 
 }


// UART0 데이터 송신 프로그램
void UART0_PutChar(unsigned char TX_data)
{    
     while(!(UCSR0A & 0x20)) ; 
     UDR0 = TX_data; 
}



// UART0 데이터 송신 프로그램 (문자열)
void USART0_PutStr(char *tx_str)
{
	while(*tx_str != '\0')
	{
		UART0_PutChar(*tx_str);//한개의 문자씩 출력
		tx_str++;
	}
}


