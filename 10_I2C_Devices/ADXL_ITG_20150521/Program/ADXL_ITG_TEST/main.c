#include<avr/io.h>

#define F_CPU 8000000
#include <util/delay.h>
#include <stdio.h> 

#include "i2c.h"
#include "ADXL_345.h"
#include "ITG_3200.h"



int UART0_PutChar(char c, FILE *unsed);
void UART0_Init();


float	adxlx_angle = 0, adxly_angle = 0, adxlz_angle = 0;
int gyrox = 0, gyroy = 0, gyroz = 0;


int main(void)
{

			
	i2cInit();
	_delay_ms(10);		
		

	UART0_Init();	
	ADXl345_INIT();	
	ITG3200_INIT();	

	_delay_ms(100);

	ADXl345_ReadAll();
	_delay_ms(2000);			

	while(1)
	{
		
		ADXl345_Angle(&adxlx_angle, &adxly_angle, &adxlz_angle);				
		printf("ADXL X: %5.2f,    Y: %5.2f,    Z: %5.2f\r\n", adxlx_angle, adxly_angle, adxlz_angle);
		ITG3200_ReadXYZ(&gyrox, &gyroy, &gyroz);
		printf("GYRO X: %+06d,    Y: %+06d,    Z: %+06d\r\n", gyrox, gyroy, gyroz);
		_delay_ms(500);
	}

}	



int UART0_PutChar(char c, FILE *unsed)
{
	register unsigned int i = 0;
	
	while (((UCSR0A>>UDRE0) & 0x01) == 0x00) {
		if(i++ > 10000) break;
	}

	UDR0 = c;

	return (1);
}

void UART0_Init()
{

	
	UBRR0H = 0;
	UBRR0L =51;        		// Baud rate
	UCSR0A = 0x00;
	UCSR0B = 0x18;                              // Rx/Tx enable, 8 data,
	UCSR0C = 0x06;                              // 비동기식, 패리티금지, 스탑비트1개, 8비트데이타전송
  
	fdevopen(UART0_PutChar, NULL);				// Set UART0 for printf	
}

