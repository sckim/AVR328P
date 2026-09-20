//!
//! @file mouse_task.c,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file manages the Mouse task.
//!
//! @version 1.4 at90usb162-2enum-mouse_ms-1_0_1 $Id: mouse_task.c,v 1.4 2007/01/08 16:09:44 arobert Exp $
//!
//! @todo
//! @bug
//!/

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "conf_usb.h"
#include "mouse_task.h"
#include "usb_drv.h"
#include "usb_descriptors.h"
#include "usb_standard_request.h"
#include "wdt_drv.h"
#include "power_drv.h"
#include "pll_drv.h"
#include "at90usb162_quickstart_drv.h"


//_____ M A C R O S ________________________________________________________

#define Usb_mouse_up()                  (usb_mouse_report[2]-=MOUSE_SPEED)
#define Usb_mouse_down()                (usb_mouse_report[2]+=MOUSE_SPEED)
#define Usb_mouse_left()                (usb_mouse_report[1]-=MOUSE_SPEED)
#define Usb_mouse_right()               (usb_mouse_report[1]+=MOUSE_SPEED)
#define Usb_mouse_click_left()          (usb_mouse_report[0] |= 0x01)
#define Usb_mouse_click_right()         (usb_mouse_report[0] |= 0x02)
#define Usb_mouse_click_middle()        (usb_mouse_report[0] |= 0x04)
#define Usb_mouse_release_left()        (usb_mouse_report[0] &= ~0x01)
#define Usb_mouse_release_right()       (usb_mouse_report[0] &= ~0x02)
#define Usb_mouse_release_middle()      (usb_mouse_report[0] &= ~0x04)
#define Usb_mouse_scroll_up()           (usb_mouse_report[3]++)
#define Usb_mouse_scroll_down()         (usb_mouse_report[3]--)
#define Usb_mouse_report_reset()        (usb_mouse_report[0]=0,usb_mouse_report[1]=0,usb_mouse_report[2]=0,usb_mouse_report[3]=0)

#define Is_mouse_left_event()           Is_joy_left()
#define Is_mouse_right_event()          Is_joy_right()
#define Is_mouse_up_event()             Is_joy_up()
#define Is_mouse_down_event()           Is_joy_down()
#define Is_mouse_click_left_event()   Is_hwb()
#define Is_mouse_release_left_event() !Is_hwb()




//_____ D E F I N I T I O N S ______________________________________________



//_____ D E C L A R A T I O N S ____________________________________________

U8 report_ready;
volatile U8 usb_mouse_report[4];
U16 wheel;
volatile U8 cpt_sof;
extern  U8   usb_configuration_nb;


//!
//! @brief This function initializes the hardware/software resources required for mouse task.
//!
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return none
//!
//!/
void mouse_task_init(void)
{
   Usb_mouse_report_reset();
   report_ready=TRUE;
   wheel=0;
   cpt_sof=0;
   Usb_enable_sof_interrupt();
   Joy_init();
   Leds_init();
   Hwb_button_init();
}



//! @brief Entry point of the mouse management
//!
//! This function has no effect, but is called by scheduler. It is replaced by mouse_task_by_IT() that is interrupt handled
//!
//! @param none
//!
//! @return none
void mouse_task(void)
{
}



//! @brief Entry point of the mouse management
//!
//! This function links the mouse and the USB bus.
//! This task is interrupt handled : the function is called periodically from the ISR of Start of Frame reception
//! That makes possible moving the mouse while the mass storage is used (file copy for example)
//!
//! @param none
//!
//! @return none
void mouse_task_by_IT(void)
{
   if(Is_device_enumerated() && !Is_usb_report_ready() && is_usb_mouse_event())
   {
      report_ready=TRUE;
   }

   if (Is_device_enumerated() && Is_usb_report_ready())
   {
      Usb_select_endpoint(EP_MOUSE_IN);
      if (Is_usb_write_enabled())
      {
         Usb_set_report_not_ready();
         Usb_write_byte(usb_mouse_report[0]);
         Usb_write_byte(usb_mouse_report[1]);
         Usb_write_byte(usb_mouse_report[2]);
         Usb_write_byte(usb_mouse_report[3]);
         Usb_ack_in_ready();
      }
   }
}

//! @brief Is_usb_mouse_event
//!
//! This function returns TRUE if a event occurs on the mouse
//! (FALSE if not). The mouse report is updated by this function
//!
//! @param none
//!
//! @return none
bit is_usb_mouse_event(void)
{
   bit usb_mouse_event_stored;

// Following must not be used if interrupt handled task
//   if(cpt_sof<NB_IDLE_POLLING_SOF) return FALSE;
//   cpt_sof=0;

   Usb_mouse_report_reset();

   if(Is_device_enumerated())
   {
		//Mouse Button Event -> LED Display
		if(Is_mouse_click_left_event())Led1On();
		else Led1Off();
		
		if(Is_mouse_up_event())Led2On();
		else Led2Off();		

		if(Is_mouse_click_left_event())
		{
			Usb_mouse_click_left();
			usb_mouse_event_stored = 1;
		}

		if(Is_mouse_release_left_event())
		{
			Usb_mouse_release_left();
			usb_mouse_event_stored = 1;
		}

		if (Is_mouse_up_event())
		{
			Usb_mouse_up();
			usb_mouse_event_stored = 1;
		}	

		if (Is_mouse_left_event())
		{
			Usb_mouse_left();
			usb_mouse_event_stored = 1;
		}

		if (Is_mouse_right_event())
		{
			Usb_mouse_right();
			usb_mouse_event_stored = 1;
		}

		if (Is_mouse_down_event())
		{
			Usb_mouse_down();
			usb_mouse_event_stored = 1;
		}	   
		

     if (usb_mouse_event_stored == 1)
     {
        usb_mouse_event_stored = 0;
        return TRUE;
     }
       else {return FALSE;}
   }
   return FALSE;
}


//! @brief sof_action
//!
//! This function increments the cpt_sof counter each times
//! the USB Start Of Frame interrupt subroutine is executed (1ms)
//! Usefull to manage time delays
//! Periodically this ISR calls the mouse_task_by_IT() function that ensure
//! the mouse operation in any circumstances (mass storage access, etc...)
//!
//! @param none
//!
//! @return none
void sof_action()
{
   U8 ep_selected;
   cpt_sof++;
   if (cpt_sof == NB_IDLE_POLLING_SOF)
   {
     ep_selected = Usb_get_selected_endpoint();   // the currently selected endpoint must be saved to avoid
                                                  // problems when interrupt happens during mass storage endpoint reading/writing
     mouse_task_by_IT();
     cpt_sof = 0;
     Usb_select_endpoint(ep_selected);            // restore current selected endpoint
   }
}

