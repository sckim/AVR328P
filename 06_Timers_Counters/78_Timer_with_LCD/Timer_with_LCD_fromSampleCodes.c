/*=======================================================*/
//
//
//overflow 타이머0 사용
//14.7456MHz라는 가정
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

#include "lcd_lib.h"

#define LED_On 	SetBit(PORTC,3)
#define LED_Off	ClearBit(PORTC,3)

volatile int cnt = 0;
volatile char str_timer[16];
volatile int Hour, Minute, Second;

// CLK: 14.7456MHz / 1024 = 14,400
// 144 = 0.01sec
// 72 = 0.005sec
#define TimerValue 144

volatile int cur_x, cur_y;
volatile unsigned char cur_char;
volatile int updated = 0;
int number = 0;

void port_init(void) {
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0x00;
	DDRE = 0xFF;
	DDRF = 0xFF;

	PORTB = 0x00;
	PORTC = 0x00;
}

void ExtInter_init(void) {
	EIMSK = 0b00000001;		//INT0 번 사용 설정
	//EIMSK = 0x01;
	EICRA = 0b00000010; 	//INT0 하강모서리에서 동작되도록 설정
}

void Timer0_init(void) {
	//TIMSK=0x01;  //1. Timer0 오버플로 인터럽트 에이블 (TOIE0)
	TIMSK |= (1 << TOIE0);
	//TIFR |= (1 << TOV0);

	// 2. Normal, 1/1024 for 프리스케일
	TCCR0 = (1 << CS02) | (1 << CS01) | (1 << CS00);
	//TCCR0 = (1 << CS00);

	// 3. Set counter
	// 14.7456MHz / 1024 = 14,400
	// 144 = 0.01sec
	TCNT0 = 0xff - TimerValue + 1;
}

volatile int Updated = 0;

SIGNAL(SIG_INTERRUPT0) {
	if (++Minute == 59)
		Minute = 0;
	Updated=1;
}

SIGNAL(SIG_OVERFLOW0) {
	// prevent generating interrupter in this loop.
	cli();

	TCNT0 = 0xff - TimerValue + 1; //3. 초기값
	cnt++;
	if (cnt >= 100) {
		cnt = 0;
		Second++;
		Updated = 1;

		PORTC ^= 0x08;
		if (Second >= 60) {
			Second = 0;
			Minute++;

			if (Minute >= 60) {
				Minute = 0;
				Hour++;
			}
			if (Hour >= 24)
				Hour = 0;
		}
	}
	sei();
}

int main(void) {
	port_init();

	LCDinit();
	LCDclr();
	LCDcursorOn();

	Second = 0;
	Minute = 0;
	Hour = 0;

	Timer0_init();
	ExtInter_init();
	sei();

	while (1) {
		if (Updated) {
			sprintf((char *) str_timer, "%02d:%02d:%02d", Hour, Minute, Second);
			LCDhome();
			LCDstring((char *) str_timer, strlen(str_timer));
			Updated = 0;
		}
		if( bit_is_clear(PIND, PD2) ){
			_delay_ms(500);
			if(++Hour>24)
				Hour = 0;
		}
	}
}
