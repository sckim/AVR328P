/*C**************************************************************************
* NAME:         df.c
*----------------------------------------------------------------------------
* Copyright (c) 2006 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      at90usb162-2enum-mouse_ms-1_0_1
* REVISION:     1.4
*----------------------------------------------------------------------------
* PURPOSE:
* This file contains the low-level dataflash routines
*
* NOTES:
* Global Variables:
*   - gl_ptr_mem: long in data space
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include "config.h"                         /* system configuration */
#ifdef DF_VALIDATION
#include "virtual_usb.h"
#else
#include "usb_drv.h"            /* usb driver definition */
#endif
#include "spi_drv.h"            /* spi driver definition */
#include "df.h"                             /* dataflash definition */


/*_____ M A C R O S ________________________________________________________*/


/*_____ D E F I N I T I O N ________________________________________________*/

extern  Uint32  gl_ptr_mem;         /* memory data pointer     */

static  U8      df_mem_busy;                /* memories in busy state  */
static  U8      df_select;                  /* current memory selected */

/*_____ D E C L A R A T I O N ______________________________________________*/

static  void    df_wait_busy(void);
static  void    df_chipselect_current(void);

s_format  df_tab_format[]=
  {
   /* nb_cylinder, nb_head, nb_sector, nb_hidden, nb_sector_per_cluster */
    { (Uint16)255, (Byte)4, (Byte)8,   (Byte)15,  (Byte)8 },    /* DF_SIZE_4MB */
    { (Uint16)510, (Byte)4, (Byte)8,   (Byte)15,  (Byte)8 },    /* DF_SIZE_8MB */
    { (Uint16)510, (Byte)4, (Byte)16,  (Byte)15,  (Byte)8 },    /* DF_SIZE_16MB */
    { (Uint16)510, (Byte)8, (Byte)16,  (Byte)15,  (Byte)8 },    /* DF_SIZE_32MB */
  };


#ifdef DF_4_MB            /* AT45DB321 memories */
  #if(DF_NB_MEM == 4)
    xdata Uint32 DF_DISK_SIZE   = DF_SIZE_16MB;
  #elif (DF_NB_MEM == 2)
    xdata Uint32 DF_DISK_SIZE   = DF_SIZE_8MB;
  #elif (DF_NB_MEM ==1)
    xdata Uint32 DF_DISK_SIZE   = DF_SIZE_4MB;
  #endif
#endif

#ifdef DF_8_MB             /* AT45DB642 memories */
  #if(DF_NB_MEM == 4)
    xdata Uint32 DF_DISK_SIZE   = DF_SIZE_32MB;
  #elif (DF_NB_MEM == 2)
    xdata Uint32 DF_DISK_SIZE   = DF_SIZE_16MB;
  #elif (DF_NB_MEM ==1)
    Uint32 DF_DISK_SIZE   = DF_SIZE_8MB;
  #endif
#endif


//!
//! @brief This function initializes the SPI communication link between the DF and the DF driver.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return none
//!
//!/
static void df_spi_init(void)
{
   Spi_set_mode(SPI_MASTER_MODE_3);
   //Spi_set_rate(SPI_RATE_0);   //impossible in AVR mode in spi_drv.h
   Spi_config_speed(SPI_RATE_1); //theses 2 lines replace the Spi_set_rate(SPI_RATE_0)
   Spi_set_doublespeed();        //theses 2 lines replace the Spi_set_rate(SPI_RATE_0)
   // Spi_set_rate(SPI_RATE_0) -> SCK freq == fosc/2.
   // ==
   // Spi_config_speed(SPI_RATE_1) -> SCK freq == fosc/4
   // +
   // Spi_set_doublespeed() -> SCK freq == fosc/2

   Spi_disable_ss();
   Spi_enable();
}

//!
//! @brief This function initializes the Dataflash controller & the SPI bus(over which the DF is controlled).
//!
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return bit
//!   The memory is ready     -> OK (always)
//!/
bit df_init (void)
{
   // Init the SPI communication link between the DF and the DF driver.
   df_spi_init();

   // Data Flash Controller init.
   df_mem_busy = 0;     // all memories ready
   df_select = MEM_DF0;
   return(OK);
}



