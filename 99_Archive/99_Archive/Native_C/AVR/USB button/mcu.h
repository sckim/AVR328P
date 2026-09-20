/*H**************************************************************************
* NAME:         mcu.h
*----------------------------------------------------------------------------
* Copyright (c) 2006 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      at90usb162-2enum-mouse_ms-1_0_1
* REVISION:     1.5
*----------------------------------------------------------------------------
* PURPOSE:
* SFR Description file for at90usb16.
*****************************************************************************/
#ifndef MCU_H
#define MCU_H

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/******************************************************************************/
#if defined(__ICCAVR__) || defined(__IAR_SYSTEMS_ASM__)
/******************************************************************************/

SFR_B(PINB,   0x03)   /* Input Pins, Port B                      */
SFR_B(DDRB,   0x04)   /* Data Direction Register, Port B         */
SFR_B(PORTB,  0x05)   /* Data Register, Port B                   */

SFR_B(PINC,   0x06)   /* Input Pins, Port C                      */
SFR_B(DDRC,   0x07)   /* Data Direction Register, Port C         */
SFR_B(PORTC,  0x08)   /* Data Register, Port C                   */

SFR_B(PIND,   0x09)   /* Input Pins, Port D                      */
SFR_B(DDRD,   0x0A)   /* Data Direction Register, Port D         */
SFR_B(PORTD,  0x0B)   /* Data Register, Port D                   */

SFR_B(TIFR0,  0x15)   /* Timer/Counter Interrupt Flag register 0 */
SFR_B(TIFR1,  0x16)   /* Timer/Counter Interrupt Flag register 1 */

SFR_B(PCIFR,  0x1B)   /* Pin Change Interrupt Flag Register      */

SFR_B(EIFR,   0x1C)   /* External Interrupt Flag Register        */
SFR_B(EIMSK,  0x1D)   /* External Interrupt Mask Register        */

SFR_B(GPIOR0, 0x1E)   /* General Purpose Register 0              */

SFR_B(EECR,   0x1F)   /* EEPROM Control Register                 */
SFR_B(EEDR,   0x20)   /* EEPROM Data Register                    */
SFR_W(EEAR,   0x21)   /* EEPROM Address Register                 */

SFR_B(GTCCR,  0x23)   /* General Purpose Register                */

SFR_B(TCCR0A, 0x24)   /* Timer/Counter 0 Control Register        */
SFR_B(TCCR0B, 0x25)   /* Timer/Counter 0 Control Register        */
SFR_B(TCNT0,  0x26)   /* Timer/Counter 0                         */
SFR_B(OCR0A,  0x27)   /* Timer/Counter 0 Output Compare Register */
SFR_B(OCR0B,  0x28)   /* Timer/Counter 0 Output Compare Register */

SFR_B(PLLCSR, 0x29)   /* PLL Control and Status Register         */

SFR_B(GPIOR1, 0x2A)   /* General Purpose Register 1              */
SFR_B(GPIOR2, 0x2B)   /* General Purpose Register 2              */

SFR_B(SPCR,   0x2C)   /* SPI Control Register                    */
SFR_B(SPSR,   0x2D)   /* SPI Status Register                     */
SFR_B(SPDR,   0x2E)   /* SPI I/O Data Register                   */

SFR_B(ACSR,   0x30)   /* Analog Comparator Control and Status Register */

SFR_B(DWDR,   0x31)   /* DebugWire Register                      */

SFR_B(SMCR,   0x33)   /* Sleep Mode Control Register             */
SFR_B(MCUSR,  0x34)   /* MCU Status Register                     */
SFR_B(MCUCR,  0x35)   /* MCU Control Register                    */

SFR_B(SPMCSR, 0x37)   /* Store Program Memory Control and Status Register */

SFR_W(SP,     0x3D)   /* Stack Pointer                           */
SFR_B(SREG,   0x3F)   /* Status Register                         */

SFR_B_EXT(WDTCR,   0x60)   /* Watchdog Timer Control Register for compatibility */
SFR_B_EXT(WDTCSR,  0x60)   /* Watchdog Timer Control Register                   */
SFR_B_EXT(CLKPR,   0x61)   /* Clock Prescale Register                           */
SFR_B_EXT(WDTCKD,  0x62)   /* Watchdog Timer Clock Divider and Early Interrupt  */

SFR_B_EXT(REGCR,   0x63)   /* Regulator Control Register */

SFR_B_EXT(OSCCAL,  0x66)   /* Oscillator Calibration Register                   */

SFR_B_EXT(PCICR,   0x68)   /* Pin Change interrupt enable                       */

SFR_B_EXT(EICRA,   0x69)   /* External Interrupt Control Register A             */
SFR_B_EXT(EICRB,   0x6A)   /* External Interrupt Control Register B             */

