/*
 ===================================================================================================
 Name        : logging.c
 Author      : Juan Ignacio Bueno Gallego
 Version     : 1.0
 Copyright   :
 Description :
 ===================================================================================================
 */

/*
 *--------------------------------------------------------------------------------------------------
 * INCLUDE FILES
 *--------------------------------------------------------------------------------------------------
 */
#include <include.h>


/*
 *--------------------------------------------------------------------------------------------------
 * CONSTANTS
 *--------------------------------------------------------------------------------------------------
 */


/*
 *--------------------------------------------------------------------------------------------------
 * TYPE DEFINITIONS
 *--------------------------------------------------------------------------------------------------
 */
/* Severity text strings for syslog severity levels */
static const char *log_sysLogSeverityNames[] =
{
	"Err",
    "War",
    "Not",
    "Inf",
    "Dbg"
};

/*
 *--------------------------------------------------------------------------------------------------
 * PRIVATE PROTOTYPES
 *--------------------------------------------------------------------------------------------------
 */


/*
 *--------------------------------------------------------------------------------------------------
 * STRUCTURES
 *--------------------------------------------------------------------------------------------------
 */


/*
 *--------------------------------------------------------------------------------------------------
 * MAIN FUNCTION
 *--------------------------------------------------------------------------------------------------
 */


/*
 *--------------------------------------------------------------------------------------------------
 * FUNCTIONS
 *--------------------------------------------------------------------------------------------------
 */


/*
 * -------------------------------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function print the Log in a file.
 *
 *  \return
 *	FALSE if the log has not been logged. TRUE if the message has been logged.
 *
 * -------------------------------------------------------------------------------------------------
 */
BOOL Print_LOG (char *lDato)
{
    BOOL           lbResult;
    FILE    	   *lfFile                      	     = NULL;
    static char    lsPath[MAX_PATHLINE + END_STRING]     = {'\0'};
    char           lsLog[MAX_SCRLINE + END_STRING]       = {'\0'};
    char           lsTrace[MAX_SCRLINE + END_STRING]     = {'\0'};
    char 		   lcDateTime[MAX_TIMELINE + END_STRING] = {'\0'};
    struct stat    st;

    /* Initialize output data */
    lbResult     = FALSE;

    /* Initialize local variable */
    stat(lsPath, &st);

    /* get the path to store the LOGs if there is no file to store the data or the file is full.*/
    if (!lsPath[INIT_POS] || ((int)st.st_size >= MAX_FILESIZE))
    {
       	Create_Path(lsPath);
    }

	lfFile = fopen (lsPath, "aw+");

	if (NULL == lfFile)
	{
		snprintf(lsTrace, sizeof(lsTrace), "The file %s can not be open.\n", lsPath);
		Print_Trace(LOG_SEV_ERROR, lsTrace);
		lbResult = FALSE;
	}
	else
	{
		// Get the time and data string.
		Get_TimeStamp (TIME_YMDHMS, lcDateTime, sizeof(lcDateTime));
		// Set the format sting with the data in the file.
		snprintf(lsLog, ARRAY_SIZE(lsLog), "%s [ADS1299-%d]\t%s\n",	lcDateTime, ADS_ID, lDato);
		fprintf (lfFile, "%s", lsLog);
		fclose(lfFile);
		// The date has been successfully set.
		lbResult = TRUE;
	}

    return lbResult;
}


/*
 * -------------------------------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function print events in a file.
 *
 *  \return
 *	FALSE if the log has not been logged. TRUE if the message has been logged.
 *
 * -------------------------------------------------------------------------------------------------
 */
