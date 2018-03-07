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
    FILE    	   *lfFile;
    static char    lsPath[MAX_PATHLINE] = "\0";
    static char    lsLog[MAX_SCRLINE]  = "\0";
    struct stat st;

    /* Initialize output data */
    lbResult     = FALSE;

    stat(lsPath, &st);

    /* get the path to store the LOGs */
    if (!lsPath[NUM_0] || ((int)st.st_size >= 500000))
    {
       	Create_Path( (char *)lsPath);
       	printf("%s",lsPath);
    }

	lfFile = fopen (lsPath, "aw+");

	if (lfFile==NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
	}
	else
	{
		sprintf(lsLog, "%s [ADS1299-%d]\t%s\n",Get_TimeStamp(), ADS_ID, lDato);
		fprintf (lfFile, "%s", lsLog);
		fclose (lfFile);
		lbResult = TRUE;
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
const char *Create_Path (char *lsPath)
{
    BOOL   			lbResult;
    FILE           	*lfFile;
    static int 	    lwCount = NUM_1;
    char 		   	*lcNamePath;
    char    		lsNameFile[MAX_SCRLINE] = "\0";
    static char    	lsLog[MAX_SCRLINE]  = "\0";


    /* Initialize output data */
    lbResult = FALSE;
    //lwCount  = NUM_1;

    /* Create the path with the date to store the files. */
    /* Get the date to create the folder to store the data files */
	lcNamePath = Get_Date (TRUE);

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

    // Store the path name.
	strcpy(lsPath, lcNamePath);

    /* If the path already exist create the file to store the data.*/
    if (TRUE == lbResult)
    {
    	// Create the file to store de data file.
    	sprintf(lsNameFile, "//LOGs_v%d.tmp", lwCount);
    	strcat(lsPath, lsNameFile);

    	// Check if the file exist previously.
    	while(access(lsPath, F_OK ) != NEG_1)
    	{
			lwCount++;
			strcpy(lsPath, lcNamePath);
			sprintf(lsNameFile, "//LOGs_v%d.txt", lwCount);
			strcat(lsPath, lsNameFile);
		}

		// Set the header to the file.
        lfFile = fopen (lsPath, "aw+");
    	sprintf(lsLog, "Date\tTime\tADC ID\tStatus Register\tChipset 1\tChipset 2\t"
    			"Chipset 3\tChipset 4\tChipset 5\tChipset 6\tChipset 7\t"
    			"Chipset 8\t\n");
		fprintf (lfFile, "%s", lsLog);
		fclose (lfFile);
    }


    // Return the name path plus filename.
    return lsPath;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function create a format string with the time or date to include in
 *  the Logs.
 *
 *  \return
 *	A format string with the date or time.
 *
 * -----------------------------------------------------------------------------
 */
char *Get_Date (BOOL SelTime)
{
    time_t         lTime;
    struct tm      *tm;
    static char    FormatT[MAX_SCRLINE];

    /* Initialize output data */
    lTime = time (NULL);
    tm = localtime(&lTime);

    /* get the time to log the events */
    if (TRUE == SelTime)
    {
        sprintf(FormatT, "%02d%02d%02d", (tm->tm_year - 100),
        		(tm->tm_mon + 1), tm->tm_mday);
    }
    else
    {
        sprintf(FormatT, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    }

    return FormatT;
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
char *Get_TimeStamp (void)
{
    time_t         lTime;
    struct tm      *tm;
    static char    TimeStamp[MAX_SCRLINE];

    /* Initialize output data */
    lTime = time (NULL);
    tm = localtime(&lTime);

    /* get the time to log the events */
    sprintf(TimeStamp, "%02d%02d%02d\t%02d:%02d:%02d\t", (tm->tm_year - 100),
    		(tm->tm_mon + 1), tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

    return TimeStamp;
}


