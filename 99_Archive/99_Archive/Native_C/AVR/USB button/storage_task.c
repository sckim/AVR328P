//!
//! @file storage_task.c,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file manages the mass storage task.
//!
//!
//! @version 1.2 at90usb162-2enum-mouse_ms-1_0_1 $Id: storage_task.c,v 1.2 2007/01/08 16:09:31 arobert Exp $
//!
//! @todo
//! @bug
//!/

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "conf_usb.h"
#include "storage_task.h"
#include "usb_drv.h"
#include "usb_descriptors.h"
#include "usb_standard_request.h"
#include "usb_specific_request.h"
#include "scsi_decoder.h"
#include "ctrl_access.h"
#include "df.h"




//_____ M A C R O S ________________________________________________________





//_____ D E F I N I T I O N S ______________________________________________



//_____ D E C L A R A T I O N S ____________________________________________



extern  U8   usb_configuration_nb;


static bit ms_data_direction;
static _MEM_TYPE_SLOW_ U8  dCBWTag[4];

extern _MEM_TYPE_SLOW_ U8  g_scsi_status;
extern _MEM_TYPE_FAST_ U32 g_scsi_data_remaining;
extern bit ms_multiple_drive;
extern _MEM_TYPE_SLOW_ U8  g_scsi_command[16];


_MEM_TYPE_SLOW_ U8 usb_LUN;


void usb_mass_storage_cbw (void);
void usb_mass_storage_csw (void);

#define Usb_set_ms_data_direction_in()  (ms_data_direction = 1)
#define Usb_set_ms_data_direction_out() (ms_data_direction = 0)
#define Is_usb_ms_data_direction_in()   (ms_data_direction == 1)


//!
//! @brief This function initializes the hardware/software ressources required for storage task.
//!
//!
//! @param none
//!
//! @return none
//!
//!/
void storage_task_init(void)
{
   Leds_init();
   //Usb_enable_sof_interrupt();
   df_init_spi();    // Init the board (definition of the links between the DF and AVR USB)
   df_mem_init();    // Init the hw/sw ressources required to drive the DF.

}





//! @brief Entry point of the mass storage task management
//!
//! This function links the mass storage SCSI commands and the USB bus.
//!
//!
//! @param none
//!
//! @return none
void storage_task(void)
{
   if (Is_device_enumerated())
   {
      Usb_select_endpoint(EP_MS_OUT);
      if (Is_usb_receive_out())
      {
         usb_mass_storage_cbw();
         usb_mass_storage_csw();
      }
   }
}






//! @brief USB Command Block Wrapper (CBW) management
//!
//! This function decodes the CBW command and stores the SCSI command
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return none
void usb_mass_storage_cbw (void)
{
bit cbw_error;
U8  c;
U8  dummy;

   cbw_error = FALSE;
   Usb_select_endpoint(EP_MS_OUT);           //! check if dCBWSignature is correct
   if (0x55 != Usb_read_byte())
      { cbw_error = TRUE; } //! 'U'
   if (0x53 != Usb_read_byte())
      { cbw_error = TRUE; } //! 'S'
   if (0x42 != Usb_read_byte())
      { cbw_error = TRUE; } //! 'B'
   if (0x43 != Usb_read_byte())
      { cbw_error = TRUE; } //! 'C'

   dCBWTag[0] = Usb_read_byte();             //! Store CBW Tag to be repeated in CSW
   dCBWTag[1] = Usb_read_byte();
   dCBWTag[2] = Usb_read_byte();
   dCBWTag[3] = Usb_read_byte();
	
   LSB0(g_scsi_data_remaining) = Usb_read_byte();
   LSB1(g_scsi_data_remaining) = Usb_read_byte();
   LSB2(g_scsi_data_remaining) = Usb_read_byte();
   LSB3(g_scsi_data_remaining) = Usb_read_byte();


   if (Usb_read_byte() != 0x00)              //! if (bmCBWFlags.bit7 == 1) {direction = IN}
   {
      Usb_set_ms_data_direction_in();
      if (cbw_error)
      {
         Usb_ack_receive_out();
         Usb_select_endpoint(EP_MS_IN);
         Usb_enable_stall_handshake();
         return;
      }
   }
   else
   {
      Usb_set_ms_data_direction_out();
      if (cbw_error)
      {
         Usb_enable_stall_handshake();
         Usb_ack_receive_out();
         return;
      }
   }

   usb_LUN = Usb_read_byte();

   if (!ms_multiple_drive)
   {
      usb_LUN = get_cur_lun();
   }

   dummy      = Usb_read_byte();                //! dummy CBWCBLength read


   for (c=0; c<16; c++)                         // store scsi_command
   {
      g_scsi_command[c] = Usb_read_byte();
   }

   Usb_ack_receive_out();

   if (Is_usb_ms_data_direction_in())
   {
      Usb_select_endpoint(EP_MS_IN);
   }

   if (TRUE != scsi_decode_command())
   {
      if (g_scsi_data_remaining != 0)
      {
         Usb_enable_stall_handshake();
      }
   }
}

//! @brief USB Command Status Wrapper (CSW) management
//!
//! This function sends the status in relation with the last CBW
//!
//!
//! @param none
//!
//! @return none
void usb_mass_storage_csw (void)
{
   Usb_select_endpoint(EP_MS_IN);
   while (Is_usb_endpoint_stall_requested())
   {
      Usb_select_endpoint(EP_CONTROL);
      if (Is_usb_receive_setup())       { usb_process_request(); }
      Usb_select_endpoint(EP_MS_IN);
   }

   Usb_select_endpoint(EP_MS_OUT);
   while (Is_usb_endpoint_stall_requested())
   {
      Usb_select_endpoint(EP_CONTROL);
      if (Is_usb_receive_setup())       { usb_process_request(); }
      Usb_select_endpoint(EP_MS_OUT);
   }

   Usb_select_endpoint(EP_MS_IN);
   while(!Is_usb_write_enabled());
                                                         //! write CSW Signature
   Usb_write_byte(0x55);                                 //! 'U'
   Usb_write_byte(0x53);                                 //! 'S'
   Usb_write_byte(0x42);                                 //! 'B'
   Usb_write_byte(0x53);                                 //! 'S'
                                                         //! write stored CBW Tag
   Usb_write_byte(dCBWTag[0]);
   Usb_write_byte(dCBWTag[1]);
   Usb_write_byte(dCBWTag[2]);
   Usb_write_byte(dCBWTag[3]);
                                                         //! write data residue value
   Usb_write_byte( ((Byte*)&g_scsi_data_remaining)[3] );
   Usb_write_byte( ((Byte*)&g_scsi_data_remaining)[2] );
   Usb_write_byte( ((Byte*)&g_scsi_data_remaining)[1] );
   Usb_write_byte( ((Byte*)&g_scsi_data_remaining)[0] );

   //! write command status
    Usb_write_byte(g_scsi_status);                        //! 0 -> PASS, 1 -> FAIL
    Usb_send_in();
}