//!
//! @brief This function selects a DF memory according to the sector pointer
//!        The "df_select" variable contains the current memory addressed
//!        Refer to the documentation of the function df_translate_addr() for more information about zones management
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param memzone    LSB of logical sector address to open
//!
//! @return none
//!/
static void df_chipselect_memzone(U8 memzone)
{
#if (DF_NB_MEM == 1)
   df_select = MEM_DF0;
#else
   #if (DF_NB_MEM == 2)
      #if (DF_PAGE_SIZE == 512)
         if ((memzone&0x01) == 0)                 // each page parity matches a memory
           df_select = MEM_DF0;
         else
           df_select = MEM_DF1;
      #else
         if ((memzone&0x02) == 0)                 // each double page parity matches a memory
           df_select = MEM_DF0;
         else
           df_select = MEM_DF1;
      #endif
   #else
      #if (DF_PAGE_SIZE == 512)
         switch(memzone&0x3)
         {
            case 0:
              df_select = MEM_DF0;
              break;
            case 1:
              df_select = MEM_DF1;
              break;
            case 2:
              df_select = MEM_DF2;
              break;
            case 3:
              df_select = MEM_DF3;
              break;
            default:
              break;
         }
      #else
         switch((memzone>>1)&0x3)
         {
            case 0:
              df_select = MEM_DF0;
              break;
            case 1:
              df_select = MEM_DF1;
              break;
            case 2:
              df_select = MEM_DF2;
              break;
            case 3:
              df_select = MEM_DF3;
              break;
            default:
              break;
         }
      #endif
   #endif
#endif
}



//!
//! @brief This function physically selects the current addressed memory
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param  none
//!
//! @return none
//!/
static void df_chipselect_current(void)
{
   Df_desel_all();
#ifndef AVRGCC

   #if (DF_NB_MEM == 1)
      Df_select_df(0,DF_SELECT_MEM);
   #else
      #if (DF_NB_MEM == 2)
         if (df_select == MEM_DF0)
           Df_select_df(0,DF_SELECT_MEM);
         else
           Df_select_df(1,DF_SELECT_MEM);
      #else
         switch (df_select)
         {
         case MEM_DF0:
           Df_select_df(0,DF_SELECT_MEM);
           break;
         case MEM_DF1:
           Df_select_df(1,DF_SELECT_MEM);
           break;
         case MEM_DF2:
           Df_select_df(2,DF_SELECT_MEM);
           break;
         default:
           Df_select_df(3,DF_SELECT_MEM);
           break;
         }
      #endif
   #endif

#else // FOR AVRGCC...

   #if (DF_NB_MEM == 1)
      DF_CS_PORT &= (U8)(~(1<<DF_CS0));
   #else
      #if (DF_NB_MEM == 2)
         if (df_select == MEM_DF0)
           DF_CS_PORT &= (U8)(~(1<<DF_CS0));
         else
           DF_CS_PORT &= (U8)(~(1<<DF_CS1));
      #else
         switch (df_select)
         {
         case MEM_DF0:
           DF_CS_PORT &= (U8)(~(1<<DF_CS0));
           break;
         case MEM_DF1:
           DF_CS_PORT &= (U8)(~(1<<DF_CS1));
           break;
         case MEM_DF2:
           DF_CS_PORT &= (U8)(~(1<<DF_CS2));
           break;
         default:
           DF_CS_PORT &= (U8)(~(1<<DF_CS3));
           break;
         }
      #endif
   #endif

#endif
}


