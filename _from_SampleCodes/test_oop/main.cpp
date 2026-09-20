/*
 * mani.cpp
 *
 *  Created on: 2019. 6. 28.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <util/delay.h>
#include "PCF8574.h"

#define F_CPU	16000000UL

PCF8574 PCF_01(0x40);

int main(void) {
	PCF_01.begin();

	for (int i = 0; i < 8; i++) {
		PCF_01.write(i, 0);
		_delay_ms(100);
	}
	for (int i = 0; i < 8; i++) {
		PCF_01.toggle(i);
		_delay_ms(100);
	}

	PCF_01.write8(0);
	_delay_ms(1000);

	PCF_01.write(7,1);
	_delay_ms(1000);
	for (int i = 0; i < 7; i++) {
		PCF_01.shiftRight(1);
		_delay_ms(100);
	}
	for (int i = 0; i < 7; i++) {
		PCF_01.shiftLeft(1);
		_delay_ms(100);
	}
	for (int i = 0; i < 8; i++) {
		PCF_01.toggle8(0xFF);
		_delay_ms(100);
	}

	return 0;
}
