/*
 * 10_Blink.c
 *
 * Created: 2017-08-07 ¿ÀÈÄ 5:12:02
 * Author : Soochan Kim
 */

#include <avr/io.h>
#include <util/delay.h>

#define sbi(sfr, bit) _SFR_BYTE(sfr) |= _BV(bit)
#define cbi(sfr, bit) _SFR_BYTE(sfr) &= ~_BV(bit)

int main(void) {
//	DDRB |= _BV(PB5);
	sbi(DDRB, PB5);

	while (1) {
		sbi(PORTB, PB5);
		//PORTB |= (1 << PB5);
		//PORTB ^= _BV(PB5);
		_delay_ms(1000);
		cbi(PORTB, PB5);
		//PORTB &= ~(1 << PB5);
		_delay_ms(1000);
	}
	return 0;
}
