/*
* SPI.h
*
*  Created on: 8 Feb, 2018
*  Author: Juan Ignacio Bueno Gallego
*/ 

#ifndef SPI_H_
#define SPI_H_


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