SFR_B_EXT(PCMSK0,  0x6B)   /* Pin Change interrupt mask                         */
SFR_B_EXT(PCMSK1,  0x6C)   /* Pin Change interrupt mask                         */

SFR_B_EXT(TIMSK0,  0x6E)   /* Timer/Counter 0 Interrupt Mask Register           */
SFR_B_EXT(TIMSK1,  0x6F)   /* Timer/Counter 1 Interrupt Mask Register           */

SFR_B_EXT(TCCR1A,  0x80)   /* Timer/Counter 1 Control Register A                */
SFR_B_EXT(TCCR1B,  0x81)   /* Timer/Counter 1 Control Register B                */
SFR_B_EXT(TCCR1C,  0x82)   /* Timer/Counter 1 Control Register C                */
SFR_W_EXT(TCNT1,   0x84)   /* Timer/Counter 1 Register                          */
SFR_W_EXT(ICR1,    0x86)   /* Timer/Counter 1 Input Capture Register            */
SFR_W_EXT(OCR1A,   0x88)   /* Timer/Counter 1 Output Compare Register A         */
SFR_W_EXT(OCR1B,   0x8A)   /* Timer/Counter 1 Output Compare Register B         */
SFR_W_EXT(OCR1C,   0x8C)   /* Timer/Counter 1 Output Compare Register C         */

SFR_B_EXT(UCSR1A,  0xC8)   /* USART1 Control and Status Register A              */
SFR_B_EXT(UCSR1B,  0xC9)   /* USART1 Control and Status Register B              */
SFR_B_EXT(UCSR1C,  0xCA)   /* USART1 Control and Status Register C              */
SFR_B_EXT(UCSR1D,  0xCB)   /* USART1 Control and Status Register D              */
SFR_W_EXT(UBRR1,   0xCC)   /* USART1 Baud Rate Register Low                     */
SFR_B_EXT(UDR1,    0xCE)   /* USART1 I/O Data Register                          */


// USB CONTROLLER
// USB General
// Page 1
SFR_B_EXT(USBCON,    0xD8);
SFR_B_EXT(UDPADDL,   0xDB);
SFR_B_EXT(UDPADDH,   0xDC);

// USB Device
// Page 1
SFR_B_EXT(UDCON,     0xE0);
SFR_B_EXT(UDINT,     0xE1);
SFR_B_EXT(UDIEN,     0xE2);
SFR_B_EXT(UDADDR,    0xE3);
SFR_B_EXT(UDFNUML,   0xE4);
SFR_B_EXT(UDFNUMH,   0xE5);
SFR_B_EXT(UDMFN,     0xE6);
SFR_B_EXT(UDTST,     0xE7);

// USB Endpoint
// Page 1
SFR_B_EXT(UENUM,     0xE9);
SFR_B_EXT(UERST,     0xEA);
SFR_B_EXT(UECONX,    0xEB);
SFR_B_EXT(UECFG0X,   0xEC);
SFR_B_EXT(UECFG1X,   0xED);
SFR_B_EXT(UESTA0X,   0xEE);
SFR_B_EXT(UESTA1X,   0xEF);
SFR_B_EXT(UEINTX,    0xE8);
SFR_B_EXT(UEIENX,    0xF0);
SFR_B_EXT(UEDATX,    0xF1);
SFR_B_EXT(UEBCLX,    0xF2);
SFR_B_EXT(UEINT,     0xF4);

// PS2 and USB
SFR_B_EXT(PS2CON,    0xFA);
SFR_B_EXT(UPOE,      0xFB);

// Clock Switching
SFR_B_EXT(CKSEL0,    0xD0);
SFR_B_EXT(CKSEL1,    0xD1);
SFR_B_EXT(CKSTA,     0xD2);


/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/
/* NB! vectors are specified as byte addresses */
#define    RESET_vect                  (0x00)
#define    INT0_vect                   (0x04)
#define    INT1_vect                   (0x08)
#define    INT2_vect                   (0x0C)
#define    INT3_vect                   (0x10)
#define    INT4_vect                   (0x14)
#define    INT5_vect                   (0x18)
#define    INT6_vect                   (0x1C)
#define    INT7_vect                   (0x20)
#define    PCINT0_vect	               (0x24)
#define    PCINT1_vect	               (0x28)
#define    USB_GENERAL_vect            (0x2C)
#define    USB_ENDPOINT_vect           (0x30)
#define    WDT_vect                    (0x34)
#define    TIMER1_CAPT_vect            (0x38)
#define    TIMER1_COMPA_vect           (0x3C)
#define    TIMER1_COMPB_vect           (0x40)
#define    TIMER1_COMPC_vect           (0x44)
#define    TIMER1_OVF_vect             (0x48)
#define    TIMER0_COMPA_vect           (0x4C)
#define    TIMER0_COMPB_vect           (0x50)
#define    TIMER0_OVF_vect             (0x54)
#define    SPI_STC_vect                (0x58)
#define    USART1_RXC_vect             (0x5C)
#define    USART1_UDRE_vect            (0x60)
#define    USART1_TXC_vect             (0x64)
#define    ANA_COMP_vect               (0x68)
#define    EE_RDY_vect                 (0x6C)
#define    SPM_RDY_vect                (0x70)
//#define                                (0x74)

