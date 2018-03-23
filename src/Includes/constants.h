/*
 ===================================================================================================
 Name        : constants.h
 Author      : Juan Ignacio Bueno Gallego
 Version     : 1.0
 Created on  : 8 February , 2018
 Description : HEADER - Constants for the SANA data acquisition program.
 ===================================================================================================
 */

#ifndef INCLUDES_CONSTANTS_H_
#define INCLUDES_CONSTANTS_H_

/*
 *------------------------------------------------------------------------------
 * INCLUDE FILES
 *------------------------------------------------------------------------------
 */
#include <include.h>


/*
 *------------------------------------------------------------------------------
 * TYPE DEFINITIONS
 *------------------------------------------------------------------------------
 */
#ifndef NULL
#define NULL (void *)0
#endif


/*
 *------------------------------------------------------------------------------
 * CONSTANTS
 *------------------------------------------------------------------------------
 */

/*
 *=====================================================
 * Unit Test constants
 *=====================================================
 */
#define UNITTEST				1
#define SPICHECK				1


/*
 *=====================================================
 * Numeric constants
 *=====================================================
 */
#define NUM_0                   0
#define NUM_1                   1
#define NUM_2                   2
#define NUM_3                   3
#define NUM_4                   4
#define NUM_5                   5
#define NUM_6                   6
#define NUM_7                   7
#define NUM_8                   8
#define NUM_9                   9
#define NUM_10					10
#define NUM_100					100

#define NEG_1				    -1
#define NEG_2				    -2
#define NEG_3				    -3
#define NEG_4				    -4
#define NEG_5				    -5
#define NEG_6				    -6
#define NEG_7				    -7
#define NEG_8				    -8
#define NEG_9				    -9

#define ADS_ID					1


/*
 *=====================================================
 * Numeric constants
 *=====================================================
 */
#define MAX_SCRLINE             200
#define MAX_PATHLINE            40
#define MAX_VERSIONLINE         16
#define MAX_TIMELINE            16
#define MAX_FILENAME			36
#define MAX_FILETRACENAME    	50
#define MAX_FILESIZE			50000
#define END_STRING				1

// Latency values
#define SYNC_TIME				50000


/*
 *=====================================================
 * Trace definitions
 *=====================================================
 */
#define TRACE_FILE              "%s//[%s]Tace_SANA.txt"
#define MAX_INT                 (int)0xFFFF


/*
 *=====================================================
 * Type bonders definitions
 *=====================================================
 */
#define MIN_INT                 (int)0
#define MAX_INT                 (int)0xFFFF

#define INIT_POS				0


/*
 *=====================================================
 * SPI definitions
 *=====================================================
 */
// SPI Generic Definitions
#define SPIDEV_BYTES_NUM                 8
#define RDATAC_BYTES_NUM                 27
#define SPIDEV_DATA_BITS_NUM             8
#define SPIDEV_DELAY_US                  0
#define SPI_SS_HIGH                      1
#define SPI_SS_LOW                       0
#define SPI_ONE_BYTE                     1

//SPI No. of bytes per transaction
#define NO_OF_BYTES                      2

// SPI BBB Definitions specific to spidev
#define SPIDEV0_PATH                     "/dev/spidev0.1"
#define SPIDEV0_BUS_SPEED_HZ             4000000
#define SPIDEV1_PATH                     "/dev/spidev1.0"
#define SPIDEV1_BUS_SPEED_HZ             4000000


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

//Constants for Individual Channel Settings
#define ICS_TEST_SIGNAL		0x05		/* Test signal as Channel input. */
#define ICS_CI_BIAS_DRN		0x07		/* BIAS_DRN (negative electrode is the driver) */
#define ICS_SRB2_OPEN		0x00		/* SRB2 connection open */
#define ICS_SRB2_CLOSE		0x08		/* SRB2 connection close */
#define ICS_NOT_PGAGAIN		0x70		/* Do not use PGA gain */

//Constants for Bias Drive Positive Derivation Register
#define SENSP_IN1P 			0x01		/* Enable Route channel 1 positive signal into BIAS channel*/
#define SENSP_IN2P 			0x02		/* Enable Route channel 2 positive signal into BIAS channel */
#define SENSP_IN3P 			0x04		/* Enable Route channel 3 positive signal into BIAS channel */
#define SENSP_IN4P 			0x08		/* Enable Route channel 4 positive signal into BIAS channel */
#define SENSP_IN5P 			0x10		/* Enable Route channel 5 positive signal into BIAS channel */
#define SENSP_IN6P 			0x20		/* Enable Route channel 6 positive signal into BIAS channel */
#define SENSP_IN7P 			0x40		/* Enable Route channel 7 positive signal into BIAS channel */
#define SENSP_IN8P 			0x80		/* Enable Route channel 8 positive signal into BIAS channel */

//Constants for CONFIG3: Configuration Register 3
#define CONFIG3_BIAS_STAT   	0x01	/* BIAS lead-off status not connected. */
#define CONFIG3_BIAS_LOFF_SENS  0x02	/* BIAS sense function enabled. */
#define CONFIG3_PD_BIAS		   	0x04 	/* BIAS buffer power enabled. */
#define CONFIG3_BIASREF_INT   	0x08    /* BIASREF signal (AVDD + AVSS) / 2 internally */
#define CONFIG3_BIAS_MEAS   	0x10	/* This bit enables BIAS measurement. */
#define CONFIG3_RESERVED	   	0x60	/* bits 6 and 7 always to 1. */
#define CONFIG3_PD_REFBUF   	0x80	/* Enable the power-down reference buffer. */

/* Wait cycles */
#define ADS1299_4_tCLK			5
#define ADS1299_18_tCLK			20

/* Array positions */
#define COMMAND_POS  			0
#define ADDRESS_POS  			0
#define TRANSFER_POS			1

//Returns values
#define ERROR_RET			-1
#define NO_ERROR_RET        0


/*
 *=====================================================
 * Queues definitions
 *=====================================================
 */
#define KEY_QUEUE 			5
#define KEY_PATHNAME 		"/bin/ls"


/*
 *=====================================================
 * Type File Permissions
 *=====================================================
 */
//#define                 S_IRWXU     (S_IRUSR | S_IWUSR | S_IXUSR)
//#define                 S_IRUSR     0000400 /* read permission, owner */
//#define                 S_IWUSR     0000200 /* write permission, owner */
//#define                 S_IXUSR     0000100/* execute/search permission, owner */
//#define                 S_IRWXG     (S_IRGRP | S_IWGRP | S_IXGRP)
//#define                 S_IRGRP     0000040 /* read permission, group */
//#define                 S_IWGRP     0000020 /* write permission, grougroup */
//#define                 S_IXGRP     0000010/* execute/search permission, group */
//#define                 S_IRWXO     (S_IROTH | S_IWOTH | S_IXOTH)
//#define                 S_IROTH     0000004 /* read permission, other */
//#define                 S_IWOTH     0000002 /* write permission, other */
//#define                 S_IXOTH     0000001/* execute/search permission, other */


/*
 *------------------------------------------------------------------------------
 * VARIABLES
 *------------------------------------------------------------------------------
 */


/*
 *------------------------------------------------------------------------------
 * FUNCTIONS
 *------------------------------------------------------------------------------
 */

#endif /* INCLUDES_CONSTANTS_H_ */
