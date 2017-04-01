/*
*********************************************************************************************************
*                        Wytec Dragon12 Board Support Package
* File : SevenSegDisp_BSP.c
* By   : Eric Shufro
*
* Notes: This file provides thread safe software support for driving the 7-Segment 
*        LED display blocks on a Wytec Dragon12.
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
*                                 7-SEGMENT DISPLAY CONSTANT DATA
*********************************************************************************************************
*/

#define  SSD_0  0x3F	                                                /* Seven segment display, character '0'                     */
#define  SSD_1  0x06                                                    /* Seven segment display, character '1'                     */  
#define  SSD_2  0x5B                                                    /* Seven segment display, character '2'                     */
#define  SSD_3  0x4F                                                    /* Seven segment display, character '3'                     */
#define  SSD_4  0x66                                                    /* Seven segment display, character '4'                     */
#define  SSD_5  0x6D                                                    /* Seven segment display, character '5'                     */
#define  SSD_6  0x7D                                                    /* Seven segment display, character '6'                     */
#define  SSD_7  0x07                                                    /* Seven segment display, character '7'                     */
#define  SSD_8  0x7F                                                    /* Seven segment display, character '8'                     */
#define  SSD_9  0x6F                                                    /* Seven segment display, character '9'                     */
#define  SSD_A  0x77                                                    /* Seven segment display, character 'A'                     */
#define  SSD_B  0x7F                                                    /* Seven segment display, character 'B'                     */
#define  SSD_C  0x39                                                    /* Seven segment display, character 'C'                     */
#define  SSD_D  0x5E                                                    /* Seven segment display, character 'D'                     */
#define  SSD_E  0x59                                                    /* Seven segment display, character 'E'                     */
#define  SSD_F  0x71                                                    /* Seven segment display, character 'F'                     */

/*
*********************************************************************************************************
*                                         GLOBALS
*********************************************************************************************************
*/

static  INT16U  nbrCnts;                                                /* Holds the number of timer increments for the 7-Seg Disp  */
static  INT16U  outputNum;                                              /* Holds the number between 0000 and 9999 to be displayed   */
static  INT8U   actBlockNum;                                            /* Holds the number of the active 7-Segment LED Block (0-3) */


/*
*********************************************************************************************************
*                                        PROTOTYPES
*********************************************************************************************************
*/

static  void     SevenSegOut(INT8U digit);                              /* Internal function for writing to the 7-Seg Disp data bus */


/*
*********************************************************************************************************
*                                        SEVEN SEGMENT DISPLAY INIT
*
* Description : This function initializes the 7-Segment Enable I/O pins as Outputs, and
*               configures one of the ECT Output Compare channels to create a periodic
*               interrupt that is used to switch the active 7-Segment LED block and
*               the corresponding number to be displayed.
*
* Arguments   : None
*
* Returns     : None
*
* Notes       : THE CORRECT ECT CHANNEL ISR VECTOR MUST BE SET WITHIN VECTORS.C. 
*               This involves plugging the right vector number with the name of
*               the ISR function below. A prototype at the top of vectors.c must
*               also be created.
*********************************************************************************************************
*/

