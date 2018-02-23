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
extern unsigned char Tx_spi[SPIDEV_BYTES_NUM];
extern unsigned char RX_spi[SPIDEV_BYTES_NUM];
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
		int  Data_SPI;
	}Set_Data;

	pthread_attr_init (&tAttributes);
	pthread_attr_setdetachstate (&tAttributes, PTHREAD_CREATE_JOINABLE);

    //Reset values of the transfer.
    memset(Tx_spi, 0, sizeof(Tx_spi));
    memset(RX_spi, 0, sizeof(RX_spi));

    //Initialize local variable
    lIndex = NUM_0;

    Tx_spi[0] = 0x56;
    Tx_spi[1] = 0x00;

    //SPI INITIALIZE
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

    //QUEUE INITIALIZE
	keyqueue = ftok ("/bin/ls", KEY_QUEUE);
	if ((msqid = msgget(keyqueue, 0777 | IPC_CREAT)) == -1)
	{
		perror("Hemos tenido un problema con la cola\n");
	    exit(1);
	}
	else
	{
	    printf("La cola ha sido creada correctamente :)\n");
	}

    //THREAD INITIALIZE
	if (pthread_create (&idHilo, &tAttributes, StoreData, NULL) != NUM_0)
	{
		perror ("ERROR the thread has not been created.\n");
		exit (-1);
	}

    while (NUM_1)
    {
        if (SPIDEV1_transfer(Tx_spi, RX_spi, NO_OF_BYTES) == NUM_0)
        {
            printf("(Main)spidev1.0: Transaction Complete\r\n");
        }
        else
        {
            printf("(Main)spidev1.0: Transaction Failed\r\n");
        }
        Init_ads1299();

        Set_Data.Id_Message = NUM_1;
        Set_Data.Data_SPI = RX_spi[0];//RX_spi[0];
        msgsnd (msqid,&Set_Data,sizeof(int),IPC_NOWAIT);
        printf("Valor recibido: %lu\n", (unsigned long)RX_spi[0]);
        printf("Num. Transaccion: %d\r\n", ++lIndex);
        usleep(50000);

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

	struct msgbuf
	{
		long Id_Message;
		int  Data_SPI;
	}Get_Data;


	//Create and join to the data queue.
	if ((msqid = msgget(keyqueue, 0777 | IPC_CREAT)) == -1)
	{
		perror("ERROR creating the data queue.\n");
	    exit(1);
	}
	else
	{
	    printf("The queue has been created.\n");
	}

   /*  */
	while (NUM_1)
	{
		msgrcv (msqid,&Get_Data,sizeof(int),1, IPC_NOWAIT);
		if(!Print_LOG((unsigned int)Get_Data.Data_SPI))
		{
			printf("ERROR: The Message has not be able to logged!.");
		}
        usleep(50000);
	}
	pthread_exit ((void *) "The Thread has been closed.\n");
}
