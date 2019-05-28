/*
 * UART_simple.c
 *
 *  Created on: 2019. 5. 28.
 *      Author: Soochan Kim
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

char str[80];

/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */
void InitUART(unsigned long iBaudrate) {

	// UCSRnA �������͸� �ʱ�ȭ��Ų��.
	// 0��° ��Ʈ, �� MPCMn �� 0���� ��Ʈ (USARTn�� ��Ƽ ���μ��� ��Ÿ��� ����)
	UCSR0A = 0x00;

	// UCSRnB �������͸� �̿��Ͽ� �۽� �� ���� ��뼳���� �Ѵ�.
	// Rx, Tx enable
	// TXENn (USARTn����� �۽ź� ���� enable)
	// RXENn (USARTn����� ���ź� ���� enable)
	UCSR0B = (1 << RXEN0);
	UCSR0B |= (1 << TXEN0);

	// UCRnC �������͸� �̿��Ͽ� ���(����/�񵿱�), �и�Ƽ���, ������Ʈ,
	// �񵿱� ���, No Parity bit, 1 Stop bit, 8bits
	UCSR0C |= (1 << UCSZ01);
	UCSR0C |= (1 << UCSZ00);

	// See http://wormfood.net/avrbaudcalc.php
	// UBRRnH(L) �������͸� �̿��� �ۼ��� ������Ʈ ����
	UBRR0H = 0x00;
	switch (iBaudrate) {
	case 9600:
		//UBRR0L = 95; // 14.7456 MHz -> 9600 bps
		UBRR0L = 103; // 16 MHz -> 9600 bps
		break;
	case 19200:
//		UBRR0L = 47; // 14.7456 MHz -> 19200 bps
		UBRR0L = 51; // 16 MHz -> 9600 bps
		break;
	case 115200:
		//UBRR0L = 7;  // 14.7456 MHz -> 115200 bps
		UBRR0L = 8;  // 16 MHz -> 115200 bps
		break;
	default: //9600
		UBRR0L = 103;
	}
}

void USART_Transmit(unsigned char data) {
	/* Wait for empty transmit buffer */
	//while (!( UCSR0A & (1 << UDRE0)))
	//	;
	loop_until_bit_is_set(UCSR0A, UDRE0);

	UDR0 = data;
}

unsigned char UART_Receive(void) {
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)))
		;
//	loop_until_bit_is_set(UCSR0A, RXC0);

	return UDR0;
}

void UART_putString(char *data) {
	while (*data != '\0')
		USART_Transmit(*data++);
}

int main(void) {
	char recieved_byte;
	char text[] = "\r\nWelcome! Serial communication world!!\r\n Good Luck\r\n";
	char echo[] = "HKNU >> ";
	int i;

	InitUART(19200);

	i = 0;
	while (text[i] != '\0') {
		USART_Transmit(text[i++]);
	}

	UART_putString(echo);
//	while (echo[i] != '\0') {
//		USART_Transmit(echo[i++]);
//	}

	for (;;) {
		recieved_byte = UART_Receive();
		_delay_ms(10);
		USART_Transmit(recieved_byte);
		if (recieved_byte == 0x0D)
			UART_putString(echo);
	}
	return 0; // never reached
}

