//! @file df_mem.c
//!
//! Copyright (c) 2004
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief  This file contains the interface routines of Data Flash memory.
//!
//! @version 1.1 (c5131-mass-storage-complete-1_0_0)
//!
//! @todo
//! @bug

//_____  I N C L U D E S ___________________________________________________

#include "config.h"                         // system configuration
#include "df_mem.h"
#include "df.h"



//_____ M A C R O S ________________________________________________________
//_____ P R I V A T E    D E C L A R A T I O N _____________________________


//_____ D E F I N I T I O N ________________________________________________


#define MEM_BASE_ADDRESS       0x0000


data    U32  gl_ptr_mem;             /* memory data pointer */


/* Disk management  */
bit     reserved_disk_space = FALSE;    /* reserved space for application on disk */



//extern xdata U32 df_mem_size;
extern xdata U32 DF_DISK_SIZE;


void  df_check_init( void );


//_____ D E C L A R A T I O N ______________________________________________

//!
//! @brief This function initializes the hw/sw ressources required to drive the DF.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return none
//!
//!/
void df_mem_init(void)
{
   df_init();        // Init the DF driver and its communication link.
}


//!
//! @brief This function tests the state of the DF memory.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!   Else           ->    CTRL_NO_PRESENT
//!/
Ctrl_status df_test_unit_ready(void)
{
   return( (OK==df_mem_check()) ? CTRL_GOOD : CTRL_NO_PRESENT);
}


//!
//! @brief This function gives the address of the last valid sector.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param *u32_nb_sector  number of sector (sector = 512B). OUT
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!/
Ctrl_status df_read_capacity( U32 _MEM_TYPE_SLOW_ *u32_nb_sector )
{
   *u32_nb_sector = DF_DISK_SIZE;
   return CTRL_GOOD;
}


//!
//! @brief This function returns the write protected status of the memory.
//!
//! Only used by memory removal with a HARDWARE SPECIFIC write protected detection
//! !!! The customer must unplug the memory to change this write protected status,
//! which cannot be for a DF.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @return FALSE  -> the memory is not write-protected (always)
//!/
Bool  df_wr_protect(void)
{
   return FALSE;
}


//!
//! @brief This function tells if the memory has been removed or not.
//!
//! @param none
//!
//! @warning Code:?? bytes (function code length)
//!
//! @return FALSE  -> The memory isn't removed
//!/
Bool  df_removal(void)
{
   return FALSE;
}



//------------ STANDARD FUNCTIONS to read/write the memory --------------------

//!
//! @brief This function performs a read operation of n sectors from a given address on.
//! (sector = 512B)
//!
//!         DATA FLOW is: DF => USB
//!
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param addr         Sector address to start the read from
//! @param nb_sector    Number of sectors to transfer
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!   A error occur  ->    CTRL_FAIL
//!
Ctrl_status df_read_10( U32 addr , U16 nb_sector )
{
#if   (DF_NB_MEM != 1)                 // if more than 1 memory, variables are needed for zones mangement
   U32   next_sector_addr = addr;
   U16   nb_sectors_remaining = nb_sector;
#endif

#if   (DF_NB_MEM == 1)     /* 1 DATAFLASH */
   df_read_open(addr);                    // wait device is not busy, then send command & address
   df_read_sector(nb_sector);             // transfer data from memory to USB
#else                      /* 2 or 4 DATAFLASH */
   #ifdef DF_4_MB             // 512B PAGES
   while (nb_sectors_remaining != 0)
   {
      df_read_open(next_sector_addr);     // wait device is not busy, then send command & address
      df_read_sector(1);                  // transfer the page from memory to USB
      df_read_close();
      nb_sectors_remaining--;
      next_sector_addr++;
   }
   #else                      // 1024B PAGES
   while (nb_sectors_remaining != 0)
   {
      df_read_open(next_sector_addr);     // wait device is not busy, then send command & address
      if ((LSB0(next_sector_addr)&0x01) == 0)
      {
        if (nb_sectors_remaining == 1)
        {
           df_read_sector(1);
           df_read_close();
           nb_sectors_remaining--;
           next_sector_addr++;
        }
        else
        {
          df_read_sector(2);
          df_read_close();
          nb_sectors_remaining -= 2;
          next_sector_addr += 2;
        }
      }
      else
      {
        df_read_sector(1);
        df_read_close();
        nb_sectors_remaining--;
        next_sector_addr++;
      }
   }
   #endif
#endif
   df_read_close();                    // unselect memory
   return CTRL_GOOD;
}


