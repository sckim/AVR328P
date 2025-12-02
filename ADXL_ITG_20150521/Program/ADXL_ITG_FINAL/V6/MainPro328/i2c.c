
#include "i2c.h"
#include "main.h"

#include <stdio.h> 
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//----------------------------------------------------------
void i2cInit(void)
{
	cbi(TWSR, TWPS0);
	cbi(TWSR, TWPS1);
    TWBR = 32;  //SCL : 100KHZ
}

//-----------------------------------------------------------------------
void i2c_error(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);	// stop
	
	//printf("error\r\n");
}

//-----------------------------------------------------------------------
unsigned char i2c_SingleByteWrite(unsigned char address, unsigned char reg_address, unsigned char data)
{
	register unsigned int cnt;
	
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);	// start
	
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait	
		
	if (((TWSR & 0xF8) != TW_START) || (cnt == 0)) {i2c_error(); return 0;};	
		
		
	TWDR = address; TWCR = (1<<TWINT) | (1<<TWEN);	// send address
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait		
	
	if (((TWSR & 0xF8) != TW_MT_SLA_ACK) || (cnt == 0)) {i2c_error(); return 0;};	
	
	
	TWDR = reg_address; TWCR = (1<<TWINT) | (1<<TWEN);	// send register address
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait		
	
	if (((TWSR & 0xF8) != TW_MT_DATA_ACK) || (cnt == 0)) {i2c_error(); return 0;};	
		

	TWDR = data; TWCR = (1<<TWINT) | (1<<TWEN);	// send data
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait		
	
	if (((TWSR & 0xF8) != TW_MT_DATA_ACK) || (cnt == 0)) {i2c_error(); return 0;};						

		
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);	// stop		
	
	return 1;			
}	

//-----------------------------------------------------------------------
unsigned char i2c_ByteWrite(unsigned char address, unsigned char reg_address, unsigned char* data, unsigned char size)
{
	register unsigned char i;
	register unsigned int cnt;
	
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);	// start
	
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait	
		
	if (((TWSR & 0xF8) != TW_START) || (cnt == 0)) {i2c_error(); return 0;};	
		
		
	TWDR = address; TWCR = (1<<TWINT) | (1<<TWEN);	// send address
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait		
	
	if (((TWSR & 0xF8) != TW_MT_SLA_ACK) || (cnt == 0)) {i2c_error(); return 0;};	
	
	
	TWDR = reg_address; TWCR = (1<<TWINT) | (1<<TWEN);	// send register address
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait		
	
	if (((TWSR & 0xF8) != TW_MT_DATA_ACK) || (cnt == 0)) {i2c_error(); return 0;};	
		
			
	
	for(i = 0; i < size; i++)
	{
		TWDR = data[i]; TWCR = (1<<TWINT) | (1<<TWEN);	// send data
	
		cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait		
	
		if (((TWSR & 0xF8) != TW_MT_DATA_ACK) || (cnt == 0)) {i2c_error(); return 0;};						
	}

		
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);	// stop		
	
	return 1;			
}	

//-----------------------------------------------------------------------
unsigned char i2c_ByteRead(unsigned char address, unsigned char reg_address, unsigned char* data, unsigned char size)
{
	register unsigned char i;
	register unsigned int cnt;
	
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);	// start
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait	
		
	if (((TWSR & 0xF8) != TW_START) || (cnt == 0)) {i2c_error(); return 0;};	
		
	TWDR = address;	TWCR = (1<<TWINT) | (1<<TWEN);	// send address
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait		
	
	if (((TWSR & 0xF8) != TW_MT_SLA_ACK) || (cnt == 0)) {i2c_error(); return 0;};	
	
	TWDR = reg_address;	TWCR = (1<<TWINT) | (1<<TWEN);	// send register address
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait		
	
	if (((TWSR & 0xF8) != TW_MT_DATA_ACK) || (cnt == 0)) {i2c_error(); return 0;};		
		
	
	
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);	// repeat start
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait	
		
	if (((TWSR & 0xF8) != TW_REP_START) || (cnt == 0)) {i2c_error(); return 0;};	
		
				
	TWDR = address+1; TWCR = (1<<TWINT) | (1<<TWEN);	// send address
	
	cnt = I2C_MAXCNT; while ((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {}; 	// wait		
	
	if (((TWSR & 0xF8) != TW_MR_SLA_ACK) || (cnt == 0)) {i2c_error(); return 0;};	
		
	for(i = 0; i < size; i++)
	{  
		if(i == (size-1)) 
		{
			TWCR = (1<<TWINT) | (1<<TWEN);				// send NACK
			cnt = I2C_MAXCNT; while((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {};	
			if(((TWSR & 0xF8) != TW_MR_DATA_NACK) || (cnt == 0)) { i2c_error(); return 0;};		
		}			
		else 
		{
			TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);	// send ACK
			cnt = I2C_MAXCNT; while((!(TWCR & (1<<TWINT))) && (cnt-- > 0)) {};	
			if(((TWSR & 0xF8) != TW_MR_DATA_ACK) || (cnt == 0)) { i2c_error(); return 0;};							
		}		
		
		*(data+i) = TWDR;
	}					
		
		
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);	// stop		
			
	return 1;		
}	