/**
 * @file spi_lib.c,v
 *
 * Copyright (c) 2004 Atmel.
 *
 * Please read file license.txt for copyright notice.
 *
 * @brief This file provides a minimal funtion set for the SPI
 *
 * @version 1.7 at90usb162-2enum-mouse_ms-1_0_1
 *
 * @todo
 * @bug
 */

/*_____ I N C L U D E S ____________________________________________________*/
#include "config.h"
//#include "lib_mem/spi\spi_lib.h"
#include "spi_lib.h"


/*_____ G L O B A L    D E F I N I T I O N _________________________________*/

/*_____ D E F I N I T I O N ________________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

bit spi_test_hit (void)
{
return Spi_rx_ready();
}


bit spi_init (spi_cf_t config)
{
  Spi_init_bus();
  if(config == SPI_MASTER){Spi_select_master_mode();}
  else                    {Spi_select_slave_mode();}

  Spi_hw_init(SPI_CONFIG);
  Spi_set_doublespeed();/*to delete if wished*/
  Spi_enable();


  return TRUE;
}


char spi_putchar (char ch)
{
Spi_send_byte(ch);
while(!Spi_tx_ready());
return ch;
}



char spi_getchar (void)
{

register char c;

while(!Spi_rx_ready());
c = Spi_get_byte();
return c;
}

void  SPI_Transmit_Master(char cData)
{
  /* Wait for transmission complete */
Spi_wait_eot();
  /* Start new transmission */
Spi_send_byte(cData);

}



