#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "ledcontrol.h"

extern "C" {
#include "gpio.h"
}

unsigned long delaytime=100;

//int dataPin, int clkPin, int csPin, int numDevices)
LedControl lc = LedControl(9, 13, 10, 2);

//void writeArduinoOnMatrix() {
//  /* here is the data for the characters */
//  byte a[5]={0b01111110,0b10001000,0b10001000,0b10001000,0b01111110};
//  byte r[5]={0b00111110,0b00010000,0b00100000,0b00100000,0b00010000};
//  byte d[5]={0b00011100,0b00100010,0b00100010,0b00010010,0b11111110};
//  byte u[5]={0b00111100,0b00000010,0b00000010,0b00000100,0b00111110};
//  byte i[5]={0b00000000,0b00100010,0b10111110,0b00000010,0b00000000};
//  byte n[5]={0b00111110,0b00010000,0b00100000,0b00100000,0b00011110};
//  byte o[5]={0b00011100,0b00100010,0b00100010,0b00100010,0b00011100};
//
//  /* now display them one by one with a small delay */
//  lc.setRow(0,0,a[0]);
//  lc.setRow(0,1,a[1]);
//  lc.setRow(0,2,a[2]);
//  lc.setRow(0,3,a[3]);
//  lc.setRow(0,4,a[4]);
//  _delay_ms(delaytime);
//  lc.setRow(0,0,r[0]);
//  lc.setRow(0,1,r[1]);
//  lc.setRow(0,2,r[2]);
//  lc.setRow(0,3,r[3]);
//  lc.setRow(0,4,r[4]);
//  _delay_ms(delaytime);
//  lc.setRow(0,0,d[0]);
//  lc.setRow(0,1,d[1]);
//  lc.setRow(0,2,d[2]);
//  lc.setRow(0,3,d[3]);
//  lc.setRow(0,4,d[4]);
//  _delay_ms(delaytime);
//  lc.setRow(0,0,u[0]);
//  lc.setRow(0,1,u[1]);
//  lc.setRow(0,2,u[2]);
//  lc.setRow(0,3,u[3]);
//  lc.setRow(0,4,u[4]);
//  _delay_ms(delaytime);
//  lc.setRow(0,0,i[0]);
//  lc.setRow(0,1,i[1]);
//  lc.setRow(0,2,i[2]);
//  lc.setRow(0,3,i[3]);
//  lc.setRow(0,4,i[4]);
//  _delay_ms(delaytime);
//  lc.setRow(0,0,n[0]);
//  lc.setRow(0,1,n[1]);
//  lc.setRow(0,2,n[2]);
//  lc.setRow(0,3,n[3]);
//  lc.setRow(0,4,n[4]);
//  _delay_ms(delaytime);
//  lc.setRow(0,0,o[0]);
//  lc.setRow(0,1,o[1]);
//  lc.setRow(0,2,o[2]);
//  lc.setRow(0,3,o[3]);
//  lc.setRow(0,4,o[4]);
//  _delay_ms(delaytime);
//  lc.setRow(0,0,0);
//  lc.setRow(0,1,0);
//  lc.setRow(0,2,0);
//  lc.setRow(0,3,0);
//  lc.setRow(0,4,0);
//  _delay_ms(delaytime);
//}

/*
 This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows() {
	for (int row = 3; row < 8; row++) {
		lc.setRow(0, row, 0b10100000);
		_delay_ms(delaytime);
		lc.setRow(1, row, 0b10110000);
		_delay_ms(delaytime);
		lc.setRow(0, row, (byte) 0);
		for (int i = 0; i < row; i++) {
			_delay_ms(delaytime);
			lc.setRow(0, row, 0b10100000);
			_delay_ms(delaytime);
			lc.setRow(0, row, (byte) 0);
		}
	}
}

/*
 This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void columns() {
	for (int col = 0; col < 8; col++) {
		_delay_ms(delaytime);
		lc.setColumn(0, col, 0b10100000);
		_delay_ms(delaytime);
		lc.setColumn(0, col, (byte) 0);
		for (int i = 0; i < col; i++) {
			_delay_ms(delaytime);
			lc.setColumn(0, col, 0b10100000);
			_delay_ms(delaytime);
			lc.setColumn(0, col, (byte) 0);
		}
	}
}

/*
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			_delay_ms(delaytime);
			lc.setLed(0, row, col, true);
			_delay_ms(delaytime);
			for (int i = 0; i < col; i++) {
				lc.setLed(0, row, col, false);
				_delay_ms(delaytime);
				lc.setLed(0, row, col, true);
				_delay_ms(delaytime);
			}
		}
	}
}

int main(void) {
	lc.shutdown(0, false);
//	/* Set the brightness to a medium values */
	lc.setIntensity(0, 8);
//	/* and clear the display */
	lc.clearDisplay(0);

	while (1) {
//		writeArduinoOnMatrix();
		 rows();
		  lc.clearDisplay(0);
		  lc.clearDisplay(1);
		  columns();
		  single();
	}

	return 1;
}
