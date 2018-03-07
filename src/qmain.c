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
extern unsigned char Tx_spi[RDATAC_BYTES_NUM];
extern unsigned char RX_spi[RDATAC_BYTES_NUM];
key_t keyqueue;  /* Key for the data queue. */


/*
 *------------------------------------------------------------------------------
 * MAIN FUNCTION
 *------------------------------------------------------------------------------
 */
int main(void)
{
    int lIndex;
	int msqid; 					/* Id queue */
	pthread_t idHilo; 			/* Id thread */
	pthread_attr_t tAttributes; 	/* Thread attributes */


	struct msgbuf
	{
		long Id_Message;
		unsigned char Data_RX_spi[RDATAC_BYTES_NUM];
	}Set_Data;

	pthread_attr_init (&tAttributes);
	pthread_attr_setdetachstate (&tAttributes, PTHREAD_CREATE_JOINABLE);

    //Reset values of the transfer.
    memset(Tx_spi, 0, sizeof(Tx_spi));
    memset(RX_spi, 0, sizeof(RX_spi));

#ifdef UNITTEST
    (void)UnitTest();
#endif

    //Initialize local variable
    lIndex = NUM_0;

    //SPI INITIALIZE
    if (SPI_DEV0_init( ARRAY_SIZE(Tx_spi), SPIDEV1_BUS_SPEED_HZ, SPI_SS_LOW,
                      SPIDEV_DELAY_US, SPIDEV_DATA_BITS_NUM,
                      SPI_MODE1) == NEG_1)
    {
        printf("(Main)spidev1.0 initialization failed\r\n");
        /* TODO: Trace Error. */
    }
    else
    {
        printf("(Main)spidev1.0 initialized - READY\r\n");
    }

    //QUEUE INITIALIZE
	keyqueue = ftok (KEY_PATHNAME, KEY_QUEUE);
	if ((msqid = msgget(keyqueue, 0777 | IPC_CREAT)) == -1)
	{
		perror("Hemos tenido un problema con la cola\n");
	    exit(NEG_1);
	    /* TODO: tracear un error */
	}
	else
	{
	    printf("La cola ha sido creada correctamente :)\n");
	}

    //THREAD INITIALIZE
	if (pthread_create(&idHilo, &tAttributes, StoreData, NULL) != NUM_0)
	{
		perror ("ERROR the thread has not been created.\n");
		exit (NEG_1);
		/* TODO: tracear un error */
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
            for (int y = 0; y < RDATAC_BYTES_NUM; y++)
            {
            	printf("###############Rx_spi[%d] = %lu\n", y, (unsigned long)RX_spi[y]);

            }
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
            /* TODO: tracear un error */
            printf("(Main)spidev1.0: Transaction Failed\r\n");
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
		perror("ERROR creating the data queue.\n");
	    exit(1);
	    /* TODO: tracear un error */
	}
	else
	{
	    printf("The queue has been created.\n");
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
			printf("ERROR: The Message has not be able to logged!.");
			/* TODO: tracear un error */
		}
        usleep(50000);
	}
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

    for (int y = 0; y < RDATAC_BYTES_NUM; y++)
    {
    	Tx_spi[y] = y;
    	printf("###############Tx_spi[%d] = %lu\n", y, (unsigned long)Tx_spi[y]);

    }

    return NUM_1;
} /* end InitSystem */