void  SevenSegDisp_Init (void) 
{
    INT32U cpu_frq;
    INT32U bus_frq;
    INT8U  ECT_Prescaler;    


    DDRP         |= 0x0F;                                               /* Set the 7-Segment Enable I/O pins to output              */
    actBlockNum   = 0;                                                  /* Set display 0 as the first active LED display block      */

    cpu_frq = BSP_CPU_ClkFreq();                                        /* Get the current CPU frequency                            */
    bus_frq = cpu_frq / 2;                                              /* Derive the BUS frequency from the CPU frequency          */
      
    ECT_Prescaler = TSCR2 & 0x07;                                       /* Get the prescaler value in the control register          */
    ECT_Prescaler = (1 << ECT_Prescaler);                               /* Calculate the correct prescaler value from the reg val   */
    
                                                                        /* Calculate the # of ticks for an interrupt period of 1ms  */                                                                        
    nbrCnts       = (INT16U)((bus_frq / (ECT_Prescaler * 225)) - 1);    /* 225 represents 225 ticks in 1 second, each tick ~4ms     */ 

#if SEVEN_SEG_OC == 0
    TIOS  |= 0x01;                                                      /* Make channel an output compare                           */
    TC0    = TCNT + nbrCnts;                                            /* Set TC0 to present time + nbrCnts                        */
    TIE |= 0x01;                                                        /* Enable OC0 interrupt.                                    */
#endif

#if SEVEN_SEG_OC == 1
    TIOS  |= 0x02;                                                      /* Make channel an output compare                           */
    TC1    = TCNT + nbrCnts;                                            /* Set TC1 to present time + nbrCnts                        */
    TIE |= 0x02;                                                        /* Enable OC1 interrupt.                                    */
#endif

#if SEVEN_SEG_OC == 2
    TIOS  |= 0x04;                                                      /* Make channel an output compare                           */
    TC2    = TCNT + nbrCnts;                                            /* Set TC2 to present time + nbrCnts                        */
    TIE |= 0x04;                                                        /* Enable OC2 interrupt.                                    */
#endif

#if SEVEN_SEG_OC == 3
    TIOS  |= 0x08;                                                      /* Make channel an output compare                           */
    TC3    = TCNT + nbrCnts;                                            /* Set TC3 to present time + nbrCnts                        */
    TIE |= 0x08;                                                        /* Enable OC3 interrupt.                                    */
#endif

#if SEVEN_SEG_OC == 4
    TIOS  |= 0x10;                                                      /* Make channel an output compare                           */
    TC4    = TCNT + nbrCnts;                                            /* Set TC4 to present time + nbrCnts                        */
    TIE |= 0x10;                                                        /* Enable OC4 interrupt.                                    */
#endif

#if SEVEN_SEG_OC == 5
    TIOS  |= 0x20;                                                      /* Make channel an output compare                           */
    TC5    = TCNT + nbrCnts;                                            /* Set TC5 to present time + nbrCnts                        */
    TIE |= 0x20;                                                        /* Enable OC5 interrupt.                                    */
#endif

#if SEVEN_SEG_OC == 6
    TIOS  |= 0x40;                                                      /* Make channel an output compare                           */
    TC6    = TCNT + nbrCnts;                                            /* Set TC6 to present time + nbrCnts                        */
    TIE |= 0x40;                                                        /* Enable OC6 interrupt.                                    */
#endif

#if SEVEN_SEG_OC == 7
    TIOS  |= 0x80;                                                      /* Make channel an output compare                           */
    TC7    = TCNT + nbrCnts;                                            /* Set TC7 to present time + nbrCnts                        */
    TIE |= 0x80;                                                        /* Enable OC7 interrupt.                                    */
#endif

    TSCR1 = 0xC0;                                                       /* Enable counter & disable counter in background mode      */
}


/*
*********************************************************************************************************
*                                   SEVEN SEGMENT INTERRUPT SERVICE ROUTINE
*
* Description : This function is the 7-Segment LED Interrupt Service Routine. This
*               interrupt occurs periodically at the rate configured within 
*               sevenSegDisp_Init(). Each time the interrupt occurs, the active
*               LED block is changed, and the value on the 7-Segment LED data
*               bus is updated.
*
* Arguments   : None
*
* Returns     : None
*
* Notes       : THE CORRECT ECT CHANNEL ISR VECTOR MUST BE SET WITHIN VECTORS.C. 
*               This involves plugging the right vector number with the name of
*               the ISR function below. A prototype at the top of vectors.c must
*               also be created.
*********************************************************************************************************
*/