//!
//! @brief This function translates the logical sector address to the physical byte address (1 logical sector = 512 bytes)
//!        In function of the memory configuration (number 1x/2x/4x, pages 512b/1024b) :
//!
//!   MEMORIES WITH PAGES OF 512 BYTES :
//!   ==================================
//!   Consider the logical sector address as "xx..xxba", where 'b' and 'a' are the two last bits, and "xx..xx" an undefined number of more significant bits
//!      - If 1 memory is used, this logical sector address directly matches with the physical sector address
//!        So the physical sector address is "xx..xxba"
//!      - If 2 memories are used, the bit 'a' indicates the memory concerned, and the rest of the address indicates the physical address
//!        So the physical sector address is "xx...xxb"
//!      - If 4 memories are used, the bits 'ba' indicates the memory concerned, and the rest of the address indicates the physical address
//!        So the physical sector address is "xx....xx"
//!
//!   MEMORIES WITH PAGES OF 1024 BYTES :
//!   ==================================
//!   Consider the logical sector address as "xx..xxcba", where 'c', 'b' and 'a' are the three last bits, and "xx..xx" an undefined number of more significant bits
//!      - If 1 memory is used, this logical sector address directly matches with the physical sector address
//!        So the physical sector address is "xx..xxcba"
//!      - If 2 memories are used, the bit 'b' indicates the memory concerned, and the rest of the address indicates the physical address
//!        So the physical sector address is "xx...xxca"
//!      - If 4 memories are used, the bits 'cb' indicates the memory concerned, and the rest of the address indicates the physical address
//!        So the physical sector address is "xx....xxa"
//!
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param  log_sect_addr     logical sector address
//!
//! @return U32               physical byte address
//!/
static U32 df_translate_addr(Uint32 log_sect_addr)
{
#if (DF_NB_MEM == 1)
   return (log_sect_addr << 9);  // this case if only one memory...
#else
   #if (DF_NB_MEM == 2)
      #if (DF_PAGE_SIZE == 512)
         return ((log_sect_addr&0xFFFFFFFE) << 8);
      #else
         return (((log_sect_addr&0xFFFFFFFC) << 8) | ((log_sect_addr&0x00000001) << 9));
      #endif
   #else
      #if (DF_PAGE_SIZE == 512)
         return ((log_sect_addr&0xFFFFFFFC) << 7);
      #else
         return (((log_sect_addr&0xFFFFFFF8) << 7) | ((log_sect_addr&0x00000001) << 9));
      #endif
   #endif
#endif
}



//!
//! @brief This function performs a memory check on all DF.
//!
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return bit
//!   The memory is ready     -> OK
//!   The memory check failed -> KO
//!/
bit df_mem_check (void)
{
   //# DF memory check.
   for(df_select=0; df_select<DF_NB_MEM; df_select++)
   {
      df_chipselect_current();
      Spi_write_data(DF_RD_STATUS); /* Send the read status register cmd
                                       + 1st step to clear the SPIF bit */
      Spi_write_dummy();            /* dummy write that:
                                    (.) finalize the clear of the SPIF bit (access to SPDR)
                                    (.) get status register
                                    (.) does the 1st step to clear the SPIF bit  */
      /* Following Spi_read_data() finalize the clear of SPIF by accessing SPDR. */
      // Check the DF density.
      if ((Spi_read_data() & DF_MSK_DENSITY) != DF_DENSITY)
      {   // Unexpected value.
        Df_desel_all();
        return (KO);
      }
      Df_desel_all();
   }

   return OK;
}



//!
//! @brief This function waits until the DataFlash is not busy.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param  None
//!
//! @return None
//!/
static void df_wait_busy (void)
{
  // Read the status register until the DataFlash is not busy.
  df_chipselect_current();
  Spi_write_data(DF_RD_STATUS); /* Send the read status register cmd
                                   + 1st step to clear the SPIF bit */
  Spi_write_dummy();            /* dummy write that:
                                    (.) finalize the clear of the SPIF bit (access to SPDR)
                                    (.) get status register
                                    (.) does the 1st step to clear the SPIF bit */
  // Following Spi_read_data() finalize the clear of SPIF by accessing SPDR
  while ((Spi_read_data() & DF_MSK_BIT_BUSY) == DF_MEM_BUSY)
  {
    Spi_write_dummy();           /* dummy write to get new status
                                   + 1st step to clear the SPIF bit */
  }
  Df_desel_all();                /* unselect memory to leave STATUS request mode */
  Spi_ack_write();               /* Final step to clear the SPIF bit. */
}