#endif /* _IAR_ */
/******************************************************************************/
#ifdef __CODEVISIONAVR__
/******************************************************************************/

#define PINB    (*(volatile unsigned char *)0x23) /* Input Pins, Port B                      */
#define DDRB    (*(volatile unsigned char *)0x24) /* Data Direction Register, Port B         */
#define PORTB   (*(volatile unsigned char *)0x25) /* Data Register, Port B                   */

#define PINC    (*(volatile unsigned char *)0x26) /* Input Pins, Port C                      */
#define DDRC    (*(volatile unsigned char *)0x27) /* Data Direction Register, Port C         */
#define PORTC   (*(volatile unsigned char *)0x28) /* Data Register, Port C                   */

#define PIND    (*(volatile unsigned char *)0x29) /* Input Pins, Port D                      */
#define DDRD    (*(volatile unsigned char *)0x2A) /* Data Direction Register, Port D         */
#define PORTD   (*(volatile unsigned char *)0x2B) /* Data Register, Port D                   */

#define TIFR0   (*(volatile unsigned char *)0x35) /* Timer/Counter Interrupt Flag register 0 */
#define TIFR1   (*(volatile unsigned char *)0x36) /* Timer/Counter Interrupt Flag register 1 */

#define PCIFR   (*(volatile unsigned char *)0x3B) /* Pin Change Interrupt Flag Register      */

#define EIFR    (*(volatile unsigned char *)0x3C) /* External Interrupt Flag Register        */
#define EIMSK   (*(volatile unsigned char *)0x3D) /* External Interrupt Mask Register        */

#define GPIOR0  (*(volatile unsigned char *)0x3E) /* General Purpose Register 0              */

#define EECR    (*(volatile unsigned char *)0x3F) /* EEPROM Control Register                 */
#define EEDR    (*(volatile unsigned char *)0x40) /* EEPROM Data Register                    */
#define EEAR    (*(volatile unsigned int  *)0x41) /* EEPROM Address Register                 */

#define GTCCR   (*(volatile unsigned char *)0x43) /* General Purpose Register                */

#define TCCR0A  (*(volatile unsigned char *)0x44) /* Timer/Counter 0 Control Register        */
#define TCCR0B  (*(volatile unsigned char *)0x45) /* Timer/Counter 0 Control Register        */
#define TCNT0   (*(volatile unsigned char *)0x46) /* Timer/Counter 0                         */
#define OCR0A   (*(volatile unsigned char *)0x47) /* Timer/Counter 0 Output Compare Register */
#define OCR0B   (*(volatile unsigned char *)0x48) /* Timer/Counter 0 Output Compare Register */

#define PLLCSR  (*(volatile unsigned char *)0x49) /* PLL Control and Status Register         */

#define GPIOR1  (*(volatile unsigned char *)0x4A) /* General Purpose Register 1              */
#define GPIOR2  (*(volatile unsigned char *)0x4B) /* General Purpose Register 2              */

#define SPCR    (*(volatile unsigned char *)0x4C) /* SPI Control Register                    */
#define SPSR    (*(volatile unsigned char *)0x4D) /* SPI Status Register                     */
#define SPDR    (*(volatile unsigned char *)0x4E) /* SPI I/O Data Register                   */

#define ACSR    (*(volatile unsigned char *)0x50) /* Analog Comparator Control and Status Register */

#define DWDR    (*(volatile unsigned char *)0x51) /* DebugWire Register                      */

#define SMCR    (*(volatile unsigned char *)0x53) /* Sleep Mode Control Register             */
#define MCUSR   (*(volatile unsigned char *)0x54) /* MCU Status Register                     */
#define MCUCR   (*(volatile unsigned char *)0x55) /* MCU Control Register                    */

#define SPMCSR  (*(volatile unsigned char *)0x57) /* Store Program Memory Control and Status Register */

#define SP      (*(volatile unsigned int  *)0x5D) /* Stack Pointer                           */
#define SREG    (*(volatile unsigned char *)0x5F) /* Status Register                         */

#define WDTCR   (*(volatile unsigned char *)0x60) /* Watchdog Timer Control Register         */
#define CLKPR   (*(volatile unsigned char *)0x61) /* Clock Prescale Register                 */
#define OSCCAL  (*(volatile unsigned char *)0x66) /* Oscillator Calibration Register         */


