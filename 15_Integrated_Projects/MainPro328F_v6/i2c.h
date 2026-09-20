
#ifndef _I2C_H_
#define _I2C_H_

// TWSR values (not bits)
// Master
#define TW_START					0x08
#define TW_REP_START				0x10

// Master Transmitter
#define TW_MT_SLA_ACK				0x18
#define TW_MT_SLA_NACK				0x20
#define TW_MT_DATA_ACK				0x28
#define TW_MT_DATA_NACK				0x30
#define TW_MT_ARB_LOST				0x38

// Master Receiver
#define TW_MR_ARB_LOST				0x38
#define TW_MR_SLA_ACK				0x40
#define TW_MR_SLA_NACK				0x48
#define TW_MR_DATA_ACK				0x50
#define TW_MR_DATA_NACK				0x58

// Slave Transmitter
#define TW_ST_SLA_ACK				0xA8
#define TW_ST_ARB_LOST_SLA_ACK		0xB0
#define TW_ST_DATA_ACK				0xB8
#define TW_ST_DATA_NACK				0xC0
#define TW_ST_LAST_DATA				0xC8

// Slave Receiver
#define TW_SR_SLA_ACK				0x60
#define TW_SR_ARB_LOST_SLA_ACK		0x68
#define TW_SR_GCALL_ACK				0x70
#define TW_SR_ARB_LOST_GCALL_ACK	0x78
#define TW_SR_DATA_ACK				0x80
#define TW_SR_DATA_NACK				0x88
#define TW_SR_GCALL_DATA_ACK		0x90
#define TW_SR_GCALL_DATA_NACK		0x98
#define TW_SR_STOP					0xA0

// Misc
#define TW_NO_INFO					0xF8
#define TW_BUS_ERROR				0x00

// defines and constants
#define TWCR_CMD_MASK		0x0F
#define TWSR_STATUS_MASK	0xF8

// return values
#define I2C_OK				0x00
#define I2C_ERROR_NODEV		0x01

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

#define WRITE_sda() DDRC = DDRC | 0b00010000 //SDA must be output when writing
#define READ_sda()  DDRC = DDRC & 0b11101111 //SDA must be input when reading - don't forget the resistor on SDA!!

//--------------------------------------------------------------------------------------------------------------
// functions

//! Initialize I2C (TWI) interface
extern void i2cInit(void);

//! Set the I2C transaction bitrate (in KHz)
extern void i2cSetBitrate(unsigned short bitrateKHz);

// Low-level I2C transaction commands 
//! Send an I2C start condition in Master mode
extern void i2cSendStart(void);

//! Send an I2C stop condition in Master mode
extern void i2cSendStop(void);

//! Wait for current I2C operation to complete
extern unsigned char i2cWaitForComplete(void);

//! Send an (address|R/W) combination or a data byte over I2C
extern void i2cSendByte(unsigned char data);

//! Receive a data byte over I2C  
// ackFlag = TRUE if recevied data should be ACK'ed
// ackFlag = FALSE if recevied data should be NACK'ed
extern void i2cReceiveByte(unsigned char ackFlag);

//! Pick up the data that was received with i2cReceiveByte()
extern unsigned char i2cGetReceivedByte(void);

//! Get current I2c bus status from TWSR
extern unsigned char i2cGetStatus(void);

//void delay_ms(uint16_t x);
extern void delay_ms(unsigned int x);

// high-level I2C transaction commands
//! send I2C data to a device on the bus (non-interrupt based)
extern unsigned char i2cMasterSendNI(unsigned char deviceAddr, unsigned char length, unsigned char* data);

//! receive I2C data from a device on the bus (non-interrupt based)
extern unsigned char i2cMasterReceiveNI(unsigned char deviceAddr, unsigned char length, unsigned char *data);

// I2C write single data
extern void i2cWrite(unsigned char ucDeviceAddress, unsigned char address, unsigned char data);

// I2C read single data
extern char i2cSingleRead(unsigned char ucDeviceAddress, unsigned char address, char ucCurrent);

// I2C read multiple data
extern int i2cMultipleRead(unsigned char ucDeviceAddress, unsigned char address, int iCurrent);

#endif /* _I2C_H_ */
