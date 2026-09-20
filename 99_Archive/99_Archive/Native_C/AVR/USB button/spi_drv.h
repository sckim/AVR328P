//***************************************************************************
//! @file spi_drv.h,v
//!
//! Copyright (c) 2005 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief SPI Low level drivers access.
//!
//! @version 1.3 at90usb162-2enum-mouse_ms-1_0_1
//!
//! @todo
//! @bug
//***************************************************************************

#ifndef _SPI_DRV_H_
#define _SPI_DRV_H_

/*_____ I N C L U D E S  ___________________________*/

#include "config.h"
/*_____ M A C R O S  ___________________________*/

/* SPI CONTROLLER */


#define MSK_SPI_SPIE  0x80
#define MSK_SPI_SPE   0x40
#define MSK_SPI_DORD  0x20
#define MSK_SPI_MSTR  0x10
#define MSK_SPI_CPOL  0x08
#define MSK_SPI_CPHA  0x04
#define MSK_SPI_SPR1  0x02
#define MSK_SPI_SPR0  0x01


#define MSK_SPI_ENABLE_IT	0x80	
#define MSK_SPI_ENABLE		0x40
#define MSK_SPI_MASTER_MODE	0x10
#define MSK_SPI_DOUBLESPEED	0x01

#define MSK_SPI_DIV4        	0x00
#define MSK_SPI_DIV16       	0x01
#define MSK_SPI_DIV64       	0x02
#define MSK_SPI_DIV128      	0x03
#define MSK_SPI_CPHA_LEADING  	0x00
#define MSK_SPI_CPHA_TRAILING 	0x04
#define MSK_SPI_CPOL_HIGH   	0x08
#define MSK_SPI_CPOL_LOW    	0x00
#define MSK_SPI_LSBFIRST    	0x20
#define MSK_SPI_MSBFIRST    	0x00
#define MSK_SPI_CONF  	    	0x2F
#define MSK_SPI_SPIF  	    	0x80
#define MSK_SPI_MODE      	0x0C
#define MSK_MSTR                0x10

/*----- Modes -----*/
#define SPI_MASTER_MODE_0 (Byte)(MSK_MSTR)
#define SPI_MASTER_MODE_1 (Byte)(MSK_MSTR|0x04)
#define SPI_MASTER_MODE_2 (Byte)(MSK_MSTR|0x08)
#define SPI_MASTER_MODE_3 (Byte)(MSK_MSTR|0x0C)

#define SPI_SLAVE_MODE_0  (Byte)0x00
#define SPI_SLAVE_MODE_1  (Byte)0x04
#define SPI_SLAVE_MODE_2  (Byte)0x08
#define SPI_SLAVE_MODE_3  (Byte)0x0C

/*----- Bit rates -----*/
//#define SPI_RATE_0        (Byte)0x00    /* Fper / 2 */
#define SPI_RATE_1        (Byte)0x00    /* Fper / 4 */
//#define SPI_RATE_2        (Byte)0x02    /* Fper / 8 */
#define SPI_RATE_3        (Byte)0x01    /* Fper / 16 */
//#define SPI_RATE_4        (Byte)0x80    /* Fper / 32 */
#define SPI_RATE_5        (Byte)0x02    /* Fper / 64 */
#define SPI_RATE_6        (Byte)0x03    /* Fper / 128 */

/*______  D E F I N I T I O N  ___________________________*/


#define Spi_enable()            (SPCR |=MSK_SPI_ENABLE)
#define Spi_disable()           (SPCR &= ~MSK_SPI_ENABLE)
#define Spi_enable_it()         (SPCR|= MSK_SPI_ENABLE_IT)
#define Spi_disable_it()        (SPCR&=~MSK_SPI_ENABLE_IT)
#define Spi_select_slave_mode() (SPCR&=~MSK_SPI_MASTER_MODE)
#define Spi_select_master_mode() (SPCR|= MSK_SPI_MASTER_MODE)
#define Spi_set_mode(mode)      (SPCR &= ~(MSK_SPI_MASTER_MODE|MSK_SPI_MODE )); (SPCR |= mode);Spi_init_bus()
#define Spi_read_data()         (SPDR)
#define Spi_get_byte()          (SPDR)
#define Spi_write_data(ch)      (SPDR=ch);Spi_wait_spif();
#define Spi_send_byte(ch)       (SPDR=ch);Spi_wait_spif();
#define Spi_wait_spif()         while ((SPSR & MSK_SPI_SPIF) == 0) /* for any SPI_RATE_x */
#define Spi_wait_eor()          while ((SPSR & MSK_SPI_SPIF) == 0) /* wait end of reception */
#define Spi_wait_eot()          while ((SPSR & MSK_SPI_SPIF) == 0) /* wait end of transmission */
#define Spi_eor()               ((SPSR & MSK_SPI_SPIF) == MSK_SPI_SPIF)/* check end of reception */
#define Spi_eot()               ((SPSR & MSK_SPI_SPIF) == MSK_SPI_SPIF)/* check end of transmission */
#define Spi_set_doublespeed()   (SPSR|= MSK_SPI_DOUBLESPEED)
#define Spi_hw_init(conf)       (SPCR&=~MSK_SPI_CONF, SPCR|=conf)
#define Spi_get_colision_status() (SPSR&(1<<WCOL))
#define Spi_get_byte()          (SPDR)
#define Spi_tx_ready()          (SPSR & (1<<SPIF))
#define Spi_rx_ready()		      Spi_tx_ready()
#define Spi_init_bus()           ((DDRB |= (1<<DDB2)|(1<<DDB1)))
#define Spi_disable_ss()
#define Spi_enble_ss()

#define Spi_write_dummy()       (SPDR = 0x00);Spi_wait_spif();
#define Spi_read_dummy()        (0x00 = SPDR)
#define Spi_config_speed(config) (SPCR &= ~(MSK_SPI_SPR1|MSK_SPI_SPR0), (SPCR |= config))/*see bit rates for config*/
//#define Spi_set_rate(rate)      (SPCR &= ~MSK_SPR); (SPCR |= rate);(if (rate == (SPI_RATE_0|SPI_RATE_2|SPI_RATE_4) doublespeed());

#ifndef DUMMY
  #error "DUMMY should be define in config.h as free general purpose IO register"
#endif
#define Spi_ack_read()          (DUMMY = SPSR)
#define Spi_ack_write()         (DUMMY = SPDR)
#define Spi_ack_cmd()           (DUMMY = SPSR)


#endif  /* _SPI_DRV_H_ */

