/*
 * types.h
 *
 *  Created on: 29 nov. 2017
 *      Author: juan.bueno
 */

#ifndef INCLUDES_TYPES_H_
#define INCLUDES_TYPES_H_


/*
 *------------------------------------------------------------------------------
 * CONSTANTS
 *------------------------------------------------------------------------------
 */


/*
 *------------------------------------------------------------------------------
 * MAKRO DEFINITIONS
 *------------------------------------------------------------------------------
 */
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

/*
 *------------------------------------------------------------------------------
 * TYPE DEFINITIONS
 *------------------------------------------------------------------------------
 */
#ifndef BOOL
typedef enum BOOL {FALSE = 0, TRUE = 1} BOOL;
#endif

#ifndef NULL
#define NULL (void *)0
#endif

/* Enum SPI Modes*/
typedef enum{
    SPI_MODE0 = 0,
    SPI_MODE1 = 1,
    SPI_MODE2 = 2,
    SPI_MODE3 = 3
}SPI_MODE;

/*SPI device configuration structure*/
typedef struct{
    char*             spi_dev_path;
    int               fd_spi;
    unsigned long     spi_bytes_num;
    unsigned long     spi_bus_speedHZ;
    unsigned char     ss_change;
    unsigned short    spi_delay_us;
    unsigned char     spi_data_bits_No;
    unsigned char     spi_mode;
}SPI_DeviceT, *SPI_DevicePtr;

#define KEY_QUEUE 5

#endif /* INCLUDES_TYPES_H_ */
