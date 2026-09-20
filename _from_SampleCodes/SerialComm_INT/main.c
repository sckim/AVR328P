/*
 * main.c
 *
 *  Created on: 2020. 5. 10.
 *      Author: Soochan Kim
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

volatile char ch;

void USART_Init(unsigned int ubrr) {
	/*Set baud rate */
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;

	// Enable receiver 	and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);

	UCSR0B |= _BV(RXCIE0);
}

ISR(USART_RX_vect)
{
	ch = UDR0;
	USART_Transmit(ch);
}

void USART_Transmit(unsigned char data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)))
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void USART_Puts(char *data) {
  while (*data != '\0')
	USART_Transmit(*data++);
}

unsigned char USART_Receive(void) {
	/* Wait for data to be received */
//	while (!(UCSR0A & (1 << RXC0)))
//		;
	loop_until_bit_is_set(UCSR0A, RXC0);
	/* Get and return received data from buffer */
	return UDR0;
}

int main(void) {

  	DDRB |= _BV(PB5);

  	USART_Init(MYUBRR);

	USART_Puts("Lamp test");
	sei();

	while(1){
      //ch = USART_Receive();
      //USART_Transmit(ch+1);
      if( ch=='1' )
        PORTB ^= _BV(PB5);
	}
}
