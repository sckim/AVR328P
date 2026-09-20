#include <LiquidCrystal.h>
#include <EEPROM.h>

#define cButton  2
#define cLight   3

// define some values used by the panel and buttons
int lcd_key = 0;
int adc_key_in = 0;

#define KEY_RIGHT   0
#define KEY_UP      1
#define KEY_DOWN   	2
#define KEY_LEFT   	3
#define KEY_SELECT 	4
#define btnNONE   	5

volatile int turnOnTime;
int running = 0;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void load_data(void) {
	turnOnTime = EEPROM.read(0);
}
void save_data(void) {
	EEPROM.write(0, turnOnTime);
}

/* ************ LCD PRINT *********** */
void lcd_print_data(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Duration [ms]");

  if(!running) {
	  lcd.setCursor(8,0);
	  lcd.print("Setting");
  } else {
      lcd.print("Ready..");
  }
  lcd.setCursor(0,1);
  lcd.print(turnOnTime);
}

int read_LCD_buttons() {               // read the buttons
	adc_key_in = analogRead(0);       // read the value from the sensor

	// my buttons when read are centered at these valies: 0, 144, 329, 504, 741
	// we add approx 50 to those values and check to see if we are close
	// We make this the 1st option for speed reasons since it will be the most likely result

	if (adc_key_in > 1000)
		return btnNONE;

	// For V1.1 us this threshold
	if (adc_key_in < 50)
		return KEY_RIGHT;
	if (adc_key_in < 250)
		return KEY_UP;
	if (adc_key_in < 450)
		return KEY_DOWN;
	if (adc_key_in < 650)
		return KEY_LEFT;
	if (adc_key_in < 850)
		return KEY_SELECT;

	// For V1.0 comment the other threshold and use the one below:
	/*
	 if (adc_key_in < 50)   return btnRIGHT;
	 if (adc_key_in < 195)  return btnUP;
	 if (adc_key_in < 380)  return btnDOWN;
	 if (adc_key_in < 555)  return btnLEFT;
	 if (adc_key_in < 790)  return btnSELECT;
	 */

	return btnNONE;                // when all others fail, return this.
}

//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(9600);

	load_data();
	lcd.begin(16, 2); /*Enable*/
	//ledkeypad.display(Voltage[VoltageIndex] * 100 + Frequency[FrequencyIndex]); //Display character for testing
	lcd_print_data();

	pinMode(13, OUTPUT);
	//optionally, now set up our application-specific display settings, overriding whatever the lcd did in lcd.init()
	//lcd.commandWrite(0x0F);//cursor on, display on, blink on.  (nasty!)

	pinMode(cButton, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(cButton), PLR, FALLING);
}

void PLR(void) {
	digitalWrite(cLight, HIGH);
	delay (turnOnTime);
	digitalWrite(cLight, LOW);
}

void loop() {
	unsigned char keyValue = 0;

	keyValue = read_LCD_buttons();/*Get key value*/
	switch (keyValue) {
	case KEY_DOWN:
	case KEY_LEFT:
		turnOnTime += 10;
		if (turnOnTime > 30000)
			turnOnTime = 0;
		lcd_print_data();
		break;
	case KEY_UP:
	case KEY_RIGHT:
		turnOnTime -= 10;
		if (turnOnTime < 0)
			turnOnTime = 30000;
		lcd_print_data();
		break;
	case KEY_SELECT:
		running ^= 1;
		if (running) {
			save_data();
			interrupts();
		} else {
			noInterrupts();
		}
		lcd_print_data();
		break;
	default: break;
	}
}
