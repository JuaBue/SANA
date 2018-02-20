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
// Enable SPI Debug
#define SPI_DBG

// SPI Generic Definitions
#define SPIDEV_BYTES_NUM                 8
#define SPIDEV_DATA_BITS_NUM             8
#define SPIDEV_DELAY_US                  0
#define SPI_SS_HIGH                      1
#define SPI_SS_LOW                       0
#define SPI_ONE_BYTE                     1

//SPI No. of bytes per transaction
#define NO_OF_BYTES                      2

// SPI BBB Definitions specific to spidev
#define SPIDEV0_PATH                     "/dev/spidev0.1"
#define SPIDEV0_BUS_SPEED_HZ             50000
#define SPIDEV1_PATH                     "/dev/spidev1.0"
#define SPIDEV1_BUS_SPEED_HZ             50000


// SPI Configuration commands.
#define SPI_DATA_MODE    	0x04       	/* CPOL = 0; CPHA = 1 (Datasheet, p8) */
#define SPI_MODE_MASK    	0x0C       	/* mask of CPOL and CPHA  on SPCR */
#define SPI_CLOCK_MASK   	0x03  		/* SPR1 = bit 1, SPR0 = bit 0 on SPCR */
#define SPI_2XCLOCK_MASK 	0x01  		/* SPI2X = bit 0 on SPSR */
#define SPI_CLOCK_DIV_2  	0X04		/* 8MHz SPI SCK */
#define SPI_CLOCK_DIV_4  	0X00		/* 4MHz SPI SCK */
#define SPI_CLOCK_DIV_16 	0x01    	/* 1MHz SPI SCK */

//SPI Command Definition Byte Assignments (Datasheet, p40)
//System commands
#define ADS1299_WAKEUP 	    0x02 		/* Wake-up from standby mode */
#define ADS1299_STANDBY		0x04 		/* Enter Standby mode */
#define ADS1299_RESET      	0x06 		/* Reset the device registers to default */
#define ADS1299_START      	0x08 		/* Start and restart (synchronize) conversions */
#define ADS1299_STOP       	0x0A 		/* Stop conversion */
//Data Read Commands
#define ADS1299_RDATAC     	0x10 		/* Enable Read Data Continuous mode (default mode at power-up) */
#define ADS1299_SDATAC     	0x11 		/* Stop Read Data Continuous mode */
#define ADS1299_RDATA      	0x12 		/* Read data by command; supports multiple read back */


//Register Addresses
#define ADS1299_ID          0x00		/* ID Control register - Type: R */
#define ADS1299_CONFIG1     0x01		/* Configuration 1 register - Type: R/W */
#define ADS1299_CONFIG2     0x02		/* Configuration 2 register - Type: R/W */
#define ADS1299_CONFIG3     0x03		/* Configuration 3 register - Type: R/W */
#define ADS1299_LOFF        0x04		/* LOFF: Lead-Off Control Register - Type: R/W */
#define ADS1299_CH1SET      0x05		/* CH1SET: Individual Channel Settings - Type: R/W */
#define ADS1299_CH2SET      0x06		/* CH2SET: Individual Channel Settings - Type: R/W */
#define ADS1299_CH3SET      0x07		/* CH3SET: Individual Channel Settings - Type: R/W */
#define ADS1299_CH4SET      0x08		/* CH4SET: Individual Channel Settings - Type: R/W */
#define ADS1299_CH5SET      0x09		/* CH5SET: Individual Channel Settings - Type: R/W */
#define ADS1299_CH6SET      0x0A		/* CH6SET: Individual Channel Settings - Type: R/W */
#define ADS1299_CH7SET      0x0B		/* CH7SET: Individual Channel Settings - Type: R/W */
#define ADS1299_CH8SET      0x0C		/* CH8SET: Individual Channel Settings - Type: R/W */
#define ADS1299_BIAS_SENSP  0x0D		/* BIAS_SENSP: Bias Drive Positive Derivation Register - Type: R/W */
#define ADS1299_BIAS_SENSN  0x0E		/* BIAS_SENSN: Bias Drive Negative Derivation Register - Type: R/W */
#define ADS1299_LOFF_SENSP  0x0F		/* LOFF_SENSP: Positive Signal Lead-Off Detection Register - Type: R/W */
#define ADS1299_LOFF_SENSN  0x10		/* LOFF_SENSN: Negative Signal Lead-Off Detection Register - Type: R/W */
#define ADS1299_LOFF_FLIP   0x11		/* LOFF_FLIP: Lead-Off Flip Register - Type: R/W */
#define ADS1299_LOFF_STATP  0x12		/* LOFF_STATP: Lead-Off Positive Signal Status Register - Type: R/W */
#define ADS1299_LOFF_STATN  0x13		/* LOFF_STATN: Lead-Off Negative Signal Status Register - Type: R/W */
#define ADS1299_GPIO        0x14		/* GPIO: General-Purpose I/O Register - Type: R/W */
#define ADS1299_MISC1       0x15		/* MISC1: Miscellaneous 1 Register - Type: R/W */
#define ADS1299_MISC2       0x16		/* MISC2: Miscellaneous 2 Register - Type: R/W */
#define ADS1299_CONFIG4     0x17		/* CONFIG4: Configuration Register 4 - Type: R/W */


//Returns values
#define ERROR_RET			-1
#define NO_ERROR_RET        0


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

#endif /* INCLUDES_TYPES_H_ */
