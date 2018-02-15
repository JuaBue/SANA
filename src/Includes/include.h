/*
* SPI.c
*
*  Created on  : 8 February , 2018
*  Author      : Juan Igancio Bueno Gallego
*  Description : header file to store the headers required for the code.
*/

#ifndef INCLUDE_H_
#define INCLUDE_H_

/*
 *------------------------------------------------------------------------------
 * INCLUDE FILES
 *------------------------------------------------------------------------------
 */


/*
 *------------------------------------------------------------------------------
 * STANDARD LIBRARIES
 *------------------------------------------------------------------------------
 */
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>



/*
 *------------------------------------------------------------------------------
 * INTERNAL LIBRARIES
 *------------------------------------------------------------------------------
 */
#include <types.h>
#include <constants.h>
#include <SPI.h>
#include <logging.h>

/*
 *------------------------------------------------------------------------------
 * LOGS LIBRARIES
 *------------------------------------------------------------------------------
 */
#include <sys/stat.h>
#include <dirent.h>

/*
 *------------------------------------------------------------------------------
 * SPI LIBRARIES
 *------------------------------------------------------------------------------
 */
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#endif /* INCLUDE_H_ */
