#include <avr/io.h>
#include "ITG-3200.h"
#include "RS232.h"
#define F_CPU 8000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "defs.h"
#include "i2c.h"



void ITG3200_INIT()
{
   	ITG3200Write(PWR_M, 0x80);	// Reset to defaults
	ITG3200Write(SMPL, 0x00);	// SMLPRT_DIV = 0
	ITG3200Write(DLPF, 0x18);	// DLPF_CFG = 0, FS_SEL = 3
	ITG3200Write(INT_C, 0x05);	// 
	ITG3200Write(PWR_M, 0x00);
}


char ITG3200Read(unsigned char address)
{
	char data;
	
	cbi(TWCR, TWEN);	// Disable TWI
	sbi(TWCR, TWEN);	// Enable TWI
	
	i2cSendStart();
	i2cWaitForComplete();
	
	i2cSendByte(ITG3200_W);	// write 0xD2
	i2cWaitForComplete();
	
	i2cSendByte(address);	// write register address
	i2cWaitForComplete();
	
	i2cSendStart();
	
	i2cSendByte(ITG3200_R);	// write 0xD3
	i2cWaitForComplete();
	i2cReceiveByte(FALSE);
	i2cWaitForComplete();
	
	data = i2cGetReceivedByte();	// Get MSB result
	i2cWaitForComplete();
	i2cSendStop();
	
	cbi(TWCR, TWEN);	// Disable TWI
	sbi(TWCR, TWEN);	// Enable TWI
	
	return data;
}

void ITG3200Write(unsigned char address, unsigned char data)
{
	i2cSendStart();
	i2cWaitForComplete();
	
	i2cSendByte(ITG3200_W);	// write 0xB4
	i2cWaitForComplete();
	
	i2cSendByte(address);	// write register address
	i2cWaitForComplete();
	
	i2cSendByte(data);
	i2cWaitForComplete();
	
	i2cSendStop();
}

void ITG3200ViewRegisters(void)
{
	
    sprintf(buf,"\nWHO_AM_I (0x00) : 0x%02x\r\n", ITG3200Read(WHO));   USART0_PutStr(buf); _delay_ms(100);
    sprintf(buf,"SMPLRT_DIV (0x15) : 0x%02x\r\n", ITG3200Read(SMPL));  USART0_PutStr(buf); _delay_ms(100);
    sprintf(buf,"DLPF_FS (0x16)    : 0x%02x\r\n", ITG3200Read(DLPF));  USART0_PutStr(buf); _delay_ms(100);
    sprintf(buf,"INT_CFG (0x17)    : 0x%02x\r\n", ITG3200Read(INT_C)); USART0_PutStr(buf); _delay_ms(100);
    sprintf(buf,"INT_STATUS (0x1A) : 0x%02x\r\n", ITG3200Read(INT_S)); USART0_PutStr(buf); _delay_ms(100);
    sprintf(buf,"TEMP_OUT_H (0x1B) : 0x%02x\r\n", ITG3200Read(TMP_H)); USART0_PutStr(buf); _delay_ms(100);
    sprintf(buf,"TEMP_OUT_L (0x1C) : 0x%02x\r\n", ITG3200Read(TMP_L)); USART0_PutStr(buf); _delay_ms(100);
    sprintf(buf,"TEMP_OUT_L (0x1C) : 0x%02x\r\n", ITG3200Read(TMP_L)); USART0_PutStr(buf); _delay_ms(100);
	sprintf(buf,"GYRO_XOUT_H (0x1D): 0x%02x\r\n", ITG3200Read(GX_H));  USART0_PutStr(buf); _delay_ms(100);
	sprintf(buf,"GYRO_XOUT_L (0x1E): 0x%02x\r\n", ITG3200Read(GX_L));  USART0_PutStr(buf); _delay_ms(100);
	sprintf(buf,"GYRO_YOUT_H (0x1F): 0x%02x\r\n", ITG3200Read(GY_H));  USART0_PutStr(buf); _delay_ms(100);
	sprintf(buf,"GYRO_YOUT_L (0x20): 0x%02x\r\n", ITG3200Read(GY_L));  USART0_PutStr(buf); _delay_ms(100);
	sprintf(buf,"GYRO_ZOUT_H (0x21): 0x%02x\r\n", ITG3200Read(GZ_H));  USART0_PutStr(buf); _delay_ms(100);
	sprintf(buf,"GYRO_ZOUT_L (0x22): 0x%02x\r\n", ITG3200Read(GZ_L));  USART0_PutStr(buf); _delay_ms(100);
	sprintf(buf,"PWR_MGM (0x3E)    : 0x%02x\r\n", ITG3200Read(PWR_M));  USART0_PutStr(buf); _delay_ms(100);
	_delay_ms(1000);

}


int checkInterrupt(void)
{
	if ((PIND & (1<<2)) == 0)
		return 0;
	else
		return 1;
}



