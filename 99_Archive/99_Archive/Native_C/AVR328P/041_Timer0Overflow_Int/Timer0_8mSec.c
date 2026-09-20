/*************************************
 * Purpose: Timer0을 이용하여 1초마다 overflow
 * interrupt에 의한 LED Shift
 *
 * TIMSK0
 * TCCR0A
 * TCCR0B
 * TCNT0
 *************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

// from TCNT = (CS / 16000000 ) * (256-x) =10msec
// x = time * (16000000/CS)
// 15625*8msec = 125
#define cDelay 256-125

volatile int sec = 0;
volatile int msec8 = 0;

SIGNAL (TIMER0_OVF_vect) {
	char s10, s1;

	TCNT0 = cDelay;

	msec8++;
	if (msec8 == 125) {
		sec++;
		msec8 = 0;
		s10 = sec/10;
		s1 = sec%10;
		PORTD = (s10<<4) + s1;
	}
	if (sec == 99) {
		sec = 0;
	}
	PORTB ^= _BV(PB5);
}

int main(void) {
	DDRD = 0xFF;
	DDRB |= _BV(PB5);

	PORTD = (sec << 4) + msec8;

	cli();

	TIMSK0 |= (1 << TOIE0);    // Timer0 오버플로 인터럽트 에이블
	TCCR0A = 0;
	//CS0[2:0]
	TCCR0B |= (1 << CS02);	// Clock/1024
	TCCR0B |= (1 << CS00);	// Clock/1024

	sei();
	//SREG |= _BV(7);
	TCNT0 = cDelay;
	while (1) {
	}
}
