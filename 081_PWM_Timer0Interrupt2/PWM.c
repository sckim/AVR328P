///*************************************
// * Purpose: Timer0�� �̿��� OC0A(PD6)�� PWM ����
// *
// *
// *************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer0.h"

// from TCNT = (CS / 16000000 ) * (256-x) =10msec
// x = time * (16000000/CS)
// if cs = 1024
// TCNT0�� 0�̸� 16.384ms ���� overflow �߻�

#define DutyRatio	50

int High = DutyRatio/100.0*256;
unsigned char flag = 0;

ISR (TIMER0_OVF_vect) {
	if(flag){
		PORTB ^= _BV(PB5);
		flag = 0;
		TCNT0 = High;
	} else {
		PORTB ^= _BV(PB5);
		flag = 1;
		TCNT0 = 256-High;
	}
}

int main(void) {
	// PD6 is now an output
	DDRB |= (1 << PB5);

	cli();
	TIMSK0 |= (1<<TOIE0);    // Timer0 �����÷� ���ͷ�Ʈ mask enable
	//TIFR0 |= (1<<TOV0);

	Timer0Mode(Normal);		 // �Ϲ� timer mode
	Timer0Prescaler(1024);	 // 16MHz/256 => 1 step = 16us

	// Toggle on Compare Match
	// ���߿� PWM�� ������ �ִ�.
	TCCR0B |= (1<<WGM02);
	TCCR0A |= _BV(COM0A1);
	TCCR0A |= _BV(COM0B1);

	sei();
	while (1)
		;
	{
		// we have a working Fast PWM
	}
}
