//const byte cLED = PB5
//const byte cBtn = PB0;
#define cBtn	PB0
#define cLED	PB5
 
void setup()
{
  	pinMode(13, OUTPUT);  
  	//DDRB |= _BV(cLED);	//_BV(PB5) ==> (1<<PB5)	

  	pinMode(8, INPUT_PULLUP);
  	//DDRB &= ~_BV(PB0); // initial state is input mode.
   	//MCUCR &= ~_BV(4); // initial state is PUD active mode.
    //PORTB |= _BV(cBtn); // enable internal pull up resistor
}

void loop()
{
  if ( digitalRead(8) ) {
  //if( PINB & _BV(cBtn) ) {
//    PINB & (1<<0)
     digitalWrite(13, HIGH);
//     PORTB |= _BV(cLED);
     //PORTB = PORTB | 0b0010 0000
  } else {
     digitalWrite(13, LOW);  
//  	 PORTB &= ~_BV(cLED);     
     //PORTB = PORTB &  0b1101 1111
  }
}