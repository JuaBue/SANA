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
 *
 * -----------------------------------------------------------------------------
 */
BOOL Print_LOG (void)
{
    BOOL           lbResult;
    FILE           *lfFile;
    BOOL           lbCreatePath;
    static char    lsPath[MAX_SCRLINE]= "\0";
    char          *lcLog;

    /* Initialize output data */
    lbResult     = FALSE;
    lbCreatePath = FALSE;

    /* create the path to store the LOGs */
    Create_Path( (char *)lsPath);
    lbCreatePath = TRUE;
    if (lbCreatePath)
    {
        strcat(lsPath, "//");
        strcat(lsPath, "LOGs.txt");
        lfFile = fopen (lsPath, "aw+");

        if (lfFile==NULL)
        {
            printf("\nError de apertura del archivo. \n\n");
        }
        else
        {
            printf("\nArchivo creado :). \n\n");
			lcLog = Get_Date (FALSE);
			strcat(lcLog, "\n");
			fprintf (lfFile, "%s", lcLog);
			fclose (lfFile);
        }
    }
    else
    {
        printf("\nError de fichero :). \n\n");
    }

    return lbResult;
}


/*
 * -----------------------------------------------------------------------------
 *
 *  \par Overview:
 *  This function print the Log in a file.
 *
 *  \return
 *  TRUE el directorio se ha creado, FALSE el directorio no se ha creado.
 * -----------------------------------------------------------------------------
 */
const char *Create_Path (char *lsPath)
{
    BOOL   lbResult;
    int    lwpath;
    char *lcNamePath;

    /* Initialize output data */
    lbResult = FALSE;

    /* Initialize local variable */
    lwpath = MIN_INT;

    lcNamePath = Get_Date (TRUE);

    if (NUM_0 == opendir(lcNamePath))
    {
        lwpath = mkdir(lcNamePath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

        if (NUM_0 == lwpath)
        {
            lbResult = TRUE;
        }
        else
        {

            lbResult = FALSE;
            /* TODO: tracear un error */
        }
    }
    else
    {
        /* The path already exist */
        lbResult = TRUE;
    }

    if (TRUE == lbResult)
    {
        strcpy(lsPath, lcNamePath);
        strcat(lsPath, "//");
        strcat(lsPath, "LOGs.txt");
        //printf("%s", lsPath);
    }

    strcpy(lsPath, lcNamePath);

    return lsPath;
}


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
char *Get_Date (BOOL SelTime)
{
    time_t t;
    struct tm *tm;
    static char FormatT[MAX_SCRLINE];

    /* Initialize output data */


    t = time (NULL);
    tm = localtime(&t);

    /* get the time to log the events */
    if (TRUE == SelTime)
    {
        sprintf(FormatT, "%02d%02d%02d", (tm->tm_year - 100), tm->tm_mon, tm->tm_mday);
    }
    else
    {
        sprintf(FormatT, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    }

    return FormatT;
}
