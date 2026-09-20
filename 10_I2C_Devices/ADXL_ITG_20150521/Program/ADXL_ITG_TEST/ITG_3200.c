
#include "i2c.h"
#include "ITG_3200.h"

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>

//----------------------------------------------------------
volatile unsigned char ITG3200_Flag = 0;

//------------------------------------------------------------------------------------------------
void ITG3200_INIT()
{
	unsigned char ucTemp[1] = {0x00};
	
   	i2c_SingleByteWrite(ITG3200_ADDRESS, ITG3200_REG_PWR_M, ITG3200_VAR_RESET);			// Reset to defaults
	_delay_ms(1);
	i2c_SingleByteWrite(ITG3200_ADDRESS, ITG3200_REG_SMPL, ITG3200_VAR_SMLPRT);			// SMLPRT_DIV = 0
	i2c_SingleByteWrite(ITG3200_ADDRESS, ITG3200_REG_DLPF, ITG3200_VAR_DLPF);			// DLPF_CFG = 0, FS_SEL = 3
	i2c_SingleByteWrite(ITG3200_ADDRESS, ITG3200_REG_INT_C, ITG3200_VAR_INT);	
	i2c_SingleByteWrite(ITG3200_ADDRESS, ITG3200_REG_PWR_M, ITG3200_VAR_PWON);	
	
	// write check
	i2c_ByteRead(ITG3200_ADDRESS, ITG3200_REG_SMPL, ucTemp, 1);		
	if(ucTemp[0] != ITG3200_VAR_SMLPRT) return;

	i2c_ByteRead(ITG3200_ADDRESS, ITG3200_REG_DLPF, ucTemp, 1);	
	if(ucTemp[0] != ITG3200_VAR_DLPF) return;

	i2c_ByteRead(ITG3200_ADDRESS, ITG3200_REG_INT_C, ucTemp, 1);	
	if(ucTemp[0] != ITG3200_VAR_INT) return;		
			
	i2c_ByteRead(ITG3200_ADDRESS, ITG3200_REG_PWR_M, ucTemp, 1);					
	if(ucTemp[0] != ITG3200_VAR_PWON) return;		
			
	ITG3200_Flag = 1;
}

//----------------------------------------------------------
unsigned char ITG3200_INIT_Flag(void)
{
	return ITG3200_Flag;
}

//------------------------------------------------------------------------
unsigned char ITG3200_ReadXYZ(int* X, int* Y, int* Z)
{
    unsigned char temp[1] = {0x00};
	unsigned char Value[6] = {0x00, };
	unsigned char status = 0;
		
	register unsigned char i;
	
	int gyrox = 0;
	int gyroy = 0;
	int gyroz = 0;
	
	for (i = 0; i < ITG3200_NUMOFSAMPLE; i++)
	{
		do 
		{
			status = i2c_ByteRead(ITG3200_ADDRESS, ITG3200_REG_INT_S, temp, 1);
		} while (!(temp[0] & 0x01) && (status == 1));		
		
		
		status = i2c_ByteRead(ITG3200_ADDRESS, ITG3200_REG_GX_H, Value, 6); 
		
		gyrox += (Value[0] << 8) | Value[1];
		gyroy += (Value[2] << 8) | Value[3];
		gyroz += (Value[4] << 8) | Value[5];
	}
	
	*X = gyrox/ITG3200_NUMOFSAMPLE;
	*Y = gyroy/ITG3200_NUMOFSAMPLE;
	*Z = gyroz/ITG3200_NUMOFSAMPLE;
	
	return status;
}
