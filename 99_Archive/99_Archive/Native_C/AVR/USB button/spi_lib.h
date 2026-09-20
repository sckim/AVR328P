/**
 * @file spi_lib.h,v
 *
 * Copyright (c) 2004 Atmel.
 *
 * Please read file license.txt for copyright notice.
 *
 * @brief This file containsSPI lib header file.
 *
 * @version 1.5 at90usb162-2enum-mouse_ms-1_0_1
 *
 * @todo
 * @bug
 */

#ifndef _SPI_LIB_H_
#define _SPI_LIB_H_

/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "spi_drv.h"

/*_____ C O N F I G U R A T I O N _________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/


//#ifndef SPI_CONFIG
//#error You must enter SPI_CONFIG in config.h
//#define SPI_CONFIG
//#endif

/**
 * @brief This enumeration allows to define a MASTER or SLAVE configuration
 **/
typedef enum {SPI_MASTER, SPI_SLAVE} spi_cf_t;

/*_____ D E C L A R A T I O N ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ P R O T O T Y P E S ____________________________________________________________*/

/**
 * @brief This function configures the SPI controller:
 * -# MASTER or SLAVE
 * -# bit timing
 * -# enable the controller
 *
 * @param configuration of the node (MASTER or SLAVE).
 * @param configuration of mode (SPI_MASTER_MODE_0...SPI_MASTER_MODE_3 or SPI_SLAVE_MODE_0...SPI_SLAVE_MODE_3).
 *
 * @return status of the init:
 * -# TRUE
 * -# FALSE
 *
 * @pre before calling this function some declaration must be define in config.h:\n
 * - SPI_CONFIG select the prescaler, CPHA leading, CPOL LOW, LSB first.
 */
bit     spi_init        (spi_cf_t config);

/**
 * @brief This function sends a byte on the SPI
 *
 * @param character to send on the SPI.
 *
 * @return character sent
 *
 */
char    spi_putchar        (char uc_wr_byte);

/**
 * @brief This function checks if a bytes has been received on the SPI
 *
 * @return TRUE if byte received
 *
 */
bit     spi_test_hit       (void);

/**
 * @brief This function reads a byte on the SPI
 *
 * @return character read
 *
 */
char    spi_getchar        (void);

//***************************************************************************
//  @fn SPI_Transmit_Master
//!
//! SPI Make the transmission possible
//!
//! @warning See SPI section in datasheet
//!
//! @param (char cData)
//!
//! @return nothing.
//!
//***************************************************************************
void SPI_Transmit_Master(char cData);

#endif /* _SPI_LIB_H_ */