#define PCICR   (*(volatile unsigned char *)0x68) /* Pin Change interrupt enable             */

#define EICRA   (*(volatile unsigned char *)0x69) /* External Interrupt Control Register A   */
#define EICRB   (*(volatile unsigned char *)0x6A) /* External Interrupt Control Register B   */

#define PCMSK0  (*(volatile unsigned char *)0x6B) /* Pin Change interrupt mask               */
#define PCMSK1  (*(volatile unsigned char *)0x6C) /* Pin Change interrupt mask               */

#define TIMSK0  (*(volatile unsigned char *)0x6E) /* Timer/Counter 0 Interrupt Mask Register */
#define TIMSK1  (*(volatile unsigned char *)0x6F) /* Timer/Counter 1 Interrupt Mask Register */

#define TCCR1A  (*(volatile unsigned char *)0x80) /* Timer/Counter 1 Control Register A      */
#define TCCR1B  (*(volatile unsigned char *)0x81) /* Timer/Counter 1 Control Register B      */
#define TCCR1C  (*(volatile unsigned char *)0x82) /* Timer/Counter 1 Control Register C      */
#define TCNT1   (*(volatile unsigned int  *)0x84) /* Timer/Counter 1 Register                */
#define ICR1    (*(volatile unsigned int  *)0x86) /* Timer/Counter 1 Input Capture Register  */
#define OCR1A   (*(volatile unsigned int  *)0x88) /* Timer/Counter 1 Output Compare Register A */
#define OCR1B   (*(volatile unsigned int  *)0x8A) /* Timer/Counter 1 Output Compare Register B */
#define OCR1C   (*(volatile unsigned int  *)0x8C) /* Timer/Counter 1 Output Compare Register C */

#define UCSR1A  (*(volatile unsigned char *)0xC8) /* USART1 Control and Status Register A    */
#define UCSR1B  (*(volatile unsigned char *)0xC9) /* USART1 Control and Status Register B    */
#define UCSR1C  (*(volatile unsigned char *)0xCA) /* USART1 Control and Status Register C    */
#define UBRR1   (*(volatile unsigned int  *)0xCC) /* USART1 Baud Rate Register               */
#define UBRR1L  (*(volatile unsigned char *)0xCC) /* USART1 Baud Rate Register Low           */
#define UBRR1H  (*(volatile unsigned char *)0xCD) /* USART1 Baud Rate Register High          */
#define UDR1    (*(volatile unsigned char *)0xCE) /* USART1 I/O Data Register                */

// USB CONTROLLER
// USB General
// Page 1
#define USBCON  (*(volatile unsigned char *)0xD8) /*   */
#define UDPADDL (*(volatile unsigned char *)0xDB) /*   */
#define UDPADDH (*(volatile unsigned char *)0xDC) /*   */

// USB Device
// Page 1
#define UDCON   (*(volatile unsigned char *)0xE0) /*   */
#define UDINT   (*(volatile unsigned char *)0xE1) /*   */
#define UDIEN   (*(volatile unsigned char *)0xE2) /*   */
#define UDADDR  (*(volatile unsigned char *)0xE3) /*   */
#define UDFNUML (*(volatile unsigned char *)0xE4) /*   */
#define UDFNUMH (*(volatile unsigned char *)0xE5) /*   */
#define UDMFN   (*(volatile unsigned char *)0xE6) /*   */
#define UDTST   (*(volatile unsigned char *)0xE7) /*   */

// USB Endpoint
// Page 1
#define UENUM   (*(volatile unsigned char *)0xE9) /*   */
#define UERST   (*(volatile unsigned char *)0xEA) /*   */
#define UECONX  (*(volatile unsigned char *)0xEB) /*   */
#define UECFG0X (*(volatile unsigned char *)0xEC) /*   */
#define UECFG1X (*(volatile unsigned char *)0xED) /*   */
#define UESTA0X (*(volatile unsigned char *)0xEE) /*   */
#define UESTA1X (*(volatile unsigned char *)0xEF) /*   */
#define UEINTX  (*(volatile unsigned char *)0xE8) /*   */
#define UEIENX  (*(volatile unsigned char *)0xF0) /*   */
#define UEDATX  (*(volatile unsigned char *)0xF1) /*   */
#define UEBCLX  (*(volatile unsigned char *)0xF2) /*   */
#define UEINT   (*(volatile unsigned char *)0xF4) /*   */

// PS2 and USB
#define PS2CON  (*(volatile unsigned char *)0xFA) /*   */
#define UPOE    (*(volatile unsigned char *)0xFB) /*   */

