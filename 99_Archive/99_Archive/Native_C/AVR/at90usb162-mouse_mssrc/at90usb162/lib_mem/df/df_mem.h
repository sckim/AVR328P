//! @file df_mem.h
//!
//! Copyright (c) 2004
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the interface routines of Data Flash memory.
//!
//! @version 1.1 (c5131-mass-storage-complete-1_0_0)
//!
//! @todo
//! @bug
#ifndef _DFMEM_H_
#define _DFMEM_H_

#include "conf\conf_access.h"
#include "modules\control_access\ctrl_status.h"




//_____ D E F I N I T I O N S ______________________________________________

//! FAT specification
#define  ENTRY_SIZE           32    // size of entrie in byte



// First sector of the disk virtual (this disk isn't partitioned, only one partion)
#define  PBR_SECTOR           (0)
#define  FAT_SECTOR           (PBR_SECTOR  + VMEM_RESERVED_SIZE)
#define  ROOT_SECTOR          (FAT_SECTOR  + (VMEM_SIZE_FAT*VMEM_NB_FATS))
#define  FILE_SECTOR          (ROOT_SECTOR + ((ENTRY_SIZE*VMEM_NB_ROOT_ENTRY) / VMEM_SECTOR_SIZE))                   // 1(sector) = size root dir





//---- CONTROL FONCTIONS ----

// those fonctions are declared in df_mem.h
void           df_mem_init(void);
Ctrl_status    df_test_unit_ready(void);
Ctrl_status    df_read_capacity( U32 _MEM_TYPE_SLOW_ *u32_nb_sector );
Bool           df_wr_protect(void);
Bool           df_removal(void);


//---- ACCESS DATA FONCTIONS ----

// Standard functions for open in read/write mode the device
Ctrl_status    df_read_10( U32 addr , U16 nb_sector );
Ctrl_status    df_write_10( U32 addr , U16 nb_sector );

// Standard functions for read/write 1 sector to 1 sector ram buffer
Ctrl_status    df_ram_2_df( U32 addr, U8 *ram);
Ctrl_status    df_df_2_ram( U32 addr, U8 *ram);

Ctrl_status    df_ram_2_df_write(void);
Ctrl_status    df_df_2_ram_read(void);

//** If your device transfer have a specific transfer for USB (Particularity of Chejudo product, or bootloader)
#ifdef DF_VALIDATION
#include "virtual_usb.h"
#else
#include "lib_mcu\usb\usb_drv.h"    // In this case the driver must be known for the USB access
#endif
Ctrl_status df_usb_read( void );
Ctrl_status df_usb_write( void );





#endif   // _DFMEM_H_

