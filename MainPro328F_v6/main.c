
/*
   ITG3200 & ADXL345 
*/


/* 
   MainBoard setting

   - LED setting
     LED1 : PD3 , LED 2 : PD4
     전원 인가시 LED1 점등 시겼음 
    
    - MAX8877
     SHDN : PB7 (MUC 전원용, high 전원인가, low ShutDown) 
     SHDN1 : PD6 (ACODE-300 전원용, high 전원인가, low ShutDown))
*/


/*
    HardWare setting for ITG3200

    - 10kOhm pull-ups on I2C lines.
	- VDD & VLOGIC = 3.3V
	- SDA -> PC4
	- SCL -> PC5
	- AD0 = GND;
	- CLK -> GND
*/


/*
    HardWare setting for ADXL345
	
	- VDD & VSS & CS = 3.3V
	- SDC = GND
	- SDA -> PC4
	- SCL -> PC5	
*/

#include "AT328.h"
#include "i2c.h"
#include "serial.h"
#include "ADXL_345.h"
#include "ITG_3200.h"
#include "types.h"
#include "defs.h"

#include <avr/interrupt.h>
#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <avr/eeprom.h>
#include <util/delay.h>

//-----------------------------------------------------------------------------
void LED_INIT();
void SW_INIT();
void MAX8877_INIT();
void getADX1345();
void getITG3200();

//-----------------------------------------------------------------------------
unsigned char EEPROM_Read_char(unsigned int address);
unsigned char EEPROM_Write_char(unsigned char ucValue, unsigned int address);
unsigned char EEPROM_Write_int(unsigned int ucValue, unsigned int address);
unsigned int EEPROM_Read_int(unsigned int address);


//-----------------------------------------------------------------------------
unsigned char EEPROM_Read_char(unsigned int address);
unsigned char EEPROM_Write_char(unsigned char ucValue, unsigned int address);
unsigned char EEPROM_Write_int(unsigned int ucValue, unsigned int address);
unsigned int EEPROM_Read_int(unsigned int address);


unsigned char	ucBaud_Rate	= 3;		// Baud rate: 1(2400), 2(4800), 3(9600), 4(14400), 5(19200), 6(28800), 
    									//            7(38400), 8(57600), 9(76800), 10(115200)
unsigned char	ucSend_Flag = 0;		// 0(send stop), 1(send start)
unsigned char	ucSerial_High = 0;		// Serial code high
unsigned char	ucSerial_Low = 0;		// Serial code low
unsigned char	ucCali_X = 0;			// X calibration
unsigned char	ucCali_Y = 0;			// Y calibration
unsigned char	ucCali_Z = 0;			// Z calibration

unsigned char	Timer_Flag = 0;		


/* 자이로 센서 측정 변수 */
volatile signed int gyrox = 0;
volatile signed int gyroy = 0;
volatile signed int gyroz = 0;


