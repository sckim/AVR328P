/*
 * 10_Blink.c
 *
 * Created: 2017-08-07 ¿ÀÈÄ 5:12:02
 * Author : Soochan Kim
 */


#include <avr/io.h>
#include <util/delay.h>

int main(void) {

#if defined (__AVR_ATmega128__)
	DDRA = 0xFF;

	while (1) {
		PORTA = 0x00;
		_delay_ms(1000);
		PORTA = 0xFF;
		_delay_ms(1000);
	}
#elif __AVR_ATmega328P__
	DDRB = 0xFF;

	while(1) {
		PORTB = 0x00;
		_delay_ms(1000);
		PORTB = 0xFF;
		_delay_ms(1000);
	}
#endif

	return 0;
}
