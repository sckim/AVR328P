/*************************************
 * Purpose: Understand GPIO registers
 *
 * DDRn
 * PORTn
 * PINn
 *************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int Value = 0;

ISR(INT0_vect)
{
	Value++;
	PORTD = Value<<4;
}

ISR(INT1_vect)
{
	Value--;
	PORTD = Value<<4;
}

int main(void) {
	DDRD = 0xF0;

	EICRA = 0b00001010;
	EIMSK = 0xFF; //0b00000011;
	sei();

	while (1) {
	}
}
