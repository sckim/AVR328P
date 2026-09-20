/*
 * timer0.c
 *
 *  Created on: 2018. 10. 17.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
int main(void)
{
	//DDRB |= (1<<5);
	DDRB |= _BV(5);
	TCCR0A =0;
	// CS02 CS01 CS00 = 101 = Clk/1024
	TCCR0B |= (1<<CS00);
	//TCCR0B |= _BV(CS00);
	TCCR0B |= (1<<CS02);

	TCNT0 = 100;
	while(1){
		//if( bit_is_set(TIFR0, TOV0)){
		if( TIFR0 & _BV(TOV0)){
			TIFR0 |= _BV(TOV0);
			TCNT0 = 100;
			//toggle bit5 in PortB
			PORTB ^= (1<<PB5);
		}
	}
	return 0;
}
