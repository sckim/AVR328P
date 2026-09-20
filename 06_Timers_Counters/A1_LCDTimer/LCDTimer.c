/*
 * LCD Timer.c
 *
 *  Created on: 2016. 5. 5.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LCD_4bit

#include "lcd_lib.h"

// CLK: 16MHz / 1024 = 15,625
// 64ns *125 =  8msec
#define cDelay 256-125

volatile char str[16];
volatile int cnt = 0;
volatile unsigned int bUpdated = 0;

volatile int sec = 0;
volatile int min = 40;
volatile int hour = 15;

ISR (TIMER0_OVF_vect) {
	// prevent generating interrupter in this loop.
	cli();

	TCNT0 = cDelay; //3. 초기값
	cnt++;
	if (cnt >= 125) {
		cnt = 0;
		sec++;
		bUpdated = 1;
		if (sec >= 60) {
			sec = 0;
			min++;
		}
		if (min >= 60) {
			min = 0;
			hour++;
		}
		if (hour >= 24)
			hour = 0;
	}
	sei();
}

void Timer0_init(void) {
	//TIMSK=0x01;  //1. Timer0 오버플로 인터럽트 에이블 (TOIE0)
	TIMSK0 |= _BV(TOIE0);

	TCCR0A = 0;
	// 2. Normal, 1/1024 for 프리스케일
	TCCR0B |= (1 << CS02);	// Clock/1024
	TCCR0B |= (1 << CS00);	// Clock/1024

	// 3. Set counter
	TCNT0 = cDelay;
}

void InitScreen() {
	LCDGotoXY(0, 0);
	sprintf(str, "My Clock");
	LCDstring(str, strlen(str));
	LCDGotoXY(0, 1);
	sprintf(str, "%02d:%02d:%02d", hour, min, sec);
}

int main(void) {
	DDRB |= (_BV(PB0)|_BV(PB1));
	PORTB |= _BV(PB0);
	PORTB |= _BV(PB1);

	LCDinit();
	LCDcursorOFF();
	LCDclr();

	cli();
	Timer0_init();
	sei();

	InitScreen();
	while (1) {
		if (bUpdated) {
			bUpdated = 0;

			LCDGotoXY(0, 1);
			sprintf(str, "%02d:%02d:%02d", hour, min, sec);
			LCDstring(str, strlen(str));

			PORTB ^= _BV(PB5);
		}
		if( bit_is_clear(PINB, PB0))
			sec = 0;
		if( bit_is_clear(PINB, PB1))	{
			min++;
			_delay_ms(500);
		}
	}

}