/* 가속도 센서 측정 변수 */
volatile signed int adxlx = 0;
volatile signed int adxly = 0;
volatile signed int adxlz = 0;

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
	volatile long int count = 0;
	double angle_x, angle_y;
	double temp1 = 0;
	
	LED_INIT();
	SW_INIT();	
	
	MAX8877_INIT();
		
	i2cInit();
	delay_ms(10);
	
	//  /* adxl345 레지스터 초기화 */ 
	ADXl345_INIT(); 
	_delay_ms(10);	
		
	/* ITG-3022 레지스터 초기화 */ 
	ITG3200_INIT(); 
	_delay_ms(10);

	ucBaud_Rate = EEPROM_Read_char(ADD_BAUD_RATE);	// EEPROM Read baud rate
	UART0_Init(ucBaud_Rate);	// UART0 initialization	

	ucSerial_High = EEPROM_Read_char(ADD_SERIAL_HIGH);	// EEPROM Read serial code high
	if(ucSerial_High > 99) ucSerial_High = 0;
	
	ucSerial_Low = EEPROM_Read_char(ADD_SERIAL_LOW);	// EEPROM Read serial code low
	if(ucSerial_Low > 99) ucSerial_Low = 0;
		
	ucCali_X = EEPROM_Read_char(ADD_CALI_X);	// EEPROM Read calibration X
	ucCali_Y = EEPROM_Read_char(ADD_CALI_Y);	// EEPROM Read calibration Y
	ucCali_Z = EEPROM_Read_char(ADD_CALI_Z);	// EEPROM Read calibration Z
			
	_delay_ms(10);	
	
	
    TIMSK1 |= 1<<OCIE1A;	
	TCCR1A = 0x00;		
	TCCR1B = 0x0A;	
	TCCR1C = 0x00;
	//OCR1A = 15625;	// 20ms = 50Hz
	OCR1A = 5000;	// 50ms = 20Hz
    
		
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
		
			// RS232 process
			if(Get_UART0_Flag() == 1) UART0_Parsing();	
		
			// ADXL345 init check
			if(ADXl345_INIT_Flag() == 0) ADXl345_INIT();
		
			// ITG3200 init check
			if(ITG3200_INIT_Flag() == 0) ITG3200_INIT();
							
			if(Timer_Flag == 1) 
			{
					getADX1345();
					getITG3200();
					
					temp1 = sqrt(adxly*adxly+adxlz*adxlz);
					angle_x = atan(adxlx/temp1);
					
					temp1 = sqrt(adxlx*adxlx+adxlz*adxlz);
					angle_y = atan(adxly/temp1);

					//printf("SA%0f,%06f,%06d,%06d,%06d,%06dP\n", angle_x, angle_y, adxlz, gyrox, gyroy, gyroz);				
					printf("SA%06d,%06d,%06d,%06d,%06d,%06dP\n", adxlx, adxly, adxlz, gyrox, gyroy, gyroz);
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
void getADX1345()
{
  	adxlx = i2cMultipleRead(ADXL345_W, VAR_X, adxlx);
    adxly = i2cMultipleRead(ADXL345_W, VAR_Y, adxly);
    adxlz = i2cMultipleRead(ADXL345_W, VAR_Z, adxlz);

}

//------------------------------------------------------------------------
void getITG3200()
{
	int gx[NumofSample], gy[NumofSample], gz[NumofSample];
    char temp=0;
	register unsigned int i;
	
	for (i = 0; i<NumofSample; i++)
	{
		while (!(i2cSingleRead(ITG3200_W, REG_INT_S, temp) & 0x01));
		temp = 0;
		temp = i2cSingleRead(ITG3200_W, REG_GY_H, temp); 	
		gy[i] = temp << 8; 	gy[i] |= i2cSingleRead(ITG3200_W, REG_GY_L, temp);

		while (!(i2cSingleRead(ITG3200_W, REG_INT_S, temp) & 0x01));
		temp = 0;
		temp = i2cSingleRead(ITG3200_W, REG_GZ_H, temp);	
		gz[i] = temp << 8;	gz[i] |= i2cSingleRead(ITG3200_W, REG_GZ_L, temp);
		
		while (!(i2cSingleRead(ITG3200_W, REG_INT_S, temp) & 0x01));
		temp = 0;
		temp = i2cSingleRead(ITG3200_W, REG_GX_H, temp);	
		gx[i] = temp << 8;	gx[i] |= i2cSingleRead(ITG3200_W, REG_GX_L, temp);

		
		gyrox += gx[i];
		gyroy += gy[i];
		gyroz += gz[i];
	}
	
	gyrox = gyrox/NumofSample;
	gyroy= gyroy/NumofSample;
	gyroz = gyroz/NumofSample;
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
	
	uctemp = EEPROM_Read_char(address);
		
	if(ucValue == uctemp) return 1;
			
	for(i=0; i<3; i++) {
		eeprom_busy_wait();	
		eeprom_write_byte((uint8_t *) address, ucValue);
		uctemp = EEPROM_Read_char(address);
		
		if(ucValue == uctemp) return 1;	
	}
	
	return 0;
}	
//------------------------------------------------------------------------
unsigned char EEPROM_Write_int(unsigned int ucValue, unsigned int address)
{
	register unsigned char i;
	unsigned int uctemp;
	
	uctemp = EEPROM_Read_int(address);
		
	if(ucValue == uctemp) return 1;
			

	for(i=0; i<3; i++) {
		eeprom_busy_wait();	
		eeprom_write_block(&ucValue, (void *) address, 2);
		uctemp = EEPROM_Read_int(address);
		
		if(ucValue == uctemp) return 1;
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

//------------------------------------------------------------------------------------------------
