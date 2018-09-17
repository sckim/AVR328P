/*=======================================================*/
// �ܺ� ���ͷ�Ʈ�� �̿��� 7 segment �� ����
// INT0 (PD0)�� Ȱ��ȭ
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>

int Index = 0;
unsigned char SEG[10] = { 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80,
		0X90 };

volatile uint8_t portbhistory = 0xFF;     // default is high because the pull-up

// ���ͷ�Ʈ ���� �Լ��� �Ʒ��� ����
// SIGNAL(SIG_INTERRUPTn)���� �Ͽ� n�� ���ͷ�Ʈ ��ȣ
ISR(PCINT0_vect) {
	if (bit_is_clear(PINB, PB0)) {
		if (++Index > 9)
			Index = 0;
	}

	if (bit_is_clear(PINB, PB1)) {
		if (--Index < 0)
			Index = 9;
	}
	PORTD = SEG[Index];
}

int main(void) {
	DDRD = 0XFF;
	PORTD = SEG[Index];

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
