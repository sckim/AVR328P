// ============================================
// = AT90USB162 REFERENCE DESIGN
// = Wired mouse with philips PNL2021 sensor
// ********************************************
// = Driver file for basic peripherals
// =============================================

//-----------------------------------------------------------------------------
// UTILITY DEFINATION
#define Sbi(Port, Value)        	(Port |= Value)
#define Cbi(Port, Value)            (Port &= (~Value))
#define Tbi(Port, Value)            (Port ^= Value)

#define BIT0						0x01
#define BIT1						0x02
#define BIT2						0x04
#define BIT3						0x08
#define BIT4						0x10
#define BIT5						0x20
#define BIT6						0x40
#define BIT7						0x80


// USB
// Used if VBUS_SENSING_IO is defined as "ENABLED"
#define   VBUS_SENSE_PORT     PORTC   // PORTx
#define   VBUS_SENSE_PIN      PINC    // PINx
#define   VBUS_SENSE_DDR      DDRC    // DDRx
#define   VBUS_SENSE_IO       4       // 0...7


#define Led1Init()					Sbi(DDRC, BIT4)
#define Led1Off()					Sbi(PORTC, BIT4)
#define Led1On()					Cbi(PORTC, BIT4)
#define Led1Toggle()				Tbi(PORTC, BIT4)

#define Led2Init()					Sbi(DDRD, BIT0)
#define Led2Off()					Sbi(PORTD, BIT0)
#define Led2On()					Cbi(PORTD, BIT0)
#define Led2Toggle()				Tbi(PORTD, BIT0)

// LEDs
// ****
#define   Leds_init()          Led1Init();Led2Init();Led2Off();Led1On();//(DDRD |= 0x33, PORTD &= ~0x33);

#define   Led0_on()            
#define   Led0_off()           
#define   Led0_toggle()        
#define   Led1_on()            
#define   Led1_off()           
#define   Led1_toggle()        
#define   Led2_on()            
#define   Led2_off()           
#define   Led2_toggle()        
#define   Led3_on()            
#define   Led3_off()           
#define   Led3_toggle()        


// PUSHBUTTONS
// ***********
#define   Joy_init()                Cbi(DDRC, BIT5|BIT6);Cbi(DDRB, BIT0|BIT1);Sbi(PORTC, BIT5|BIT6);Sbi(PORTB, BIT0|BIT1);
#define   Push_button_init()        Joy_init()

#define   Is_joy_left()             (((PINC&BIT5) == 0) ? TRUE : FALSE)    
#define   Is_joy_not_left()         (((PINC&BIT5) == 0) ? FALSE : TRUE)
#define   Is_button_left()          Is_joy_left()
#define   Is_button_not_left()      Is_joy_not_left()

#define   Is_joy_middle()           FALSE
#define   Is_joy_not_middle()       TRUE
#define   Is_joy_select()           Is_joy_middle()
#define   Is_joy_not_select()       Is_joy_not_middle()
#define   Is_button_middle()        Is_joy_middle()
#define   Is_button_not_middle()    Is_joy_not_middle()

#define   Is_joy_right()            (((PINC&BIT6) == 0) ? TRUE : FALSE)
#define   Is_joy_not_right()        (((PINC&BIT6) == 0) ? FALSE : TRUE)
#define   Is_button_right()         Is_joy_right()
#define   Is_button_not_right()     Is_joy_not_right()

#define   Is_joy_down()             (((PINB&BIT1) == 0) ? TRUE : FALSE)
#define   Is_joy_not_down()         (((PINB&BIT1) == 0) ? FALSE : TRUE)
#define   Is_button_down()          Is_joy_down()
#define   Is_button_not_down()      Is_joy_not_down()

#define   Is_joy_up()               (((PINB&BIT0) == 0) ? TRUE : FALSE)
#define   Is_joy_not_up()           (((PINB&BIT0) == 0) ? FALSE : TRUE)
#define   Is_button_up()            Is_joy_up()
#define   Is_button_not_up()        Is_joy_not_up()


#define   Hwb_button_init()         Cbi(DDRD, BIT1);Sbi(PORTD, BIT1)
#define   Is_hwb()                  (((PIND&BIT1) == 0) ? TRUE : FALSE)



//! @defgroup Philips Wired mouse ATMEL Hardware data flash configuration
      //! Macros to init the environnement for DF on Philips Wired mouse board
      //! @{

#define DF_8_MB   // Type of DF implemented.


#define DF_SELECT_MEM        0
#define DF_UNSELECT_MEM      1
#define DF_NB_MEM            1

#ifndef AVRGCC
   // PORTB_Bit0=1,DDRB_Bit0=0: SPI Slave Select Input. The data direction of the
   //    NOT(SS) is INPUT and the pull-up resistor is activated.
   // DDRB_Bit1=1: the SCK signal direction is OUTPUT.
   // DDRB_Bit2=1: the SI signal direction is OUTPUT.
   // DDRB_Bit3=0: the SO signal direction is INPUT.
   // PORTB_Bit4=1,DDRB_Bit4=1: CS driven high
   //    and both CS are OUTPUT.

   #define Init_df_stk526()   (DDRC_Bit2=1,PORTC_Bit2=1,DDRB_Bit0=1)
   #define DF_CS_PIN          PORTC_Bit2
   #define DF_CS0             DF_CS_PIN
   #define DF_CS1             DF_CS0
   #define DF_CS2             DF_CS0
   #define DF_CS3             DF_CS0
   #define Df_select_df(i, val) (DF_CS##i = val)
   #define Df_desel_all()       (DF_CS0=DF_UNSELECT_MEM)     // set CS# dataflash memories
#else //! for AVRGCC
   #define Init_df_stk526()   (DDRC |=(1<<DF_CS0), PORTC|=(1<<DF_CS0), PORTB |= (1<<0))
   #define DF_CS_PORT         PORTC
   #define DF_CS0             2
   #define DF_CS1             DF_CS0
   #define DF_CS2             DF_CS0
   #define DF_CS3             DF_CS0
   #define Df_desel_all()     (DF_CS_PORT|=(1<<DF_CS0)) // set CS# dataflash memories (unselect).
#endif
#define df_init_spi()      Init_df_stk526()
      //! @}


