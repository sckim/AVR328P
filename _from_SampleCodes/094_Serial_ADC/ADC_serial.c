/*
 * ADC_hold.c
 *
 *  Created on: 2016. 5. 25.
 *      Author: Soochan Kim
 */
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define nChs 1

/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */
void uart_init(unsigned long iBaudrate) {

	// UCSRnA 레지스터를 초기화시킨다.
	// 0번째 비트, 즉 MPCMn 를 0으로 세트 (USARTn을 멀티 프로세서 통신모드로 설정)
	UCSR0A = 0x00;

	// UCSRnB 레지스터를 이용하여 송신 및 수신 사용설정을 한다.
	// Rx, Tx enable
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// 3번째, 4번째 비트 세트 즉, TXENn (USARTn모듈의 송신부 동작 enable) RXENn (USARTn모듈의 수신부 동작 enable)
	//  2번 비트 UCSZ02 = 0으로 세트

	// UCRnC 레지스터를 이용하여 모드(동기/비동기), 패리티모드, 정지비트,
	// 전송 데이터 비트수를 설정한다.
	// 비동기 방식, No Parity bit, 1 Stop bit, 8bits
	UCSR0C |= (1 << UCSZ01);
	UCSR0C |= (1 << UCSZ00);

	// See http://wormfood.net/avrbaudcalc.php
	// UBRRnH(L) 레지스터를 이용한 송수신 보레이트 설정
	UBRR0H = 0x00;
	switch (iBaudrate) {
	case 9600:
		//UBRR0L = 95; // 14.7456 MHz -> 9600 bps
		UBRR0L = 103; // 16 MHz -> 9600 bps
		break;
	case 19200:
		//UBRR0L = 47; // 14.7456 MHz -> 19200 bps
		UBRR0L = 51; // 16 MHz -> 19200 bps
		break;
	case 115200:
		//UBRR0L = 7;  // 14.7456 MHz -> 115200 bps
		UBRR0L = 8;  // 16 MHz -> 115200 bps
		break;
	default:
		UBRR0L = 95;
	}
}

void uart_putch(unsigned char data) {
	//전송준비가 될 때까지 대기
	loop_until_bit_is_set(UCSR0A, UDRE0);
	//while ((UCSR0A & (1 << UDRE0)) == 0);
	// while(!(UCSR0A & 0x20)) ;

	UDR0 = data;
}

void uart_putchar(unsigned char data, FILE *stream) {
	if (data == '\n') {
		uart_putchar('\r', stream);
	}
	loop_until_bit_is_set(UCSR0A, UDRE0);

	UDR0 = data;
}

unsigned char uart_getch(void) {
	loop_until_bit_is_set(UCSR0A, RXC0);
	//while(!(UCSR0A & (1<<RXC0) )) ;
	//while(!(UCSR0A & 0x80)) ;

	return UDR0;
}

unsigned char uart_getchar(FILE *stream) {
	loop_until_bit_is_set(UCSR0A, RXC0);

	return UDR0;
}

void uart_puts(char *data) {
	while (*data != '\0')
		uart_putch(*data++);
}

void uart_printf(char data, FILE * stream) {
	uart_putch(data);
}

unsigned char uart_scanf(FILE * stream) {
	return uart_getch();
}

//새로운 standard io를 지정한다.
static FILE std_output = FDEV_SETUP_STREAM(uart_printf, NULL, _FDEV_SETUP_WRITE);
static FILE std_input = FDEV_SETUP_STREAM(NULL, uart_scanf, _FDEV_SETUP_READ);

void InitADC() {
	// For Aref=AVcc;
	// REFS[1:0] = 01
	ADMUX = (1 << REFS0);

	//Prescalar div factor =128
	// ADPS[2:0]
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ReadADC(uint8_t ch) {
	//Select ADC Channel ch must be 0-7
	// MUXn[3:0]
	ADMUX &= 0xF0;
	ADMUX |= (ch & 0x07);

	//Start Single conversion
	ADCSRA |= (1 << ADSC);

	//Wait for conversion to complete
	while (!(ADCSRA & (1 << ADIF)))
		;

	//Clear ADIF by writing one to it
	//Note you may be wondering why we have write one to clear it
	//This is standard way of clearing bits in io as said in datasheets.
	//The code writes '1' but it result in setting bit to '0' !!!
	ADCSRA |= (1 << ADIF);

	return (ADC);
}

int main(void) {
	int temp[nChs];
	double voltage[nChs];

	char text[] = "\r\nWelcome! Serial communication world!!\r\n Good Luck\r\n";
	char echo[] = "HKNU >> ";
	int i;

	//stdout과 stdin에 사용자가 정의한 함수로 설정
	//아래 2줄은 main 함수 밖에 작성하면 오류가 발생하므로 주의
	stdout = &std_output;
	stdin = &std_input;

	uart_init(19200);

	i = 0;
	//	while (text[i] != '\0') {
	//		UART_Transmit(text[i++]);
	//	}
	printf("\r%s", text);

	//	UART_putString(echo);
	puts(echo);

	DDRB = 0xFF;
	PORTB = 0;

	InitADC();
	while (1) {
		PORTB = 0x00;
		for (int loop = 0; loop < nChs; loop++) {
			temp[loop] = ReadADC(loop);
			voltage[loop] = (temp[loop] / 1023.0) * 5.0;
			printf("Ch[%d] = %d, %3.2f[V]\r\n", loop, temp[loop],
					voltage[loop]);
			_delay_ms(100);
		}
		PORTB = 0xFF;
		_delay_ms(100);
	}
}

