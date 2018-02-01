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
 * INCLUDE FILES
 *------------------------------------------------------------------------------
 */

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
#define ADS1299_CH1SET      0x05		/* CHnSET: Individual Channel Settings (n = 1 to 8) - Type: R/W */
#define ADS1299_CH2SET      0x06		/* ID Control register - Type: R*/
#define ADS1299_CH3SET      0x07		/* ID Control register - Type: R*/
#define ADS1299_CH4SET      0x08		/* ID Control register - Type: R*/
#define ADS1299_CH5SET      0x09		/* ID Control register - Type: R*/
#define ADS1299_CH6SET      0x0A		/* ID Control register - Type: R*/
#define ADS1299_CH7SET      0x0B		/* ID Control register - Type: R*/
#define ADS1299_CH8SET      0x0C		/* ID Control register - Type: R*/
#define ADS1299_BIAS_SENSP  0x0D		/* ID Control register - Type: R*/
#define ADS1299_BIAS_SENSN  0x0E		/* ID Control register - Type: R*/
#define ADS1299_LOFF_SENSP  0x0F		/* ID Control register - Type: R*/
#define ADS1299_LOFF_SENSN  0x10		/* ID Control register - Type: R*/
#define ADS1299_LOFF_FLIP   0x11		/* ID Control register - Type: R*/
#define ADS1299_LOFF_STATP  0x12		/* ID Control register - Type: R*/
#define ADS1299_LOFF_STATN  0x13		/* ID Control register - Type: R*/
#define ADS1299_GPIO        0x14		/* ID Control register - Type: R*/
#define ADS1299_MISC1       0x15		/* ID Control register - Type: R*/
#define ADS1299_MISC2       0x16		/* ID Control register - Type: R*/
#define ADS1299_CONFIG4     0x17		/* ID Control register - Type: R*/

/*
 *------------------------------------------------------------------------------
 * CONSTANTS
 *------------------------------------------------------------------------------
 */


/*
 *------------------------------------------------------------------------------
 * TYPE DEFINITIONS
 *------------------------------------------------------------------------------
 */
#ifndef BOOL
typedef enum BOOL {FALSE = 0, TRUE = 1} BOOL;
#endif


#endif /* INCLUDES_TYPES_H_ */
