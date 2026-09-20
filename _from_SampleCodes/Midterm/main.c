/*
 * Midterm.c
 *
 * Created: 2019-04-30 오후 3:41:57
 * Author : Soochan Kim
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	//DDRB = DDRB | (1<<5);
	DDRB |= (1<<5);
	//DDRB  |= _BV(PB5);

    /* Replace with your application code */
    while (1) 
    {
		PORTB |= (1<<5);
		_delay_ms(1000);
		PORTB &= ~(1<<5);
		_delay_ms(1000);
    }

	return 0;
}

