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
void *StoreData (void *parametro);


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
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


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
    memset(RX_spi, 1, sizeof(RX_spi));

    //Initialize local variable
    lIndex = NUM_0;

    //SPI INITIALIZE
    if (SPI_DEV0_init( ARRAY_SIZE(Tx_spi), SPIDEV1_BUS_SPEED_HZ, SPI_SS_LOW,
                      SPIDEV_DELAY_US, SPIDEV_DATA_BITS_NUM,
                      SPI_MODE1) == NEG_1)
    {
        printf("(Main)spidev1.0 initialization failed\r\n");
        /* TODO: tracear un error */
    }
    else
    {
        printf("(Main)spidev1.0 initialized - READY\r\n");
    }

    //QUEUE INITIALIZE
	keyqueue = ftok ("/bin/ls", KEY_QUEUE);
	if ((msqid = msgget(keyqueue, 0777 | IPC_CREAT)) == -1)
	{
		perror("Hemos tenido un problema con la cola\n");
	    exit(1);
	    /* TODO: tracear un error */
	}
	else
	{
	    printf("La cola ha sido creada correctamente :)\n");
	}

	//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
	    for (int y = 0; y < RDATAC_BYTES_NUM; y++)
	    {
	    	Tx_spi[y] = y;
	    	printf("###############Tx_spi[%d] = %lu\n", y, (unsigned long)Tx_spi[y]);
			printf ("byte:0x%02x\n", (unsigned int)Tx_spi[y] );

	    }
	//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑ

    //THREAD INITIALIZE
	if (pthread_create (&idHilo, &tAttributes, StoreData, NULL) != NUM_0)
	{
		perror ("ERROR the thread has not been created.\n");
		exit (-1);
		/* TODO: tracear un error */
	}

	// INIT ADS1299
    //Init_ads1299();

    while (NUM_1)
    {

        if (SPIDEV1_transfer(Tx_spi, RX_spi, RDATAC_BYTES_NUM) == NUM_0)
        {

            printf("(Main)spidev1.0: Transaction Complete\r\n");
            memcpy(&Set_Data.Data_RX_spi[0],&RX_spi[0],ARRAY_SIZE(Set_Data.Data_RX_spi));
            Set_Data.Id_Message = NUM_1;
            msgsnd (msqid,&Set_Data,ARRAY_SIZE(Set_Data.Data_RX_spi),IPC_NOWAIT);
            printf("Valor recibido: %lu\n", (unsigned long)RX_spi[0]);
            printf("Num. Transaccion: %d\r\n", ++lIndex);
            usleep(50000);



        }
        else
        {
            printf("(Main)spidev1.0: Transaction Failed\r\n");
            /* TODO: tracear un error */
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
    char    lbuff[30] = "\0";

	struct msgbuf
	{
		long Id_Message;
		unsigned char Data_RX_spi[RDATAC_BYTES_NUM];
	}Get_Data;

    memset(&Get_Data.Data_RX_spi[0],NUM_0,ARRAY_SIZE(Get_Data.Data_RX_spi));
	//Create and join to the data queue.
	if ((msqid = msgget(keyqueue, 0777 | IPC_CREAT)) == -1)
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
		msgrcv (msqid,&Get_Data,ARRAY_SIZE(Get_Data.Data_RX_spi),1, IPC_NOWAIT);


		printf ("Recibo Primer byte:0x%02x | 0x%02x | 0x%02x\n", Get_Data.Data_RX_spi[0], Get_Data.Data_RX_spi[1], Get_Data.Data_RX_spi[2] );

				printf("Register Status:\t0x%06x\n"
						"Chipset1:\t0x%06x\n"
						"Chipset2:\t0x%06x\n"
						"Chipset3:\t0x%06x\n"
						"Chipset4:\t0x%06x\n"
						"Chipset5:\t0x%06x\n"
						"Chipset6:\t0x%06x\n"
						"Chipset7:\t0x%06x\n"
						"Chipset8:\t0x%06x\n",
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
