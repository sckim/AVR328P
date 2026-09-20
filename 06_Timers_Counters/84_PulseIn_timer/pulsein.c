/*
 * main.c
 *
 *  Created on: 2017. 10. 27.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <avr/interrupt.h>
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

// the prescaler is set so that timer0 ticks every 64 clock cycles, and the
// the overflow handler is called every 256 ticks.
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))

// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)

// the fractional number of milliseconds per timer0 overflow. we shift right
// by three to fit these numbers into a byte. (for the clock speeds we care
// about - 8 and 16 MHz - this doesn't lose precision.)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;

ISR(TIMER0_OVF_vect) {
	// copy these to local variables so they can be stored in registers
	// (volatile variables must be read from memory on every access)
	unsigned long m = timer0_millis;
	unsigned char f = timer0_fract;

	m += MILLIS_INC;
	f += FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}

	timer0_fract = f;
	timer0_millis = m;
	timer0_overflow_count++;
}

unsigned long micros() {
	unsigned long m;
	uint8_t oldSREG = SREG, t;

	cli();
	m = timer0_overflow_count;
	t = TCNT0;

	if ((TIFR0 & _BV(TOV0)) && (t < 255))
		m++;

	// interrupt enable이 포함되어 있다.
	SREG = oldSREG;

	return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}

void init() {
	// this needs to be called before setup() or some functions won't
	// work there
	sbi(TCCR0A, WGM01);
	sbi(TCCR0A, WGM00);
	sbi(TCCR0B, CS01);
	sbi(TCCR0B, CS00);
	sbi(TIMSK0, TOIE0);

	sei();
}

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse.
 *
 * ATTENTION:
 * this function relies on micros() so cannot be used in noInterrupt() context
 */
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout) {
	// cache the port and bit of the pin in order to speed up the
	// pulse width measuring loop and achieve finer resolution.  calling
	// digitalRead() instead yields much coarser resolution.
	uint8_t stateMask = (state ? _BV(pin) : 0);

	unsigned long startMicros = micros();

	// wait for any previous pulse to end
	while ((inPortPORT & _BV(pin)) == stateMask) {
		if (micros() - startMicros > timeout)
			return 0;
	}

	// wait for the pulse to start
	while ((inPortPORT & _BV(pin)) != stateMask) {
		if (micros() - startMicros > timeout)
			return 0;
	}

	unsigned long start = micros();
	// wait for the pulse to stop
	while ((inPortPORT & _BV(pin)) == stateMask) {
		if (micros() - startMicros > timeout)
			return 0;
	}
	return micros() - start;
}

unsigned long duration;
// the loop function runs over and over again forever
void loop(void) {
	// Detect high pulse
	printf("Pressure button 5\r\n");
	duration = pulseInLong(5, 1, 5000000UL);
	printf("High pulse width = %ld\r\n", duration);

	// Detect low pulse
	//duration = pulseIn(4, 0, 10000);
	//printf("Low pulse width = %d\r\n", duration);
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

	init();
	setup();
	Display_menu();

	for (;;) {
		loop();
	}

	return 0;
}
