//! @file ctrl_access.h
//!
//! Copyright (c) 2004
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the interface :
//! - between USB <-> MEMORY
//! OR
//! - between USB <- Access Memory Ctrl -> Memory
//!
//! This interface may be controled by a "Access Memory Control" for :
//! - include a management of write protect global or specific
//! - include a management of access password
//! - ...
//!
//! @version 1.1 (c5131-mass-storage-virtual-1_0_4)
//!
//! @todo
//! @bug


#ifndef _MEM_CTRL_H_
#define _MEM_CTRL_H_

#include "conf_access.h"
#include "ctrl_status.h"

// FYC: Memory = Logical Unit
#if (LUN_0 == ENABLE)
   #include    LUN_0_INCLUDE
#endif
#if (LUN_1 == ENABLE)
   #include    LUN_1_INCLUDE
#endif
#if (LUN_2 == ENABLE)
   #include    LUN_2_INCLUDE
#endif
#if (LUN_3 == ENABLE)
   #include    LUN_3_INCLUDE
#endif
#if (LUN_4 == ENABLE)
   #include    LUN_4_INCLUDE
#endif
#if (LUN_5 == ENABLE)
   #include    LUN_5_INCLUDE
#endif
#if (LUN_6 == ENABLE)
   #include    LUN_6_INCLUDE
#endif
#if (LUN_7 == ENABLE)
   #include    LUN_7_INCLUDE
#endif
#if (LUN_USB == ENABLE)
   #include    LUN_USB_INCLUDE
#endif


//------- Test the configuration in conf_access.h

// Specific option control access
#ifndef  GLOBAL_WR_PROTECT
#  error GLOBAL_WR_PROTECT must be defined with ENABLED or DISABLED in conf_access.h
#endif
//------- END OF Test the configuration in conf_access.h



//_____ D E F I N I T I O N S ______________________________________________



//!**** Listing of commun interface ****************************************

U8             get_nb_lun();
U8             get_cur_lun();
Ctrl_status    mem_test_unit_ready( U8 lun );
Ctrl_status    mem_read_capacity( U8 lun , U32 _MEM_TYPE_SLOW_ *u32_nb_sector );
Bool           mem_wr_protect( U8 lun );
Bool           mem_removal( U8 lun );
U8 *       mem_name( U8 lun );


//!**** Listing of READ/WRITE interface ************************************


//---- Interface for USB ---------------------------------------------------
   Ctrl_status memory_2_usb( U8 lun , U32 addr , U16 nb_sector );
   Ctrl_status usb_2_memory( U8 lun , U32 addr , U16 nb_sector );
#include "usb_drv.h"
#include "conf_usb.h"
//--------------------------------------------------------------------------

//---- Interface for RAM to MEM --------------------------------------------
Ctrl_status    memory_2_ram( U8 lun , const U32 _MEM_TYPE_SLOW_ *addr , U8 _MEM_TYPE_SLOW_ *ram );
Ctrl_status    ram_2_memory( U8 lun , const U32 _MEM_TYPE_SLOW_ *addr , U8 _MEM_TYPE_SLOW_ * ram );
//--------------------------------------------------------------------------


//!---- Interface for streaming interface ----------------------------------
#if (ACCESS_STREAM == ENABLED)

#define  ID_STREAM_ERR        0xFF


// RLE #include "dfc_mngt.h"

#define  TYPE_STREAM_AUDIO    DFC_ID_AUDIOPROC1
#define  TYPE_STREAM_AUDIO2   DFC_ID_AUDIOPROC2
#define  TYPE_STREAM_SIO      DFC_ID_SIO
#define  TYPE_STREAM_SPI      DFC_ID_SPI
#define  TYPE_STREAM_DEVNULL  DFC_ID_NULL_DEV

   U8          stream_mem_to_mem       ( U8 src_lun , U32 src_addr , U8 dest_lun , U32 dest_addr , U16 nb_sector );
   U8          stream_read_10_start    ( U8 TypeStream , U8 lun , U32 addr , U16 nb_sector );
   U8          stream_write_10_start   ( U8 TypeStream , U8 lun , U32 addr , U16 nb_sector );
   U8          stream_to_stream_start  ( U8 TypeStream_src , U8 TypeStream_dest  , U16 nb_sector );
   Ctrl_status stream_state( U8 Id );
   U16         stream_stop( U8 Id );

#endif   // (ACCESS_STREAM == ENABLED)
//--------------------------------------------------------------------------

#endif   // _MEM_CTRL_H_

