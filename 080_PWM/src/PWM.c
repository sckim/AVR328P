///*************************************
// * Purpose: Timer0을 이용한 OC0A(PD6)에 PWM 생성
// *
// *
// *************************************/

#include <avr/io.h>

int main(void)
{
	// PD6 is now an output
	DDRD |= (1 << DDD6);

    OCR0A = 125;
    // set PWM for 50% duty cycle

    // COM0A1 COM0A0
    // 00: OC0A disconnected
    // 01: Toggle on Match
    // 10: Clear on Match, Non inverting
    // 11: Set on Match , Inverting
    TCCR0A |= (1 << COM0A1);
    //TCCR0A |= (1 << COM0A0);

    // WGM01 WMG00
    // 00: Normal
    // 01: PWM, Phase Correct
    // 10: CTC
    // 11: Fast PWM
    TCCR0A |= (1 << WGM01);
    TCCR0A |= (1 << WGM00);

    // set prescaler to 8 and starts PWM
    // CS02 CS01 CS00
    // 000: No clock source
    // 001: No prescaling
    // 010: clk_IO/8
    // 011: clk_IO/64
    // 100: clk_IO/256
    // 101: clk_IO/1024
    TCCR0B |= (1 << CS02);
    TCCR0B |= (1 << CS00);

    while (1)
    {
        // we have a working Fast PWM
    }
}
