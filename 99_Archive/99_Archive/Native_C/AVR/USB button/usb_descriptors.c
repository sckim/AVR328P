//! @file usb_descriptors.c,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief  USB parameters.
//!
//! This file contains the usb parameters that uniquely identify the
//! application through descriptor tables.
//!
//! @version 1.1 at90usb162-2enum-mouse_ms-1_0_1 $Id: usb_descriptors.c,v 1.1 2006/09/07 14:15:12 rletendu Exp $
//!
//! @todo
//! @bug


//_____ I N C L U D E S ____________________________________________________

#include "config.h"
#include "conf_usb.h"

#include "usb_drv.h"
#include "usb_descriptors.h"
#include "usb_standard_request.h"
#include "usb_specific_request.h"


//_____ M A C R O S ________________________________________________________




//_____ D E F I N I T I O N ________________________________________________

// usb_user_device_descriptor
code S_usb_device_descriptor usb_dev_desc =
{
  sizeof(usb_dev_desc)
, DEVICE_DESCRIPTOR
, Usb_write_word_enum_struc(USB_SPECIFICATION)
, DEVICE_CLASS
, DEVICE_SUB_CLASS
, DEVICE_PROTOCOL
, EP_CONTROL_LENGTH
, Usb_write_word_enum_struc(VENDOR_ID)
, Usb_write_word_enum_struc(PRODUCT_ID)
, Usb_write_word_enum_struc(RELEASE_NUMBER)
, MAN_INDEX
, PROD_INDEX
, SN_INDEX
, NB_CONFIGURATION
};

// usb_user_configuration_descriptor FS
code S_usb_user_configuration_descriptor usb_conf_desc = {
 { sizeof(S_usb_configuration_descriptor)
 , CONFIGURATION_DESCRIPTOR
 , Usb_write_word_enum_struc(sizeof(S_usb_configuration_descriptor)\
       +sizeof(S_usb_interface_descriptor)   \
       +sizeof(S_usb_hid_descriptor)         \
       +sizeof(S_usb_endpoint_descriptor)    \
       +sizeof(S_usb_interface_descriptor)   \
       +sizeof(S_usb_endpoint_descriptor)    \
       +sizeof(S_usb_endpoint_descriptor))
 , NB_INTERFACE
 , CONF_NB
 , CONF_INDEX
 , CONF_ATTRIBUTES
 , MAX_POWER
 }
 ,
 { sizeof(S_usb_interface_descriptor)
 , INTERFACE_DESCRIPTOR
 , INTERFACE_NB_MOUSE
 , ALTERNATE_MOUSE
 , NB_ENDPOINT_MOUSE
 , INTERFACE_CLASS_MOUSE
 , INTERFACE_SUB_CLASS_MOUSE
 , INTERFACE_PROTOCOL_MOUSE
 , INTERFACE_INDEX_MOUSE
 }
 ,
 { sizeof(S_usb_hid_descriptor)
 , HID_DESCRIPTOR
 , HID_BDC
 , HID_COUNTRY_CODE
 , HID_CLASS_DESC_NB
 , HID_DESCRIPTOR_TYPE
 , Usb_write_word_enum_struc(sizeof(S_usb_hid_report_descriptor_mouse))
 }
 ,
 { sizeof(S_usb_endpoint_descriptor)
 , ENDPOINT_DESCRIPTOR
 , ENDPOINT_NB_1
 , EP_ATTRIBUTES_1
 , Usb_write_word_enum_struc(EP_SIZE_1)
 , EP_INTERVAL_1
 }
,
 { sizeof(S_usb_interface_descriptor)
 , INTERFACE_DESCRIPTOR
 , INTERFACE_NB
 , ALTERNATE
 , NB_ENDPOINT
 , INTERFACE_CLASS
 , INTERFACE_SUB_CLASS
 , INTERFACE_PROTOCOL
 , INTERFACE_INDEX
 }
 ,
 { sizeof(S_usb_endpoint_descriptor)
 , ENDPOINT_DESCRIPTOR
 , ENDPOINT_NB_2
 , EP_ATTRIBUTES_2
 , Usb_write_word_enum_struc(EP_SIZE_2)
 , EP_INTERVAL_2
 }
 ,
 { sizeof(S_usb_endpoint_descriptor)
 , ENDPOINT_DESCRIPTOR
 , ENDPOINT_NB_3
 , EP_ATTRIBUTES_3
 , Usb_write_word_enum_struc(EP_SIZE_3)
 , EP_INTERVAL_3
 }
};



                                      // usb_user_manufacturer_string_descriptor
code S_usb_manufacturer_string_descriptor usb_user_manufacturer_string_descriptor = {
  sizeof(usb_user_manufacturer_string_descriptor)
, STRING_DESCRIPTOR
, USB_MANUFACTURER_NAME
};


                                      // usb_user_product_string_descriptor

code S_usb_product_string_descriptor usb_user_product_string_descriptor = {
  sizeof(usb_user_product_string_descriptor)
, STRING_DESCRIPTOR
, USB_PRODUCT_NAME
};


                                      // usb_user_serial_number

code S_usb_serial_number usb_user_serial_number = {
  sizeof(usb_user_serial_number)
, STRING_DESCRIPTOR
, USB_SERIAL_NUMBER
};


                                      // usb_user_language_id

code S_usb_language_id usb_user_language_id = {
  sizeof(usb_user_language_id)
, STRING_DESCRIPTOR
, Usb_write_word_enum_struc(LANGUAGE_ID)
};

code S_usb_hid_report_descriptor_mouse usb_hid_report_descriptor_mouse = {
      0x05,0x01,          /* Usage Page (Generic Desktop)      */
      0x09,0x02,          /* Usage (Mouse)                     */
      0xA1,0x01,          /* Collection (Application)          */
      0x09,0x01,          /* Usage (Pointer)                   */
      0xA1,0x00,          /* Collection (Application)          */
      0x05,0x09,          /* Usage Page (Button)               */
      0x19,0x01,          /* Usage Minimum (1)                 */
      0x29,0x03,          /* Usage Maximum (3)                 */
      0x15,0x00,          /* Logical Minimum (0)               */
      0x25,0x01,          /* Logical Maximum (1)               */
      0x75,0x01,          /* Report Size (1)                   */
      0x95,0x03,          /* Report Count (3)                  */
      0x81,0x02,          /* Input (Data, Variable, Absolute)  */
      0x75,0x05,          /* Report Size (5)                   */
      0x95,0x01,          /* Report Count (1)                  */
      0x81,0x01,          /* Input (Constant)                  */
      0x05,0x01,          /* Usage Page (Generic Desktop Control)*/
      0x09,0x30,          /* Usage X                           */
      0x09,0x31,          /* Usage Y                           */
      0x09,0x38,          /* Usage Wheel                       */
      0x15,0x81,          /* Logical Minimum (-127)            */
      0x25,0x7F,          /* Logical Maximum (127)             */
      0x75,0x08,          /* Report Size (8)                   */
      0x95,0x03,          /* Report Count (3)                  */
      0x81,0x06,          /* Input (Data, Variable, Absolute)  */
      0xC0,               /* End Collection                    */
      0xC0                /* End Collection                    */
};




