//! @file usb_specific_request.c,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief user call-back functions
//!
//! This file contains the user call-back functions corresponding to the
//! application:
//!
//! @version 1.1 at90usb162-2enum-mouse_ms-1_0_1 $Id: usb_specific_request.c,v 1.1 2006/09/07 14:15:12 rletendu Exp $
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
#include "ctrl_access.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N ________________________________________________
       bit  ms_multiple_drive;
//_____ P R I V A T E   D E C L A R A T I O N ______________________________

#ifdef AVRGCC
extern PGM_VOID_P pbuffer;
#else
extern U8   code *pbuffer;
#endif
extern U8   data_to_transfer;
extern code S_usb_hid_report_descriptor_mouse usb_hid_report_descriptor_mouse;
extern U16  wInterface;


//_____ D E C L A R A T I O N ______________________________________________

//! usb_user_read_request(type, request);
//!
//! This function is called by the standard usb read request function when
//! the Usb request is not supported. This function returns TRUE when the
//! request is processed. This function returns FALSE if the request is not
//! supported. In this case, a STALL handshake will be automatically
//! sent by the standard usb read request function.
//!
//! @param none
//!
//! @return none
//!
Bool usb_user_read_request(U8 type, U8 request)
{
U8  descriptor_type ;
U8  string_type     ;

   string_type     = Usb_read_byte();
	descriptor_type = Usb_read_byte();
	switch(request)
	{
		case GET_DESCRIPTOR:

			switch (descriptor_type)
			{
			   case REPORT:
					hid_get_report();
					return TRUE;
      			break;

			   case HID:
                                        hid_get_hid_descriptor();
					return TRUE;
      			break;
			   default:
					return FALSE;
      			break;
			}
			break;

		 case SET_CONFIGURATION:
			switch (descriptor_type)
			{
			   case SET_REPORT:
					hid_set_report();
					return TRUE;
      			break;

			   default:
					return FALSE;
      			break;
			}
			break;
   case GET_INTERFACE:
//      usb_hid_set_idle();
      usb_hid_get_interface();
      return TRUE;
      break;

    case MASS_STORAGE_RESET:
         Usb_ack_receive_setup();
         Usb_send_control_in();
         return TRUE;
         break;

    case GET_MAX_LUN:
         Usb_ack_receive_setup();
         Usb_write_byte( (get_nb_lun()-1) );
         Usb_send_control_in();
         ms_multiple_drive = 1;
         return TRUE;
         break;

 		default:
			return FALSE;
			break;

	}
  	return FALSE;
}



//! usb_user_endpoint_init.
//!
//! @brief This function configures the endpoints.
//!
//! @param none
//!
//! @return none
//!
void usb_user_endpoint_init(U8 conf_nb)
{
 usb_configure_endpoint(EP_MOUSE_IN,      \
                         TYPE_INTERRUPT,     \
                         DIRECTION_IN,  \
                         SIZE_8,       \
                         ONE_BANK,     \
                         NYET_ENABLED);

 usb_configure_endpoint(EP_MS_IN,      \
                         TYPE_BULK,     \
                         DIRECTION_IN,  \
                         SIZE_64,       \
                         ONE_BANK,     \
                         NYET_ENABLED);

 usb_configure_endpoint(EP_MS_OUT,     \
                         TYPE_BULK,     \
                         DIRECTION_OUT, \
                         SIZE_64,       \
                         ONE_BANK,     \
                         NYET_ENABLED);
}


//! usb_user_get_descriptor.
//!
//! @brief This function returns the size and the pointer on a user information
//! structure
//!
//! @param none
//!
//! @return none
//!
Bool usb_user_get_descriptor(U8 type, U8 string)
{
	switch(type)
	{
		case STRING_DESCRIPTOR:
      	switch (string)
      	{
        		case LANG_ID:
          		data_to_transfer = sizeof (usb_user_language_id);
          		pbuffer = &(usb_user_language_id.bLength);
					return TRUE;
          		break;
        		case MAN_INDEX:
         	 	data_to_transfer = sizeof (usb_user_manufacturer_string_descriptor);
         	 	pbuffer = &(usb_user_manufacturer_string_descriptor.bLength);
					return TRUE;
          		break;
        		case PROD_INDEX:
         		data_to_transfer = sizeof (usb_user_product_string_descriptor);
          		pbuffer = &(usb_user_product_string_descriptor.bLength);
					return TRUE;
          		break;
        		case SN_INDEX:
          		data_to_transfer = sizeof (usb_user_serial_number);
          		pbuffer = &(usb_user_serial_number.bLength);
					return TRUE;
          		break;
        		default:
          		return FALSE;
			}
		default:
			return FALSE;
	}

	return FALSE;
}


