/*
 ============================================================================
 Name        : main.c
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
extern unsigned char    Tx_spi[RDATAC_BYTES_NUM];
extern unsigned char    RX_spi[RDATAC_BYTES_NUM];
key_t                   keyqueue;  /* Key for the data queue. */


/*
 *------------------------------------------------------------------------------
 * MAIN FUNCTION
 *------------------------------------------------------------------------------
 */
int main(void)
{
    int                lIndex;        /* Index variable */
	int                msqid; 		  /* Id queue */
	pthread_t          idHilo; 		  /* Id thread */
	pthread_attr_t     tAttributes;   /* Thread attributes */


	struct msgbuf
	{
		long Id_Message;
		unsigned char Data_RX_spi[RDATAC_BYTES_NUM];
	}Set_Data;

    /* Initialize local variable */
	pthread_attr_init (&tAttributes);
	pthread_attr_setdetachstate (&tAttributes, PTHREAD_CREATE_JOINABLE);
	lIndex = NUM_0;
	msqid  = NUM_0;

    /* Reset values of the transfer. */
    memset(Tx_spi, 0, sizeof(Tx_spi));
    memset(RX_spi, 0, sizeof(RX_spi));

    /* Initialize the application to get traces. */
   	Init_Trace();


#ifdef UNITTEST
   	/* This section is active only for unit test proposes. */
    (void)UnitTest();
#endif

    //SPI INITIALIZE
    if (SPI_DEV0_init( ARRAY_SIZE(Tx_spi), SPIDEV1_BUS_SPEED_HZ, SPI_SS_LOW, SPIDEV_DELAY_US,
    		SPIDEV_DATA_BITS_NUM, SPI_MODE1) == NEG_1)
    {
       	Print_Trace(LOG_SEV_ERROR, "spidev1.0 initialization failed");
    }
    else
    {
    	Print_Trace(LOG_SEV_INFORMATIONAL, "spidev1.0 initialized - READY");
    }

    //QUEUE INITIALIZE
	keyqueue = ftok (KEY_PATHNAME, KEY_QUEUE);
	if ((msqid = msgget(keyqueue, 0777 | IPC_CREAT)) == -1)
	{
		Print_Trace(LOG_SEV_ERROR, "The queue has not been created.");
	}
	else
	{
		Print_Trace(LOG_SEV_INFORMATIONAL, "The queue has been created.");
	}

    //THREAD INITIALIZE
	if (pthread_create(&idHilo, &tAttributes, StoreData, NULL) != NUM_0)
	{
		Print_Trace(LOG_SEV_ERROR, "The thread has not been created.");
	}
	else
	{
		Print_Trace(LOG_SEV_INFORMATIONAL, "The thread has been created.");
	}

	// INIT ADS1299
    //Init_ads1299();

    while (NUM_1)
    {
        for (int y = 0; y < RDATAC_BYTES_NUM; y++)
        {
        	Tx_spi[y] = y;
        	//printf("###############Tx_spi[%d] = %lu\n", y, (unsigned long)Tx_spi[y]);

        }
        if (SPIDEV1_transfer(Tx_spi, RX_spi, RDATAC_BYTES_NUM) == NUM_0)
        {
        	// Copy the data input into the queue data structure.
            Set_Data.Id_Message = NUM_1;
            memcpy(&Set_Data.Data_RX_spi[0],&RX_spi[0],ARRAY_SIZE(Set_Data.Data_RX_spi));
            //memset(Set_Data.Trace_Message, 1, sizeof(Set_Data.Trace_Message));
            //strcpy(Set_Data.Trace_Message, "hola\n");

            // Set the message in the structure.
            msgsnd (msqid,&Set_Data,(sizeof(long) + ARRAY_SIZE(Set_Data.Data_RX_spi)),IPC_NOWAIT);

            // TODO: change this for a GPIO interruption.
            printf("Num. Transaccion: %d\r\n", ++lIndex);
            usleep(50000);
        }
        else
        {
        	Print_Trace(LOG_SEV_ERROR, "spidev1.0: Transaction Failed");
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


/*
 * ------------------------------------------------------------------------------
 *
 *  \par Overview:
 *  The function get values from the data queue and store it in a file.
 *
 *  \return
 *
 * ------------------------------------------------------------------------------
 */
void *StoreData (void *parametro)
{
	int msqid; /* Id of the queue */
    char    lbuff[MAX_SCRLINE] = "\0";

	struct msgbuf
	{
		long Id_Message;
		unsigned char Data_RX_spi[RDATAC_BYTES_NUM];
	}Get_Data;

    memset(&Get_Data.Data_RX_spi[0],NUM_0,ARRAY_SIZE(Get_Data.Data_RX_spi));

	//Create and join to the data queue.
	if ((msqid = msgget(keyqueue, IPC_CREAT | 0666)) == -1)
	{
		Print_Trace(LOG_SEV_ERROR, "The thread has not been created.");
	}
	else
	{
		Print_Trace(LOG_SEV_INFORMATIONAL, "The thread has been created.");
	}

	while (NUM_1)
	{
		// Receive the message into the structure.
		msgrcv (msqid, &Get_Data, (sizeof(long) + ARRAY_SIZE(Get_Data.Data_RX_spi)),1, IPC_NOWAIT);

		// Create the formated string to include in the file.
		sprintf(lbuff,"0x%06x\t0x%06x\t0x%06x\t0x%06x\t0x%06x\t0x%06x\t0x%06x\t0x%06x\t0x%06x",
				(Get_Data.Data_RX_spi[0] | Get_Data.Data_RX_spi[1] << 8 | Get_Data.Data_RX_spi[2] << 16),
				(Get_Data.Data_RX_spi[3] | Get_Data.Data_RX_spi[4] << 8 | Get_Data.Data_RX_spi[5] << 16),
				(Get_Data.Data_RX_spi[6] | Get_Data.Data_RX_spi[7] << 8 | Get_Data.Data_RX_spi[8] << 16),
				(Get_Data.Data_RX_spi[9] | Get_Data.Data_RX_spi[10] << 8 | Get_Data.Data_RX_spi[11] << 16),
				(Get_Data.Data_RX_spi[12] | Get_Data.Data_RX_spi[13] << 8 | Get_Data.Data_RX_spi[14] << 16),
				(Get_Data.Data_RX_spi[15] | Get_Data.Data_RX_spi[16] << 8 | Get_Data.Data_RX_spi[17] << 16),
				(Get_Data.Data_RX_spi[18] | Get_Data.Data_RX_spi[19] << 8 | Get_Data.Data_RX_spi[20] << 16),
				(Get_Data.Data_RX_spi[21] | Get_Data.Data_RX_spi[22] << 8 | Get_Data.Data_RX_spi[23] << 16),
				(Get_Data.Data_RX_spi[24] | Get_Data.Data_RX_spi[25] << 8 | Get_Data.Data_RX_spi[26] << 16));

		if(!Print_LOG((char *)lbuff))
		{
			Print_Trace(LOG_SEV_ERROR, "The Message has not be able to logged!.");
		}
        usleep(50000);
	}
	return 0;
	//pthread_exit ((void *) "The Thread has been closed.\n");
}


/*
 * ------------------------------------------------------------------------------
 *
 *  \par Overview:
 *  The function provide initialize values for unit testing of the application
 *
 *  \return
 *
 * ------------------------------------------------------------------------------
 */
int UnitTest(void)
{
	char lcLog[MAX_SCRLINE +1] = "\0";

	Print_Trace(LOG_SEV_DEBUG, "Dummy data for transfer:");
    for (int y = 0; y < RDATAC_BYTES_NUM; y++)
    {
    	Tx_spi[y] = y;
    	snprintf(lcLog, sizeof(lcLog), "\t\tTx_spi[%d] = %lu", y, (unsigned long)Tx_spi[y]);
    	Print_Trace(LOG_SEV_DEBUG, lcLog);
    }

    return NUM_1;
} /* end InitSystem */



