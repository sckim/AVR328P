//! @file conf_access.h
//!
//! Copyright (c) 2004
//!
//! Please read file license.txt for copyright notice.
//!
//! This file contains the possible external configuration of the control access
//! This file will be given to any external customer
//!
//! @version 1.2 (c5131-mass-storage-virtual-1_0_4)
//!
//! @todo
//! @bug

#ifndef _CONF_ACCESS_H_
#define _CONF_ACCESS_H_


// Active the Logical Unit
#define  LUN_0                DISABLE   // On-Chip flash vitual memory
#define  LUN_1                DISABLE   // NF 2KB
#define  LUN_2                DISABLE   // NF 512B
#define  LUN_3                ENABLE    // Data Flash
#define  LUN_4                DISABLE
#define  LUN_5                DISABLE
#define  LUN_6                DISABLE
#define  LUN_7                DISABLE
#define  LUN_USB              DISABLE

// LUN 0 DEFINE
#define  LUN_0_INCLUDE                           "lib_mem\virtual_mem\virtual_mem.h"
#define  Lun_0_test_unit_ready()                 virtual_test_unit_ready()
#define  Lun_0_read_capacity(nb_sect)            virtual_read_capacity(nb_sect)
#define  Lun_0_wr_protect()                      virtual_wr_protect()
#define  Lun_0_removal()                         virtual_removal()
#define  Lun_0_read_10(ad, sec)                  virtual_read_10(ad, sec)
#define  Lun_0_usb_read()                        virtual_usb_read()
#define  Lun_0_write_10(ad, sec)                 virtual_write_10(ad, sec)
#define  Lun_0_usb_write()                       virtual_usb_write()
#define  Lun_0_ram_2_mem(addr , ram)             virtual_ram_2_mem(addr, ram)
#define  Lun_0_ram_2_mem_write()                 virtual_ram_2_mem_write()
#define  Lun_0_mem_2_ram(addr , ram)             virtual_mem_2_ram(addr, ram)
#define  Lun_0_mem_2_ram_read()                  virtual_mem_2_ram_read()
#define  LUN_0_NAME                              "VIRTUAL_MEM_ON_CHIP"

// LUN 1 DEFINE
#if (LUN_1 == ENABLE)
#define  NF_2K_MEM                               ENABLE
#else
#define	 NF_2K_MEM                               DISABLE
#endif
#define  LUN_1_INCLUDE                           "lib_mem\nf_1x_2kb\nf_mem.h"
#define  Lun_1_test_unit_ready()                 nf_test_unit_ready()
#define  Lun_1_read_capacity(nb_sect)            nf_read_capacity(nb_sect)
#define  Lun_1_wr_protect()                      nf_wr_protect()
#define  Lun_1_removal()                         nf_removal()
#define  Lun_1_read_10(ad, sec)                  nf_read_10(ad, sec)
#define  Lun_1_usb_read()                        nf_usb_read()
#define  Lun_1_write_10(ad, sec)                 nf_write_10(ad, sec)
#define  Lun_1_usb_write()                       nf_usb_write()
#define  Lun_1_ram_2_mem(addr , ram)             TODO
#define  Lun_1_ram_2_mem_write()                 TODO
#define  Lun_1_mem_2_ram(addr , ram)             TODO
#define  Lun_1_mem_2_ram_read()                  TODO

// LUN 2 DEFINE
#if (LUN_2 == ENABLE)
#define  NF_512_MEM                              ENABLE
#else
#define	 NF_512_MEM                             DISABLE
#endif
#define  LUN_2_INCLUDE                           "lib_mem\nf_1x_512\nf_mem.h"
#define  Lun_2_test_unit_ready()                 nf_test_unit_ready()
#define  Lun_2_read_capacity(nb_sect)            nf_read_capacity(nb_sect)
#define  Lun_2_wr_protect()                      nf_wr_protect()
#define  Lun_2_removal()                         nf_removal()
#define  Lun_2_read_10(ad, sec)                  nf_read_10(ad, sec)
#define  Lun_2_usb_read()                        nf_usb_read()
#define  Lun_2_write_10(ad, sec)                 nf_write_10(ad, sec)
#define  Lun_2_usb_write()                       nf_usb_write()
#define  Lun_2_ram_2_mem(addr , ram)             TODO
#define  Lun_2_ram_2_mem_write()                 TODO
#define  Lun_2_mem_2_ram(addr , ram)             TODO
#define  Lun_2_mem_2_ram_read()                  TODO

// LUN 3 DEFINE
#if (LUN_3 == ENABLE)
#define  DF_MEM                                  ENABLE
#else
#define	DF_MEM                                  DISABLE
#endif
#define  LUN_ID_DF                               LUN_ID_3
#define  LUN_3_INCLUDE                           "df_mem.h"
#define  Lun_3_test_unit_ready()                 df_test_unit_ready()
#define  Lun_3_read_capacity(nb_sect)            df_read_capacity(nb_sect)
#define  Lun_3_wr_protect()                      df_wr_protect()
#define  Lun_3_removal()                         df_removal()
#define  Lun_3_read_10(ad, sec)                  df_read_10(ad, sec)
#define  Lun_3_usb_read()                        df_usb_read()
#define  Lun_3_write_10(ad, sec)                 df_write_10(ad, sec)
#define  Lun_3_usb_write()                       df_usb_write()
#define  Lun_3_ram_2_mem(addr , ram)             df_ram_2_df(addr, ram)
#define  Lun_3_ram_2_mem_write()                 df_ram_2_df_write()
#define  Lun_3_mem_2_ram(addr , ram)             df_df_2_ram(addr, ram)
#define  Lun_3_mem_2_ram_read()                  df_df_2_ram_read()
#define  LUN_3_NAME                               "\"On board data flash\""

// LUN USB DEFINE
#if (LUN_USB == ENABLE)
#define  MEM_USB                                  ENABLE
#else
#define	MEM_USB                                  DISABLE
#endif
#define  LUN_USB_INCLUDE                           "lib_mem\host_mem\host_mem.h"
#define  Lun_usb_test_unit_ready(lun)              host_test_unit_ready(lun)
#define  Lun_usb_read_capacity(lun,nb_sect)        host_read_capacity(lun,nb_sect)
#define  Lun_usb_wr_protect(lun)                   host_wr_protect(lun)
#define  Lun_usb_removal()                         host_removal()
#define  Lun_usb_ram_2_mem(addr , ram)             host_write_10_ram(addr, ram)
#define  Lun_usb_mem_2_ram(addr , ram)             host_read_10_ram(addr, ram)
#define  LUN_USB_NAME                              "\"USB Remote memory\""


// ATMEL DEFINE - DO NOT MODIFY

// Active interface fonction
#define  ACCESS_USB           ENABLED  // USB I/O in control access
#define  ACCESS_STREAM        DISABLED  // Stream I/O in control access
#define  ACCESS_STREAM_RECORD DISABLED // Stream I/O in control access AND RECORD MODE
#define  ACCESS_MEM_TO_RAM    DISABLED  // RAM to Mem I/O in control access
#define  ACCESS_MEM_TO_MEM    DISABLED // Mem to Mem I/O in control access



// Specific option control access
#define  GLOBAL_WR_PROTECT    DISABLED // To manage a global write protection


#endif  //! _CONF_ACCESS_H_

