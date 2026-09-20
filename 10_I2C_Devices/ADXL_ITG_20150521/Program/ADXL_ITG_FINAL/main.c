

#include "main.h"
#include "eeprom.h"
#include "i2c.h"
#include "serial.h"
#include "ADXL_345.h"
#include "ITG_3200.h"

#include <stdio.h> 
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//-----------------------------------------------------------------------------
void LED_INIT();
void SW_INIT();
void MAX8877_INIT();

//-----------------------------------------------------------------------------
unsigned char	ucBaud_Rate	= 3;		// Baud rate: 1(2400), 2(4800), 3(9600), 4(14400), 5(19200), 6(28800), 
    									//            7(38400), 8(57600), 9(76800), 10(115200)
unsigned char	ucSend_Flag = 0;		// 0(send stop), 1(send start)
unsigned char	ucSerial_High = 0;		// Serial code high
unsigned char	ucSerial_Low = 0;		// Serial code low
unsigned char	ucCali_X = 0;			// X calibration
unsigned char	ucCali_Y = 0;			// Y calibration
unsigned char	ucCali_Z = 0;			// Z calibration

unsigned char	Timer_Flag = 0;		


int gyrox = 0;
int gyroy = 0;
int gyroz = 0;


int adxlx = 0;
int adxly = 0;
int adxlz = 0;

float	adxlx_angle = 0;
float	adxly_angle = 0;
float	adxlz_angle = 0;

//-----------------------------------------------------------------
/* Timer Interrupt Routine */
SIGNAL (TIMER1_COMPA_vect)	// 20Hz
{
	if(ucSend_Flag == 1) 
	{
		if(Timer_Flag == 0) Timer_Flag = 1;
	}		
}

//--------------------------------------------------------------
int main(void)
{
	volatile unsigned char count = 0;
						
	LED_INIT();
	SW_INIT();	
	
	MAX8877_INIT();
	
			
	i2cInit();
	_delay_ms(10);		
		
	// read data from eeprom 
	ucBaud_Rate = EEPROM_Read_char(ADD_BAUD_RATE);	// EEPROM Read baud rate
	UART0_Init(ucBaud_Rate);	// UART0 initialization	

	ucSerial_High = EEPROM_Read_char(ADD_SERIAL_HIGH);	// EEPROM Read serial code high
	if(ucSerial_High > 99) ucSerial_High = 0;
	
	ucSerial_Low = EEPROM_Read_char(ADD_SERIAL_LOW);	// EEPROM Read serial code low
	if(ucSerial_Low > 99) ucSerial_Low = 0;
		
	ucCali_X = EEPROM_Read_char(ADD_CALI_X);	// EEPROM Read calibration X
	ucCali_Y = EEPROM_Read_char(ADD_CALI_Y);	// EEPROM Read calibration Y
	ucCali_Z = EEPROM_Read_char(ADD_CALI_Z);	// EEPROM Read calibration Z		

	
	ADXl345_INIT();	
	ITG3200_INIT();	
	
	_delay_ms(100);


    //Timer1: 20Hz
    TIMSK1 |= 1<<OCIE1A;	
	TCCR1A = 0x00;		
	TCCR1B = 0x0A;	//64, TOP : OCR1A
	TCCR1C = 0x00;
	OCR1A = 2500;	// 50ms  6250; 20ms 2500
    
	
	sei();					// enable interrupts 
	
				
	while(1)
	{		
		// SW check
  	    if((PINB & 0x40)== 0x40)
		{
		    count++;
			_delay_ms(100);

            if(count >= 25) { 
			    PORTD = 0x00;
			    PORTB &= 0x7F; 					
				_delay_ms(1); 
			 }
		}         
		else 
		{
			count = 0;		
		
			//RS232 process
			if(Get_UART0_Flag() == 1) UART0_Parsing();	
		
			//ADXL345 init check
			if(ADXl345_INIT_Flag() == 0) ADXl345_INIT();		
			
			//ITG3200 init check
			if(ITG3200_INIT_Flag() == 0) ITG3200_INIT();			
			
			if(Timer_Flag == 1) 
			{
					ADXl345_Angle(&adxlx_angle, &adxly_angle, &adxlz_angle);
					ITG3200_ReadXYZ(&gyrox, &gyroy, &gyroz);
	
					//printf("SA%04d%04d%04d%06d%06d%06dP\n", 4000+(int)(adxlx_angle*10.0), 4000+(int)(adxly_angle*10.0), 4000+(int)(adxlz_angle*10.0), gyrox, gyroy, gyroz);
					printf("!Data:%04d,%04d,%04d,%06d,%06d,%06d\n", 4000+(int)(adxlx_angle*10.0), 4000+(int)(adxly_angle*10.0), 4000+(int)(adxlz_angle*10.0), gyrox, gyroy, gyroz);
					Timer_Flag = 0;
			}
		}				
	}
}	

