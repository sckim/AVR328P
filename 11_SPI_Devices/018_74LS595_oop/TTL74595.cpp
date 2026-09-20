#include <util/delay.h>

extern "C" {
#include "pins.h"
#include "gpio.h"
}

#include "TTL74595.h"

TTL74595::TTL74595(const uint8_t DataIn, const uint8_t clock, const uint8_t trigger)
{
    _dataIn = DataIn;
    _clk = clock;
    _latch = trigger;

    pinMode(_dataIn, OUTPUT);
    pinMode(_clk, OUTPUT);
    pinMode(_latch, OUTPUT);
}

//Sends a clock pulse on SH_CP line
void TTL74595::Clock() {
	//Pulse the Shift Clock
	digitalWrite(_clk, HIGH);
	_delay_us(100);
	digitalWrite(_clk, LOW);
}

void TTL74595::Latch() {
	//Pulse the Shift Clock
	digitalWrite(_latch, HIGH);
	_delay_loop_1(1);
	digitalWrite(_latch, LOW);
	_delay_loop_1(1);
}

void TTL74595::write(uint8_t val, uint8_t bitOrder) {
	uint8_t i;

	for (i = 0; i < 8; i++) {
		if (bitOrder == LSBFIRST)	{
			if(val & (1 << i))
				digitalWrite(_dataIn, HIGH);
			else
				digitalWrite(_dataIn, LOW);
		}
		else{
			if(val & (1 << (7 - i)))
				digitalWrite(_dataIn, HIGH);
			else
				digitalWrite(_dataIn, LOW);
		}
		Clock();
	}
	Latch();
}
//
// END OF FILE
//
