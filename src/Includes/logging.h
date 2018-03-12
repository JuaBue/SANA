/*
 ============================================================================
 Name        : include.h
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#ifndef LOGGING_H_
#define LOGGING_H_

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


/*
 *------------------------------------------------------------------------------
 * INTERNAL LIBRARIES
 *------------------------------------------------------------------------------
 */


/*
 *------------------------------------------------------------------------------
 * LOGS LIBRARIES
 *------------------------------------------------------------------------------
 */


/*
 *------------------------------------------------------------------------------
 * PRIVATE PROTOTYPES
 *------------------------------------------------------------------------------
 */
int Logging(void);
BOOL Print_LOG(char *lDato);
BOOL Create_Path(char *lsPath);
BOOL Get_TimeStamp (TIME_MODE lSelTypeTime, char * TimeStamp, size_t lBufferLength);

#endif /* LOGGING_H_ */






