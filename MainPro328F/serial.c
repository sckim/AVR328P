
/*
*******************************************************************************
Include Part
*******************************************************************************
*/
#include "AT328.h"
#include "serial.h"

#include <avr/io.h>
#include <stdio.h> 
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

//-----------------------------------------------------------------------------
volatile unsigned char Rx_Buff[BUFF_SIZE] = {0x00, };

unsigned int UART0_head = 0;
unsigned char UART0_flag = 0;

//-----------------------------------------------------------------------------
void UART0_Init(unsigned char Index)
{
	unsigned int bps;
	
	switch(Index) {
		case 1:
			bps = BAUD_2400;			
			break;
			
		case 2:
			bps = BAUD_4800;			
			break;		
			
		case 3:
			bps = BAUD_9600;			
			break;

		case 4:
			bps = BAUD_14400;			
			break;

		case 5:
			bps = BAUD_19200;			
			break;
				
		case 6:
			bps = BAUD_28800;			
			break;

		case 7:
			bps = BAUD_38400;			
			break;
			
		case 8:
			bps = BAUD_57600;			
			break;

/*
		case 9:
			bps = BAUD_76800;			
			break;
		
		case 10:
			bps = BAUD_115200;			
			break;
			
			*/																								
		default:
			bps = BAUD_9600;	
			break;				
	}
	
	UBRR0H = (unsigned char) ( bps >> 8 );
	UBRR0L = (unsigned char) bps;        		// Baud rate
	UCSR0B = 0x18;                              // Rx/Tx enable, 8 data,
	UCSR0B |= ( 1<< 7 );

	UCSR0C = 0x06;                              // 비동기식, 패리티금지, 스탑비트1개, 8비트데이타전송
          

	fdevopen(UART0_PutChar, NULL);				// Set UART0 for printf	
	
	UART0_Rx_Buf_Clear();	
}

//--------------------------------------------------------------------------------------------------
SIGNAL(USART_RX_vect)     
{
	register unsigned char ucValue = 0;
	
	ucValue = UDR0;	
	
	if(UART0_flag == 0)
	{
		Rx_Buff[UART0_head++] = ucValue;
		
		if(ucValue == 0x50) UART0_flag = 1;		// Check ASCII "P"
		
		if (UART0_head > BUFF_SIZE)	UART0_head = 0;	
		
		if(Rx_Buff[0] != 'S') UART0_Rx_Buf_Clear();	
		//UART0_PutChar(ucValue);
	}
}

//------------------------------------------------------------------------
unsigned char Get_UART0_Flag(void)
{
	return UART0_flag;
}

//------------------------------------------------------------------------------------------------
void Power_Off(void)
{
	PORTB = 0x00;
	PORTD = 0x00;
}
		
//------------------------------------------------------------------------
void UART0_Parsing(void)
{	
	// ASCII "S" check
	if(Rx_Buff[0] != 0x053)
	{
		UART0_Rx_Buf_Clear();
		return;		
	}
	
	// Second ASCII check
	switch(Rx_Buff[1]) {
		case 'M': //0x4D:	
			if(UART0_head != 7) break;		// Length check
		
			if(Rx_Buff[3] == 'E')			// 0x45:E, "SMTESTP"
				printf("SMTESTP\n");	
			else							// "SMT001P"
				Update_BaudRate((unsigned char*)Rx_Buff);
			break;
			
		case 0x39:	// "S9900P"
			if(UART0_head != 6) break;		// Length check
			
			Send_Serial();
			break;
			
		case 0x45:	// "E"
			if(UART0_head != 6) break;		// Length check
		
			if(Rx_Buff[2] == 0x48)	Update_SerialCode(1, (unsigned char*)Rx_Buff);		// Update serial code high
			else if(Rx_Buff[2] == 0x4C) Update_SerialCode(0, (unsigned char*)Rx_Buff);	// Update serial code low
			else if(Rx_Buff[2] == 0x43) Update_Calibration((unsigned char*)Rx_Buff);	// Update calibration		
			break;	
			
		case 0x30:	// "0"
			if(UART0_head != 4) break;		// Length check
			
			Update_Send((unsigned char*)Rx_Buff);			
			break;		
			
		case 0x31:	// "1"
			if(UART0_head != 4) break;		// Length check
			
			Update_Send((unsigned char*)Rx_Buff);
			break;		
			
		case 0x32:	// "2"
			if(UART0_head != 4) break;		// Length check
			
			UART0_RxReturn();		// Return Rx
			_delay_ms(10);
			
			Power_Off();		
			break;										
	}
	
	UART0_Rx_Buf_Clear();
}

		
//------------------------------------------------------------------------
void UART0_Rx_Buf_Clear(void)
{
	UART0_head = 0;
	UART0_flag = 0;
}

//------------------------------------------------------------------------------------------------
void UART0_RxReturn(void)
{
	register unsigned char i;
	
	for(i = 0; i < UART0_head; i++)	
		UART0_PutChar(Rx_Buff[i]);
}

		
/*
********************************************************************************
*              WRITE A CHARACTER
*
* Description : This function sends a character through UART.
* Arguments   : c - is a character to write
* Returns     : None
* Note        : 
********************************************************************************
*/

int UART0_PutChar(char c)
{
	register unsigned int uctemp = 0;
	
	while (((UCSR0A>>UDRE0) & 0x01) == 0) {
		if(uctemp++ > 10000) break;
	}

	UDR0 = c;

	return (1);
}

//------------------------------------------------------------------------------------------------
int UART0_GetChar(void)
{
	return (Rx_Buff[UART0_head-1]);
}

//------------------------------------------------------------------------------------------------
void UART0_PutStr(unsigned char *Buff, unsigned char ucSize)
{
	register unsigned char i;
	
	for(i = 0; i < ucSize; i++)
		UART0_PutChar(Buff[i]);
}
//------------------------------------------------------------------------------------------------
// End of File

