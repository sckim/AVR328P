// 프로그램이 정상적으로 동작하지 않으면
// Fuse bit를 확인해 보세요.

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "uart.h"

volatile uint16_t eepromaddress;
unsigned int start = 0;

void EEPROM_write(void) {
	unsigned int addr = 0;
	char ch;

	ch = 0x0;

	for (addr = start; addr < start+30; addr++) {
//		eeprom_write_byte((uint8_t*) addr, ch);
		eeprom_update_byte((uint8_t*) addr, ch);
		printf("W: %d @ %d\r\n", ch++, addr);
	}
}
void EEPROM_read(void) {
	unsigned char rw8;
	unsigned int addr = 0;

	for (addr = start; addr < start+30; addr++) {
		rw8 = eeprom_read_byte((uint8_t*) addr);
		printf("R %d @ %d\r\n", rw8, addr);
	}
}

int main(void) {
	stdout = &uart_output;
	stdin = &uart_input;

	uart_init(9600UL);
	DDRB |= _BV(5);

//	while(1){
//	PORTB ^= _BV(5);
//		printf("Current EEprom data\r");
//		readEEPROM();
		EEPROM_write();
//		printf("New EEprom data\r");
		EEPROM_read();
//		_delay_ms(100);
//	}
}
