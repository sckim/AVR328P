#include <Arduino.h>

#define FOSC 16000000 // Clock Speed

char str[80];

void InitADC() {
	// For Aref=AVcc;
	// REFS[1:0] = 01
	ADMUX = (1 << REFS0);

	//Prescalar div factor =128
	// ADPS[2:0]
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ReadADC(uint8_t ch) {
	//Select ADC Channel ch must be 0-7
	// MUXn[3:0]
	ADMUX &= 0xF0;
	ADMUX |= (ch & 0x07);

	//Start Single conversion
	ADCSRA |= (1 << ADSC);

	//Wait for conversion to complete
	//while (!(ADCSRA & (1 << ADIF)))
	//	;
    loop_until_bit_is_clear(ADCSRA, ADIF);
  
	//Clear ADIF by writing one to it
	//Note you may be wondering why we have write one to clear it
	//This is standard way of clearing bits in io as said in datasheets.
	//The code writes '1' but it result in setting bit to '0' !!!
	ADCSRA |= (1 << ADIF);

	return (ADC);
}

void UART_Init(unsigned int baudrate) {
  unsigned int ubrr;
  
  ubrr = FOSC/16/baudrate-1;
  UBRR0H = (unsigned char) (ubrr >> 8);
  UBRR0L = (unsigned char) ubrr;

  /* Enable receiver and transmitter */
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
  UCSR0B |= (1<<RXCIE0); 

  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (3 << UCSZ00);
}

void USART_Transmit(unsigned char data) {
	/* Wait for empty transmit buffer */
	while (!( UCSR0A & (1 << UDRE0)))
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void USART_Puts(const char *data) {
	while (*data != '\0')
		USART_Transmit(*data++);
}

void dispSeg(unsigned char ch)
{
  PORTD &= 0x0F;
  PORTD |= (ch<<4);
}

 // �� �ϳ��ϳ��� ���������� �����Ͽ� ���α׷��ϴ� ��
void setup()
{
  /*
   for(int i=4; i<8; i++) {
  	pinMode(i, OUTPUT);  // pin�� ����� ���� ����
  	digitalWrite(i, LOW); // ���� pin ����� high
  }*/
  // Initialize GPIO for 7 segments
  for(int i=4; i<8; i++){
  	DDRD |= _BV(i);
    PORTD |= _BV(i);
  }   

  //Serial.begin(9600);
  UART_Init(9600);
  InitADC();
}

void loop()
{
  int adc_value;
  int num;

  adc_value = ReadADC(0);
  num = map(adc_value, 0, 1023, 0, 9);
  dispSeg(num);

  USART_Puts("ADC[0] = ");
  USART_Puts(itoa(adc_value, str, 10));
  
  USART_Puts(", ");
  USART_Puts(itoa(map(adc_value, 0, 1023, 0, 500), str, 10));
  USART_Puts("[V]\r\n");

  delay(500);   
}