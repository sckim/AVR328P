// 준석 PCB 보드에서 구동되는 프로그램
// ADC 채널없이 PEMF 신호만 생성
// Run, Stop 2개 버튼은 인터럽트 처리
// 나머지 버튼은 ADC를 이용하여 입력 받음
// Repetition : 14~20

#include <LiquidCrystal.h>
#include <EEPROM.h>
#define generate 13

// When final output is Non_inverting, Active_High
// otherwise, Active_low
#define Active_Low  1

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void load_data(void); 
void save_data(void); 
void lcd_print_data(void);
void Generation(int f);
int button(void);

int repetition=20;
int frequency=50;
int running=0; 
int repe_set=0;
int temp;
int DELAY;

void setup(void)
{  
  Serial.begin(9600);
  lcd.begin(16,2);  
  pinMode(generate,OUTPUT);      
  attachInterrupt(0,toggle, RISING);
  attachInterrupt(1,TOGGLE_R, RISING);
  running=0;
  repe_set=0; 
  load_data(); 
  lcd_print_data();
} 
/* ******************* MAIN **************** */
void loop(void)
{
#ifdef Active_High
  digitalWrite(generate,LOW);
#else
  digitalWrite(generate,HIGH);
#endif

  if(running==0)
  { temp=button();
    if(repe_set==1) REPE();
    if(temp>=0)
    {
      frequency=temp;
      delay(10);
      lcd_print_data();
    }
  }
  else
  {
    lcd.setCursor(8,1);
    lcd.print("running");
    if(frequency==50) DELAY= 19760-250*repetition;
    else if(frequency==60) DELAY=16400-250*repetition;
    else if(frequency==75) DELAY=13100-250*repetition;
    else if(frequency==100) DELAY=9880-250*repetition;
    
    while(running==1)
     Generation(frequency,DELAY);
     
    lcd.clear();
    lcd_print_data();
  }  
}

/* *************************** function *************************** */

/* ***************** REPE ***************** */
int REPE (void)
{
  int val;
  while(repe_set==1)
  {
    val=button();
    if(val==50) repetition++;
    if(val==0) repetition--;
    else repetition=repetition;
    delay(100);
    lcd.clear();
    lcd_print_data();
    lcd.setCursor(8,1);
    lcd.println("Repe_Set");
    lcd.setCursor(0,1);
    lcd.print("REPE:");
    lcd.print(repetition);
  } 
  lcd_print_data();
}
/* ************ LCD PRINT *********** */
void lcd_print_data(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("frequency :");
  lcd.print(frequency);
  lcd.print("Hz");
  lcd.setCursor(8,1);
  lcd.print("setting");
  lcd.setCursor(0,1);
  lcd.print("REPE:");
  lcd.print(repetition);
}

/* ********** INTERRUPT ************* */

void toggle(void)
{
   save_data();
  delay(200);
  if(repe_set==0) running^=1;


}

void TOGGLE_R(void)
{
   
  delay(200);
  if(running==0) repe_set^=1;
}

/* ********** LOAD DATA ************ */

void load_data(void)
{
  frequency = EEPROM.read(0);
  repetition=EEPROM.read(1);
}

/* ********** SAVE DATA *********** */

void save_data(void)
{
  EEPROM.write(0,frequency);
  EEPROM.write(1,repetition);
}

/* ********* BUTTON ************** */

int button(void) { 
  int val;
  val = analogRead(0); 
  delay(100);
 if(1000<=val && val<=1023) return 0;
  else if(450<=val && val<=550) return 50;
  else if(300<=val && val<=350) return 60;
  else if(230<=val && val<=280) return 75;
  else if(150<=val && val<=210) return 100;
  else return -1;
} 

/* ************* GENERATION ********** */

void Generation(int f,int DELAY)
{
  int i;

#ifdef Active_High
  if(f==0) digitalWrite(generate,HIGH);  
  else {
    for(i=0;i<repetition;i++)
    {
      PORTB |= 0x20;
      //digitalWrite(generate,HIGH);
      delayMicroseconds(125);
      PORTB &= ~0X20;
      //digitalWrite(generate,LOW);
      delayMicroseconds(125);
    }
    delayMicroseconds(DELAY);
  }
#else
  if(f==0) digitalWrite(generate,LOW);  
  else {
    for(i=0;i<repetition;i++)
    {
      PORTB &= ~0X20;
      //digitalWrite(generate,HIGH);
      delayMicroseconds(125);
      PORTB |= 0x20;
      //digitalWrite(generate,LOW);
      delayMicroseconds(125);
    }
    delayMicroseconds(DELAY);
  }
#endif
 }