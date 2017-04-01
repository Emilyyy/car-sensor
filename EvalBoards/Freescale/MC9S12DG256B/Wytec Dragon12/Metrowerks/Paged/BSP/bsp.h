#ifndef BSP_H
#define BSP_H

/*
*********************************************************************************************************
*                        Wytec Dragon12 Board Support Package
* File    : bsp.h
* By      : Eric Shufro
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void     BSP_Init(void);

void     LED_Off(INT8U led);
void     LED_On(INT8U led);
void     LED_Toggle(INT8U led);
void     BSP_DlyMS(INT8U ms);

INT32U   BSP_CPU_ClkFreq(void);


/*
*********************************************************************************************************
*                                         PROCESSOR SPECIFICS
*********************************************************************************************************
*/

/*-----------------------------------------------------*/
/*                   OS TICKER SETUP                   */
/*-----------------------------------------------------*/                    
								   
#define  OS_TICK_OC                  7        /* ECT Output Compare channel # used to generate OS Tick   */
                                              /* Must be configured between 0-7 depending on derivative  */
                                              
/*-----------------------------------------------------*/
/*                   SYSTEM CLOCK SETUP                */
/*-----------------------------------------------------*/                    

#define  OSCFREQ               8000000L	      /* Define the system crystal (oscillator) frequency.       */                                             

#define  PLL_EN                      1        /* Select whether the PLL should be enabled. 0=No, 1=Yes.  */

#define  PLL_CLK_MUL                 2        /* PLL Multiplier. Setting 0 has value of 1 and so forth.  */
                                              /* PLL Freq = (OSCFREQ * 2) * MUL / DIV.                   */

#define  PLL_CLK_DIV                 0        /* Set PLL Divider. Can be 0-15. Setting 0 has value = 1.  */
	
	                                          /* Using MUL = 2, DIV = 1, we have:                        */
	                                          /* PLL Freq  =  (8MHz * 2) * (MUL + 1) / (DIV + 1)         */
	                                          /* PLL Freg  =  16MHz * 3 / 1 = 48MHz CPU, 24MHz BUS.      */
		                                              
#if PLL_EN == 0                              
#define  SYSCLK                OSCFREQ	      /* If PLL disabled, then SYSCLOCK = OSCCLK                 */ 
#define  BUS_CLK_FREQ         (SYSCLK  / 2)   /* BUSCLK = SYSCLK / 2                                     */
#else				    
#define  PLLCLK              ((OSCFREQ * 2) * (PLL_CLK_MUL + 1) / (PLL_CLK_DIV + 1))	     
#define  BUS_CLK_FREQ         (PLLCLK  / 2)   /* BUSCLK = PLLCLK / 2                                     */
#endif


/*
*********************************************************************************************************
*                                      CONFIGURATION CHECKING
*********************************************************************************************************
*/

#ifndef PLL_EN 
#error "PLL_EN must be defined in bsp.h. 0 = PLL Disabled, 1 = PLL Enabled"
#endif

#if PLL_EN == 1
#ifndef PLL_CLK_MUL
#error "PLL_CLK_MUL must be defined in bsp.h."
#endif
#ifndef PLL_CLK_DIV
#error "PLL_CLK_DIV must be defined in bsp.h."
#endif
#if     PLL_CLK_MUL > 63
#error "PLL_CLK_MUL must must have a value between 0 and 63"
#endif
#if     PLL_CLK_DIV > 15
#error "PLL_CLK_DIV must have a value between 0 and 15"
#endif
#endif

#ifndef OSCFREQ 
#error "OSCFREQ must be defined in bsp.h"
#endif

#ifndef BUS_CLK_FREQ  
#error "BUS_CLK_FREQ must be defined in bsp.h."
#endif

#if     BUS_CLK_FREQ > 25000000L 
#error "BUS_CLK_FREQ configuration error in bsp.h (WARNING: BUS_CLK_FREQ > 25 MHZ!)"
#endif

#if    (OS_TICK_OC < 0) && (OS_TICK_OC > 7)
#error "OS_TICK_OC is illegally defined in bsp.h. Expected valued between 0-7."
#endif


#endif


