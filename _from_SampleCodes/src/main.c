#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "pcf8574/pcf8574.h"

#define UART_BAUD_RATE 2400
#include "uart/uart.h"


int main(void) {
    //init uart
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));

	//init interrupt
	sei();

	//init pcf8574
	pcf8574_init();

	//test output
	pcf8574_setoutput(0, 0);

	pcf8574_setoutputpinhigh(0, 4);
	pcf8574_setoutputpinhigh(0, 5);

	uart_putc(pcf8574_getoutput(0));

	uart_putc(pcf8574_getoutputpin(0, 1));
	uart_putc(pcf8574_getoutputpin(0, 4));
	uart_putc(pcf8574_getoutputpin(0, 5));

	uart_putc(pcf8574_getoutput(0));

	pcf8574_setoutput(0, 0);

	pcf8574_setoutputpins(0, 7, 3, 0b1011);

	uart_putc(pcf8574_getoutput(0));

	//reset for input
	pcf8574_setoutput(0, 0xFF);
	pcf8574_setoutput(1, 0xFF);

	//test input
	for(;;) {
		uint8_t b = 0;
		b = pcf8574_getinput(0);
		uart_putc(b);
		b = pcf8574_getinputpin(0, 0);
		uart_putc(b);
		b = pcf8574_getinputpin(0, 5);
		uart_putc(b);
		b = pcf8574_getinput(1);
		uart_putc(b);
		_delay_ms(100);
	}

}