//------------------------------------------------------------------------
void LED_INIT()
{
	DDRD  |= 0b00011000;
	PORTD |= 0b00010000; //LED2 high, LED1 low
}

//------------------------------------------------------------------------
void SW_INIT()
{
	DDRB &= 0b10111111; 
}

//------------------------------------------------------------------------
void MAX8877_INIT()
{
	DDRB  |= 0x80;  
    PORTB |= 0x80;

	DDRD  |= 0x40;
	PORTD |= 0x40;  
}


//------------------------------------------------------------------------
void Update_SerialCode(unsigned char ucPos, unsigned char *Buff)
{
	unsigned char ucTemp = ((Buff[3]-0x30) * 10) + (Buff[4]-0x30);
	
	if((ucTemp < 0) || (ucTemp > 99)) return;	// Bound check
	
	if(ucPos == 1)				// Update serial code high
	{
		if(EEPROM_Write_char(ucTemp, ADD_SERIAL_HIGH) == 1) 
		{			
			UART0_RxReturn();		// Return Rx
			ucSerial_High = ucTemp;
		}			
	}
	else if(ucPos == 0)			// Update serial code low
	{
		if(EEPROM_Write_char(ucTemp, ADD_SERIAL_LOW) == 1) 
		{			
			UART0_RxReturn();		// Return Rx
			ucSerial_Low = ucTemp;
		}			
	}
}

//------------------------------------------------------------------------
void Update_Send(unsigned char *Buff)
{
	if(Buff[1] == 0x30) ucSend_Flag = 0;		// Stop send
	else if(Buff[1] == 0x31) ucSend_Flag = 1;	// Start send
	
	UART0_RxReturn();		// Return Rx		
}

//------------------------------------------------------------------------
void Send_Serial(void)
{
	printf("SK%02d%02d", ucSerial_High, ucSerial_Low);
}
		
//------------------------------------------------------------------------
void Update_Calibration(unsigned char *Buff)
{
	switch(Buff[3]) {
		case 0x58:			// X Calibration
			if(EEPROM_Write_char(Buff[4], ADD_CALI_X) == 1) 
			{				
				UART0_RxReturn();		// Return Rx
				ucCali_X = Buff[4];
			}				
			break;
			
		case 0x59:			// Y Calibration
			if(EEPROM_Write_char(Buff[4], ADD_CALI_Y) == 1) 
			{				
				UART0_RxReturn();		// Return Rx
				ucCali_Y = Buff[4];
			}				
			break;	
			
		case 0x5A:			// Z Calibration
			if(EEPROM_Write_char(Buff[4], ADD_CALI_Z) == 1) 
			{				
				UART0_RxReturn();		// Return Rx
				ucCali_Z = Buff[4];
			}				
			break;					
	}
}
		
//------------------------------------------------------------------------
void Update_BaudRate(unsigned char *Buff)
{
	unsigned char ucTemp = ((Buff[3]-0x30) * 100) + ((Buff[4]-0x30) * 10) + (Buff[5]-0x30);
	
	// Index check
	if((ucTemp < 1) || (ucTemp > 8)) return;
	else  
	{
		if(EEPROM_Write_char(ucTemp, ADD_BAUD_RATE) == 1)	// EEPROM Write
		{
			UART0_RxReturn(); // Return Rx			
			_delay_ms(10);
			
			ucBaud_Rate = ucTemp;
			UART0_Init(ucBaud_Rate);
				
			_delay_ms(10);		
		}			
	}	
}

//------------------------------------------------------------------------------------------------
