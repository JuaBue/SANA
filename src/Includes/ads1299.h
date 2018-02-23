/*
 * ads1299.h
 *
 *  Created on: 23 feb. 2018
 *      Author: juan.bueno
 */

#ifndef ADS1299_H_
#define ADS1299_H_

BOOL Init_ads1299 (void);
BOOL SendCommad_ads1299 (unsigned char Command);
BOOL SendByte_ads1299 (unsigned char Address, unsigned char Transfer);

#endif /* ADS1299_H_ */
