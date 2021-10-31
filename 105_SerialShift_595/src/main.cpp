#include <Arduino.h>

int SerialIn = 3; 
int LatchCP = 4;
int ShiftCP = 5; 

int pos = 0;

/*
unsigned char lookup[8] = {
    0x01, 0x02, 0x04, 0x08, 0x10,
    0x20, 0x40, 0x80 
};
*/
unsigned char lookup[8] = {
    0b00000001,
    0b00000011,
    0b00000111,
    0b00001111,
    0b00011111,
    0b00111111,
    0b01111111,
    0b11111111
};


void setup()
{  
  pinMode(SerialIn, OUTPUT);
  pinMode(LatchCP, OUTPUT);
  pinMode(ShiftCP, OUTPUT);
}

void loop()
{
  //array index
  int index = pos % 8;
  
  //shiftOut(dataPin, clockPin, bitOrder, value);
  shiftOut(SerialIn, ShiftCP, MSBFIRST, lookup[index]);
  
  // Generate latch clock
  digitalWrite(LatchCP, LOW);
  delayMicroseconds(1);  
  digitalWrite(LatchCP, HIGH);
  
  pos++;
 	
  delay(500);
}