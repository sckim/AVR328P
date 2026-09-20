/*=================================================*/
// 1장_예제1-2(b)
//
// PortB의 입/출력 설정
// 0.1초마다 LED가 점멸
/*=================================================*/
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	int a=128;
	unsigned char Number[10];

	DDRB = 0xFF;

	itoa(a,Number, 10);

	while (1) {
		PORTB = 0x0F;
		_delay_ms(1000);
		PORTB = 0xF0;
		_delay_ms(1000);
	}
}
