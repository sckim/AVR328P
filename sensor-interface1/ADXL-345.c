#include <avr/io.h>
#include <avr/interrupt.h>
#include "types.h"
#include "defs.h"
#include "i2c.h"
#include "ADXL-345.h"


void ADXl345_INIT(void)
{
	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte(ADXL345_W); //write to ADXL345
	i2cWaitForComplete();

	i2cSendByte(0x2D); //Write to Power CTL register
	i2cWaitForComplete();

	i2cSendByte( (1<<3) ); //Set the measure bit on D3
	i2cWaitForComplete();

	i2cSendStop();
}


int16_t read_adxl345(char reg_adr)
{		
	char lsb, msb;

	i2cSendStart();
	i2cWaitForComplete();
	
	i2cSendByte(ADXL345_W);	// write to this I2C address, R/*W cleared
	i2cWaitForComplete();
	
	i2cSendByte(reg_adr);	//Read from a given address
	i2cWaitForComplete();
	
	i2cSendStart();
	
	i2cSendByte(ADXL345_R); // read from this I2C address, R/*W Set
	i2cWaitForComplete();
	
	i2cReceiveByte(TRUE);
	i2cWaitForComplete();
	lsb = i2cGetReceivedByte(); //Read the LSB data
	i2cWaitForComplete();

	i2cReceiveByte(FALSE);
	i2cWaitForComplete();
	msb = i2cGetReceivedByte(); //Read the MSB data
	i2cWaitForComplete();
	
	i2cSendStop();
	
	return( (msb<<8) | lsb);
}