BOOL Init_Trace (void)
{
    BOOL           lbResult;
    FILE    	   *lfFile                           		   = NULL;
    char 		   lcNamePath[MAX_FILETRACENAME + END_STRING]  = {'\0'};
    char    	   lsLog[MAX_SCRLINE + END_STRING]             = {'\0'};
    char           lsTraceName[MAX_FILETRACENAME + END_STRING] = {'\0'};

    /* Initialize output data */
    lbResult = FALSE;

    /* Create the path with the date to store the files. */
    /* Get the date to create the folder to store the data files */
	Get_TimeStamp (TIME_YMD, lcNamePath, sizeof(lcNamePath));

    /* Check if the folder already exits  */
    if (NUM_0 == opendir(lcNamePath))
    {
        if (NUM_0 == mkdir(lcNamePath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
        {
    		Print_Trace(LOG_SEV_ERROR, "The path has been created.");
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
		/* TODO: tracear info */
    }

   	snprintf(lsTraceName, sizeof(lsTraceName), TRACE_FILE, lcNamePath, lcNamePath);
    // Create the path of the trace file.

	// Check if the file exist previously.
	if(NEG_1 == access(lsTraceName, F_OK ))
	{
		lfFile = fopen (lsTraceName, "aw+");
	   	snprintf(lsLog, ARRAY_SIZE(lsLog), "Date\tTime\tADC ID\tStatus Register\tChipset 1\tChipset"
	   			" 2\tChipset 3\tChipset 4\tChipset 5\tChipset 6\tChipset 7\tChipset 8\t\n");
		fprintf (lfFile, "%s", lsLog);
		fclose (lfFile);
	}
	else
	{
        lbResult = FALSE;
		/* TODO: tracear error */
	}

    return lbResult;
}


/*
 * -------------------------------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function print events in a file.
 *
 *  \return
 *	FALSE if the log has not been logged. TRUE if the message has been logged.
 *
 * -------------------------------------------------------------------------------------------------
 */
BOOL Print_Trace (LOG_SEV_TYPE leSevType, const char *lcTrace)
{
    BOOL           lbResult;
    FILE    	   *lfFile                                     = NULL;
    char 		   lcNamePath[MAX_FILETRACENAME + END_STRING]  = {'\0'};
    char    	   lsLog[MAX_SCRLINE + END_STRING]             = {'\0'};
    char           lsTraceName[MAX_FILETRACENAME + END_STRING] = {'\0'};

    /* Initialize output data */
    lbResult = FALSE;

    /* Create the path with the date to store the files. */
    /* Get the date to create the folder to store the data files */
	Get_TimeStamp (TIME_YMD, lcNamePath, sizeof(lcNamePath));

	snprintf(lsTraceName, sizeof(lsTraceName), TRACE_FILE, lcNamePath, lcNamePath);
	// Check if the file exist previously.
	if(NEG_1 != access(lsTraceName, F_OK ))
	{
		lfFile = fopen (lsTraceName, "aw+");
		Get_TimeStamp (TIME_YMDHMS, lcNamePath, sizeof(lcNamePath));
	   	snprintf(lsLog, ARRAY_SIZE(lsLog), "%sSANA - %s:\t%s\n", lcNamePath,
	   			log_sysLogSeverityNames[leSevType], lcTrace);
		fprintf (lfFile, "%s", lsLog);
		fclose (lfFile);
		lbResult = TRUE;
	}
	else
	{
	    lbResult = FALSE;
		/* TODO: tracear info */
	}

    return lbResult;
}


/*
 * -------------------------------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function create the file where the data has to be stored.
 *
 *  \return
 *  TRUE the path has been created, FALSE the path has not been created.
 *
 * -------------------------------------------------------------------------------------------------
 */
BOOL Create_Path (char *lsPath)
{
    BOOL   			lbResult;
    FILE    	    *lfFile                            			= NULL;
    static int 	    lwCount 								    = NUM_1;
    char 		   	lcNamePath[MAX_PATHLINE + END_STRING]       = {'\0'};
    char    		lsNameFile[MAX_FILENAME + END_STRING]       = {'\0'};
    char    		lcVersionTime[MAX_VERSIONLINE + END_STRING] = {'\0'};
    char    	    lsLog[MAX_SCRLINE + END_STRING]             = {'\0'};
    char    	    lsTrace[MAX_SCRLINE + END_STRING]           = {'\0'};


    /* Initialize output data */
    lbResult = FALSE;

    /* Create the path with the date to store the files. */
    /* Get the date to create the folder to store the data files */
	Get_TimeStamp (TIME_YMD, lcNamePath, sizeof(lcNamePath));

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
    	snprintf(lsPath, sizeof(lcNamePath), "%s//LOGs_v%d.tmp", lcNamePath, lwCount);

    	// Check if the file exist previously.
    	while(NEG_1 != access(lsPath, F_OK ))
    	{
    		snprintf(lsNameFile, sizeof(lsNameFile), "%s//%s_LOGs_v%d.txt",lcNamePath,
    				lcVersionTime, lwCount);
    		rename(lsPath, lsNameFile);
    		snprintf(lsTrace, sizeof(lsTrace), "The file %s has been created.", lsNameFile);

    		//Trace the creation of the new file.
    		Print_Trace(LOG_SEV_NOTICE, lsTrace);
	    	snprintf(lsPath, sizeof(lcNamePath), "%s//LOGs_v%d.tmp", lcNamePath, ++lwCount);
		}
		// Set the header to the file.
        lfFile = fopen (lsPath, "aw+");
    	snprintf(lsLog, sizeof(lsLog), "Date\tTime\tADC ID\tStatus Register\tChipset 1\tChipset "
    			"2\tChipset 3\tChipset 4\tChipset 5\tChipset 6\tChipset 7\tChipset 8\t\n");
		fprintf (lfFile, "%s", lsLog);
		fclose (lfFile);

    }

    // Return the name path plus filename.
    return lbResult;
}


/*
 * -------------------------------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function create a format string to stamp the time/date in the logs.
 *
 *  \return
 *	The format string with the date and time.
 *
 * -------------------------------------------------------------------------------------------------
 */
BOOL Get_TimeStamp (TIME_MODE lSelTypeTime, char * TimeStamp,
		size_t lBufferLength)
{
    time_t       lTime;
    struct tm    *tm;
    BOOL   		 lbResult;

    /* Initialize output data */
    lTime    = time (NULL);
    tm       = localtime (&lTime);
    lbResult = FALSE;

    switch(lSelTypeTime)
    {
		case TIME_YMD:
			/* get the time to folder name */
	        snprintf(TimeStamp, lBufferLength, "%02d%02d%02d", (tm->tm_year - NUM_100),
	        		(tm->tm_mon + NUM_1), tm->tm_mday);
	        lbResult = TRUE;
			break;

		case TIME_HMS:
			/* get the time */
	        snprintf(TimeStamp, lBufferLength, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min,
	        		tm->tm_sec);
	        lbResult = TRUE;
			break;

		case TIME_YMDHMS:
		    /* get the time to log the events */
		    snprintf(TimeStamp, lBufferLength, "%02d%02d%02d\t%02d:%02d:%02d\t",
		    		(tm->tm_year - NUM_100), (tm->tm_mon + NUM_1), tm->tm_mday, tm->tm_hour,
					tm->tm_min, tm->tm_sec);
	        lbResult = TRUE;
			break;

		case TIME_NFILE:
			/* get the time to name of the file */
	        snprintf(TimeStamp, lBufferLength, "%02d%02d%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
	        lbResult = TRUE;
			break;

		default:
			/* do nothing */
			/* TODO: include an error. */
	        lbResult = FALSE;
			break;
    }

    return lbResult;
}


