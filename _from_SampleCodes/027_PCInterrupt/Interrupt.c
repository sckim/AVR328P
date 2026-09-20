/*=======================================================*/
// 외부 인터럽트를 이용한 7 segment 값 변경
// INT0 (PD0)를 활성화
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>

int Index = 0;

// 인터럽트 수행 함수는 아래와 같이
// SIGNAL(SIG_INTERRUPTn)으로 하여 n이 인터럽트 번호
ISR(PCINT0_vect)
{
	if (bit_is_clear(PINB, PB0))
		if( ++Index > 0x10)
			Index = 0;
	if (bit_is_clear(PINB, PB1))
		if( --Index < 0)
			Index = 0x0F;

	PORTD = Index<<4;
}

int main(void) {
	DDRD = 0XF0;
	PORTD = 0;

	DDRB = ~0x03;
	PORTB |= 0x03;

	PCMSK0 = 0b00000011;
//	PCMSK0 |= (1<<0);
//	PCMSK0 |= (1<<1);
	PCICR = 0b000000001; // PORTB
//	PCICR = 0b000000010; // PORTC
//	PCICR = 0b000000100; // PORTD
//	PCICR = 0x01;

	SREG = 0b10000000;
	//sei();
	//SREG = 0x80;
	while (1) {
	}
}
