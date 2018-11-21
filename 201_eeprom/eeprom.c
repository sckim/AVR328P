#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "uart.h"

volatile uint16_t eepromaddress;
unsigned int start = 30;

void writeEEPROM(void) {
	unsigned int addr = 0;
	char ch;

	ch = 0x0;

	for (addr = start; addr < start+30; addr++) {
		eeprom_write_byte((uint8_t*) addr, ch);
		//printf("R/W %d @ %d\r", ch++, addr);
		ch++;
	}
}
void readEEPROM(void) {
	unsigned char rw8;
	unsigned int addr = 0;

	for (addr = start; addr < start+30; addr++) {
		rw8 = eeprom_read_byte((uint8_t*) addr);
		printf("R/W %d @ %d\r", rw8, addr);
	}
}

int main(void) {
	stdout = &uart_output;
	stdin = &uart_input;

	uart_init(9600UL);
	DDRB |= _BV(5);

	while(1){
		PORTB ^= _BV(5);
		printf("Current EEprom data\r");
		readEEPROM();
		writeEEPROM();
		printf("New EEprom data\r");
		readEEPROM();
	}
}
