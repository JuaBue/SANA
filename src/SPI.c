/*
* SPI.c
*
*  Created on  : 8 February , 2018
*  Author      : Juan Igancio Bueno Gallego
*  Description : This is an SPI Library for the BeagleBone that consists of the
*  API's to enable SPI transactions.
*/

/*
 *------------------------------------------------------------------------------
 * INCLUDE FILES
 *------------------------------------------------------------------------------
 */
#include "include.h"




/* Static objects for spidev0.0 */
static SPI_DeviceT SPI_device0;
static struct spi_ioc_transfer  transfer_spidev0;

/* Globals */
unsigned char Tx_spi[RDATAC_BYTES_NUM];
unsigned char RX_spi[RDATAC_BYTES_NUM];


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function opens the SPI device to use
 *   	spi_dev_path : Path to the SPI device
 *   	fd           : Variable to store the file handler
 *
 *  \return
 *  NO_ERROR_RET on success, ERROR_RET on failure.
 * -----------------------------------------------------------------------------
 */
int Open_device(char *spi_dev_path, int *fd)
{
    int lResult;

    //Initialize local variable
    lResult = NO_ERROR_RET;

    if((*fd = open(spi_dev_path, O_RDWR | O_NOCTTY | O_NDELAY | O_EXCL)) < NUM_0)//O_RDWR)) < NUM_0)
    {
    	// An error have occurred opening the device.
    	perror ("Failed open the device and returned error ");
    	lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    return lResult;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function set the SPI mode of operation
 *   	fd       : File handler
 *   	spi_mode : SPI Mode
 *
 *  \return
 *  NO_ERROR_RET on success, ERROR_RET on failure.
 * -----------------------------------------------------------------------------
 */
int Set_SPI_mode(int fd, unsigned char spi_mode)
{
    int lResult;

    //Initialize local variable
    lResult = NO_ERROR_RET;

    if(ioctl(fd, SPI_IOC_WR_MODE, &spi_mode) < NUM_0)
    {
    	perror ("Failed to set the write SPI mode and returned error ");
    	lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    if(ioctl(fd, SPI_IOC_RD_MODE, &spi_mode) < NUM_0)
    {
    	perror ("Failed to set the Read SPI mode and returned error ");
    	lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    return lResult;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function set the No. of bits/transaction
 *   	fd            : File handler
 *   	bits_per_word : No. of bits
 *
 *  \return
 *  NO_ERROR_RET on success, ERROR_RET on failure.
 * -----------------------------------------------------------------------------
 */
int Set_SPI_bits(int fd, unsigned char bits_per_word)
{
    int lResult;

    //Initialize local variable
    lResult = NO_ERROR_RET;

    if(ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word) < NUM_0)
    {
    	perror ("Failed to set the No. of bits/transation in write operation"
    			" and returned error ");
    	lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    if(ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits_per_word) < NUM_0)
    {
    	perror ("Failed to set the No. of bits/transation in read operation"
    			" and returned error ");
    	lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    return lResult;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function set the SPI bus frequency in Hertz(Hz)
 *   	fd           : File handler
 *   	bus_speed_HZ : Bus speed
 *
 *  \return
 *  NO_ERROR_RET on success, ERROR_RET on failure.
 * -----------------------------------------------------------------------------
 */
int Set_SPI_speed(int fd, unsigned long bus_speed_HZ)
{
    int lResult;

    //Initialize local variable
    lResult = NO_ERROR_RET;

    if(ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &bus_speed_HZ) < NUM_0)
    {
    	perror ("Failed to set the frecuency for the write operation "
    			"and returned error ");
    	lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    if(ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &bus_speed_HZ) < NUM_0)
    {
    	perror ("Failed to set the frecuency for the read operation "
    			"and returned error ");
    	lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    return lResult;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function initialization configuration for the SPI device
 *   	spi_bytes_no  : File handler
 *   	spi_bus_speed : Bus speed
 *   	chip_select   : chip select line
 *   	spi_delay     : delay in us
 *   	spi_bits_No   : No. of bits/transaction
 *      mode_spi      : SPI Mode
 *      SPI_devicePtr : Points to the SPI device configuration structure.
 *
 *  \return
 *  N\A
 * -----------------------------------------------------------------------------
 */
void SPI_Config_init(unsigned long spi_bytes_no, unsigned long spi_bus_speed,
        unsigned char chip_select, unsigned short spi_delay,
        unsigned char spi_bits_No, unsigned char mode_spi,
		SPI_DevicePtr SPI_devicePtr)
{
    SPI_devicePtr->spi_bytes_num    = spi_bytes_no;
    SPI_devicePtr->spi_bus_speedHZ  = spi_bus_speed;
    SPI_devicePtr->ss_change        = chip_select;
    SPI_devicePtr->spi_delay_us     = spi_delay;
    SPI_devicePtr->spi_data_bits_No = spi_bits_No;
    SPI_devicePtr->spi_mode         = mode_spi;
    SPI_devicePtr->fd_spi           = NUM_1;
    SPI_devicePtr->spi_dev_path     = NULL;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function initialize and set up spidev1.0
 *
 *  \return
 *  NO_ERROR_RET on success, ERROR_RET on failure.
 * -----------------------------------------------------------------------------
 */
int SPI_DEV0_init(unsigned long spi_bytes_no, unsigned long spi_bus_speed,
	   unsigned char chip_select, unsigned short spi_delay,
	   unsigned char spi_bits_No, unsigned char mode_spi)
{
    int lResult;

    //Initialize local variable
    lResult = NO_ERROR_RET;

    /* Initialize the parameters for spidev1.0 structure */
    SPI_Config_init(spi_bytes_no, spi_bus_speed, chip_select,
            spi_delay, spi_bits_No, mode_spi, &SPI_device0);

    /* Assign the path to the spidev1.0 for use */
    SPI_device0.spi_dev_path =  (char *) SPIDEV1_PATH;

    /* Open the spidev1.0 device */
    if(Open_device(SPI_device0.spi_dev_path, &SPI_device0.fd_spi) < NUM_0)
    {
    	perror ("SPI: Failed to open spidev1.0 | ");
        lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    /* Set the SPI mode for RD and WR operations */
    if(Set_SPI_mode(SPI_device0.fd_spi, SPI_device0.spi_mode) < NUM_0)
    {
    	perror ("SPI: Failed to set SPIMODE | ");
        lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    /* Set the No. of bits per transaction */
    if(Set_SPI_bits(SPI_device0.fd_spi, SPI_device0.spi_data_bits_No) < NUM_0)
    {
    	perror ("SPI: Failed to set No. of bits per word | ");
        lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    /* Set the SPI bus speed in Hz */
    if(Set_SPI_speed(SPI_device0.fd_spi, SPI_device0.spi_bus_speedHZ) < NUM_0)
    {
    	perror ("SPI: Failed to set SPI bus frequency | ");
        lResult = ERROR_RET;
        /* TODO: tracear un error */
    }

    /* Initialize the spi_ioc_transfer structure that will be passed to the
    * KERNEL to define/configure each SPI Transactions*/
    transfer_spidev0.tx_buf 	   = NUM_0;
    transfer_spidev0.rx_buf 	   = NUM_0;
    transfer_spidev0.pad           = NUM_0;
    transfer_spidev0.len           = SPI_device0.spi_bytes_num;
    transfer_spidev0.speed_hz      = SPI_device0.spi_bus_speedHZ;
    transfer_spidev0.delay_usecs   = SPI_device0.spi_delay_us;
    transfer_spidev0.bits_per_word = SPI_device0.spi_data_bits_No;
    transfer_spidev0.cs_change     = SPI_device0.ss_change;

    return lResult;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function performs a SPI transaction
 * 	    send    : Points to the buffer containing the data to be sent
 *      receive : Points to the buffer into which the received bytes are stored
 *
 *  \return
 *  NO_ERROR_RET on success, ERROR_RET on failure.
 * -----------------------------------------------------------------------------
 */
int SPIDEV1_transfer(unsigned char *send, unsigned char *receive,
        unsigned char bytes_num)
{
    int lResult;

    //Initialize local variable
    lResult = NO_ERROR_RET;

    /* Points to the Tx and Rx buffer */
    transfer_spidev0.tx_buf = (unsigned long)send;
    transfer_spidev0.rx_buf = (unsigned long)receive;

    /* Override No. of bytes per transaction */
    transfer_spidev0.len = bytes_num;

    printf("@@@@@@@@@:%d", SPI_device0.fd_spi);
    /* Perform a SPI Transaction */
    if (ioctl(SPI_device0.fd_spi, SPI_IOC_MESSAGE(1), &transfer_spidev0)<0)
    {
        perror("SPI: SPI_IOC_MESSAGE Failed |");
        lResult = ERROR_RET;
        /* TODO: tracear un error */
    }
    return lResult;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function performs a single full duplex SPI transaction
 * 	    data_byte : Points to the address of the variable containing the data
 * 	      		    to be sent
 *
 *  \return
 *  NO_ERROR_RET on success, ERROR_RET on failure.
 * -----------------------------------------------------------------------------
 */
unsigned char SPIDEV1_single_transfer(unsigned char data_byte)
{
    unsigned char rec_byte;

    //Initialize local variable
    rec_byte = NUM_0;

    /* Override No. of bytes to send and receive one byte */
    transfer_spidev0.len = SPI_ONE_BYTE;

    /* Points to the address of Tx and Rx variable  */
    transfer_spidev0.tx_buf = (unsigned long)&data_byte;
    transfer_spidev0.rx_buf = (unsigned long)&rec_byte;

    /* Perform an SPI Transaction */
    if (ioctl(SPI_device0.fd_spi, SPI_IOC_MESSAGE(1), &transfer_spidev0)<0)
    {
        perror("SPI: SPI_IOC_MESSAGE Failed |");
        rec_byte = NEG_1;
        /* TODO: tracear un error */
    }

    return rec_byte;
}
