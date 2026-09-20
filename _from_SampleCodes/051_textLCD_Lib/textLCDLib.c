/*
 * textLCDLib.c
 *
 *  Created on: 2016. 5. 5.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "lcd_lib.h"

#define strWelcome	"Hello, World!"

// Sender
//int main(void) {
//	LCDinit();
//	LCDcursorOn();
//	LCDclr();
//
//	LCDGotoXY(0, 0);
//	LCDstring((uint8_t*)strWelcome, strlen(strWelcome));
//
//	DDRC |= _BV(PC0);
//	DDRC |= _BV(PC1);
//
//	PORTC &= _BV(PC0);
//	for( int i=0; i<strlen(strWelcome); i++){
//		LCDcursorOFF();
//		unsigned char ch = strWelcome[i];
//		for(int j=0; j<8; j++)	{
//			LCDGotoXY(j, 1);
//			PORTC |= _BV(PC0);
//			if((ch<<j) & 0x80)	{
//				LCDsendChar('1');
//				PORTC |= _BV(PC1);
//			} else {
//				LCDsendChar('0');
//				PORTC &= ~_BV(PC1);
//			}
//			PORTC &= _BV(PC0);
//		}
//		LCDcursorOn();
//		LCDGotoXY(i, 0);
//		_delay_ms(2000);
//	}
//	return 0;
//}

// Receiver
int main(void) {
	LCDinit();
	LCDcursorOn();
	LCDclr();

	LCDGotoXY(0, 0);
	LCDstring((uint8_t*)strWelcome, strlen(strWelcome));

	DDRC &= _BV(PC0);
	DDRC &= _BV(PC1);

	for( int i=0; i<strlen(strWelcome); i++){
		unsigned char ch = 0;
		for(int j=0; j<8; j++)	{
			if( bit_is_set(PORTC, PC1))	{
				LCDsendChar('1');
				ch |= _BV(j);
			} else {
				LCDsendChar('0');
			}
		}

		LCDcursorOn();
		LCDGotoXY(i, 0);
		LCDsendChar(ch);
		_delay_ms(2000);
	}
	return 0;
}
