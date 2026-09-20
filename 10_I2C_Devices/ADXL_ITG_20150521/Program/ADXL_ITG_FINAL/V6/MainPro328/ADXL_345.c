
#include "ADXL_345.h"
#include "i2c.h" 

#include <stdio.h> 
#include <math.h>

//----------------------------------------------------------
_ADXL345_REG ADXL345_REG;
volatile unsigned char ADXL345_Flag = 0;

//----------------------------------------------------------
void ADXl345_INIT(void)
{
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_POWER_CTL, ADXL345_VAR_STOP); // stop measuring
		
	ADXL345_REG.THRESH_TAP = 0;				// Tap threshold 
	ADXL345_REG.OFSX = 0;
	ADXL345_REG.OFSY = 0;
	ADXL345_REG.OFSZ = 0;		
	ADXL345_REG.DUR = 0;
	ADXL345_REG.Latent = 0;
	ADXL345_REG.Window = 0;
	ADXL345_REG.THRESH_ACT = 0;
	ADXL345_REG.THRESH_INACT = 0;
	ADXL345_REG.TIME_INACT = 0;
	
	ADXL345_REG.BW_RATE.all = 0b00001010;
	ADXL345_REG.INT_SOURCE.all = 0b00000010;	
	ADXL345_REG.DATA_FORMAT.bit.Justify = 0;
	
	ADXl345_Write();	
}

//----------------------------------------------------------
unsigned char ADXl345_INIT_Flag(void)
{
	return ADXL345_Flag;
}

//----------------------------------------------------------
void ADXl345_Write(void)
{
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_THRESH_TAP, ADXL345_REG.THRESH_TAP);
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_OFSX, ADXL345_REG.OFSX);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_OFSY, ADXL345_REG.OFSY);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_OFSZ, ADXL345_REG.OFSZ);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_DUR, ADXL345_REG.DUR);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_LATENT, ADXL345_REG.Latent);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_WINDOW, ADXL345_REG.Window);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_THRESH_ACT, ADXL345_REG.THRESH_ACT);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_THRESH_INACT, ADXL345_REG.THRESH_INACT);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_TIME_INACT, ADXL345_REG.TIME_INACT);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_ACT_INACT_CTL, ADXL345_REG.ACT_INACT_CTL.all);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_THRESH_FF, ADXL345_REG.THRESH_FF);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_TIME_FF, ADXL345_REG.TIME_FF);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_TAP_AXES, ADXL345_REG.TAP_AXES.all);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_BW_RATE, ADXL345_REG.BW_RATE.all);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_POWER_CTL, ADXL345_REG.POWER_CTL.all);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_INT_ENABLE, ADXL345_REG.INT_ENABLE.all);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_INT_MAP, ADXL345_REG.INT_MAP.all);		
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_DATA_FORMAT, ADXL345_REG.DATA_FORMAT.all);	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_FIFO_CTL, ADXL345_REG.FIFO_CTL.all);			
	
	i2c_SingleByteWrite(ADXL345_ADDRESS, ADXL345_POWER_CTL, ADXL345_VAR_START); // start measuring		
	// write check
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_POWER_CTL, &ADXL345_REG.POWER_CTL.all, 1);
	if(ADXL345_REG.POWER_CTL.all != ADXL345_VAR_START) ADXL345_Flag = 0;
	else ADXL345_Flag = 1;										
}	

