/*
ADC
*/

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

unsigned char analog_reference=1;

void setup() {
  Serial.begin(9600);
}

int ReadADC(unsigned char pin) {
	uint8_t low, high;

	if (pin >= 14)
		pin -= 14; // allow for channel or pin numbers
	ADMUX = (analog_reference << 6) | (pin & 0x07);

	sbi(ADCSRA, ADSC);
	// ADSC is cleared when the conversion finishes
	while (bit_is_set(ADCSRA, ADSC))
		;

	low = ADCL;
	high = ADCH;

	return (high << 8) | low;
}

char str[80];

void loop() {
  int val;
  float voltage;

  //val = analogRead(A0);
  val = ReadADC(0);
  voltage = map(val, 0, 1023, 0, 5000)/1000.0;

  for(int i=0; i<6; i++) {
	  sprintf(str, "ADC[%d] = %d, %2.2f", i, val, voltage);
	  Serial.println(str);
  }
  delay(100);
}

int main(void)
{
	setup();

	while(1){
		loop();
	}
}
