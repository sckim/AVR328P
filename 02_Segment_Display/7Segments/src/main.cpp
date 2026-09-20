#include <Arduino.h>

unsigned char SEG[10] = {0b11000000, 0b11111001,
                         0b10100100, 0b10110000,
                         0b10011001, 0b10010010,
                         0b10000010, 0b11111000,
                         0b10000000, 0b10010000};
unsigned char num = 0;

// 핀 하나하나를 개별적으로 제어하여 프로그램하는 예
void setup()
{
  for(int i=0; i<8; i++) {
  	pinMode(i, OUTPUT);  // pin의 입출력 상태 결정
  	digitalWrite(i, HIGH); // 현재 pin 출력을 high
  }
  // DDRD = 0xFF;
}

void dispSeg(unsigned char ch)
{
	for(int i=0; i<8; i++)
      digitalWrite(i, SEG[ch] & (1<<i));

  // PORTD = SEG[ch];
}

void loop()
{
  dispSeg(num++);
  if( num>9 )
      num = 0;
  delay(200);
  /*
  for(int i=0; i<10; i++ ){
    dispSeg(SEG[i]);
  	delay(500);
  }
  for(int i=8; i>0; i-- ){
    dispSeg(SEG[i]);
  	delay(500);
  }
*/
}
