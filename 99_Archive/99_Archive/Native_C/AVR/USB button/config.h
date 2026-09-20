//! @file config.h,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! This file contains the system configuration definition
//!
//! @version 1.2 at90usb162-2enum-mouse_ms-1_0_1 $Id: config.h,v 1.2 2007/01/08 16:09:30 arobert Exp $
//!
//! @todo
//! @bug

#ifndef _CONFIG_H_
#define _CONFIG_H_

//! @defgroup global_config Application configuration
//! @{

//_____ I N C L U D E S ____________________________________________________


#define AVRGCC

#ifdef AVRGCC
   #define __AVR_AT90USB162__
#endif

#include "compiler.h" //!< Compiler definitions

#include <avr/io.h>
#ifdef AVRGCC
   #include <avr/io.h>
#else
   #include "mcu.h" //!< Register declaration
#endif
#include "conf_scheduler.h" //!< Scheduler tasks declaration

#define  STK525     0
#define  USBKEY     1
#define  SPIDER     2
#define  WRD_PHLPS  3

//! To include proper target hardware definitions, select
//! target board
#define TARGET_BOARD STK526

#if (TARGET_BOARD==USBKEY)
   //! @warning for #define USBKEY_HAS_321_DF, only first prototypes versions have AT45DB321C memories
   //! should be undefined for std series
   #define USBKEY_HAS_321_DF
   #include "lib_board\usb_key\usb_key.h"
#elif (TARGET_BOARD==STK526)
   #include "stk_526.h"
#elif (TARGET_BOARD==SPIDER)
   #include "lib_board\spider\spider_drv.h"
#elif (TARGET_BOARD==WRD_PHLPS)
   #include "lib_board\wired_philips\mouse_wired_philips_drv.h"
   #include "lib_mcu/quickstart/at90usb162_quickstart_drv.h"
#else
   #error TARGET_BOARD must be defined somewhere
#endif


//! CPU core frequency in kHz
#define FOSC 8000

#define BYPASS_USB_AUTOBAUD

// -------- END Generic Configuration -------------------------------------

//!Mouse configuration
//#define NB_IDLE_POLLING_SOF  8   //!10ms before looking for new mouse hardware event
#define NB_IDLE_POLLING_SOF  25   //!10ms before looking for new mouse hardware event
#define MOUSE_SPEED          4
//#define MOUSE_SPEED          1
#define WH_ZERO_MOTION       10


#define DUMMY     GPIOR1                     //! For SPI drv
#define SPI_CONFIG 0x00                      //! Default SPI config see spi_drv.h file

//!--------- Device Mass Storage Identifiers Signature -----------------------
#define SBC_VENDOR_ID         {'A','T','M','E','L',' ',' ',' '}      // 8 Bytes only
#define SBC_PRODUCT_ID        {'A','T','9','0','U','S','B','1','6','2',' ','M',' ','S',' ',' '}  // 16 Bytes only
#define SBC_REVISION_ID       {'0','.','0','0'}  // 4 Bytes only

//! @}

#endif // _CONFIG_H_

