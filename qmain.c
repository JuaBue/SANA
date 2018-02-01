/*
 ============================================================================
 Name        : main.c
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
//#include <include.h>
#include <include.h>
#include <logging.h>


/*
 *------------------------------------------------------------------------------
 * CONSTANTS
 *------------------------------------------------------------------------------
 */
#ifndef NULL
#define NULL (void *)0
#endif


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
int InitSystem(void);

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
int main(void)
{
    int MenuSystem;

    /* Initialize local variable */
    MenuSystem = MIN_INT;

    /* Call to the init function */
    MenuSystem = InitSystem();

    if (NUM_1 == MenuSystem)
    {
        do{
            (void)Print_LOG();
        } while (1);
    }
    else
    {
        /* do nothing */
    }

    return NUM_1;
}


/*
 *------------------------------------------------------------------------------
 * FUNCTIONS
 *------------------------------------------------------------------------------
 */

/*
 * ------------------------------------------------------------------------------
 *
 *  \par Overview:
 *  The function...
 *
 *  \return
 *
 * ------------------------------------------------------------------------------
 */
int InitSystem(void)
{
    return NUM_1;
} /* end InitSystem */