// Clock Switching
#define CKSEL0  (*(volatile unsigned char *)0xD0) /*   */
#define CKSEL1  (*(volatile unsigned char *)0xD1) /*   */
#define CKSTA   (*(volatile unsigned char *)0xD2) /*   */


/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/
/* NB! vectors are specified as byte addresses */
#define    RESET_vect           1
#define    INT0_vect            2
#define    INT1_vect            3
#define    INT2_vect            4
#define    INT3_vect            5
#define    INT4_vect            6
#define    INT5_vect            7
#define    INT6_vect            8
#define    INT7_vect            9
#define    PCINT0_vect          10
#define    PCINT1_vect          11
#define    USB_GENERAL_vect     12
#define    USB_ENDPOINT_vect    13
#define    WDT_vect             14
#define    TIMER1_CAPT_vect     15
#define    TIMER1_COMPA_vect    16
#define    TIMER1_COMPB_vect    17
#define    TIMER1_COMPC_vect    18
#define    TIMER1_OVF_vect	19	 					
#define    TIMER0_COMPA_vect    20 		
#define    TIMER0_COMPB_vect    21
#define    TIMER0_OVF_vect      22
#define    SPI_STC_vect         23
#define    USART1_RXC_vect      24
#define    USART1_UDRE_vect     25
#define    USART1_TXC_vect      26
#define    ANA_COMP_vect        27
#define    EE_RDY_vect          28
#define    SPM_RDY_vect         29

#endif /* _ICC_*/



/*==========================*/
/* Bit Position Definitions */
/*==========================*/
/* PINB : Input Pins, Port B */
#define    PINB7    7
#define    PINB6    6
#define    PINB5    5
#define    PINB4    4
#define    PINB3    3
#define    PINB2    2
#define    PINB1    1
#define    PINB0    0

/* DDRB : Data Direction Register, Port B */
#define    DDB7     7
#define    DDB6     6
#define    DDB5     5
#define    DDB4     4
#define    DDB3     3
#define    DDB2     2
#define    DDB1     1
#define    DDB0     0

/* PORTB : Data Register, Port B */
#define    PB7      7
#define    PB6      6
#define    PB5      5
#define    PB4      4
#define    PB3      3
#define    PB2      2
#define    PB1      1
#define    PB0      0

/* PORTB : Data Register, Port B */
#define    PORTB7   7
#define    PORTB6   6
#define    PORTB5   5
#define    PORTB4   4
#define    PORTB3   3
#define    PORTB2   2
#define    PORTB1   1
#define    PORTB0   0

/* PINC : Input Pins, Port C */
#define    PINC7    7
#define    PINC6    6
#define    PINC5    5
#define    PINC4    4
//#define    PINC3    3
#define    PINC2    2
#define    PINC1    1
#define    PINC0    0

/* DDRC : Data Direction Register, Port C */
#define    DDC7     7
#define    DDC6     6
#define    DDC5     5
#define    DDC4     4
//#define    DDC3     3
#define    DDC2     2
#define    DDC1     1
#define    DDC0     0

/* PORTC : Data Register, Port C */
#define    PC7      7
#define    PC6      6
#define    PC5      5
#define    PC4      4
//#define    PC3      3
#define    PC2      2
#define    PC1      1
#define    PC0      0

/* PORTC : Data Register, Port C */
#define    PORTC7   7
#define    PORTC6   6
#define    PORTC5   5
#define    PORTC4   4
//#define    PORTC3   3
#define    PORTC2   2
#define    PORTC1   1
#define    PORTC0   0

/* PIND : Input Pins, Port D */
#define    PIND7    7
#define    PIND6    6
#define    PIND5    5
#define    PIND4    4
#define    PIND3    3
#define    PIND2    2
#define    PIND1    1
#define    PIND0    0

/* DDRD : Data Direction Register, Port D */
#define    DDD7     7
#define    DDD6     6
#define    DDD5     5
#define    DDD4     4
#define    DDD3     3
#define    DDD2     2
#define    DDD1     1
#define    DDD0     0

/* PORTD : Data Register, Port D */
#define    PD7      7
#define    PD6      6
#define    PD5      5
#define    PD4      4
#define    PD3      3
#define    PD2      2
#define    PD1      1
#define    PD0      0

/* PORTD : Data Register, Port D */
#define    PORTD7   7
#define    PORTD6   6
#define    PORTD5   5
#define    PORTD4   4
#define    PORTD3   3
#define    PORTD2   2
#define    PORTD1   1
#define    PORTD0   0

/* TFR0 : Timer/Counter Interrupt Flag Register 0 */
#define    OCF0B    2
#define    OCF0A    1
#define    TOV0     0

/* TFR1 : Timer/Counter Interrupt Flag Register 1 */
#define    ICF1     5
#define    OCF1C    3
#define    OCF1B    2
#define    OCF1A    1
#define    TOV1     0

