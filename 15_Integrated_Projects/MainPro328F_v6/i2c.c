#include "AT328.h"
#include "types.h"
#include "defs.h"
#include "i2c.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


//----------------------------------------------------------
void i2cInit(void)
{
	// set i2c bit rate to 40KHz
	i2cSetBitrate(40);
	// enable TWI (two-wire interface)
	sbi(TWCR, TWEN);	// Enable TWI
}

//----------------------------------------------------------
void i2cSetBitrate(unsigned short bitrateKHz)
{
	unsigned char bitrate_div;
	// set i2c bitrate
	// SCL freq = F_CPU/(16+2*TWBR))
	cbi(TWSR, TWPS0);
	cbi(TWSR, TWPS1);
	
	//calculate bitrate division	
	bitrate_div = ((F_CPU/4000l)/bitrateKHz);
	if(bitrate_div >= 16)
		bitrate_div = (bitrate_div-16)/2;
	outb(TWBR, bitrate_div);
}

//----------------------------------------------------------
void i2cSendStart(void)
{
	WRITE_sda();
	// send start condition
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
}

//----------------------------------------------------------
void i2cSendStop(void)
{
	// transmit stop condition
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

//----------------------------------------------------------
unsigned char i2cWaitForComplete(void)
{
	volatile register int i = 0;		//time out variable
	
	// wait for i2c interface to complete operation
    while ((!(TWCR & (1<<TWINT))) && (i < 90))
		i++;
		
	if(i == 90) return 1;
	else return 0;
}

//----------------------------------------------------------
void i2cSendByte(unsigned char data)
{
	delay_ms(1);

	WRITE_sda();
	
	// save data to the TWDR
	TWDR = data;
	
	// begin send
	TWCR = (1<<TWINT)|(1<<TWEN);
}

//----------------------------------------------------------
void i2cReceiveByte(unsigned char ackFlag)
{	
	// begin receive over i2c
	if( ackFlag )
	{
		// ackFlag = TRUE: ACK the recevied data
		outb(TWCR, (inb(TWCR)&TWCR_CMD_MASK)|BV(TWINT)|BV(TWEA));
	}
	else
	{
		// ackFlag = FALSE: NACK the recevied data
		outb(TWCR, (inb(TWCR)&TWCR_CMD_MASK)|BV(TWINT));
	}
}

//----------------------------------------------------------
unsigned char i2cGetReceivedByte(void)
{
	// retieve received data byte from i2c TWDR
	return( inb(TWDR) );
}

//----------------------------------------------------------
unsigned char i2cGetStatus(void)
{
	// retieve current i2c status from i2c TWSR
	return( inb(TWSR) );
}

//----------------------------------------------------------
void delay_ms(unsigned int x)
{
  volatile register uint8_t y, z;
  for ( ; x > 0 ; x--){
    for ( y = 0 ; y < 90 ; y++){
      for ( z = 0 ; z < 6 ; z++){
        asm volatile ("nop");
      }
    }
  }
}


//-----------------------------------------------------------------------
void i2cWrite(unsigned char ucDeviceAddress, unsigned char address, unsigned char data)
{
	i2cSendStart();
	if(i2cWaitForComplete()) {i2cSendStop(); return;};
	
	i2cSendByte(ucDeviceAddress);	
	if(i2cWaitForComplete()) {i2cSendStop(); return;};
	
	i2cSendByte(address);	// write register address
	if(i2cWaitForComplete()) {i2cSendStop(); return;};
	
	i2cSendByte(data);
	if(i2cWaitForComplete()) {i2cSendStop(); return;};
	
	i2cSendStop();
}

//-----------------------------------------------------------------------------------------------
char i2cSingleRead(unsigned char ucDeviceAddress, unsigned char address, char ucCurrent)
{
	char data;
	
	cbi(TWCR, TWEN);	// Disable TWI
	sbi(TWCR, TWEN);	// Enable TWI
	
	i2cSendStart();
	if(i2cWaitForComplete()) {i2cSendStop(); return ucCurrent;};
	
	i2cSendByte(ucDeviceAddress);	
	if(i2cWaitForComplete()) {i2cSendStop(); return ucCurrent;};
	
	i2cSendByte(address);	// write register address
	if(i2cWaitForComplete()) {i2cSendStop(); return ucCurrent;};
	
	i2cSendStart();
	
	i2cSendByte(ucDeviceAddress+1);	
	if(i2cWaitForComplete()) {i2cSendStop(); return ucCurrent;};
	
	i2cReceiveByte(0);
	if(i2cWaitForComplete()) {i2cSendStop(); return ucCurrent;};
	
	data = i2cGetReceivedByte();	// Get MSB result
	if(i2cWaitForComplete()) {i2cSendStop(); return ucCurrent;};
	i2cSendStop();
	
	cbi(TWCR, TWEN);	// Disable TWI
	sbi(TWCR, TWEN);	// Enable TWI
	
	return data;
}

//-------------------------------------------------------------------------------------------
int i2cMultipleRead(unsigned char ucDeviceAddress, unsigned char address, int iCurrent)
{
	int data = 0;
	
	cbi(TWCR, TWEN);	// Disable TWI
	sbi(TWCR, TWEN);	// Enable TWI
	
	i2cSendStart();
	if(i2cWaitForComplete()) {i2cSendStop(); return iCurrent;};
	
	i2cSendByte(ucDeviceAddress);	
	if(i2cWaitForComplete()) {i2cSendStop(); return iCurrent;};
	
	i2cSendByte(address);	// write register address
	if(i2cWaitForComplete()) {i2cSendStop(); return iCurrent;};
	
	i2cSendStart();
	
	i2cSendByte(ucDeviceAddress+1);	
	if(i2cWaitForComplete()) {i2cSendStop(); return iCurrent;};
	
	i2cReceiveByte(1);
	if(i2cWaitForComplete()) {i2cSendStop(); return iCurrent;};
	
	data = i2cGetReceivedByte();	// Get MSB result
	if(i2cWaitForComplete()) {i2cSendStop(); return iCurrent;};
	
	WRITE_sda();
	
	data += i2cGetReceivedByte();	// Get MSB result
	if(i2cWaitForComplete()) {i2cSendStop(); return iCurrent;};
		
	i2cSendStop();
	
	cbi(TWCR, TWEN);	// Disable TWI
	sbi(TWCR, TWEN);	// Enable TWI
	
	return data;
}