void  SevenSegDisp_ISR_Handler (void) 
{
   INT8U digits[4];
   INT8U currDispNum;
   
   
   PTP        |=   0x0F;                                                /* Shut off all 7-Segment LED blocks by removing the ground */   
   currDispNum = ((actBlockNum) % 4);                                   /* Get the number of the current LED block to display on    */
   actBlockNum++;                                                       /* Increment the display # used for the next interrupt      */
   
                                                                        /* Calculate all the digits for each display even though    */
                                                                        /* only one of these digits will be used during this ISR    */
                                                                        
   digits[0]   =  (INT8U) (outputNum / 1000);	                        /* Calculate digit 4 (most significant) 1000's place        */
   digits[1]   =  (INT8U)((outputNum % 1000) / 100);                    /* Calculate digit 3, the 100's place                       */
   digits[2]   =  (INT8U)((outputNum % 100)  / 10);                     /* Calculate digit 2, the 10's place                        */
   digits[3]   =  (INT8U) (outputNum % 10);                             /* Calculate digit 1 (lease significant) 1's place          */
      
   SevenSegOut(digits[currDispNum]);                                    /* Put the value on the 7-Segment LED data bus              */
   PTP        &= ~(1 << currDispNum);                                   /* Enable the current LED block, by supplying the ground    */
   
#if SEVEN_SEG_OC == 0
    TFLG1 |= 0x01;                                                      /* Clear interrupt                                          */
    TC0   += nbrCnts;                                                   /* Set TC0 to present time + nbrCnts                        */
#endif

#if SEVEN_SEG_OC == 1 
    TFLG1 |= 0x02;                                                      /* Clear interrupt                                          */
    TC1   += nbrCnts;                                                   /* Set TC1 to present time + nbrCnts                        */
#endif

#if SEVEN_SEG_OC == 2
    TFLG1 |= 0x04;                                                      /* Clear interrupt                                          */
    TC2   += nbrCnts;                                                   /* Set TC2 to present time + nbrCnts                        */
#endif

#if SEVEN_SEG_OC == 3
    TFLG1 |= 0x08;                                                      /* Clear interrupt                                          */
    TC3   += nbrCnts;                                                   /* Set TC3 to present time + nbrCnts                        */
#endif

#if SEVEN_SEG_OC == 4
    TFLG1 |= 0x10;                                                      /* Clear interrupt                                          */
    TC4   += nbrCnts;                                                   /* Set TC4 to present time + nbrCnts                        */
#endif

#if SEVEN_SEG_OC == 5
    TFLG1 |= 0x20;                                                      /* Clear interrupt                                          */
    TC5   += nbrCnts;                                                   /* Set TC5 to present time + nbrCnts                        */
#endif

#if SEVEN_SEG_OC == 6
    TFLG1 |= 0x40;                                                      /* Clear interrupt                                          */
    TC6   += nbrCnts;                                                   /* Set TC6 to present time + nbrCnts                        */
#endif

#if SEVEN_SEG_OC == 7
    TFLG1 |= 0x80;                                                      /* Clear interrupt                                          */
    TC7   += nbrCnts;                                                   /* Set TC7 to present time + nbrCnts                        */   
#endif    
}


/*
*********************************************************************************************************
*                                        7-Segment Display Write
*
* Description : This function puts data on PORTB, the 7-Segment LED data bus.
*********************************************************************************************************
*/

static  void  SevenSegOut (INT8U digit)
{
    PTJ |= (1 << 1);                                                    /* Shut off the other regular LED's while displaying        */
    
    switch (digit) {
        case 0:
             PORTB = SSD_0;
             break;

        case 1:
             PORTB = SSD_1;
             break;

        case 2:
             PORTB = SSD_2;
             break;

        case 3:
             PORTB = SSD_3;
             break;

        case 4:
             PORTB = SSD_4;
             break;

        case 5:
             PORTB = SSD_5;
             break;

        case 6:
             PORTB = SSD_6;
             break;

        case 7:
             PORTB = SSD_7;
             break;

        case 8:
             PORTB = SSD_8;
             break;

        case 9:
             PORTB = SSD_9;
             break;

        case 'A':
             PORTB = SSD_A;
             break;

        case 'B':
             PORTB = SSD_B;
             break;
        
        case 'C':
             PORTB = SSD_C;
             break;
        
        case 'D':
             PORTB = SSD_D;
             break;
        
        case 'E':
             PORTB = SSD_E;
             break;
        
        case 'F':
             PORTB = SSD_F;
             break;
        
        default:
             break; 
    }
}


/*
*********************************************************************************************************
*                                        Multiple 7-Seg Output
*
* Description : This function updates a global variable used to pass the desired
*               value of the digit to be displayed on the 7-Segment LEDs to the
*               SevenSegDisp_ISR. A critical section must be used to ensure exclusive
*               access to the global variable while it is being updated. This function
*               is thread safe.
*
* Notes       : This function only allows decimal numbers between 0000 and 9999 inclusive to be
*               written to the global output variable. Any number < 0 or > 9999 can not be
*               represented on four, 7-Segment LED blocks.  Ex: [9][1][2][3], 9123.
*********************************************************************************************************
*/

void  SevenSegWrite (INT16U num) 
{
    CPU_SR  cpu_sr;
    
    
    if (num <= 9999) {                                                      /* Only display numbers between 0000 and 9999 inclusive     */        
        CPU_CRITICAL_ENTER();                                               /* Lock access to the global output variable                */
        outputNum = num;                                                    /* Update the variable with the new output value            */
        CPU_CRITICAL_EXIT();                                                /* Unlock access to the global output variable              */
    }
}


