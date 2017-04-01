/*
*********************************************************************************************************
*                                 7-SEGMENT LED MODULE RTOS INTERFACE SOURCE FILE
*
* Filename      : SevenSegDisp_OS.c
* Programmer(s) : EHS
* Version       : 1.00
* 
* Notes         : This file provides a thread safe interface to a 7-Segment LED display
*                 using uC/OS-II Semaphores. Critical Sections (disabling interrupts) may be
*                 used instead of uC/OS-II is not available to you.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include "includes.h"


/*
*********************************************************************************************************
*                                              VARIABLES
*********************************************************************************************************
*/

static  OS_EVENT   *SevenSegDispSem;                            /* Semaphore used to access display functions           */


/*
*********************************************************************************************************
*                                       INITIALIZE RTOS SERVICES
*
* Description : This function creates a semaphore to ensure exclusive access to the LCD module and thus
*               provide thread safe access to the display.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

void  SevenSegDispInitOS (void)
{
#if OS_EVENT_NAME_SIZE > 11
    INT8U  err;
#endif


    SevenSegDispSem  = OSSemCreate(1);                          /* Create display access semaphore                      */
#if OS_EVENT_NAME_SIZE > 15
    OSEventNameSet(SevenSegDispSem, (INT8U *)"7-Seg LED Lock", &err);
#endif
}


/*
*********************************************************************************************************
*                              EXCLUSIVE ACCESS FUNCTIONS TO THE DISPLAY
*
* Description : These functions are used to gain and release exclusive access to the LCD display.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

void  SevenSegDispLock (void)
{
    INT8U  err;


    OSSemPend(SevenSegDispSem, 0, &err);                        /* Obtain exclusive access to the display               */
}


void  SevenSegDispUnlock (void)
{
    OSSemPost(SevenSegDispSem);                                 /* Release access to display                            */
}
