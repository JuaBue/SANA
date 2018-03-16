/*
 ============================================================================
 Name        : das1299.c
 Author      : Juan Ignacio Bueno Gallego
 Version     : 1.0
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
    BOOL    lbResult;
    int 	lwConfigReg;

    /* Initialize output data */
    lbResult    = TRUE;
    lwConfigReg = NUM_0;

    //=====================================================
    // Send RESET command to default all registers
    //=====================================================
    SendCommad_ads1299(ADS1299_RESET);

    // wait 18 tCLK cycles to decode and execute the command.
    usleep(ADS1299_18_tCLK);


    //=====================================================
    //Exit Read Data Continuous mode to communicate with ADS.
    //=====================================================
    SendCommad_ads1299(ADS1299_SDATAC);

    // wait 4 tCLK cycles to decode and execute the command.
    usleep(ADS1299_4_tCLK);

    //=====================================================
    //ICS. Individual Channel Settings for test_signal
    //=====================================================
    // Config the Individual Channel Settings Register with:
    // ICS_NOT_PGAGAIN = Do not use PGA gain
    // ICS_SRB2_OPEN   = SRB2 connection open.
    // ICS_TEST_SIGNAL = Test signal as Channel input.
    lwConfigReg = (ICS_NOT_PGAGAIN | ICS_SRB2_OPEN | ICS_TEST_SIGNAL);

    SendByte_ads1299(ADS1299_CH1SET, lwConfigReg);
    SendByte_ads1299(ADS1299_CH2SET, lwConfigReg);
    SendByte_ads1299(ADS1299_CH3SET, lwConfigReg);
    SendByte_ads1299(ADS1299_CH4SET, lwConfigReg);
    SendByte_ads1299(ADS1299_CH5SET, lwConfigReg);
    SendByte_ads1299(ADS1299_CH6SET, lwConfigReg);
    SendByte_ads1299(ADS1299_CH7SET, lwConfigReg);
    SendByte_ads1299(ADS1299_CH8SET, lwConfigReg);

    usleep(ADS1299_4_tCLK);

//    //=====================================================
//    //ICS. Individual Channel Settings for signal_positiv
//    //=====================================================
//    // Config the Individual Channel Settings Register with:
//    // ICS_NOT_PGAGAIN = Do not use PGA gain
//    // ICS_SRB2_OPEN   = SRB2 connection open.
//    // ICS_CI_BIAS_DRN = BIAS_DRN (negative electrode is the driver)
//    lwConfigReg = (ICS_NOT_PGAGAIN | ICS_SRB2_OPEN | ICS_CI_BIAS_DRN);
//
//    SendByte_ads1299(ADS1299_CH1SET, lwConfigReg);
//    SendByte_ads1299(ADS1299_CH2SET, lwConfigReg);
//    SendByte_ads1299(ADS1299_CH3SET, lwConfigReg);
//    SendByte_ads1299(ADS1299_CH4SET, lwConfigReg);
//    SendByte_ads1299(ADS1299_CH5SET, lwConfigReg);
//    SendByte_ads1299(ADS1299_CH6SET, lwConfigReg);
//    SendByte_ads1299(ADS1299_CH7SET, lwConfigReg);
//    SendByte_ads1299(ADS1299_CH8SET, lwConfigReg);
//
//    usleep(5);

    //=====================================================
    //BIAS_SENSP: Bias Drive Positive Derivation Register
    //=====================================================
    // Config the Individual Channel Settings Register with:
    // SENSP_IN1P : SENSP_IN8P = Enable Route channel positive
    // 				signal into BIAS channel
    lwConfigReg = (SENSP_IN1P | SENSP_IN2P | SENSP_IN3P | SENSP_IN4P |
    		SENSP_IN5P | SENSP_IN6P | SENSP_IN7P | SENSP_IN8P);

    SendByte_ads1299(ADS1299_BIAS_SENSN, lwConfigReg);

    usleep(ADS1299_4_tCLK);

    //=====================================================
    //CONFIG3: Bias Drive Positive Derivation Register
    //=====================================================
    // Config the Individual Channel Settings Register with:
    // CONFIG3_BIAS_STAT      = BIAS lead-off status not connected.
    // CONFIG3_BIAS_LOFF_SENS = BIAS sense function enabled.
    // CONFIG3_PD_BIAS        = BIAS buffer power enabled.
    // CONFIG3_BIASREF_INT    = BIASREF signal (AVDD + AVSS) / 2 internally
    // CONFIG3_BIAS_MEAS      = This bit enables BIAS measurement.
    // CONFIG3_PD_REFBUF      = Enable the power-down reference buffer.

    lwConfigReg = (CONFIG3_BIAS_STAT | CONFIG3_BIAS_LOFF_SENS | CONFIG3_PD_BIAS
    		| CONFIG3_BIASREF_INT | CONFIG3_BIAS_MEAS | CONFIG3_RESERVED |
			CONFIG3_PD_REFBUF);

    SendByte_ads1299(ADS1299_CONFIG3, lwConfigReg);

    usleep(ADS1299_4_tCLK);

    //=====================================================
    // Send RDATAC to enable Read Data Continuous mode.
    //=====================================================
    SendCommad_ads1299(ADS1299_RDATAC);

    // wait 4 tCLK cycles to decode and execute the command.
    usleep(ADS1299_4_tCLK);

    //=====================================================
    // Send START to Start and restart (synchronize) conversions.
    //=====================================================
    SendCommad_ads1299(ADS1299_START);

    // wait 4 tCLK cycles to decode and execute the command.
    usleep(ADS1299_4_tCLK);

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
BOOL SendCommad_ads1299 (unsigned char Command)
{
    BOOL           lbResult;

    /* Initialize output data */
    lbResult     = TRUE;

    //Reset values of the transfer.
    memset(Tx_spi, NUM_0, sizeof(Tx_spi));
    memset(RX_spi, NUM_0, sizeof(RX_spi));

    Tx_spi[COMMAND_POS] = Command;

    if (SPIDEV1_transfer(Tx_spi, RX_spi, NO_OF_BYTES) == ERROR_RET)
    {
        perror("ERROR to reset the ads1299.\n");
        lbResult = FALSE;
        /* TODO: tracear un error */
    }

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
BOOL SendByte_ads1299 (unsigned char Address, unsigned char Transfer)
{
    BOOL           lbResult;

    /* Initialize output data */
    lbResult     = TRUE;

    //Reset values of the transfer.
    memset(Tx_spi, NUM_0, sizeof(Tx_spi));
    memset(RX_spi, NUM_0, sizeof(RX_spi));

    Tx_spi[ADDRESS_POS]  = Address;
    Tx_spi[TRANSFER_POS] = Transfer;

    if (ERROR_RET == SPIDEV1_transfer(Tx_spi, RX_spi, NO_OF_BYTES))
    {
        perror("ERROR to reset the ads1299.\n");
        lbResult = FALSE;
        /* TODO: tracear un error */
    }

    return lbResult;
}


