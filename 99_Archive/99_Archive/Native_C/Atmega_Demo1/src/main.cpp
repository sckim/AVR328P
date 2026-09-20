#include <Arduino.h>

#define Latch 8

void setup()
{
  for(int i = 10; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  pinMode(Latch, OUTPUT); // Latch control, /Storage
  digitalWrite(Latch, HIGH); // disable
  pinMode(Latch+1, OUTPUT); // Latch control, /Storage
  digitalWrite(Latch+1, HIGH); // disable
}

void dispNum(unsigned char ch, unsigned char dig)
{
  ch = ch & 0x0F;
  
  for(int i = 0; i < 4; i++) {
    digitalWrite(i+10, ch&(1<<i) ? HIGH : LOW);
  }
  if( dig==0 ) {
      digitalWrite(Latch, LOW);
      delay(10);
      digitalWrite(Latch, HIGH);
   } else {
      digitalWrite(Latch+1, LOW);
      delay(10);
      digitalWrite(Latch+1, HIGH);
   }
}

unsigned char num = 0;

void loop()
{ 
  // unsigned char tens = num / 10; // 10의 자리
  // unsigned char ones = num % 10; // 1의 자리
  
  dispNum(num, 0); // 0의 자리 출력
  dispNum(num+1, 1); // 1의 자리 출력
   
  num++;
  if (num > 9) 
      num = 0;
  
  delay(2000);
}