//! hid_get_report.
//!
//! @brief This function manages hit get repport request.
//!
//! @param none
//!
//! @return none
//!
void hid_get_report(void)
{

U16 wLength;
U8  nb_byte;
bit zlp=0;



   LSB(wInterface)=Usb_read_byte();
   MSB(wInterface)=Usb_read_byte();

   data_to_transfer = sizeof(usb_hid_report_descriptor_mouse);
   pbuffer = &(usb_hid_report_descriptor_mouse.report[0]);

   LSB(wLength) = Usb_read_byte();      //!< read wLength
   MSB(wLength) = Usb_read_byte();
   Usb_ack_receive_setup() ;                  //!< clear the receive setup flag

   if (wLength > data_to_transfer)
   {
      if ((data_to_transfer % EP_CONTROL_LENGTH) == 0) { zlp = TRUE; }
      else { zlp = FALSE; }                   //!< no need of zero length packet
   }
   else
   {
      data_to_transfer = (U8)wLength;         //!< send only requested number of data
   }

    while((data_to_transfer != 0) )
   {
      while(!Is_usb_read_control_enabled());

		nb_byte=0;
      while(data_to_transfer != 0)			//!< Send data until necessary
      {
			if(nb_byte++==EP_CONTROL_LENGTH) //!< Check endpoint 0 size
			{
				break;
			}
#ifndef AVRGCC
         Usb_write_byte(*pbuffer++);
#else    // AVRGCC does not support point to PGM space
#warning with avrgcc assumes devices descriptors are stored in the lower 64Kbytes of on-chip flash memory
         Usb_write_byte(pgm_read_byte_near((unsigned int)pbuffer++));
#endif
         data_to_transfer --;
      }
      Usb_send_control_in();
   }

   Usb_send_control_in();

   if(Is_usb_receive_out()) { Usb_ack_receive_out(); return; } //!< abort from Host
   if(zlp == TRUE)        { Usb_send_control_in(); }

   while(!Is_usb_receive_out());
   Usb_ack_receive_out();
}



//! hid_set_report.
//!
//! @brief This function manages hit set report request.
//!
//! @param none
//!
//! @return none
//!
void hid_set_report (void)
{
	Usb_ack_receive_setup();
	Usb_send_control_in();

   while(!Is_usb_receive_out());
   Usb_ack_receive_out();
   Usb_send_control_in();

}


//! usb_hid_set_idle.
//!
//! @brief This function manages hid set idle request.
//!
//! @param none
//!
//! @return none
//!
void usb_hid_set_idle (void)
{
  U8 dummy;
  dummy = Usb_read_byte();
  dummy = Usb_read_byte();
  LSB(wInterface)=Usb_read_byte();
  MSB(wInterface)=Usb_read_byte();

  Usb_ack_receive_setup();

  Usb_send_control_in();                       /* send a ZLP for STATUS phase */
  while(!Is_usb_in_ready());
}


//! usb_hid_get_interface.
//!
//! @brief This function manages hid get interface request.
//!
//! @param none
//!
//! @return none
//!
void usb_hid_get_interface (void)
{
  U8 dummy;
  dummy = Usb_read_byte();
  dummy = Usb_read_byte();
  LSB(wInterface)=Usb_read_byte();
  MSB(wInterface)=Usb_read_byte();

  Usb_ack_receive_setup();

  Usb_send_control_in();                       /* send a ZLP for STATUS phase */
  while(!Is_usb_in_ready());
}

//! hid_get_hid_descriptor.
//!
//! @brief This function manages hid get hid descriptor request.
//!
//! @param none
//!
//! @return none
//!
void hid_get_hid_descriptor(void)
{

U16 wLength;
U8  nb_byte;
bit zlp=0;



   LSB(wInterface)=Usb_read_byte();
   MSB(wInterface)=Usb_read_byte();

   data_to_transfer = sizeof(usb_conf_desc.hid_mouse);
   pbuffer = &(usb_conf_desc.hid_mouse.bLength);

   LSB(wLength) = Usb_read_byte();      //!< read wLength
   MSB(wLength) = Usb_read_byte();
   Usb_ack_receive_setup() ;                  //!< clear the receive setup flag

   if (wLength > data_to_transfer)
   {
      if ((data_to_transfer % EP_CONTROL_LENGTH) == 0) { zlp = TRUE; }
      else { zlp = FALSE; }                   //!< no need of zero length packet
   }
   else
   {
      data_to_transfer = (U8)wLength;         //!< send only requested number of data
   }

   while((data_to_transfer != 0) && (!Is_usb_receive_out()))
   {
      while(!Is_usb_read_control_enabled());

		nb_byte=0;
      while(data_to_transfer != 0)			//!< Send data until necessary
      {
			if(nb_byte++==EP_CONTROL_LENGTH) //!< Check endpoint 0 size
			{
				break;
			}
#ifndef AVRGCC
         Usb_write_byte(*pbuffer++);
#else    // AVRGCC does not support point to PGM space
#warning with avrgcc assumes devices descriptors are stored in the lower 64Kbytes of on-chip flash memory
         Usb_write_byte(pgm_read_byte_near((unsigned int)pbuffer++));
#endif
         data_to_transfer --;
      }
      Usb_send_control_in();
   }

   Usb_send_control_in();

   if(Is_usb_receive_out()) { Usb_ack_receive_out(); return; } //!< abort from Host
   if(zlp == TRUE)        { Usb_send_control_in(); }

   while(!Is_usb_receive_out());
   Usb_ack_receive_out();
}
