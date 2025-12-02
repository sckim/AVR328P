#ifndef _AT328_H_
#define _AT328_H_

//-----------------------------------------------------------------------------
//#define F_CPU 8000000

#define ADD_BAUD_RATE		0x00	// Baud rate address
#define ADD_SERIAL_HIGH		0x04	// Serial code high address
#define ADD_SERIAL_LOW		0x06	// Serial code low address
#define ADD_CALI_X			0x10	// X calibration
#define ADD_CALI_Y			0x12	// Y calibration
#define ADD_CALI_Z			0x14	// Z calibration

#define NumofSample			1

//-----------------------------------------------------------------------------
extern void Update_BaudRate(unsigned char *Buff);
extern void Update_SerialCode(unsigned char ucPos, unsigned char *Buff);
extern void Update_Calibration(unsigned char *Buff);
extern void Update_Send(unsigned char *Buff);
extern void Send_Serial(void);
extern void Goto_Sleep(void);

//-----------------------------------------------------------------------------

#endif /* _AT328_H_ */
