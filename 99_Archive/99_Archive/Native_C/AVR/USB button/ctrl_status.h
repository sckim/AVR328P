//! @file ctrl_status.h
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


#ifndef _CTRL_STATUS_H_
#define _CTRL_STATUS_H_

//_____ D E F I N I T I O N S ______________________________________________

//!   Define control status
typedef enum
{
   CTRL_GOOD         =(PASS  )  // It is ready
,  CTRL_FAIL         =(FAIL  )  // Memory fail
,  CTRL_NO_PRESENT   =(FAIL+1)  // Memory unplug
,  CTRL_BUSY         =(FAIL+2)  // Not initialize
} Ctrl_status;

#endif   // _CTRL_STATUS_H_

