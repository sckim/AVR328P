/*************************************
 *
 * TIMSK0
 * TCCR0A
 * TCCR0B
 * OCR0A
 *************************************/
#include <avr/io.h>
//#include <avr/interrupt.h>

// 15625*8msec = 125
#define cDelay 125

volatile int sec = 0;
volatile int msec8 = 0;

int main(void) {
	char s10, s1;

	DDRD = 0xFF;
	DDRB |= _BV(PB5);

	PORTD = 0;

	//Set CTC mode
	TCCR0A |= (1<<WGM01);
	//CS0[2:0]
	TCCR0B |= (1 << CS02);	// Clock/1024
	TCCR0B |= (1 << CS00);	// Clock/1024

	// Toggle on Compare Match
	//TCCR0A |= _BV(COM0A1);
	TCCR0A |= _BV(COM0A0);
	
	//TCCR0A |= _BV(COM0B1);
	TCCR0A |= _BV(COM0B0);

	OCR0A = cDelay;
	while (1) {
		// Check overflow flag
		if (bit_is_set(TIFR0, OCF0A)) {
			// reset the overflow flag
			TIFR0 |= _BV(OCF0A);

			msec8++;
			if (msec8 == 125) {
				sec++;
				msec8 = 0;
				s10 = sec / 10;
				s1 = sec % 10;
				//PORTD = (s10 << 4) + s1;
				PORTD = s1;

			}
			if (sec == 99) {
				sec = 0;
			}
			PORTB ^= _BV(PB5);
		}
	}
}
