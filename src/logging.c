/*
 ============================================================================
 Name        : logging.c
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
 * MAIN FUNCTION
 *------------------------------------------------------------------------------
 */


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function print the Log in a file.
 *
 *  \return
 *
 * -----------------------------------------------------------------------------
 */
int Logging()
{
    /* do nothing */

    return NUM_0;
}


/*
 *------------------------------------------------------------------------------
 * FUNCTIONS
 *------------------------------------------------------------------------------
 */


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function print the Log in a file.
 *
 *  \return
 *	FALSE if the log has not been logged. TRUE if the message has been logged.
 *
 * -----------------------------------------------------------------------------
 */
BOOL Print_LOG (char *lDato)
{
    BOOL           lbResult;
    FILE    	   *lfFile                      = NULL;
    static char    lsPath[20]     			    = "\0";
    char           lsLog[MAX_SCRLINE + 1]       = "\0";
    char 		   lcDateTime[MAX_TIMELINE + 1] = "\0";
    struct stat st;

    /* Initialize output data */
    lbResult     = FALSE;

    stat(lsPath, &st);


    /* get the path to store the LOGs */
    if (!lsPath[NUM_0] || ((int)st.st_size >= 50000))
    {
       	Create_Path(lsPath);
    }

	lfFile = fopen (lsPath, "aw+");

	if (lfFile==NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
	}
	else
	{
		(void)Get_TimeStamp (TIME_YMDHMS, lcDateTime, sizeof(lcDateTime));
		snprintf(lsLog, ARRAY_SIZE(lsLog), "%s [ADS1299-%d]\t%s\n",
				lcDateTime, ADS_ID, lDato);
		fprintf (lfFile, "%s", lsLog);
		lbResult = TRUE;
		fclose(lfFile);
	}

    return lbResult;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function create the file where the data has to be stored.
 *
 *  \return
 *  TRUE the path has been created, FALSE the path has not been created.
 *
 * -----------------------------------------------------------------------------
 */
BOOL Create_Path (char *lsPath)
{
    BOOL   			lbResult;
    FILE    	    *lfFile                            = NULL;
    static int 	    lwCount 						   = NUM_1;
    char 		   	lcNamePath[MAX_PATHLINE + 1]       = "\0";
    char    		lsNameFile[MAX_FILENAME + 1]       = "\0";
    char    		lcVersionTime[MAX_VERSIONLINE + 1] = "\0";
    char    	    lsLog[MAX_SCRLINE + 1]             = "\0";


    /* Initialize output data */
    lbResult = FALSE;

    /* Create the path with the date to store the files. */
    /* Get the date to create the folder to store the data files */
	(void)Get_TimeStamp (TIME_YMD, lcNamePath, sizeof(lcNamePath));

    /* Check if the folder already exits  */
    if (NUM_0 == opendir(lcNamePath))
    {
        if (NUM_0 == mkdir(lcNamePath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
        {
            lbResult = TRUE;
        }
        else
        {
        	/* The folder has not been possible to create */
            lbResult = FALSE;
            /* TODO: tracear un error */
        }
    }
    else
    {
        lbResult = TRUE;
    }

	(void)Get_TimeStamp (TIME_NFILE, lcVersionTime, sizeof(lcVersionTime));
    /* If the path already exist create the file to store the data.*/
    if (TRUE == lbResult)
    {
    	// Create the file to store de data file.
    	snprintf(lsPath, MAX_SCRLINE, "%s//LOGs_v%d.tmp", lcNamePath, lwCount);

    	// Check if the file exist previously.
    	while(access(lsPath, F_OK ) != NEG_1)
    	{
    		snprintf(lsNameFile, 30, "%s//%s_LOGs_v%d.txt",lcNamePath,
    				lcVersionTime, lwCount);
    		rename(lsPath, lsNameFile);
			lwCount++;
	    	snprintf(lsPath, 50, "%s//LOGs_v%d.tmp", lcNamePath, lwCount);
		}
		// Set the header to the file.
        lfFile = fopen (lsPath, "aw+");
    	snprintf(lsLog, ARRAY_SIZE(lsLog), "Date\tTime\tADC ID\tStatus Register"
    			"\tChipset 1\tChipset 2\tChipset 3\tChipset 4\tChipset 5\t"
    			"Chipset 6\tChipset 7\tChipset 8\t\n");
		fprintf (lfFile, "%s", lsLog);
		fclose (lfFile);
    }

    // Return the name path plus filename.
    return lbResult;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function create a format string to stamp the time/date in the logs.
 *
 *  \return
 *	The format string with the date and time.
 *
 * -----------------------------------------------------------------------------
 */
BOOL Get_TimeStamp (TIME_MODE lSelTypeTime, char * TimeStamp,
		size_t lBufferLength)
{
    time_t         lTime;
    struct tm      *tm;

    /* Initialize output data */
    lTime = time (NULL);
    tm    = localtime (&lTime);

    switch(lSelTypeTime)
    {
		case TIME_YMD:
			/* get the time to folder name */
	        snprintf(TimeStamp, lBufferLength, "%02d%02d%02d",
	        		(tm->tm_year - 100), (tm->tm_mon + 1), tm->tm_mday);
			break;

		case TIME_HMS:
			/* get the time */
	        snprintf(TimeStamp, lBufferLength, "%02d:%02d:%02d",
	        		tm->tm_hour, tm->tm_min, tm->tm_sec);
			break;

		case TIME_YMDHMS:
		    /* get the time to log the events */
		    snprintf(TimeStamp, lBufferLength, "%02d%02d%02d\t%02d:%02d:%02d\t",
		    		(tm->tm_year - 100), (tm->tm_mon + 1), tm->tm_mday,
					tm->tm_hour, tm->tm_min, tm->tm_sec);
			break;

		case TIME_NFILE:
			/* get the time to name of the file */
	        snprintf(TimeStamp, lBufferLength, "%02d%02d%02d",
	        		tm->tm_hour, tm->tm_min, tm->tm_sec);
			break;

		default:
			/* do nothing */
			/* TODO: include an error. */
			break;
    }

    return TRUE;
}


