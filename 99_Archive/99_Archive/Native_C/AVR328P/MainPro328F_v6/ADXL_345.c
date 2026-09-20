
#include <stdio.h>
#include <avr/io.h>

#include "i2c.h" 
#include "ADXL_345.h"

//----------------------------------------------------------
volatile unsigned char ADXL345_Flag = 0;


//----------------------------------------------------------
void ADXl345_INIT(void)
{
	i2cWrite(ADXL345_W, REG_MEASURE, VAR_START); // start measuring
	
	// write check
	if(i2cSingleRead(ADXL345_W, REG_MEASURE, 0xFF) != VAR_START) ADXL345_Flag = 0;
	else ADXL345_Flag = 1;
}

//----------------------------------------------------------
unsigned char ADXl345_INIT_Flag(void)
{
	return ADXL345_Flag;
}