/* EIFR : External Interrupt Flag Register */
#define    INTF7    7
#define    INTF6    6
#define    INTF5    5
#define    INTF4    4
#define    INTF3    3
#define    INTF2    2
#define    INTF1    1
#define    INTF0    0

/* EIMSK : External Interrupt Mask Register */
#define    INT7     7
#define    INT6     6
#define    INT5     5
#define    INT4     4
#define    INT3     3
#define    INT2     2
#define    INT1     1
#define    INT0     0

/* EICRA : External Interrupt Control Register A*/
#define    ISC31     7
#define    ISC30     6
#define    ISC21     5
#define    ISC20     4
#define    ISC11     3
#define    ISC10     2
#define    ISC01     1
#define    ISC00     0

/* EICRB : External Interrupt Control Register B*/
#define    ISC71     7
#define    ISC70     6
#define    ISC61     5
#define    ISC60     4
#define    ISC51     3
#define    ISC50     2
#define    ISC41     1
#define    ISC40     0

/* EECR : EEPROM Control Register */
#define    EEPM1    5
#define    EEPM0    4
#define    EERIE    3
#define    EEMWE    2
#define    EEWE     1
#define    EERE     0

/* GTCCR : General Timer Control Register */
#define    TSM      7
#define    PSR2     1
#define    PSR310   0


/* TCCR0A : Timer/Counter 0 Control Register */
#define    COM0A1   7
#define    COM0A0   6
#define    COM0B1   5
#define    COM0B0   4
#define    WGM01    1
#define    WGM00    0

/* TCCR0B : Timer/Counter 0 Control Register */
#define    FOC0A    7
#define    FOC0B    6
#define    WGM02    3
#define    CS02     2
#define    CS01     1
#define    CS00     0

/* SPCR : SPI Control Register */
#define    SPIE     7
#define    SPE      6
#define    DORD     5
#define    MSTR     4
#define    CPOL     3
#define    CPHA     2
#define    SPR1     1
#define    SPR0     0

/* SPSR : SPI Status Register */
#define    SPIF     7
#define    WCOL     6
#define    SPI2X    0

/* ACSR : Analog Comparator Control and Status Register */
#define    ACD      7
#define    ACBG     6
#define    ACO      5
#define    ACI      4
#define    ACIE     3
#define    ACIC     2
#define    ACIS1    1
#define    ACIS0    0

/* DWDR : DebugWire Register */
#define    DWR7     7
#define    DWR6     6
#define    DWR5     5
#define    DWR4     4
#define    DWR3     3
#define    DWR2     2
#define    DWR1     1
#define    DWR0     0

/* SMCR : Sleep Mode Control Register */
#define    SM2      3
#define    SM1      2
#define    SM0      1
#define    SE       0

/* MCUSR : MCU general Status Register */
#define    USBRF    5
#define    DWRF     4
#define    WDRF     3
#define    BORF     2
#define    EXTRF    1
#define    PORF     0

/* MCUCR : MCU general Control Register */
#define    DWD      7
#define    PUD      4
#define    IVSEL    1
#define    IVCE     0

/* SPMCR : Store Program Memory Control and Status Register */
#define    SPMIE    7
#define    RWWSB    6
#define    SIGRD    5
#define    RWWSRE   4
#define    BLBSET   3
#define    PGWRT    2
#define    PGERS    1
#define    SPMEN    0

/* SPH : Stack Pointer High */
#define    SP15     7
#define    SP14     6
#define    SP13     5
#define    SP12     4
#define    SP11     3
#define    SP10     2
#define    SP9      1
#define    SP8      0

/* SPL : Stack Pointer Low */
#define    SP7      7
#define    SP6      6
#define    SP5      5
#define    SP4      4
#define    SP3      3
#define    SP2      2
#define    SP1      1
#define    SP0      0

/* WTDCR : Watchdog Timer Control Register */
#define    WDIF     7
#define    WDIE     6
#define    WDP3     5
#define    WDCE     4
#define    WDE      3
#define    WDP2     2
#define    WDP1     1
#define    WDP0     0

/* WDTCKD : Watchdog Clock Divider and Interrupt Register */
#define    WDEWIF   3
#define    WDEWIE   2
#define    WCLKD1   1
#define    WCLKD0   0

/* CLKPR : Source Clock Prescaler Register */
#define    CKLPCE   7
#define    CLKPCE   7 //for compatiblity
#define    CKLPS3   3
#define    CKLPS2   2
#define    CKLPS1   1
#define    CKLPS0   0

/* TIMSK0 : Timer Interrupt Mask Register0 */
#define    OCIE0B   2
#define    OCIE0A   1
#define    TOIE0    0