//----------------------------------------------------------
void ADXl345_ReadAll(void)
{
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_DEVID, &ADXL345_REG.DEVID, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_THRESH_TAP, &ADXL345_REG.THRESH_TAP, 1); 	
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_OFSX, &ADXL345_REG.OFSX, 1); 	
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_OFSY, &ADXL345_REG.OFSY, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_OFSZ, &ADXL345_REG.OFSZ, 1); 	
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_DUR, &ADXL345_REG.DUR, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_LATENT, &ADXL345_REG.Latent, 1); 	
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_WINDOW, &ADXL345_REG.Window, 1); 	
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_THRESH_ACT, &ADXL345_REG.THRESH_ACT, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_THRESH_INACT, &ADXL345_REG.THRESH_INACT, 1); 	
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_TIME_INACT, &ADXL345_REG.THRESH_INACT, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_ACT_INACT_CTL, &ADXL345_REG.ACT_INACT_CTL.all, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_THRESH_FF, &ADXL345_REG.THRESH_FF, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_TIME_FF, &ADXL345_REG.TIME_FF, 1); 		
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_TAP_AXES, &ADXL345_REG.TAP_AXES.all, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_ACT_TAP_STATUS, &ADXL345_REG.ACT_TAP_STATUS.all, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_BW_RATE, &ADXL345_REG.BW_RATE.all, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_POWER_CTL, &ADXL345_REG.POWER_CTL.all, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_INT_ENABLE, &ADXL345_REG.INT_ENABLE.all, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_INT_MAP, &ADXL345_REG.INT_MAP.all, 1); 
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_INT_SOURCE, &ADXL345_REG.INT_SOURCE.all, 1); 						
	i2c_ByteRead(ADXL345_ADDRESS, ADXL345_DATA_FORMAT, &ADXL345_REG.DATA_FORMAT.all, 1); 
	
							
	printf("ADXL345_DEVID: 0X%02X\r\n", ADXL345_REG.DEVID);	
	printf("ADXL345_THRESH_TAP: 0X%02X\r\n", ADXL345_REG.THRESH_TAP);
	printf("ADXL345_OFSX: 0X%02X\r\n", ADXL345_REG.OFSX);
	printf("ADXL345_OFSY: 0X%02X\r\n", ADXL345_REG.OFSY);
	printf("ADXL345_OFSZ: 0X%02X\r\n", ADXL345_REG.OFSZ);
	printf("ADXL345_DUR: 0X%02X\r\n", ADXL345_REG.DUR);
	printf("ADXL345_LATENT: 0X%02X\r\n", ADXL345_REG.Latent);
	printf("ADXL345_WINDOW: 0X%02X\r\n", ADXL345_REG.Window);
	printf("ADXL345_THRESH_ACT: 0X%02X\r\n", ADXL345_REG.THRESH_ACT);
	printf("ADXL345_THRESH_INACT: 0X%02X\r\n", ADXL345_REG.THRESH_INACT);
	printf("ADXL345_TIME_INACT: 0X%02X\r\n", ADXL345_REG.TIME_INACT);	
	printf("ADXL345_ACT_INACT_CTL: 0X%02X\r\n", ADXL345_REG.ACT_INACT_CTL.all);
	printf("ADXL345_THRESH_FF: 0X%02X\r\n", ADXL345_REG.THRESH_FF);
	printf("ADXL345_TIME_FF: 0X%02X\r\n", ADXL345_REG.TIME_FF);
	printf("ADXL345_TAP_AXES: 0X%02X\r\n", ADXL345_REG.TAP_AXES.all);
	printf("ADXL345_ACT_TAP_STATUS: 0X%02X\r\n", ADXL345_REG.ACT_TAP_STATUS.all);	
	printf("ADXL345_BW_RATE: 0X%02X\r\n", ADXL345_REG.BW_RATE.all);
	printf("ADXL345_POWER_CTL: 0X%02X\r\n", ADXL345_REG.POWER_CTL.all);	
	printf("ADXL345_INT_ENABLE: 0X%02X\r\n", ADXL345_REG.INT_ENABLE.all);		
	printf("ADXL345_INT_MAP: 0X%02X\r\n", ADXL345_REG.INT_MAP.all);	
	printf("ADXL345_INT_SOURCE: 0X%02X\r\n", ADXL345_REG.INT_SOURCE.all);		
	printf("ADXL345_DATA_FORMAT: 0X%02X\r\n", ADXL345_REG.DATA_FORMAT.all);															
}	

//----------------------------------------------------------
unsigned char ADXl345_ReadXYZ(int* X, int* Y, int* Z)
{
	unsigned char ucTemp[6] = {0x00, };
	unsigned char status;	
		
	status = i2c_ByteRead(ADXL345_ADDRESS, ADXL345_DATAX0, ucTemp, 6); 	
	
	*X = ucTemp[0] | (ucTemp[1] << 8);	
	*Y = ucTemp[2] | (ucTemp[3] << 8);	
	*Z = ucTemp[4] | (ucTemp[5] << 8);	
		
	return status;
}	

//----------------------------------------------------------
unsigned char ADXl345_Angle(float* X_ang, float* Y_ang, float* Z_ang)
{
	int X, Y, Z;	
	unsigned char status;	
		
	status = ADXl345_ReadXYZ(&X, &Y, &Z);
	
	*X_ang = atan((float)X/sqrt((float)Y*Y + (float)Z*Z))*57.2958;
	*Y_ang = atan((float)Y/sqrt((float)X*X + (float)Z*Z))*57.2958;
	*Z_ang = atan((float)Z/sqrt((float)X*X + (float)Y*Y))*57.2958;	
		
	return status;
}