/*=======================================================*/
// 외부 인터럽트를 이용한 7 segment 값 변경
// INT0 (PD0)를 활성화
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>

int Index = 0;

volatile uint8_t portbhistory = 0xFF;     // default is high because the pull-up

// 인터럽트 수행 함수는 아래와 같이
// SIGNAL(SIG_INTERRUPTn)으로 하여 n이 인터럽트 번호
ISR(PCINT0_vect) {
	if (bit_is_clear(PINB, PB0)) {
		if (++Index > 9)
			Index = 0;
	}

	if (bit_is_clear(PINB, PB1)) {
		if (--Index < 0)
			Index = 9;
	}
	PORTD = Index<<4;
}

int main(void) {
	DDRD = 0XFF;

	DDRB &= ~(1 << DDB0) ; // Clear the PB0 pin
	DDRB &= ~(1 << DDB1) ; // Clear the PB1 pin
	// PB0 (PCINT0 pin) is now an input

	//PORTB |= ((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2)); // turn On the Pull-up
	// PB0, PB1 and PB2 are now inputs with pull-up enabled

	PCMSK0 |= (1 << PCINT0); // set PCINT0 to trigger an interrupt on state change 	SREG = 0b10000000;
	PCMSK0 |= (1 << PCINT1);

	PCICR |= (1 << PCIE0);     // set PCIE0 to enable PCMSK0 scan
	sei();

	while (1) {
	}
}