/* TIMSK1 : Timer Interrupt Mask Register1 */
#define    ICIE1    5
#define    OCIE1C   3
#define    OCIE1B   2
#define    OCIE1A   1
#define    TOIE1    0

/* TCCR1A : Timer/Counter 1 Control Register A */
#define    COM1A1   7
#define    COM1A0   6
#define    COM1B1   5
#define    COM1B0   4
#define    COM1C1   3
#define    COM1C0   2
#define    WGM11    1
#define    WGM10    0

/* TCCR1B : Timer/Counter 1 Control Register B */
#define    ICNC1    7
#define    ICES1    6
#define    WGM13    4
#define    WGM12    3
#define    CS12     2
#define    CS11     1
#define    CS10     0

/* TCCR1C : Timer/Counter 1 Control Register C */
#define    FOC1A    7
#define    FOC1B    6
#define    FOC1C    5

/* UCSR0A : USART0 Control and Status Register A */
#define    RXC0     7
#define    TXC0     6
#define    UDRE0    5
#define    FE0      4
#define    DOR0     3
#define    UPE0     2
#define    U2X0     1
#define    MPCM0    0

/* UCSR1A : USART1 Control and Status Register A */
#define    RXC1     7
#define    TXC1     6
#define    UDRE1    5
#define    FE1      4
#define    DOR1     3
#define    UPE1     2
#define    U2X1     1
#define    MPCM1    0

/* UCSR1B : USART1 Control and Status Register B */
#define    RXCIE1   7
#define    TXCIE1   6
#define    UDRIE1   5
#define    RXEN1    4
#define    TXEN1    3
#define    UCSZ12   2
#define    RXB81    1
#define    TXB81    0

/* UCSR1C : USART1 Control and Status Register C */
#define    UMSEL11  7
#define    UMSEL10  6
#define    UMSEL1   6  // for compatibility
#define    UPM11    5
#define    UPM10    4
#define    USBS1    3
#define    UCSZ11   2
#define    UCSZ10   1
#define    UCPOL1   0

/* UCSR1D : USART1 Control and Status Register D */
#define    CTSEN    1
#define    RTSEN    0

/* PCICR Pin Change Interrupt control */
#define    PCIE1    1
#define    PCIE0    0

/* PCIFR Pin Change Interrupt flag */
#define    PCIF1    1
#define    PCIF0    0

/* ***** USB_DEVICE ******************* */
/* UDCON -  */
#define    DETACH          0       //
#define    RMWKUP          1       //
#define    RSTCPU          2       //

/* UDINT -  */
#define    SUSPI           0       //
//#define    MSOFI           1       //
#define    SOFI            2       //
#define    EORSTI          3       //
#define    WAKEUPI         4       //
#define    EORSMI          5       //
#define    UPRSMI          6       //

/* UDIEN -  */
#define    SUSPE           0       //
//#define    MSOFE           1       //
#define    SOFE            2       //
#define    EORSTE          3       //
#define    WAKEUPE         4       //
#define    EORSME          5       //
#define    UPRSME          6       //

/* UDADDR -  */
#define    UDADDR0         0       //
#define    UDADDR1         1       //
#define    UDADDR2         2       //
#define    UDADDR3         3       //
#define    UDADDR4         4       //
#define    UDADDR5         5       //
#define    UDADDR6         6       //
#define    ADDEN           7       //

/* UDFNUML -  */
#define    UDFNUML_0       0       //
#define    UDFNUML_1       1       //
#define    UDFNUML_2       2       //
#define    UDFNUML_3       3       //
#define    UDFNUML_4       4       //
#define    UDFNUML_5       5       //
#define    UDFNUML_6       6       //
#define    UDFNUML_7       7       //

/* UDFNUMH -  */
#define    UDFNUMH_0       0       //
#define    UDFNUMH_1       1       //
#define    UDFNUMH_2       2       //

/* UDMFN -  */
#define    FNCERR          4       //

/* UEINTX -  */
#define    TXINI           0       //
#define    STALLEDI        1       //
#define    RXOUTI          2       //
#define    RXSTPI          3       //
#define    NAKOUTI         4       //
#define    RWAL            5       //
#define    NAKINI          6       //
#define    FIFOCON         7       //

/* UENUM -  */
#define    UENUM_0         0       //
#define    UENUM_1         1       //
#define    UENUM_2         2       //

/* UERST -  */
#define    EPRST0          0       //
#define    EPRST1          1       //
#define    EPRST2          2       //
#define    EPRST3          3       //
#define    EPRST4          4       //
#define    EPRST5          5       //
#define    EPRST6          6       //

/* UECONX -  */
#define    EPEN            0       //
#define    RSTDT           3       //
#define    STALLRQC        4       //
#define    STALLRQ         5       //

