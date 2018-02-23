/*
 ============================================================================
 Name        : das1299.c
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

/*
 *------------------------------------------------------------------------------
 * INCLUDE FILES
 *------------------------------------------------------------------------------
 */
#include <include.h>


/*
 *------------------------------------------------------------------------------
 * EXTERNAL VARIABLES
 *------------------------------------------------------------------------------
 */
extern unsigned char Tx_spi[SPIDEV_BYTES_NUM];
extern unsigned char RX_spi[SPIDEV_BYTES_NUM];


/*
 *------------------------------------------------------------------------------
 * FUNCTIONS
 *------------------------------------------------------------------------------
 */


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function print the Log in a file.
 *
 *  \return
 *	FALSE if the log has not been logged. TRUE if the message has been logged.
 * -----------------------------------------------------------------------------
 */
BOOL Init_ads1299 (void)
{
    BOOL           lbResult;

    /* Initialize output data */
    lbResult     = TRUE;


    //=====================================================
    // Send RESET command to default all registers
    //=====================================================
    SendByte_ads1299(ADS1299_RESET);

    // wait 18 tCLK cycles to decode and execute the command.
    usleep(20);


    //=====================================================
    //Exit Read Data Continuous mode to communicate with ADS.
    //=====================================================
    SendByte_ads1299(ADS1299_SDATAC);

    // wait 4 tCLK cycles to decode and execute the command.
    usleep(5);

    return lbResult;
}

/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function send a byte to the device ADS1299.
 *
 *  \return
 *	FALSE if the byte has not been send. TRUE if the message has been send.
 * -----------------------------------------------------------------------------
 */
BOOL SendByte_ads1299 (unsigned char Transfer)
{
    BOOL           lbResult;

    /* Initialize output data */
    lbResult     = TRUE;

    //Reset values of the transfer.
    memset(Tx_spi, 0, sizeof(Tx_spi));
    memset(RX_spi, 0, sizeof(RX_spi));

    Tx_spi[0] = Transfer;

    if (SPIDEV1_transfer(Tx_spi, RX_spi, NO_OF_BYTES) == ERROR_RET)
    {
        perror("ERROR to reset the ads1299.\n");
        lbResult = FALSE;
    }

    return lbResult;
}


