/*
*
* Created: 2017-08-07 ¿ÀÈÄ 5:12:02
* Author : Soochan Kim
*/

#define F_CPU 16000000L  //clear warning message

#include <avr/io.h>
#include <avr/interrupt.h>

#define sbi(sfr, bit)    sfr |= (1<<bit)
#define cbi(sfr, bit)    sfr &= ~(1<<bit)

#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))
#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))

volatile int8_t value = 0;
uint8_t seg[16]={0xC0, 0xF9,0xA4,0xB0,0x99,0x92,0x82,
0xD8,0x80,0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8e};

ISR(PCINT0_vect) {
	value = 0;
	if( bit_is_set(PINB, PB0) )
	value += 1;
	if( bit_is_set(PINB, PB1) )
	value += 2;
	if( bit_is_set(PINB, PB2) )
	value += 4;
	if( bit_is_set(PINB, PB3) )
	value += 8;

	PORTD = seg[value];
}

int main(void) {
	DDRD = 0xFF;
	DDRB = 0x00;

	sbi(PCICR, PCIE0);
	PCMSK0 = 0x0F;
	sbi(SREG, 7);

	while (1) {
	}
	return 0;
}
