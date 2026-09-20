///*************************************
// * Purpose: Timer0을 이용한 OC0A(PD6)에 PWM 생성
// *
// *
// *************************************/
#define F_CPU	16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer0.h"

#define DutyRatio	50
#define DutyValue (DutyRatio / 100.0 * 256)

volatile int duty = 50;

int main(void)
{
	OCR0A = 156;
	OCR0B = 8;
	// set PWM for 50% duty cycle

	Timer0Mode(FPWM);		 // Compare capture mode
	Timer0Prescaler(1024);	 // 16MHz/1024 => 1 step = 64us

	Timer0OutputA(NonInvert);
	Timer0OutputB(NonInvert);

	while (1)	{
		// we have a working Fast PWM
		OCR0B = duty;
		_delay_ms(10);
		duty ++;
		if( duty>39 )
			duty = 8;
	}
}
