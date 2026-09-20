#ifndef _TTL74595_H
#define _TTL74595_H

#include <stdint.h>

class TTL74595
{
public:
	TTL74595(const uint8_t DataIn, const uint8_t clock, const uint8_t trigger);
	void write(uint8_t val, uint8_t bitOrder);

private:
    uint8_t _dataIn;
    uint8_t _clk;
    uint8_t _latch;

    void Clock(void);
	void Latch(void);

};

#endif
//
// END OF FILE
//
