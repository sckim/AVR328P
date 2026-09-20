// Install Pin change interrupt for a pin, can be called multiple times
#include <avr/io.h>
#include <avr/interrupt.h>

// Use one Routine to handle each group
ISR (PCINT0_vect)// handle pin change interrupt for D8 to D13 here
{
	if( bit_is_set(PINB, PB0))
		PORTB |= _BV(PB4);
	else
		PORTB &= ~_BV(PB4);
}

ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
{
	if( bit_is_set(PINC, PC0) && bit_is_set(PINC, PC1))
		PORTB |= _BV(PB5);
	else
		PORTB &= ~_BV(PB5);
}

ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{
	if( bit_is_set(PIND, PD7))
		PORTB |= _BV(PB3);
	else
		PORTB &= ~_BV(PB3);
}

void setup() {
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0xFF;

	DDRB |= _BV(PB3);
	DDRB |= _BV(PB4);
	DDRB |= _BV(PB5);

	PCICR |= 0x07;

	PCMSK0 |= 0x01;
	PCMSK1 |= 0x03;
	PCMSK2 |= 0x80;

	sei();
}

void loop() {
	// Nothing needed
}

int main(void)
{
	setup();

	while(1){
		loop();
	}
}
