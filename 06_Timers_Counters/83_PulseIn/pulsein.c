/*
 * main.c
 *
 *  Created on: 2017. 10. 27.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"

unsigned char text[] = "\r\nWelcome!\r\n";

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define inPortDDR	DDRD
#define inPortPORT	PIND

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout) {
	uint8_t stateMask;

	volatile unsigned long width = 0; // keep initialization out of time critical area
	volatile unsigned long numloops = 0;
	volatile unsigned long maxloops = microsecondsToClockCycles(timeout) / 16;

	// wait for any previous pulse to end
	do {
		stateMask = (inPortPORT & _BV(pin)) ? 1 : 0;
		//printf("1. state = %d\r\n", stateMask ? 1 : 0);
		if (numloops++ > maxloops)
			return 0;
	} while (stateMask == state);

	// wait for the pulse to start
	do {
		stateMask = (inPortPORT & _BV(pin)) ? 1 : 0;
		//printf("2. state = %d\r\n", stateMask ? 1 : 0);
		if (numloops++ > maxloops)
			return 0;
	} while (stateMask != state);

	do {
		// return 될때 수식의 영향을 받는다.
		stateMask = (inPortPORT & _BV(pin)) ? 1 : 0;
		//printf("3. state = %d\r\n", stateMask ? 1 : 0);
		width++;
		if (numloops++ > maxloops)
			return 0;
	} while (stateMask == state);

	// 아래 수식은 위의 루프의 시간에 따라 수정되어야 한다.
	return clockCyclesToMicroseconds(width);
}

unsigned long duration;
// the loop function runs over and over again forever
void loop(void) {
	// Detect high pulse
	printf("Pressure button 5\r\n");
	duration = pulseIn(5, 1, 10000000L);
	printf("High pulse width = %ld\r\n", duration);

	// Detect low pulse
	//duration = pulseIn(4, 0, 10000);
	//printf("Low pulse width = %d\r\n", duration);
//	printf("inPortPORT = %x\r\n", inPortPORT);
//	printf("(inPortPORT & cBit) = %x\r\n", (inPortPORT & _BV(cBit) ));
}

void Display_menu(void) {
	printf("Detect pulse width\r\n");
}

void setup(void) {
	uart_init(UART_BAUD_SELECT(9600, 16000000L));

	cbi(inPortDDR, 5);
	cbi(inPortDDR, 4);
}

static FILE std_inout = FDEV_SETUP_STREAM(uart_printf, uart_scanf, _FDEV_SETUP_RW);

int main(void) {
	stdout = stdin = &std_inout;

	setup();
	Display_menu();

	for (;;) {
		loop();
	}

	return 0;
}
