/*
 * main.c
 *
 *  Created on: 2019. 7. 16.
 *      Author: Soochan Kim
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdint.h>

#include "uart.h"

enum {
	IDLE, READY, RUN
} state = IDLE;

static FILE std_inout = FDEV_SETUP_STREAM(uart_printf, uart_scanf, _FDEV_SETUP_RW);

int main(void) {
	uint8_t condition = 0;
	uint8_t x, y, z;

	stdout = stdin = &std_inout;

	uart_init(UART_BAUD_SELECT(9600, 16000000L));
	sei();

	state = 1;
	printf("Enter number");
	while (1) {
		_delay_ms(1000);

		switch (state) {
		case IDLE:
			y = z = 0;
			state = x >= 20 ? RUN : x >= 10 ? READY : IDLE;
			break;
		case READY:
			y = 20;
			state = x >= 30 ? RUN : IDLE;
			break;
		case RUN:
			z = 100;
			state = x < 10 ? IDLE : x < 20 ? READY : RUN;
			break;
		}
		printf("x = %d, y = %d, z = %d\r\n", x, y, z);
		if (x++ >= 40)
			x = 0;
	}
	return 0;
}
