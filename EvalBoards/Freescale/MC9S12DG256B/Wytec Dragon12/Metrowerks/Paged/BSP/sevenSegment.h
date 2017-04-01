#ifndef SEVEN_SEG_BSP_H
#define SEVEN_SEG_BSP_H

/*
*********************************************************************************************************
*                        Wytec Dragon12 Board Support Package
*
* File : SevenSegDisp_BSP.h
* By   : Eric Shufro
*
* Notes: This file contains function prototypes for initializing and user the four, 7-Segment
*        LED blocks on the Wytec Dragon12 EVB.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        PROTOTYPES
*********************************************************************************************************
*/

void  SevenSegDisp_Init(void);
void  SevenSegWrite(INT16U num);
void  SevenSegDisp_ISR_Handler(void);


#endif


