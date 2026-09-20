//! @file wdt_drv.h,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the Watchdog low level driver definition for AT90USB162
//!
//! @version 1.2 at90usb162-2enum-mouse_ms-1_0_1 $Id: wdt_drv.h,v 1.2 2006/09/05 09:11:33 arobert Exp $
//!
//! @todo
//! @bug


#ifndef _WDT_DRV_H_
#define _WDT_DRV_H_

//_____ I N C L U D E S ____________________________________________________

#ifdef AVRGCC
   #include <avr/io.h>
   #include <avr/wdt.h>
#endif


#ifdef AVRGCC
//#define Wdt_reset_instruction()   (asm("WDR"))
#define Wdt_reset_instruction()  (wdt_reset())
#else
#define Wdt_reset_instruction()  (__watchdog_reset())
#endif


// ======================
// == LOW LEVEL MACROS ==
// ======================

// ** GENERAL RESET **
#define   Is_ext_reset()                ((MCUSR&(1<<EXTRF)) ? TRUE:FALSE)
#define   Ack_ext_reset()               (MCUSR= ~(1<<EXTRF))
#define   Is_POR_reset()                ((MCUSR&(1<<(MCUSR= ~(1<<PORF)))) ? TRUE:FALSE)
#define   Ack_POR_reset()               (MCUSR= ~(1<<PORF))
#define   Is_BOD_reset()                ((MCUSR&(1<<BORF)) ? TRUE:FALSE)
#define   Ack_BOD_reset()               (MCUSR= ~(1<<BORF))
#define   Is_wdt_reset()                ((MCUSR&(1<<WDRF)) ? TRUE:FALSE)
#define   Ack_wdt_reset()               (MCUSR= ~(1<<WDRF))
#define   Wdt_clear_flag()              Ack_wdt_reset()

// ** WATCHDOG GENERAL **
#define   Wdt_change_enable()           (WDTCSR = (1<<WDCE) | (1<<WDE))     // to change WDE or prescaler
#define   Wdt_system_reset_enable()     (WDTCSR |= (1<<WDE))
#define   Wdt_system_reset_disable()    (WDTCSR &= ~(1<<WDE))
#define   Wdt_stop()                    (WDTCSR = 0x00, WDTCKD = 0x00)

// ** INTERRUPTS & FLAGS **
// Warning : both flags are auto cleared once the interrupt routine is branched (flag polling should be only used if interrupts are disabled)
#define   Wdt_enable_early_interrupt()  (WDTCKD |= (1<<WDEWIE))
#define   Wdt_disable_early_interrupt() (WDTCKD &= ~(1<<WDEWIE))
#define   Is_wdt_early_interrupt()      (((WDTCKD&(1<<WDEWIF)) != 0) ? TRUE : FALSE)
#define   Ack_wdt_early_interrupt()     (WDTCKD |= (1<<WDEWIF))

#define   Wdt_enable_real_interrupt()   (WDTCSR |= (1<<WDIE))
#define   Wdt_disable_real_interrupt()  (WDTCSR &= ~(1<<WDIE))
#define   Is_wdt_real_interrupt()       (((WDTCSR&(1<<WDIF)) != 0) ? TRUE : FALSE)
#define   Ack_wdt_real_interrupt()      (WDTCSR |= (1<<WDIF))

// ** CLOCK SOURCE DIVIDER **
// Can be changed only if WDE and WDCE are set in a single instruction before
#define   Wdt_set_clock_divider(ck)     (WDTCKD = ck)
#define   WDT_CLOCK_DIV_1               0x00
#define   WDT_CLOCK_DIV_3               0x01
#define   WDT_CLOCK_DIV_5               0x02
#define   WDT_CLOCK_DIV_7               0x03

// ** PRESCALER **
// Can be changed only if WDE and WDCE are set in a single instruction before
#define   Wdt_set_prescaler(ck)         (WDTCSR = ck)
#define   WDT_PRESC_1                   0x00
#define   WDT_PRESC_2                   0x01
#define   WDT_PRESC_4                   0x02
#define   WDT_PRESC_8                   0x03
#define   WDT_PRESC_16                  0x04
#define   WDT_PRESC_32                  0x05
#define   WDT_PRESC_64                  0x06
#define   WDT_PRESC_128                 0x07
#define   WDT_PRESC_256                 0x20
#define   WDT_PRESC_512                 0x21


