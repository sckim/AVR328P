/*************************************
* Purpose: Understand GPIO registers
*
* DDRn
* PORTn
* PINn
*************************************/

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	//Initialize_Ports();

	DDRB = 0xF0;
	DDRD = 0xFF;

	while(1)	{
		if( bit_is_clear(PINB, PB0) )
			PORTD = 0x00;
		else if( bit_is_clear(PINB, PB1) )
			PORTD = 0x0F;
		else
			PORTD = 0xFF;

		_delay_ms(10);  // 500ms Áö¿¬½ÃÅ´
	}
}
