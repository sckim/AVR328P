///*************************************
// * Purpose: Timer0�� �̿��� OC0A(PD6)�� PWM ����
// *
// *
// *************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// from TCNT = (CS / 16000000 ) * (256-x) =10msec
// x = time * (16000000/CS)
// if cs = 1024
// TCNT0�� 0�̸� 16.384ms ���� overflow �߻�

#define Normal 	0
#define PWM		1
#define CTC		2
#define FPWM	3

void Timer0Mode(unsigned char mode) {
	// WGM01 WMG00
	// 00: Normal
	// 01: PWM, Phase Correct
	// 10: CTC
	// 11: Fast PWM

	switch (mode) {
	case Normal:
		TCCR0A &= ~(1 << WGM01);
		TCCR0A &= ~(1 << WGM00);
		break;
	case PWM:
		TCCR0A &= ~(1 << WGM01);
		TCCR0A |= (1 << WGM00);
		break;
	case CTC:
		TCCR0A |= (1 << WGM01);
		TCCR0A &= ~(1 << WGM00);
		break;
	case FPWM:
		TCCR0A |= (1 << WGM01);
		TCCR0A |= (1 << WGM00);
		break;
	}
}

void Timer0Prescaler(unsigned int scale) {
	// set prescaler to 8 and starts PWM
	// CS02 CS01 CS00
	// 000: No clock source
	// 001: No prescaling
	// 010: clk_IO/8
	// 011: clk_IO/64
	// 100: clk_IO/256
	// 101: clk_IO/1024
	switch (scale) {
	case 0:
		TCCR0B &= ~(1 << CS02);
		TCCR0B &= ~(1 << CS01);
		TCCR0B &= ~(1 << CS00);
		break;
	case 8:
		TCCR0B &= ~(1 << CS02);
		TCCR0B |= (1 << CS01);
		TCCR0B &= ~(1 << CS00);
		break;
	case 64:
		TCCR0B &= ~(1 << CS02);
		TCCR0B |= (1 << CS01);
		TCCR0B |= (1 << CS00);
		break;
	case 256:
		TCCR0B |= (1 << CS02);
		TCCR0B &= ~(1 << CS01);
		TCCR0B &= ~(1 << CS00);
		break;
	case 1024:
		TCCR0B |= (1 << CS02);
		TCCR0B &= ~(1 << CS01);
		TCCR0B |= (1 << CS00);
		break;
	default:
		TCCR0B &= ~(1 << CS02);
		TCCR0B &= ~(1 << CS01);
		TCCR0B |= (1 << CS00);
	}
}

ISR (TIMER0_OVF_vect) {
	PORTB ^= _BV(PB5);
	_delay_us(1000);	//100us
	PORTB &= ~_BV(PB5);
	TCNT0 = 0;  //Period�� 16.25msec�̱� ������
}

int main(void) {
	// PD6 is now an output
	DDRB |= (1 << PB5);

	cli();
	TIMSK0 |= (1<<TOIE0);    // Timer0 �����÷� ���ͷ�Ʈ mask enable
	//TIFR0 |= (1<<TOV0);

	Timer0Mode(Normal);		 // �Ϲ� timer mode
	Timer0Prescaler(1024);	 // 16MHz/256 => 1 step = 16us

	sei();
	while (1)
		;
	{
		// we have a working Fast PWM
	}
}
