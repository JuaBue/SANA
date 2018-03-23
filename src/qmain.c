/*
 ===================================================================================================
 Name        : qmain.c
 Author      : Juan Ignacio Bueno Gallego
 Version     : 1.0
 Created on  : 8 February , 2018
 Description : This is the main process of the SANA data acquisition program.
 ===================================================================================================
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

	// Struct to store the data to send to the queue.
	struct msgbuf
	{
		long             Id_Message;
		unsigned char    Data_RX_spi[RDATAC_BYTES_NUM];
	}Set_Data;

    /* Initialize local variable */
	pthread_attr_init (&tAttributes);
	pthread_attr_setdetachstate (&tAttributes, PTHREAD_CREATE_JOINABLE);
	lIndex = NUM_0;
	msqid  = NUM_0;

    /* Reset values of the transfer. */
    memset(Tx_spi, NUM_0, sizeof(Tx_spi));
    memset(RX_spi, NUM_0, sizeof(RX_spi));

    /* Initialize the application to get traces. */
   	Init_Trace();

    //SPI INITIALIZE
    if (NEG_1 == SPI_DEV0_init( ARRAY_SIZE(Tx_spi), SPIDEV1_BUS_SPEED_HZ, SPI_SS_LOW, SPIDEV_DELAY_US,
    		SPIDEV_DATA_BITS_NUM, SPI_MODE1))
    {
       	Print_Trace(LOG_SEV_ERROR, "spidev1.0 initialization failed");
    }
    else
    {
    	Print_Trace(LOG_SEV_INFORMATIONAL, "spidev1.0 initialized - READY");
    }


#ifdef UNITTEST
   	/* This section is active only for unit test proposes. */
    (void)UnitTest();
#else
	// INIT ADS1299
    Init_ads1299();
#endif

    //QUEUE INITIALIZE
	keyqueue = ftok (KEY_PATHNAME, KEY_QUEUE);
	if (NEG_1 == (msqid = msgget(keyqueue, 0777 | IPC_CREAT)))
	{
		Print_Trace(LOG_SEV_ERROR, "The queue has not been created.");
	}
	else
	{
		Print_Trace(LOG_SEV_INFORMATIONAL, "The queue has been created.");
	}

    //THREAD INITIALIZE
	if (NUM_0 != pthread_create(&idHilo, &tAttributes, StoreData, NULL))
	{
		Print_Trace(LOG_SEV_ERROR, "The thread has not been created.");
	}
	else
	{
		Print_Trace(LOG_SEV_INFORMATIONAL, "The thread has been created.");
	}


	while (NUM_1)
    {
        if (NUM_0 == SPIDEV1_transfer((unsigned char *) &Tx_spi, (unsigned char *) &RX_spi,
        		RDATAC_BYTES_NUM))
        {
        	// Copy the data input into the queue data structure.
            Set_Data.Id_Message = NUM_1;
            memcpy(&Set_Data.Data_RX_spi[INIT_POS], &RX_spi[INIT_POS],
            		ARRAY_SIZE(Set_Data.Data_RX_spi));

            // Set the message in the structure.
            msgsnd (msqid, &Set_Data, (sizeof(Set_Data.Id_Message) +
            		ARRAY_SIZE(Set_Data.Data_RX_spi)), IPC_NOWAIT);

            // TODO: change this for a GPIO interruption.
            printf("Num. Transaccion: %d\r\n", ++lIndex);
            usleep(SYNC_TIME);
        }
        else
        {
        	Print_Trace(LOG_SEV_ERROR, "spidev1.0: Transaction Failed");
        	exit(NEG_1);
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
	int     msqid; /* Id of the queue */
    char    lbuff[MAX_SCRLINE] = {'\0'};

	struct msgbuf
	{
		long Id_Message;
		unsigned char Data_RX_spi[RDATAC_BYTES_NUM];
	}Get_Data;

    memset(&Get_Data.Data_RX_spi[INIT_POS],NUM_0,ARRAY_SIZE(Get_Data.Data_RX_spi));

	//Create and join to the data queue.
	if (NEG_1 == (msqid = msgget(keyqueue, IPC_CREAT | 0666)))
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
		msgrcv (msqid, &Get_Data, (sizeof(long) + ARRAY_SIZE(Get_Data.Data_RX_spi)), NUM_1, IPC_NOWAIT);

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
        usleep(SYNC_TIME);
	}
	return NUM_0;
	//pthread_exit ((void *) "The Thread has been closed.\n");
}

#ifdef UNITTEST
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
	char    lcLog[MAX_SCRLINE + END_STRING] = {'\0'};
	int     lIndey;

	/* Initialize local variable */
	lIndey = NUM_0;

	Print_Trace(LOG_SEV_DEBUG, "Dummy data for transfer:");
    for (lIndey = NUM_0; lIndey < RDATAC_BYTES_NUM; lIndey++)
    {
    	Tx_spi[lIndey] = lIndey;
    	snprintf(lcLog, sizeof(lcLog), "\t\tTx_spi[%d] = %lu", lIndey,
    			(unsigned long)Tx_spi[lIndey]);
    	Print_Trace(LOG_SEV_DEBUG, lcLog);
    }

    return NUM_1;
} /* end InitSystem */
#endif


