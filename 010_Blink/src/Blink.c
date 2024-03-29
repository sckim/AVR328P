/*
 * 10_Blink.c
 *
 * Created: 2017-08-07 오후 5:12:02
 * Author : Soochan Kim
 */

#define F_CPU 16000000L  //clear warning message

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRB = 0xFF;

	while (1) {
		PORTB |= _BV(PB5);
		//PORTB |= (1<<PB5);
		_delay_ms(1000);
		PORTB &= ~_BV(PB5);
		//PORTB &= ~(1<<PB5);
		_delay_ms(1000);
	}
	return 0;
}
