

#include "eeprom.h"

#include <avr/eeprom.h>


//------------------------------------------------------------------------
unsigned char EEPROM_Read_char(unsigned int address)
{
	eeprom_busy_wait();	
	return eeprom_read_byte((uint8_t *) address);
}

//------------------------------------------------------------------------
unsigned char EEPROM_Write_char(unsigned char ucValue, unsigned int address)
{
	register unsigned char i;
	unsigned char uctemp;
	
			
	for(i = 0; i < EEPROM_MAXCNT; i++) {
		eeprom_busy_wait();		
		uctemp = EEPROM_Read_char(address);
		
		if(ucValue == uctemp) return 1;
		
		eeprom_busy_wait();		
		eeprom_write_byte((uint8_t *) address, ucValue);
	}
	
	return 0;
}	
//------------------------------------------------------------------------
unsigned char EEPROM_Write_int(unsigned int ucValue, unsigned int address)
{
	register unsigned char i;
	unsigned int uctemp;
	
	for(i = 0; i < EEPROM_MAXCNT; i++) {
		eeprom_busy_wait();	
		uctemp = EEPROM_Read_int(address);
		
		if(ucValue == uctemp) return 1;
			
		eeprom_busy_wait();	
		eeprom_write_block(&ucValue, (void *) address, 2);
	}	
	
	return 0;
}
	
//------------------------------------------------------------------------
unsigned int EEPROM_Read_int(unsigned int address)
{
	unsigned int uitemp = 0;
	
	eeprom_busy_wait();
	eeprom_read_block(&uitemp, (void *)address, 2);
	
	return uitemp;
}
