#ifndef _SERIAL_H_
#define _SERIAL_H_

//-----------------------------------------------------------------------------
extern void UART0_Init(unsigned char Index);

extern int UART0_PutChar(char c);	// Send a character through UART 
extern int UART0_GetChar(void);

extern void UART0_Rx_Buf_Clear(void);
extern unsigned char Get_UART0_Flag(void);
extern void UART0_Parsing(void);
extern void UART0_PutStr(unsigned char *Buff, unsigned char ucSize);
extern void UART0_RxReturn(void);

//-----------------------------------------------------------------------------
#define	BUFF_SIZE		10

// Type Define
#define   BAUD_2400     207
#define   BAUD_4800     103
#define   BAUD_9600      51
#define   BAUD_14400     34
#define   BAUD_19200     25
#define   BAUD_28800     16
#define   BAUD_38400     12
#define   BAUD_57600      8
#define   BAUD_76800      6
#define   BAUD_115200     3

#endif		/* _SERIAL_H_ */
//------------------------------------------------------------------------------------------------
// End of File