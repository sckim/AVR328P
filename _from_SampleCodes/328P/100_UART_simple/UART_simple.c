#include <avr/io.h>
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "lcd_lib.h"

#define strWelcome	"Welcome"
#define strWelcome1	"Microcontroller"

// 7 segments
#define cSegmentPortDir		DDRF
#define cSegmentPortData	PORTF

unsigned char SEG[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80,
		0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8e };
char str[80];
char key_input;

// Timer
#define cDelay 144
volatile int sec = 0;
volatile int msec = 0;
volatile int min = 0;
volatile int hour = 0;

volatile char dispOn = 0;
volatile char AlarmOn = 0;
volatile char TimerOn = 0;

void InitExternalInT(void)
{
    EIMSK = 0b00000011;		//INT0, 1 번 사용 설정
    //EIMSK = 0x01;
    EICRA = 0b00001010; 	//INT0, 1 하강모서리에서 동작되도록 설정
    //EIMSK = 0x02;
}

// 인터럽트 수행 함수는 아래와 같이
// SIGNAL(SIG_INTERRUPTn)으로 하여 n이 인터럽트 번호
ISR(INT0_vect)
{
	hour++;
	if (hour == 24) hour = 0;
}

ISR(INT1_vect)
{
	min++;
	if (min == 60) hour = 0;
}

ISR (TIMER0_OVF_vect) {
	msec++;
	if (msec == 100) {
		sec++;
		msec = 0;
		if(dispOn)	{
			LCDclr();
			LCDGotoXY(0, 0);
			sprintf(str, "%02d:%02d:%02d", hour, min, sec);
			LCDstring((uint8_t*) str, strlen(str));
		}
	}
	if (sec == 60) {
		min++;
		sec = 0;
	}
	if (min == 60) {
		hour++;
		sec = 0;
	}
	if (hour == 24)
		hour = 0;

	TCNT0 = 0xFF - cDelay + 1;    //초기값
}

void Timer0Init(void) {
/*
	cli();
	TIMSK |= (1 << TOIE0);    // Timer0 오버플로 인터럽트 에이블

// Normal, 1/1024 for 프리스케일
	TCCR0 |= (1 << CS02);
	TCCR0 |= (1 << CS01);
	TCCR0 |= (1 << CS00);

	TCNT0 = 0xFF - cDelay + 1;    // 10msec

	sei();
	//SRGE  = 0x80;
	*/
}

void AdjustTime()
{
	InitExternalInT();
	puts("\nPress button 1 for hour and 2 for minute");
	puts("\nQ. Return to main menu");

	do{
		key_input = getchar();
		printf("%c\n", key_input);
	} while(key_input!='q');
}

void SetAlarm(void)
{

}

void StopWatch(void)
{

}

void myTimer(void)
{

}

int SetTimer(void) {
	puts("\n===================");
	puts("   Control Time    ");
	puts("-------------------");
	puts("1. Set time");
	puts("2. Set alarm");
	puts("3. Stop watch");
	puts("4. Timer");
	puts("\nQ. Return to main menu");
	printf("Choose menu : ");

	key_input = getchar();
	printf("%c\n", key_input);
	_delay_ms(200);

	switch (key_input) {
	case '1': AdjustTime();
		break;
	case '2': SetAlarm();
		AlarmOn = 1;
		break;
	case '3': StopWatch();
		break;
	case '4': myTimer();
		break;
	case 'q':
	case 'Q':
		return 1;

	default:
		return 0;
	}
	return 0;
}

void printSegment(unsigned char number) {
	//cSegmentPortDir = 0xFF;
	//cSegmentPortData = SEG[number];
}

char *GetString(void) {
	unsigned char i = 0;

	do {
		key_input = getchar();
		printf("%c", key_input);
		str[i] = key_input;
		i++;            // -> Skip ?
	} while (key_input != 0x20);
	str[--i] = 0x00;
	puts("");

	return str;
}

int SegmentDisplay(void) {

	printf("Enter your number [press 'q' to upper menu]: ");
	key_input = getchar();
	printf("%c\n", key_input);
	_delay_ms(200);
	if (key_input == 'q') {
		puts("Goodbye segment\n");
		return 1;
	}
	printSegment(key_input - 0x30);
	return 0;
}

void menu(void) {
	puts("\n===================");
	puts("     Main Menu     ");
	puts("-------------------");
	puts("1. Display Segment");
	puts("2. Control LCD");
	puts("3. Set Timer");
	puts("4. Get ADC");
	puts("5. Get Acc");
	puts("6. Control motor");  // RC server and speed
	puts("8. Adjust LED intensity");
	puts("\nQ. Exit");
}

int ControlLCD(void) {
	puts("\n===================");
	puts("   Control LCD     ");
	puts("-------------------");
	puts("1. Display str at 1st line: ");
	puts("2. Display str at 2nd line: ");
	puts("3. Clear LCD");
	puts("\nQ. return to main menu");
	printf("Choose menu : ");

	key_input = getchar();
	printf("%c\n", key_input);
	_delay_ms(200);

	switch (key_input) {
	case '1':
		GetString();
		LCDGotoXY(0, 0);
		LCDstring((uint8_t*) str, strlen(str));
		break;
	case '2':
		GetString();
		LCDGotoXY(0, 1);
		LCDstring((uint8_t*) str, strlen(str));
		break;
	case '3':
		LCDclr();
		break;
	case 'q':
	case 'Q':
		puts("\nGoodbye LCD\n");
		return 1;
	default:
		return 0;
	}
	return 0;
}

int main(void) {
	DDRB = 0xff;
	DDRC = 0x00;

	LCDinit();
	LCDcursorOn();
	LCDclr();

	LCDstring((uint8_t*) strWelcome, strlen(strWelcome));
	LCDGotoXY(0, 1);
	LCDstring((uint8_t*) strWelcome1, strlen(strWelcome1));

	uart_init(9600UL);
	Timer0Init();

	stdout = &uart_output;
	stdin = &uart_input;

	printf("Hello world!");
	while (1) {
		menu();
		printf("Choose menu : ");
		key_input = getchar();
		printf("%c\n", key_input);
		_delay_ms(200);
		switch (key_input) {
		case '1':
			while (!SegmentDisplay())
				;
			break;
		case '2':
			while (!ControlLCD())
				;
			//GetString();
			break;
		case '3':
			dispOn = 1;
			while (!SetTimer())
				;
			dispOn = 0;
			break;
		case 'q':
		case 'Q':
			puts("\nGood Main\n");
			printSegment(4);
			return 0;
		default:
			printf("\n");
		}
	}
	return 0;
}