/* UECFG0X -  */
#define    EPDIR           0       //
#define    NYETDIS         1       //
#define    AUTOSW          2       //
#define    ISOSW           3       //
#define    EPTYPE0         6       //
#define    EPTYPE1         7       //

/* UECFG1X -  */
#define    ALLOC           1       //
#define    EPBK0           2       //
#define    EPBK1           3       //
#define    EPSIZE0         4       //
#define    EPSIZE1         5       //
#define    EPSIZE2         6       //

/* UESTA0X -  */
#define    NBUSYBK0        0       //
#define    NBUSYBK1        1       //
#define    DTSEQ0          2       //
#define    DTSEQ1          3       //
#define    ZLPSEEN         4       //
#define    UNDERFI         5       //
#define    OVERFI          6       //
#define    CFGOK           7       //

/* UESTA1X -  */
#define    CURRBK0         0       //
#define    CURRBK1         1       //
#define    CTRLDIR         2       //

/* UEIENX -  */
#define    TXINE           0       //
#define    STALLEDE        1       //
#define    RXOUTE          2       //
#define    RXSTPE          3       //
#define    NAKOUTE         4       //
#define    NAKINE          6       //
#define    FLERRE          7       //

/* UEDATX -  */
#define    UEDATX_0        0       //
#define    UEDATX_1        1       //
#define    UEDATX_2        2       //
#define    UEDATX_3        3       //
#define    UEDATX_4        4       //
#define    UEDATX_5        5       //
#define    UEDATX_6        6       //
#define    UEDATX_7        7       //

/* UEBCLX -  */
#define    UEBCLX_0        0       //
#define    UEBCLX_1        1       //
#define    UEBCLX_2        2       //
#define    UEBCLX_3        3       //
#define    UEBCLX_4        4       //
#define    UEBCLX_5        5       //
#define    UEBCLX_6        6       //
#define    UEBCLX_7        7       //

/* UEBCHX -  */
#define    UEBCHX_0        0       //
#define    UEBCHX_1        1       //
#define    UEBCHX_2        2       //

/* UEINT -  */
#define    UEINT_0         0       //
#define    UEINT_1         1       //
#define    UEINT_2         2       //
#define    UEINT_3         3       //
#define    UEINT_4         4       //
#define    UEINT_5         5       //
#define    UEINT_6         6       //


/* ***** USB_GLOBAL ******************* */

/* USBCON - USB General Control Register */
//#define    VBUSTE          0       //
//#define    IDTE            1       //
//#define    OTGPADE         4       //
#define    FRZCLK          5       //
//#define    HOST            6       //
#define    USBE            7       //

/* USBSTA -  */
//#define    VBUS            0       //
//#define    ID              1       //
//#define    SPEED1          3       //

/* USBINT -  */
//#define    VBUSTI          0       //
//#define    IDTI            1       //

/* ***** USB PS2 ******************** */

/* PS2CON - PS2 Control Register */
#define    PS2EN           0

/* UPOE - USB PS2 Output Enable Register */
#define    UPWE1           7
#define    UPWE0           6
#define    UPDRV1          5
#define    UPDRV0          4
#define    SCKI            3
#define    DATAI           2
#define    DPI             1
#define    DMI             0


/* ***** Clock Switching ************ */

/* CKSEL0 - Clock Selection Register 0 */
#define    RCSUT1          7
#define    RCSUT0          6
#define    EXSUT1          5
#define    EXSUT0          4
#define    RCE             3
#define    EXTE            2
#define    CLKS            0

/* CKSEL1 - Clock Selection Register 1 */
#define    RCCKSEL3        7
#define    RCCKSEL2        6
#define    RCCKSEL1        5
#define    RCCKSEL0        4
#define    EXCKSEL3        3
#define    EXCKSEL2        2
#define    EXCKSEL1        1
#define    EXCKSEL0        0

/* CKSTA  - Clock Status Register */
#define    RCON            1
#define    EXTON           0


/* ***** PLL *********************** */

/* PLLCSR - PLL Control and Status Register */
#define    PLLP2           4
#define    PLLP1           3
#define    PLLP0           2
#define    PLLE            1
#define    PLOCK           0


/* ***** REGULATOR ***************** */

/* REGCR - 3V2 Regulator Control Register */
#define    REGDIS          0


/* Pointer definition */
#define    XL     r26
#define    XH     r27
#define    YL     r28
#define    YH     r29
#define    ZL     r30
#define    ZH     r31

/* PCMSK0 */
#define    PCINT6          6
#define    PCINT5          5
#define    PCINT4          4
#define    PCINT3          3
#define    PCINT2          2
#define    PCINT1          1
#define    PCINT0          0

/* PCMSK1 */
#define    PCINT12         4
#define    PCINT11         3
#define    PCINT10         2
#define    PCINT9          1
#define    PCINT8          0

#endif  /* _MCU_H*/














