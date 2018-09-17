/*=======================================================*/
// �ܺ� ���ͷ�Ʈ�� �̿��� 7 segment �� ����
// INT0 (PD0)�� Ȱ��ȭ
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>

int Index = 0;

// ���ͷ�Ʈ ���� �Լ��� �Ʒ��� ����
// SIGNAL(SIG_INTERRUPTn)���� �Ͽ� n�� ���ͷ�Ʈ ��ȣ
ISR(INT0_vect)

{
	if (++Index == 0x10)
		Index = 0;
	PORTD = Index<<4;
}

ISR(INT1_vect) {
	if (--Index < 0)
		Index = 0x0F;
	PORTD = Index<<4;
}

int main(void) {
	DDRD = 0XF0;
	PORTD = 0;

	EIMSK = 0b00000011;		//INT0 �� ��� ����
	//EIMSK = 0x01;
	EICRA = 0b00001010; 	//INT0 �ϰ��𼭸����� ���۵ǵ��� ����
	//EIMSK = 0x02;
	SREG = 0b10000000;
	//sei();
	//SREG = 0x80;

	while (1) {
	}
}
