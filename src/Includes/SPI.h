/*
* SPI.h
*
*  Created on: 8 Feb, 2018
*  Author: Juan Ignacio Bueno Gallego
*/ 

#ifndef SPI_H_
#define SPI_H_

#include<stdint.h>

/* Generic Definitions */
#define SPIDEV_BYTES_NUM                 8
#define SPIDEV_DATA_BITS_NUM             8
#define SPIDEV_DELAY_US                  0
#define SPI_SS_HIGH                      1
#define SPI_SS_LOW                       0
#define SPI_ONE_BYTE                     1

/* No. of bytes per transaction */
#define NO_OF_BYTES                      2

/*Definitions specific to spidev */
#define SPIDEV0_PATH                     "/dev/spidev0.1"
#define SPIDEV0_BUS_SPEED_HZ             50000
#define SPIDEV1_PATH                     "/dev/spidev1.0"
#define SPIDEV1_BUS_SPEED_HZ             50000



/* Enum SPI Modes*/
typedef enum{
    SPI_MODE0 = 0,
    SPI_MODE1 = 1,
    SPI_MODE2 = 2,
    SPI_MODE3 = 3
}SPI_MODE;

/*SPI device configuration structure*/
typedef struct{
    char*             spi_dev_path;
    int               fd_spi;
    unsigned long     spi_bytes_num;
    unsigned long     spi_bus_speedHZ;
    unsigned char     ss_change;
    unsigned short    spi_delay_us;
    unsigned char     spi_data_bits_No;
    unsigned char     spi_mode;
}SPI_DeviceT, *SPI_DevicePtr;

/* SPI API's*/
extern int Open_device(char *spi_dev_path, int *fd);
extern int Set_SPI_mode(int fd, unsigned char spi_mode);
extern int Set_SPI_bits(int fd, unsigned char bits_per_word);
extern int Set_SPI_speed(int fd, unsigned long bus_speed_HZ);
extern void SPI_Config_init(unsigned long spi_bytes_no, unsigned long spi_bus_speed,
                unsigned char chip_select, unsigned short spi_delay,
                unsigned char spi_bits_No, unsigned char mode_spi, SPI_DevicePtr SPI_devicePtr);

/* API's to initialize and use spidev1.0 - Configure the Bus as you like*/
extern int SPI_DEV0_init(unsigned long spi_bytes_no, unsigned long spi_bus_speed,
                unsigned char chip_select, unsigned short spi_delay,
                unsigned char spi_bits_No, unsigned char mode_spi);
extern int SPIDEV1_transfer(unsigned char *send, unsigned char *receive,
                unsigned char bytes_num);
extern unsigned char SPIDEV1_single_transfer(unsigned char data_byte);

#endif /* SPI_H_ */
