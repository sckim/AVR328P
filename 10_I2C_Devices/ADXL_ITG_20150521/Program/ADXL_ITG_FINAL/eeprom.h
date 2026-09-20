
#ifndef EEPROM_H_
#define EEPROM_H_


#define EEPROM_MAXCNT	3

//-----------------------------------------------------------------------------
extern unsigned char EEPROM_Read_char(unsigned int address);
extern unsigned char EEPROM_Write_char(unsigned char ucValue, unsigned int address);
extern unsigned char EEPROM_Write_int(unsigned int ucValue, unsigned int address);
extern unsigned int EEPROM_Read_int(unsigned int address);


#endif /* EEPROM_H_ */