//!
//! @brief This function opens a DF memory in read mode at a given sector address.
//!
//! NOTE: Address may not be synchronized on the beginning of a page (depending on the DF page size).
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param  pos   Logical sector address
//!
//! @return bit
//!   The open succeeded      -> OK
//!/
bit df_read_open (Uint32 pos)
{
  // Set the global memory ptr at a Byte address.
  gl_ptr_mem = df_translate_addr(pos);

  // Select the DF that memory "pos" points to (the "df_select" variable will be updated)
  df_chipselect_memzone(LSB0(pos));

  // If the DF memory is busy, wait until it's not.
  if (is_df_busy(df_select))
  {
    df_release_busy(df_select);
    df_wait_busy();                              /* wait end of programming */
  }

  // Physically assert the selected dataflash
  df_chipselect_current();

  //#
  //# Initiate a page read at a given sector address.
  //#
  // Send read main command, + first step to clear the SPIF bit
  Spi_write_data(DF_RD_MAIN);
  // Final step to clear the SPIF bit will be done on the next write

  // Send the three address Bytes made of:
  //  (.) the page-address(first xbits),
  //  (.) the Byte-address within the page(last ybits).
  // (x and y depending on the DF type).
  // NOTE: the bits of gl_ptr_mem above the 24bits are not useful for the local
  // DF addressing. They are used for DF discrimination when there are several
  // DFs.
  Spi_write_data((MSB1(gl_ptr_mem) << DF_SHFT_B1) | (MSB2(gl_ptr_mem) >> DF_SHFT_B2));
  Spi_write_data(((MSB2(gl_ptr_mem) & ~DF_PAGE_MASK) << DF_SHFT_B1) | (MSB2(gl_ptr_mem) & DF_PAGE_MASK));
  Spi_write_data(MSB3(gl_ptr_mem));
  // Final step to clear the SPIF bit will be done on the next write

  // 4 dummy writes for reading delay
  Spi_write_data(0xFF);
  Spi_write_data(0xFF);
  Spi_write_data(0xFF);
  Spi_write_data(0xFF); /* Tx 0xFF, first step to clear the SPIF bit */
  Spi_ack_write();      /* Final step to clear the SPIF bit. */

  return OK;
}


//!
//! @brief This function unselects the current DF memory.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param  None
//!
//! @return None
//!/
void df_read_close (void)
{
  Df_desel_all();   /* Unselect memory */
}



//!
//! @brief This function is optimized and writes nb-sector * 512 Bytes from
//! DataFlash memory to USB controller
//!
//!         DATA FLOW is: DF => USB
//!
//!
//! NOTE:
//!   - First call must be preceded by a call to the df_read_open() function,
//!   - The USB EPIN must have been previously selected,
//!   - USB ping-pong buffers are free,
//!   - As 512 is always a sub-multiple of page size, there is no need to check
//!     page end for each Bytes,
//!   - Interrupts are disabled during transfer to avoid timer interrupt,
//!   - nb_sector always >= 1, cannot be zero.
//!
//! @warning code:?? bytes (function code length)
//!
//! @param nb_sector    number of contiguous sectors to read [IN]
//!
//! @return bit
//!   The read succeeded   -> OK
//!/
bit df_read_sector (Uint16 nb_sector)
{
   U8 i;
   do
   {
      for (i = 8; i != 0; i--)
      {
         Disable_interrupt();    // Global disable.

         // Principle: send any Byte to get a Byte.
         // Spi_write_dummy(): send any Byte + 1st step to clear the SPIF bit.
         // Spi_read_data(): get the Byte + final step to clear the SPIF bit.
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());
         Spi_write_dummy(); Usb_write_byte(Spi_read_data());

         //# Send the USB FIFO IN content to the USB Host.
         Usb_send_in();       // Send the FIFO IN content to the USB Host.

         Enable_interrupt();     // Global interrupt re-enable.

         // Wait until the tx is done so that we may write to the FIFO IN again.
         while(Is_usb_write_enabled()==FALSE);
      }
      gl_ptr_mem += 512;      // increment global address pointer
      nb_sector--;            // 1 more sector read
      #if (DF_NB_MEM == 1)    // end of page ?
         #if (DF_PAGE_SIZE == 512)
            Df_desel_all();
            if (nb_sector != 0)
              df_read_open(gl_ptr_mem>>9);
         #else
            if ((MSB2(gl_ptr_mem) & DF_PAGE_MASK) == 0x00)
            {
               Df_desel_all();
               if (nb_sector != 0)
                 df_read_open(gl_ptr_mem>>9);
            }
         #endif
      #endif
   }
   while (nb_sector != 0);

  return OK;   // Read done.
}


