//!
//! @file usb_device_task.c,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file manages the USB device controller.
//!
//! The USB task checks the income of new requests from the USB Host.
//! When a Setup request occurs, this task will launch the processing
//! of this setup contained in the usb_standard_request.c file.
//! Other class specific requests are also processed in this file.
//!
//!
//! @version 1.9 at90usb162-2enum-mouse_ms-1_0_1 $Id: usb_device_task.c,v 1.9 2006/11/30 16:05:02 arobert Exp $
//!
//! @todo
//! @bug
//!/

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "conf_usb.h"
#include "usb_device_task.h"
#include "modules\usb\usb_task.h"
#include "lib_mcu\usb\usb_drv.h"
#include "usb_descriptors.h"
#include "modules\usb\device_chap9\usb_standard_request.h"
#include "lib_mcu\pll\pll_drv.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

//!
//! Public : (bit) usb_connected
//! usb_connected is set to TRUE when VBUS has been detected
//! usb_connected is set to FALSE otherwise
//!/
bit   usb_connected=0;


//!
//! Public : (U8) usb_configuration_nb
//! Store the number of the USB configuration used by the USB device
//! when its value is different from zero, it means the device mode is enumerated
//! Used with USB_DEVICE_FEATURE == ENABLED only
//!/
extern U8  usb_configuration_nb;

//_____ D E C L A R A T I O N S ____________________________________________

//!
//! @brief This function initializes the USB device controller and system interrupt
//!
//! This function enables the USB controller and init the USB interrupts.
//! The aim is to allow the USB connection detection in order to send
//! the appropriate USB event to the operating mode manager.
//!
//! @param none
//!
//! @return none
//!
//!/
void usb_device_task_init(void)
{
   Usb_disable();
   Usb_enable();
#if (VBUS_SENSING_IO == ENABLED)
   Usb_vbus_sense_init();   // init. the I/O used for Vbus sensing
#endif
}

//!
//! @brief This function initializes the USB device controller
//!
//! This function enables the USB controller and init the USB interrupts.
//! The aim is to allow the USB connection detection in order to send
//! the appropriate USB event to the operating mode manager.
//! Start device function is executed once VBUS connection has been detected
//! either by the VBUS change interrupt either by the VBUS high level
//!
//! @param none
//!
//! @return none
//!
void usb_start_device (void)
{
   Usb_freeze_clock();
#ifdef BYPASS_USB_AUTOBAUD
   Pll_start_auto();
   Wait_pll_ready();
   Usb_unfreeze_clock();
#else
   Usb_enable_device();
   Usb_attach();
   usb_autobaud();
#endif

   Usb_unfreeze_clock();
   Usb_attach();
#if (USB_RESET_CPU == ENABLED)
   Usb_reset_all_system();
#else
   Usb_reset_macro_only();
#endif
   Usb_enable_suspend_interrupt();
   Usb_enable_reset_interrupt();
   Enable_interrupt();
   usb_init_device();         // configure the USB controller EP0
}

//! @brief Entry point of the USB device mamagement
//!
//! This function is the entry point of the USB management. Each USB
//! event is checked here in order to launch the appropriate action.
//! If a Setup request occurs on the Default Control Endpoint,
//! the usb_process_request() function is call in the usb_standard_request.c file
//!
//! @param none
//!
//! @return none
void usb_device_task(void)
{
   if (usb_connected == FALSE)
   {
     #if (VBUS_SENSING_IO == ENABLED)
     if (Is_usb_vbus_on())    // check if Vbus ON to attach
     {
       Usb_enable();
       usb_connected = TRUE;
       usb_start_device();
       Usb_vbus_on_action();
     }
     #else
     usb_connected = TRUE;    // attach if application is not self-powered
     usb_start_device();
     Usb_vbus_on_action();
     #endif
   }

   #if (VBUS_SENSING_IO == ENABLED)
   if ((usb_connected == TRUE) && Is_usb_vbus_off())  // check if Vbus OFF to detach
   {
     Usb_detach();
     Usb_disable();
     Stop_pll();
     usb_connected = FALSE;
     usb_configuration_nb=0;
   }
   #endif

   if(Is_usb_event(EVT_USB_RESET))
   {
      Usb_ack_event(EVT_USB_RESET);
      Usb_reset_endpoint(0);
      usb_configuration_nb=0;
   }

   // Here connection to the device enumeration process
   Usb_select_endpoint(EP_CONTROL);
   if (Is_usb_receive_setup())
   {
      usb_process_request();
   }
}

#ifndef BYPASS_USB_AUTOBAUD
//! @brief USB devive autobaud
//!
//! This function performs an autobaud configuration for the USB interface.
//! the autobaud function performs the configuration of the PLL dedicated to the USB interface.
//! The autobaud algorithm consists in trying each USB PLL until the correct detection of Start
//! of Frame (USB SOF).
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return none
void usb_autobaud(void)
{
   U8 i=0;
   while(Is_usb_sof()==FALSE) //! Try until Start of Frame is correctly detected...
   {
      Usb_freeze_clock();
      Stop_pll();
      TCCR0B=0x00; TCCR0A=0x00;    //! Timer 2 stop and default normal mode
      TCNT0=0;  TIFR0=0x01;        //!  Clear TOV2 flag and counter value
      switch (i)
      {
         case 0:
            Start_pll(PLLx06);  //! FOSC 8MHz
            break;
         case 1:
            Start_pll(PLLx03);  //! FOSC 16MHz
            break;

         default:
            Start_pll(PLLx06);  //! FOSC 8MHz
            i=0;
            break;
      }
      i++;
      TCCR0B|=(1<<CS02)|(1<<CS00);            //! 128 prescaler for timer 2 & run
      while(!Is_pll_ready() &&(TIFR0!=0x01)); //! Wait for Pll lock or timeout in pll lock
      TCCR0B=0x00;TCNT0=0;           //! Timer 2 stop and reset counter value
      if(TIFR0==0x01)                //! If overflow occurs during pll lock-> invalid configuration
      {
         TIFR0=0x01;                 //!  Just Clear TOV2 flag
      }
      else                           //! Try looking for SOF detection
      {
         Usb_unfreeze_clock();
         TIFR0=0x01;                    //!  Clear TOV2 flag
         TCCR0B|=(1<<CS02)|(1<<CS00);   //! 128 prescaler for timer 2 & run
         while((TIFR0!=0x01));          //! Wait timer 2 overflow to have at least 1 SOF from host
      }
   }
   //! Restore default registers values for timer2
   TCCR0A=0;TCCR0B=0x00;TCNT0=0;
   Usb_ack_sof();
}
#endif
