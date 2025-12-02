#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "i2c.h"
#include "ITG_3200.h"
#include "types.h"
#include "defs.h"

//----------------------------------------------------------
volatile unsigned char ITG3200_Flag = 0;

//------------------------------------------------------------------------------------------------
void ITG3200_INIT()
{
   	i2cWrite(ITG3200_W, REG_PWR_M, VAR_RESET);	// Reset to defaults
	i2cWrite(ITG3200_W, REG_SMPL, VAR_SMLPRT);	// SMLPRT_DIV = 0
	i2cWrite(ITG3200_W, REG_DLPF, VAR_DLPF);	// DLPF_CFG = 0, FS_SEL = 3
	i2cWrite(ITG3200_W, REG_INT_C, VAR_INT);	
	i2cWrite(ITG3200_W, REG_PWR_M, VAR_PWON);
	
	// write check
	if(i2cSingleRead(ITG3200_W, REG_SMPL, 0xFF) != VAR_SMLPRT) return;

	if(i2cSingleRead(ITG3200_W, REG_DLPF, 0xFF) != VAR_DLPF) return;

	if(i2cSingleRead(ITG3200_W, REG_INT_C, 0xFF) != VAR_INT) return;			
			
				
	if(i2cSingleRead(ITG3200_W, REG_PWR_M, 0xFF) != VAR_PWON) return;
			
	ITG3200_Flag = 1;
}

//----------------------------------------------------------
unsigned char ITG3200_INIT_Flag(void)
{
	return ITG3200_Flag;
}