//!
//! @brief This function opens a DF memory in write mode at a given sector
//! address.
//!
//! NOTE: If page buffer > 512 bytes, page content is first loaded in buffer to
//! be partially updated by write_byte or write64 functions.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param  pos   Sector address
//!
//! @return bit
//!   The open succeeded      -> OK
//!/
bit df_write_open (Uint32 pos)
{
  // Set the global memory ptr at a Byte address.
  gl_ptr_mem = df_translate_addr(pos);

  // Select the DF that memory "pos" points to
  df_chipselect_memzone(LSB0(pos));

  // If the DF memory is busy, wait until it's not.
  if (is_df_busy(df_select))
  {
    df_release_busy(df_select);
    df_wait_busy();                              /* wait end of programming */
  }

#if DF_PAGE_SIZE > 512
  // Physically assert the selected dataflash
  df_chipselect_current();

  //#
  //# Transfer the current page content in buffer1.
  //#
  // Send Main Mem page to Buffer1 command, + first step to clear the SPIF bit
  Spi_write_data(DF_TF_BUF_1);
  // Final step to clear the SPIF bit will be done on the next write

  // Send the three address Bytes made of:
  //  (.) the page-address(first xbits),
  //  (.) remaining don't care bits(last ybits).
  // (x and y depending on the DF type).
  // NOTE: the bits of gl_ptr_mem above the 24bits are not useful for the local
  // DF addressing. They are used for DF discrimination when there are several
  // DFs.
  Spi_write_data((MSB1(gl_ptr_mem) << DF_SHFT_B1) | (MSB2(gl_ptr_mem) >> DF_SHFT_B2));
  Spi_write_data(MSB2(gl_ptr_mem) << DF_SHFT_B1);
  Spi_write_dummy();       // Remaining don't care bits.
  Spi_ack_write();         // Final step to clear the SPIF bit.

  Df_desel_all();          // Unselect memory to validate the command

  df_wait_busy();               // Wait end of page transfer
#endif

  // Physically assert the selected dataflash
  df_chipselect_current();

  //#
  //# Initiate a page write at a given sector address.
  //#
  // Send Main Memory Page Program Through Buffer1 command,
  // + first step to clear the SPIF bit
  Spi_write_data(DF_PG_BUF_1);
  // Final step to clear the SPIF bit will be done on the next write

  // Send the three address Bytes made of:
  //  (.) the page-address(first xbits),
  //  (.) the Byte-address within the page(last ybits).
  // (x and y depending on the DF type).
  // NOTE: the bits of gl_ptr_mem above the 24bits are not useful for the local
  // DF addressing. They are used for DF discrimination when there are several
  // DFs.
  Spi_write_data((MSB1(gl_ptr_mem) << DF_SHFT_B1) | (MSB2(gl_ptr_mem) >> DF_SHFT_B2));
  Spi_write_data(((MSB2(gl_ptr_mem) & ~DF_PAGE_MASK) << DF_SHFT_B1) | (MSB2(gl_ptr_mem) & DF_PAGE_MASK));
  Spi_write_data(MSB3(gl_ptr_mem));
  Spi_ack_write();         // Final step to clear the SPIF bit.

  return OK;
}


//!
//! @brief This function fills the end of the logical sector (512B) and launch
//! page programming.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param  None
//!
//! @return None
//!/
void df_write_close (void)
{
  //#
  //# While end of logical sector (512B) not reached, zero-fill the remaining
  //# memory Bytes.
  //#
  while ((MSB3(gl_ptr_mem) != 0x00) || ((MSB2(gl_ptr_mem) & 0x01) != 0x00))
  {
    Spi_write_data(0x00);  // (.) Final step to clear the SPIF bit,
                           // (.) Write 0x00
                           // (.) first step to clear the SPIF bit.
    gl_ptr_mem++;
  }
  Spi_ack_write();            // Final step to clear the SPIF bit.

  Df_desel_all();             // Launch page programming (or simply unselect memory
                              // if the while loop was not performed).
  df_set_busy(df_select);     // Current memory is busy
}



