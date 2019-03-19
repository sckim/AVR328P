/*
 * 10_Blink.c
 *
 * Created: 2017-08-07 ¿ÀÈÄ 5:12:02
 * Author : Soochan Kim
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRB |= 0x01;

	while (1) {
		PORTB |= 0x01;
		_delay_ms(1000);
		PORTB &= ~0x01;
		_delay_ms(1000);
	}
	return 0;
}
