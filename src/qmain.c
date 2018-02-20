/*
 ============================================================================
 Name        : main.c
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
 * CONSTANTS
 *------------------------------------------------------------------------------
 */


/*
 *------------------------------------------------------------------------------
 * TYPE DEFINITIONS
 *------------------------------------------------------------------------------
 */


/*
 *------------------------------------------------------------------------------
 * PRIVATE PROTOTYPES
 *------------------------------------------------------------------------------
 */
int InitSystem(void);

/*
 *------------------------------------------------------------------------------
 * STRUCTURES
 *------------------------------------------------------------------------------
 */


/*
 *------------------------------------------------------------------------------
 * EXTERN VARIABLES
 *------------------------------------------------------------------------------
 */
extern unsigned char Tx_spi[SPIDEV_BYTES_NUM];
extern unsigned char RX_spi[SPIDEV_BYTES_NUM];


/*
 *------------------------------------------------------------------------------
 * MAIN FUNCTION
 *------------------------------------------------------------------------------
 */
int main(void)
{
    int MenuSystem;
    int lIndex = NUM_0;

    //Initialize local variable
    lIndex = NUM_0;

    //SPI INITIALIZE
    memset(Tx_spi, 0, sizeof(Tx_spi));
    memset(RX_spi, 0, sizeof(RX_spi));
    Tx_spi[0] = 0x56;
    Tx_spi[1] = 0x00;

    if (SPI_DEV0_init(SPIDEV_BYTES_NUM, SPIDEV1_BUS_SPEED_HZ, SPI_SS_LOW,
                      SPIDEV_DELAY_US, SPIDEV_DATA_BITS_NUM,
                      SPI_MODE1) == NEG_1)
    {
        printf("(Main)spidev1.0 initialization failed\r\n");
    }
    else
    {
        printf("(Main)spidev1.0 initialized - READY\r\n");
    }

#ifdef SPI_DBG
    while (1)

    {
        if (SPIDEV1_transfer(Tx_spi, RX_spi, NO_OF_BYTES) == NUM_0)
            printf("(Main)spidev1.0: Transaction Complete\r\n");

        else
            printf("(Main)spidev1.0: Transaction Failed\r\n");

        usleep(50000);
        SPIDEV1_single_transfer(0x22);
        printf("%s\n", RX_spi);
        printf("%d\r\n", ++lIndex);

#endif

    /* Initialize local variable */
    MenuSystem = MIN_INT;

    /* Call to the init function */
    MenuSystem = InitSystem();

    if (NUM_1 == MenuSystem)
    {
            (void)Print_LOG();
    }
    else
    {
        /* do nothing */
    }
    }
    return NUM_1;
}


/*
 *------------------------------------------------------------------------------
 * FUNCTIONS
 *------------------------------------------------------------------------------
 */

/*
 * ------------------------------------------------------------------------------
 *
 *  \par Overview:
 *  The function...
 *
 *  \return
 *
 * ------------------------------------------------------------------------------
 */
int InitSystem(void)
{
    return NUM_1;
} /* end InitSystem */
