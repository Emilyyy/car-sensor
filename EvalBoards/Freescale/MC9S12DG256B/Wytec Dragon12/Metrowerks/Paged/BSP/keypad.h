#ifndef KEYPAD_BSP_H
#define KEYPAD_BSP_H

/*
*********************************************************************************************************
*                        Wytec Dragon12 Board Support Package
* File : keypad.h
*
* By   : Eric Shufro
*
* Notes: This file provides hardware interface functions for the Wytec Dragon12 EVB
*        4x4, 16 digit Keypad.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        PROTOTYPES
*********************************************************************************************************
*/

void   KeypadInitPort(void);
INT8U  KeypadReadPort(void);


#endif