//! This fonction initialise the memory for a write operation
//!
//!         DATA FLOW is: USB => DF
//!
//!
//! (sector = 512B)
//! @param addr         Sector address to start write
//! @param nb_sector    Number of sectors to transfer
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!   A error occur  ->    CTRL_FAIL
//!
Ctrl_status df_write_10( U32 addr , U16 nb_sector )
{
#if   (DF_NB_MEM != 1)                 // if more than 1 memory, variables are needed for zones mangement
   U32   next_sector_addr = addr;
   U16   nb_sectors_remaining = nb_sector;
#endif

#if      (DF_NB_MEM == 1)  /* 1 DATAFLASH */
   df_write_open(addr);                    // wait device is not busy, then send command & address
   df_write_sector(nb_sector);             // transfer data from memory to USB
#else                      /* 2 or 4 DATAFLASH */
   #ifdef DF_4_MB       // 512B PAGES
   while (nb_sectors_remaining != 0)
   {
      df_write_open(next_sector_addr);     // wait device is not busy, then send command & address
      df_write_sector(1);                  // transfer the page from memory to USB
      df_write_close();
      nb_sectors_remaining--;
      next_sector_addr++;
   }
   #else                // 1024B PAGES
   while (nb_sectors_remaining != 0)
   {
      df_write_open(next_sector_addr);     // wait device is not busy, then send command & address
      if ((LSB0(next_sector_addr)&0x01) == 0)
      {
        if (nb_sectors_remaining == 1)
        {
          df_write_sector(1);
          df_write_close();
          nb_sectors_remaining--;
          next_sector_addr++;
        }
        else
        {
          df_write_sector(2);
          df_write_close();
          nb_sectors_remaining -= 2;
          next_sector_addr += 2;
        }
      }
      else
      {
        df_write_sector(1);
        df_write_close();
        nb_sectors_remaining--;
        next_sector_addr++;
      }
   }
   #endif
#endif
   df_write_close();                    // unselect memory
   return CTRL_GOOD;
}


//------------ SPECIFIC FONCTION USB TRANSFER -----------------------------------------

//** If your device transfer have a specific transfer for USB (Particularity of Chejudo product, or bootloader)
// !!! In this case the driver must be know the USB access

//! This fonction transfer the memory data (programed in scsi_read_10) directly to the usb interface
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!
Ctrl_status df_usb_read()
{
   return CTRL_GOOD;
}


//! This fonction transfer the usb data (programed in scsi_write_10) directly to the memory data
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!
Ctrl_status df_usb_write( void )
{
   return CTRL_GOOD;
}


//------------ Standard functions for read/write 1 sector to 1 sector ram buffer -----------------

//! This fonction initialise the memory for a write operation
//! from ram buffer
//!
//!         DATA FLOW is: RAM => DF
//!
//! (sector = 512B)
//! @param addr         Sector address to write
//! @param ram          Ram buffer pointer
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!   A error occur  ->    CTRL_FAIL
//!
Ctrl_status    df_ram_2_df(U32 addr, U8 *ram)
{
   df_write_open(addr);
   df_write_sector_from_ram(ram);
   df_write_close();
   return CTRL_GOOD;
}

//! This fonction read 1 sector from DF to ram buffer
//!
//!         DATA FLOW is: DF => RAM
//!
//! (sector = 512B)
//! @param addr         Sector address to read
//! @param ram          Ram buffer pointer
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!   A error occur  ->    CTRL_FAIL
//!
Ctrl_status    df_df_2_ram( U32 addr, U8 *ram)
{
   df_read_open(addr);
   df_read_sector_2_ram(ram);
   df_read_close();
   return CTRL_GOOD;
}



//! This fonction transfer the memory data to ram
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!
Ctrl_status df_df_2_ram_read()
{
   return CTRL_GOOD;
}


//! This fonction transfer ram to the memory data
//!
//! @return                Ctrl_status
//!   It is ready    ->    CTRL_GOOD
//!
Ctrl_status df_ram_2_df_write( void )
{
   return CTRL_GOOD;
}

