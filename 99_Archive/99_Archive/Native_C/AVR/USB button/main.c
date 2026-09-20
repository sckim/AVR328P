//!
//! @file main.c,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief Main for USB application.
//!
//! @version 1.2 at90usb162-2enum-mouse_ms-1_0_1 $Id: main.c,v 1.2 2007/02/15 12:50:17 arobert Exp $
//!
//! @mainpage AT90USBxxx Mouse + Mass Storage demonstration
//!
//! @section intro License
//! Use of this program is subject to Atmel's End User License Agreement.
//!
//! Please read file license.txt for copyright notice.
//!
//! @section install Description
//! This embedded application source code illustrates how to implement a composite device that gather
//! an HID mouse and a Mass Storage device over the AT90USBxxx controller.
//!
//! @section sample About the sample application
//! The sample code is delivered for STK526.
//!
//! @section arch Architecture
//! As illustrated in the figure bellow, the application entry point is located is the main.c file.
//! The main function first performs the initialization of a scheduler module and then runs it in an infinite loop.
//! The scheduler is a simple infinite loop calling all its tasks defined in the conf_scheduler.h file.
//! No real time schedule is performed, when a task ends, the scheduler calls the next task defined in
//! the configuration file (conf_scheduler.h).
//!
//! The sample dual role application is based on two different tasks:
//! - The usb_task  (usb_task.c associated source file), is the task performing the USB low level
//! enumeration process in device mode.
//! - The mouse task performs mouse events decoding and report construction to the USB host.
//! - The storage_task handles Mass Storage class commands, and manages low level memory drivers
//!
//! \image html arch_full.gif
//!

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "scheduler.h"
#include "wdt_drv.h"
#include "power_drv.h"
#include "usb_drv.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

void main(void)
{

  Usb_enable_regulator();

#ifndef  AVRGCC
   Wdt_off();
#else
   wdt_reset();
   Wdt_clear_flag();
   Wdt_change_enable();
   Wdt_stop();
#endif
   Clear_prescaler();

   scheduler();
}

