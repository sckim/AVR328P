
/*
 * main.cpp
 *
 *  Created on: 2019. 7. 22.
 *      Author: Soochan Kim
 */
#include <stdint.h>
#include <util/delay.h>
#include "TTL74595.h"

extern "C" {
#include "pins.h"
#include "gpio.h"
}

//Datain, Clock, Latch
TTL74595 ttl74595(2, 3, 4);

int main(void) {
	uint8_t led_pattern[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

	while (1) {
		for (uint8_t i = 0; i < 8; i++) {
			ttl74595.write(led_pattern[i], LSBFIRST);   //Write the data to HC595
			_delay_ms(100);                 //Wait

		}
	}
	return 1;
}
