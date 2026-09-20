//! @file conf_scheduler.h,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! This file contains the scheduler configuration definition
//!
//! @version 1.1 at90usb162-2enum-mouse_ms-1_0_1 $Id: conf_scheduler.h,v 1.1 2006/09/07 14:15:11 rletendu Exp $
//!
//! @todo
//! @bug

#ifndef _CONF_SCHEDULER_H_
#define _CONF_SCHEDULER_H_



//! @defgroup scheduler_conf Scheduler configuration
//! @{
#define SCHEDULER_TYPE          SCHEDULER_FREE  // SCHEDULER_(TIMED|TASK|FREE|CUSTOM)
#define Scheduler_task_1_init   usb_task_init
#define Scheduler_task_1        usb_task
#define Scheduler_task_2_init   mouse_task_init
#define Scheduler_task_2        mouse_task
#define Scheduler_task_3_init   storage_task_init
#define Scheduler_task_3        storage_task

//! @}

#endif  //! _CONF_SCHEDULER_H_

