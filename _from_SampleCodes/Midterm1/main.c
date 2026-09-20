/*
 * Midterm1.c
 *
 * Created: 2019-04-30 오후 7:28:24
 * Author : Soochan Kim
 */ 

#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
//#include <avr/delay.h>

#define sbi(Reg, bit)    Reg = Reg | (1<<bit)

int main(void)
{
	//DDRB |= (1<<5);
	DDRB = DDRB | (1<<5);
	DDRB = DDRB | 0b00100000;
	sbi(DDRB, 5);

    /* Replace with your application code */
    while (1) 
    {
		PORTB = PORTB | 0b00100000;
		//PORTB |= 0b00100000;
		//PORTB |= (1<<5);
		sbi(PORTB, 5);

		_delay_ms(1000);
		PORTB = PORTB & ~0b00100000;
		//PORTB &= ~0b00100000;
		//PORTB &= ~(1<<5);
		//PORTB = PORTB & 0b11011111;
		_delay_ms(1000);
    }
}

