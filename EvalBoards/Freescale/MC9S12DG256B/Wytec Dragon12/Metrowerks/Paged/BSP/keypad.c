/*
*********************************************************************************************************
*                        Wytec Dragon12 Board Support Package
* File : keypad.c
*
* By   : Eric Shufro
*
* Notes: This file provides hardware interface functions for the Wytec Dragon12 EVB
*        4x4, 16 digit Keypad.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        INCLUDES
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                       CONSTANTS
*********************************************************************************************************
*/

#define  KEYPAD_COL_0                 (INT8U)(1 <<  0)                  /* Port A, Bit 0                                            */
#define  KEYPAD_COL_1                 (INT8U)(1 <<  1)                  /* Port A, Bit 1                                            */
#define  KEYPAD_COL_2                 (INT8U)(1 <<  2)                  /* Port A, Bit 2                                            */
#define  KEYPAD_COL_3                 (INT8U)(1 <<  3)                  /* Port A, Bit 3                                            */

#define  KEYPAD_ROW_0				  (INT8U)(1 <<  4)                  /* Port A, Bit 4                                            */
#define  KEYPAD_ROW_1                 (INT8U)(1 <<  5)                  /* Port A, Bit 5                                            */
#define  KEYPAD_ROW_2                 (INT8U)(1 <<  6)                  /* Port A, Bit 6                                            */
#define  KEYPAD_ROW_3                 (INT8U)(1 <<  7)                  /* Port A, Bit 7                                            */

#define  KEYPAD_IN_MASK               (INT8U)(KEYPAD_COL_0 | KEYPAD_COL_1 | KEYPAD_COL_2 | KEYPAD_COL_3)
#define  KEYPAD_OUT_MASK              (INT8U)(KEYPAD_ROW_0 | KEYPAD_ROW_1 | KEYPAD_ROW_2 | KEYPAD_ROW_3)

/*
*********************************************************************************************************
*                                 Keypad Hardware Initialization
*
* Description : KeypadInitPort() is responsible for initializing the hardware used to interface with the
*               keypad module.
*
* Arguments   : None
*
* Callers     : The application must call this function before attempting to read data from the
*               keypad by means of KeypadReadPort().
*
* Notes       : None
*********************************************************************************************************
*/

void  KeypadInitPort (void)
{
	DDRA  |=   KEYPAD_OUT_MASK;                                         /* Configure the ROWS as outputs                            */
	DDRA  &=  ~KEYPAD_IN_MASK;                                          /* Configure the COLS as inputs                             */
	PUCR  |=   PUCR_PUPAE_MASK;                                         /* Enable pull-up resistors for PORTA                       */
}

/*
*********************************************************************************************************
*                                 Keypad Read Operation
*
* Description : KeypadReadPort() scans the keypad from left to right and top to bottom looking for
*               pressed keys. The first pressed key detected is returned. 
*
* Arguments   : None
*
* Callers     : User Application
*
* Returns     : INT8U value 0 - 15 corresponding to which button is pressed and 0xFF NULL Event
*
* Notes       : 1) Columns are to be treated as inputs Rows are outputs.
*                 Rows are set HIGH to start and brougnt low, if a column on that
*                 row is found to be low, then that button value (0-15) is returned.
*
*                   C0  C1  C2  C3
*                   PA0 PA1 PA2 PA3
*                    |   |   |   |
*                -----------------
*                |   |   |   |   |   
*                | 0 | 1 | 2 | 3 |
*                ------------------- PA4, R0
*                |   |   |   |   |   
*                | 4 | 5 | 6 | 7 |
*                ------------------- PA5, R1
*                |   |   |   |   |  
*                | 8 | 9 | 10| 11|
*                ------------------- PA6, R2
*                |   |   |   |   | 
*                | 12| 13| 14| 15|
*                ------------------- PA7, R3        
*********************************************************************************************************
*/

INT8U  KeypadReadPort (void)
{
    INT8S  row; 
    INT8U  col;
    INT8U  input;
    INT8U  key_pressed;
                                           
         
    key_pressed = 0;   										            /* Keep track of which key is  currently being scanned.     */
    
    for (row = 0; row < 4; row++) {                                     /* Start scanning from row 0.                               */
        PORTA   =   KEYPAD_OUT_MASK;                                    /* Initialize all rows to non-active (set HIGH).            */
        PORTA  &= ~(KEYPAD_ROW_0 << row);                               /* Clear the pin of the desired row to scan.                */
        for (col = 0; col < 4; col++) {                                 /* Scan the columns from left to right.                     */
            input = (PORTA & KEYPAD_IN_MASK);                           /* Read PORTA and ignore the value of the output pins       */
            if ((input & (1 << col)) == 0) {                            /* If a col bit is found low, then the key is pressed       */
                return (key_pressed);                                   /* Return the position of the key being pressed (0-15)      */
            }
            key_pressed++;                                              /* If no key was pressed, increment the next key position   */
        }         
    }
    
    key_pressed = 0xFF;                                                 /* If scan is complete and no keys are pressed, return 0xFF */
    return (key_pressed);                                               /* Return 0xFF indicating that no key was pressed           */
}