// =======================
// == HIGH LEVEL MACROS ==
// ===============================================
// = Select time-out delay first (prescaler), then select operating mode
// ===============================================

// These macros select the operating mode
// WARNING : they don't clear the prescaler except for "Wdt_off()", so may be used after having set the prescaler
#define   Wdt_off()                          (Wdt_reset_instruction(),  \
                                              Wdt_clear_flag(),         \
                                              Wdt_change_enable(),      \
                                              Wdt_stop())

#define   Wdt_set_mode_interrupt()           (Wdt_reset_instruction(),  \
                                              Wdt_clear_flag(),         \
                                              WDTCSR |= (1<<WDIE))

#define   Wdt_set_mode_system_reset()        (Wdt_reset_instruction(),  \
                                              Wdt_clear_flag(),         \
                                              WDTCSR |= (1<<WDE))

#define   Wdt_set_mode_interrupt_and_reset() (Wdt_reset_instruction(),  \
                                              Wdt_clear_flag(),         \
                                              WDTCSR |= ((1<<WDE) | (1<<WDIE)))

// These macros change the watchdog prescaler settings
// The delay indicated below is the delay of the EARLY interrupt
// The real delay before a wdt REAL interrupt or wdt reset is the double of the delay indicated below
// WARNING : use these macros first, before setting operating mode, because they clear the current mode
#define   Wdt_change_16ms()             (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_1),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_1))
#define   Wdt_change_32ms()             (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_1),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_2))
#define   Wdt_change_48ms()             (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_3),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_1))
#define   Wdt_change_64ms()             (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_1),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_4))
#define   Wdt_change_80ms()             (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_5),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_1))
#define   Wdt_change_96ms()             (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_3),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_2))
#define   Wdt_change_112ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_7),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_1))
#define   Wdt_change_125ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_1),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_8))
#define   Wdt_change_160ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_5),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_2))
#define   Wdt_change_192ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_3),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_4))
#define   Wdt_change_224ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_7),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_2))
#define   Wdt_change_250ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_1),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_16))
#define   Wdt_change_320ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_5),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_4))
#define   Wdt_change_375ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_3),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_8))
#define   Wdt_change_448ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_7),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_4))
#define   Wdt_change_500ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_1),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_32))
#define   Wdt_change_640ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_5),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_8))
#define   Wdt_change_750ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_3),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_16))
#define   Wdt_change_896ms()            (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_7),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_8))
#define   Wdt_change_1s()               (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_1),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_64))
#define   Wdt_change_1s25()             (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_5),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_16))
#define   Wdt_change_1s5()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_3),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_32))
#define   Wdt_change_1s75()             (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_7),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_16))
#define   Wdt_change_2s()               (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_1),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_128))
#define   Wdt_change_2s5()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_5),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_32))
#define   Wdt_change_3s()               (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_3),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_64))
#define   Wdt_change_3s5()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_7),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_32))
#define   Wdt_change_4s()               (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_1),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_256))
#define   Wdt_change_5s()               (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_5),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_64))
#define   Wdt_change_6s()               (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_3),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_128))
#define   Wdt_change_7s()               (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_7),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_64))
#define   Wdt_change_8s()               (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_1),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_512))
#define   Wdt_change_10s()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_5),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_128))
#define   Wdt_change_12s()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_3),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_256))
#define   Wdt_change_14s()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_7),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_128))
#define   Wdt_change_20s()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_5),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_256))
#define   Wdt_change_24s()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_3),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_512))
#define   Wdt_change_28s()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_7),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_256))
#define   Wdt_change_40s()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_5),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_512))
#define   Wdt_change_56s()              (Wdt_reset_instruction(),                 \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_clock_divider(WDT_CLOCK_DIV_7),  \
                                         Wdt_change_enable(),                     \
                                         Wdt_set_prescaler(WDT_PRESC_512))

#endif  // _WDT_DRV_H_



