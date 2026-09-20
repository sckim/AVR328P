/*H**************************************************************************
* NAME:         df.h
*----------------------------------------------------------------------------
* Copyright (c) 2006 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      at90usb162-2enum-mouse_ms-1_0_1
* REVISION:     1.3
*----------------------------------------------------------------------------
* PURPOSE:
* This file contains the low-level dataflash interface.
*****************************************************************************/

#ifndef _DF_H_
#define _DF_H_

/*_____ I N C L U D E S ____________________________________________________*/

#include "config.h"


/*_____ M A C R O S ________________________________________________________*/

#ifndef DF_SECTOR_SIZE
#define DF_SECTOR_SIZE   512   //default sector size is 512 bytes
#endif

/* FAT Format Structure */
typedef struct
{
  Uint16 nb_cylinder;
  Byte   nb_head;
  Byte   nb_sector;
  Byte   nb_hidden_sector;
  Byte   nb_sector_per_cluster;
} s_format;

#define MEM_BSY       0
#define MEM_OK        1
#define MEM_KO        2

/*----- DataFlash definition -----*/
#define DF_MSK_DENSITY    ((Byte)0x3C)      /* status density mask */
#define DF_MSK_BIT_BUSY   ((Byte)0x80)
#define DF_MEM_BUSY       ((Byte)0x00)

#define DF_RD_STATUS      ((Byte)0xD7)      /* read status cmd */
#define DF_PG_ERASE       ((Byte)0x81)      /* page erase cmd  */
#define DF_BK_ERASE       ((Byte)0x50)      /* block erase cmd */

#define DF_WR_BUF_1       ((Byte)0x84)      /* write buffer 1 cmd */
#define DF_WR_BUF_2       ((Byte)0x87)      /* write buffer 2 cmd */
#define DF_B1_MAIN        ((Byte)0x83)      /* buffer 1 to main program with erase cmd */
#define DF_B2_MAIN        ((Byte)0x86)      /* buffer 2 to main program with erase cmd */

#define DF_RD_MAIN        ((Byte)0xD2)      /* main memory page read cmd */
#define DF_TF_BUF_1       ((Byte)0x53)      /* main memory page to buffer 1 transfer cmd */
#define DF_TF_BUF_2       ((Byte)0x55)      /* main memory page to buffer 2 transfer cmd */
#define DF_RD_BUF_1       ((Byte)0xD4)      /* buffer 1 read cmd */
#define DF_RD_BUF_2       ((Byte)0xD6)      /* buffer 2 read cmd */


/* Memory Size based on 512 bytes block size */
#define DF_SIZE_4MB         ((Uint32)(8192 - 1))
#define DF_SIZE_8MB         ((Uint32)(16384 - 1))
#define DF_SIZE_16MB        ((Uint32)(32768 - 1))
#define DF_SIZE_32MB        ((Uint32)(65536 - 1))
#define DF_SIZE_64MB        ((Uint32)(131072 - 1))

#define DF_4MB            ((Byte)0)
#define DF_8MB            ((Byte)1)
#define DF_16MB           ((Byte)2)
#define DF_32MB           ((Byte)3)
#define DF_64MB           ((Byte)4)


/* BUSY Management and Memory Selection */

/* The variable "df_mem_busy" can contain the state of 4 dataflash */
#define  df_set_busy(i)       (df_mem_busy |= (1<<i))
#define  df_release_busy(i)   (df_mem_busy &= ~(1<<i))
#define  is_df_busy(i)        (((df_mem_busy&(1<<i)) != 0) ? TRUE : FALSE)

/* The variable "df_select" contains the current number of the memory addressed */
#define  MEM_DF0           0x00
#define  MEM_DF1           0x01
#define  MEM_DF2           0x02
#define  MEM_DF3           0x03


/*_____ D E F I N I T I O N ________________________________________________*/

#ifdef DF_4_MB            /* AT45DB321 memories */
  #define DF_SHFT_DFIDX   (22)              /* RShift to apply to an absolute
                                             * Byte address to get the DF idx */
  #define DF_DENSITY      ((Byte)0x34)
  #define DF_PG_BUF_1     ((Byte)0x82)      /* main memory program through buf1 */
  #define DF_PG_BUF_2     ((Byte)0x85)      /* main memory program through buf2 */
  #define DF_PAGE_SIZE    (512)             /* page length */
  #define DF_PAGE_MASK    ((Byte)0x01)      /* mask MSB page bits */
  #define DF_SHFT_B1      (1)
  #define DF_SHFT_B2      (7)
#endif

#ifdef DF_8_MB             /* AT45DB642 memories */
  #define DF_SHFT_DFIDX   (23)             /* RShift to apply to an absolute
                                             * Byte address to get the DF idx */
  #define DF_DENSITY      ((Byte)0x3C)
  #define DF_PG_BUF_1     ((Byte)0x82)      /* fast main memory program through buf1 */
  #define DF_PG_BUF_2     ((Byte)0x85)      /* fast main memory program through buf2 */
  #define DF_PAGE_SIZE    (1024)            /* page length */
  #define DF_PAGE_MASK    ((Byte)0x03)      /* mask MSB page bits */
  #define DF_SHFT_B1      (1)
  #define DF_SHFT_B2      (7)
#endif


/*_____ D E C L A R A T I O N ______________________________________________*/

bit     df_init (void);
bit     df_mem_check(void);
bit     df_read_open (Uint32);
void    df_read_close (void);
bit     df_write_open (Uint32);
void    df_write_close (void);

//! Funtions to link USB DEVICE flow with data flash
bit     df_write_sector (Uint16);
bit     df_read_sector (Uint16);

//! Functions to read/write one sector (512btes) with ram buffer pointer
bit     df_read_sector_2_ram(U8 *ram);
bit     df_write_sector_from_ram(U8 *ram);


s_format  * df_format (void);


/* Disk size: number of block - 1 */
#define Df_disk_size()            ((Uint32)(DF_DISK_SIZE))
#define Df_disk_size_0()          ((Byte)(Df_disk_size() >> 24))
#define Df_disk_size_1()          ((Byte)(Df_disk_size() >> 16))
#define Df_disk_size_2()          ((Byte)(Df_disk_size() >> 8))
#define Df_disk_size_3()          ((Byte)(Df_disk_size()))

/* Block size: size of a block in byte */
#define Df_block_size()           ((Uint32)512)
#define Df_block_size_0()         ((Byte)(Df_block_size() >> 24))
#define Df_block_size_1()         ((Byte)(Df_block_size() >> 16))
#define Df_block_size_2()         ((Byte)(Df_block_size() >> 8))
#define Df_block_size_3()         ((Byte)(Df_block_size()))


#endif  /* _DF_H_ */