//!
//! @brief This function is optimized and writes nb-sector * 512 Bytes from
//! USB controller to DataFlash memory
//!
//!         DATA FLOW is: USB => DF
//!
//!
//! NOTE:
//!   - First call must be preceded by a call to the df_write_open() function,
//!   - As 512 is always a sub-multiple of page size, there is no need to check
//!     page end for each Bytes,
//!   - The USB EPOUT must have been previously selected,
//!   - Interrupts are disabled during transfer to avoid timer interrupt,
//!   - nb_sector always >= 1, cannot be zero.
//!
//! @warning code:?? bytes (function code length)
//!
//! @param nb_sector    number of contiguous sectors to write [IN]
//!
//! @return bit
//!   The write succeeded  -> OK
//!/
bit df_write_sector (Uint16 nb_sector)
{
  Byte i;

   do
   {
    //# Write 8x64b = 512b from the USB FIFO OUT.
    for (i = 8; i != 0; i--)
    {
      // Wait end of rx in USB EPOUT.
      while(Is_usb_read_enabled()==FALSE);

      Disable_interrupt();    // Global disable.

      // SPI write principle: send a Byte then clear the SPIF flag.
      // Spi_write_data(Usb_read_byte()): (.) Final step to clear the SPIF bit,
      //                                  (.) send a Byte read from USB,
      //                                  (.) 1st step to clear the SPIF bit.
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_write_data(Usb_read_byte());
      Spi_ack_write();        // Final step to clear the SPIF bit.

      Usb_ack_receive_out();  // USB EPOUT read acknowledgement.

      Enable_interrupt();     // Global re-enable.
    } // for (i = 8; i != 0; i--)

      gl_ptr_mem += 512;        // Update the memory pointer.
      nb_sector--;              // 1 more sector written

      //# Launch page programming if end of page.
      //#
      #if DF_PAGE_SIZE > 512
         // Check if end of 1024b page.
         if ((MSB2(gl_ptr_mem) & DF_PAGE_MASK) == 0x00)
         {
            Df_desel_all();         // Launch page programming
            df_set_busy(df_select);     // memory is busy
            #if (DF_NB_MEM == 1)
               if (nb_sector != 0)
                 df_write_open(gl_ptr_mem>>9);
            #endif
         }
      #else
         // Always end of page.
         Df_desel_all();           // Launch page programming
         df_set_busy(df_select);     // memory is busy
         #if (DF_NB_MEM == 1)
            if (nb_sector != 0)
              df_write_open(gl_ptr_mem>>9);
         #endif
      #endif
   }
   while (nb_sector != 0);

  return OK;                  // Write done
}



//! @brief This function read one DF sector and load it into a ram buffer
//!
//!         DATA FLOW is: DF => RAM
//!
//!
//! NOTE:
//!   - First call must be preceded by a call to the df_read_open() function,
//!
//! @param *ram         pointer to ram buffer
//!
//! @return bit
//!   The read succeeded   -> OK
//!/
bit df_read_sector_2_ram(U8 *ram)
{
   U16 i;
   for(i=0;i<DF_SECTOR_SIZE;i++)
   {
      Spi_write_dummy();
      *ram=Spi_read_data();
      ram++;
   }
   gl_ptr_mem += 512;     // Update the memory pointer.
   return OK;
}

//! @brief This function write one DF sector from a ram buffer
//!
//!         DATA FLOW is: RAM => DF
//!
//!
//! NOTE:
//!   - First call must be preceded by a call to the df_write_open() function,
//!
//! @param *ram         pointer to ram buffer
//!
//! @return bit
//!   The read succeeded   -> OK
//!
bit df_write_sector_from_ram(U8 *ram)
{
   U16 i;
   for(i=0;i<DF_SECTOR_SIZE;i++)
   {
      Spi_write_data(*ram);
      *ram++;
   }
   Spi_ack_write();        // Final step to clear the SPIF bit.
   gl_ptr_mem += 512;      // Update the memory pointer.
   return OK;
}



/*F**************************************************************************
* NAME: df_format
*----------------------------------------------------------------------------
* PARAMS:
*
* return:
*   Address of the format parameter structure in code
*----------------------------------------------------------------------------
* PURPOSE:
*   This function is called by the fat_format function and returns a pointer
*   to a table containing the format parameters.
*----------------------------------------------------------------------------
* EXAMPLE:
*----------------------------------------------------------------------------
* NOTE:
*   DF FORMAT PARAMETERS
*   CAPACITY  LBAs      CYL   HDs   S/T   CLUSTs  S/C   S/F   FAT   HID
*   4MB        8160     255   4     8             8                 15
*   8MB       16320     510   4     8             8     12    12    15
*   16MB      32640     510   4     16    4080    8     12    12    15
*   32MB      65280     510   8     16    8160    8     12    16    15
*----------------------------------------------------------------------------
* REQUIREMENTS:
*****************************************************************************/
s_format * df_format (void)
{

  /* -- DF Type Selection -- */
  switch (DF_DISK_SIZE)
  {
    case DF_SIZE_4MB:
         return (s_format*)&df_tab_format[DF_4MB];
    break;
    case DF_SIZE_8MB:
         return (s_format*)&df_tab_format[DF_8MB];
    break;
    case DF_SIZE_16MB:
         return (s_format*)&df_tab_format[DF_16MB];
    break;
    case DF_SIZE_32MB:
         return (s_format*)&df_tab_format[DF_32MB];
    break;
    default:
    break;
  }
  return(NULL);
}

