
/*
   ITG3200 & ADXL345 
*/

//test
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




#include <avr/io.h>
#include "RS232.h"
#include "i2c.h"
#include "ITG-3200.h"
#include "ADXL-345.h"

#define F_CPU 8000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "defs.h"

#define NumofSample 5


void LED_INIT();
void SW_INIT();
void MAX8877_INIT();
void I2C_INIT();
void getADX1345();
void getITG3200();

/* 자이로 센서 측정 변수 */
volatile signed int gyrox = 0;
volatile signed int gyroy = 0;
volatile signed int gyroz = 0;


/* 가속도 센서 측정 변수 */
volatile signed int adxlx = 0;
volatile signed int adxly = 0;
volatile signed int adxlz = 0;


int main(void)
{

	volatile long int count = 0;


	LED_INIT();
	SW_INIT();
	MAX8877_INIT();
	I2C_INIT();
    UART0_INIT(8); // 115200bps @ 8MHz


   /* ITG-3022 레지스터 초기화 */ 
   ITG3200_INIT(); 
   _delay_ms(1);

   /* adxl345 레지스터 초기화 */ 
   ADXl345_INIT(); 
    _delay_ms(1);

	while(1)
	{
        if((PINB & 0x40)== 0x40)
		{
		    count++;
			_delay_ms(100);

            if(count >=25) { 
			    PORTD = 0x00;
			    PORTB &= 0x7F; 					
				_delay_ms(1); 
			 }
		} 
        
		else 
		{
		    count = 0;

			getADX1345();
	 		getITG3200();
		    sprintf(buf,"S %d %d %d %d %d %d\r\n", adxlx, adxly, adxlz, gyrox, gyroy, gyroz);
            USART0_PutStr(buf);       
			_delay_ms(100);

			
	    }
	}
}

void getADX1345()
{
  	adxlx = read_adxl345(0x32);
    adxly = read_adxl345(0x34);
    adxlz = read_adxl345(0x36);

}

void getITG3200()
{
	int gx[NumofSample], gy[NumofSample], gz[NumofSample];
    char temp;
	unsigned int i;
	
	for (i = 0; i<NumofSample; i++)
	{
		while (!(ITG3200Read(INT_S) & 0x01));
		temp = 0;
		temp = ITG3200Read(GY_H); 	gy[i] = temp << 8; 	gy[i] |= ITG3200Read(GY_L);

		while (!(ITG3200Read(INT_S) & 0x01));
		temp = 0;
		temp = ITG3200Read(GZ_H);	gz[i] = temp << 8;	gz[i] |= ITG3200Read(GZ_L);
		
		while (!(ITG3200Read(INT_S) & 0x01));
		temp = 0;
		temp = ITG3200Read(GX_H);	gx[i] = temp << 8;	gx[i] |= ITG3200Read(GX_L);

		
		gyrox += gx[i];
		gyroy += gy[i];
		gyroz += gz[i];
	}
	
	gyrox = gyrox/NumofSample;
	gyroy= gyroy/NumofSample;
	gyroz = gyroz/NumofSample;
}


void LED_INIT()
{
   DDRD  |= 0b00011000;
   PORTD |= 0b00010000; //LED2 high, LED1 low
}


void MAX8877_INIT()
{
	DDRB  |= 0x80;  
    PORTB |= 0x80;

	DDRD  |= 0x40;
	PORTD |= 0x40;  
}

void I2C_INIT()
{

    DDRC  |= 0b00110000; //PORTC4 (SDA), PORTC5 (SCL)
	PORTC |= 0b00110000; //pullups on the I2C bus

}

void SW_INIT()
{
   DDRB &= 0b10111111; 

}
