#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "arduino.h"
#include "ledcontrol.h"

extern "C" {
#include "uart.h"
}

unsigned long delaytime=100;

LedControl lc = LedControl(11, 13, 10, 1);

/*
 This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows() {
	for (int row = 3; row < 8; row++) {
		lc.setRow(0, row, B10100000);
		delay (delaytime);
//    lc.setRow(1,row,B10110000);
//    delay(delaytime);
//    lc.setRow(0,row,(byte)0);
//    for(int i=0;i<row;i++) {
//      delay(delaytime);
//      lc.setRow(0,row,B10100000);
//      delay(delaytime);
//      lc.setRow(0,row,(byte)0);
//    }
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
		delay (delaytime);
		lc.setColumn(0, col, B10100000);
		delay(delaytime);
		lc.setColumn(0, col, (byte) 0);
		for (int i = 0; i < col; i++) {
			delay(delaytime);
			lc.setColumn(0, col, B10100000);
			delay(delaytime);
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
			delay (delaytime);
			lc.setLed(0, row, col, true);
			delay(delaytime);
			for (int i = 0; i < col; i++) {
				lc.setLed(0, row, col, false);
				delay(delaytime);
				lc.setLed(0, row, col, true);
				delay(delaytime);
			}
		}
	}
}

int main(void) {
	FILE std_inout;

	std_inout.put = uart_printf;
	std_inout.get = uart_scanf;
	std_inout.flags = _FDEV_SETUP_RW;

	stdin = stdout = &std_inout;

	uart_init(UART_BAUD_SELECT(9600, 16000000L));
	sei();

	lc.shutdown(0, false);
//	/* Set the brightness to a medium values */
	lc.setIntensity(0, 8);
//	/* and clear the display */
	lc.clearDisplay(0);

//	while (1) {
//		for (int row = 3; row < 8; row++) {
//			lc.setRow(0, row, B10100000);
//			_delay_ms(100);
//		}
//	}

	return 1;
}
