/*H**************************************************************************
* NAME:         usb_specific_request.h
*----------------------------------------------------------------------------
* Copyright (c) 2006 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      at90usb162-2enum-mouse_ms-1_0_1
* REVISION:     1.1
*----------------------------------------------------------------------------
* PURPOSE:
* This file contains the user call-back functions corresponding to the
* application:
*****************************************************************************/

#ifndef _USB_USER_ENUM_H_
#define _USB_USER_ENUM_H_

/*_____ I N C L U D E S ____________________________________________________*/

#include "config.h"

/*_____ M A C R O S ________________________________________________________*/

extern  code S_usb_device_descriptor usb_dev_desc;
extern  code S_usb_user_configuration_descriptor usb_conf_desc;
extern  code S_usb_user_configuration_descriptor usb_other_conf_desc;
extern  code S_usb_device_qualifier_descriptor usb_qual_desc;
extern  code S_usb_manufacturer_string_descriptor usb_user_manufacturer_string_descriptor;
extern  code S_usb_product_string_descriptor usb_user_product_string_descriptor;
extern  code S_usb_serial_number usb_user_serial_number;
extern  code S_usb_language_id usb_user_language_id;



/*_____ D E F I N I T I O N ________________________________________________*/
Bool  usb_user_read_request(U8, U8);
Bool  usb_user_get_descriptor(U8 , U8);
void  usb_user_endpoint_init(U8);
void hid_get_report(void);
void hid_set_report(void);
void usb_hid_get_interface(void);
void usb_hid_set_idle(void);
void hid_get_hid_descriptor(void);

#define MASS_STORAGE_RESET    0xFF
#define GET_MAX_LUN           0xFE

               //! Usb HID Report Descriptor Mouse
typedef struct {
   U8      report[0x34];
}  S_usb_hid_report_descriptor_mouse;

             //! Usb HID Report Descriptor Keyboard
typedef struct {
  U8      report[0x3B];
}  S_usb_hid_report_descriptor_kbd;


#endif

