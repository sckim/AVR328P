//! @file power_drv.c,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the Power management driver routines.
//!
//! This file contains the Power management driver routines.
//!
//! @version 1.1 at90usb162-2enum-mouse_ms-1_0_1 $Id: power_drv.c,v 1.1 2006/08/29 15:58:42 arobert Exp $
//!
//! @todo Implemets adc, stanby, extended stanby and power save modes
//! @bug

//_____ I N C L U D E S ____________________________________________________

#include "config.h"
#include "power_drv.h"

//_____ M A C R O S ________________________________________________________

//_____ D E C L A R A T I O N ______________________________________________

//! set_power_down_mode.
//!
//! This function makes the AVR core enter power down mode.
//!
//! @param none
//!
//! @return none.
//!
void set_power_down_mode(void)
{
   Setup_power_down_mode();
   Sleep_instruction();
}



//! set_idle_mode.
//!
//! This function makes the AVR core enter idle mode.
//!
//! @param none
//!
//! @return none.
//!
void set_idle_mode(void)
{
   Setup_idle_mode();
   Sleep_instruction();
}

//! set_adc_noise_reduction_mode.
//!
//! This function makes the AVR core enter adc noise reduction mode.
//!
//! @param none
//!
//! @return none.
//!
void set_adc_noise_reduction_mode(void)
{
   Setup_adc_noise_reduction_mode();
   Sleep_instruction();
}

//! set_power_save_mode.
//!
//! This function makes the AVR core enter power save mode.
//!
//! @param none
//!
//! @return none.
//!
void set_power_save_mode(void)
{
   Setup_power_save_mode();
   Sleep_instruction();
}

//! set_standby_mode.
//!
//! This function makes the AVR core enter standby mode.
//!
//! @param none
//!
//! @return none.
//!
void set_standby_mode(void)
{
   Setup_standby_mode();
   Sleep_instruction();
}

//! set_ext_standby_mode.
//!
//! This function makes the AVR core enter extended standby mode.
//!
//! @param none
//!
//! @return none.
//!
void set_ext_standby_mode(void)
{
   Setup_ext_standby_mode();
   Sleep_instruction();
}
