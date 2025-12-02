#define F_CPU	16000000L

#include <avr/io.h>
#include "timer0.h"

int main(void)
{
	OCR0A = DutyValue;
	OCR0B = DutyValue;
	// set PWM for 50% duty cycle

	Timer0Mode(FPWM);		 // Compare capture mode
	Timer0Prescaler(1024);	 // 16MHz/256 => 1 step = 16us
	Timer0OutputA(Invert);
	Timer0OutputB(Invert);

	while (1)
	{
		// we have a working Fast PWM
	}
}