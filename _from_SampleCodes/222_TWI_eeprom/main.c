/****************************************************************************
 Title:    Access serial EEPROM 24C02 using I2C interace
 Author:   Peter Fleury <pfleury@gmx.ch>
 File:     $Id: test_i2cmaster.c,v 1.3 2015/09/16 09:29:24 peter Exp $
 Software: AVR-GCC 4.x
 Hardware: any AVR device can be used when using i2cmaster.S or any
 AVR device with hardware TWI interface when using twimaster.c

 Description:
 This example shows how the I2C/TWI library i2cmaster.S or twimaster.c
 can be used to access a serial eeprom.

 *****************************************************************************/
#include <avr/io.h>
#include "i2c.h"

#define Dev24C02  0xA2      // device address of EEPROM 24C02, see datasheet

int main(void) {
	unsigned char ret;

	DDRB = 0xff;                            // use all pins on port B for output
	PORTB = 0xff;                              // (active low LED's )

	initI2C();                                // init I2C interface

	/* write 0x75 to eeprom address 0x05 (Byte Write) */
	i2cStart();
	i2cSend(Dev24C02 + I2C_WRITE);       // set device address and write mode
	if (ret) {
		/* failed to issue start condition, possibly no device found */
		i2cStop();
		PORTB = 0x00;                     // activate all 8 LED to show error */
	} else {
		/* issuing start condition ok, device accessible */
    	i2cStart();
		i2cSend(0x05);                       // write address = 5
		i2cSend(0x75);                       // ret=0 -> Ok, ret=1 -> no ACK
		i2cStop();                            // set stop conditon = release bus

		/* write ok, read value back from eeprom address 0x05, wait until
		 the device is no longer busy from the previous write operation */
		i2cStart();
		i2cSend(Dev24C02 + I2C_WRITE);     // set device address and write mode
		i2cSend(0x05);                        // write address = 5
//        i2cStart();
		i2cSend(Dev24C02 + I2C_READ);       // set device address and read mode
		ret = i2cReadNoAck();                    // read one byte
		i2cStop();

		PORTB = ~ret;                           // output byte on the LED's

		/* write 0x70,0x71,072,073 to eeprom address 0x00..0x03 (Page Write),
		 wait until the device is no longer busy from the previous write operation */
		i2cStart();
		i2cSend(Dev24C02 + I2C_WRITE);     // set device address and write mode
		i2cSend(0x00);                        // write start address = 0
		i2cSend(0x70);                        // write data to address 0
		i2cSend(0x71);                        //    "    "   "    "    1
		i2cSend(0x72);                        //    "    "   "    "    2
		i2cSend(0x74);                        //    "    "   "    "    3
		i2cStop();                            // set stop conditon = release bus

		/* write ok, read value back from eeprom address 0..3 (Sequencial Read),
		 wait until the device is no longer busy from the previous write operation */
		i2cStart();
		i2cSend(Dev24C02 + I2C_WRITE);      // set device address and write mode
		i2cSend(0x00);      // write address = 0
		i2cStart();
		i2cSend(Dev24C02 + I2C_READ);        // set device address and read mode
		ret = i2cReadAck();                      // read one byte form address 0
		ret = i2cReadAck();                      //  "    "    "    "     "    1
		ret = i2cReadAck();                      //  "    "    "    "     "    2
		ret = i2cReadNoAck();                    //  "    "    "    "     "    3
		i2cStop();                           // set stop condition = release bus

		PORTB = ~ret;                            // output byte on the LED's
	}

	for (;;)
		;
}
