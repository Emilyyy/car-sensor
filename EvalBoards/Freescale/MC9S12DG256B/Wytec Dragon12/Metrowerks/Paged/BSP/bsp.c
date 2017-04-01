/*
*********************************************************************************************************
*                               Wytec Dragon12 Board Support Package 
*
*                                       Freescale MC9S12DP256
*
* File       : bsp.c
* By         : Eric Shufro
*
* Description: Provides low level hardware functions for use with portable application code
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
*                                       REGISTERS 
*
* Registers that are not included in the processor header file may be defind here
*********************************************************************************************************
*/

#ifndef  BDMSTS
#define  BDMSTS                (*((INT8U *)0xFF01))                     /* Cast a pointer to the BDM Status register                */
#define  BDMSTS_CLKSW_MASK                     (4)						/* Bit mask for the CLKSW bit in the BDMSTS register        */
#endif


/*
*********************************************************************************************************
*                                 CHARACTER LCD CONSTANT DATA
*
* Notes       : 1) RW is permanently pulled LOW in hardware. Under normal circumstances, 
*                  it too should be declared below and referenced in the LCD Write functions
*                  below.
*********************************************************************************************************
*/

#define  LCD_LOWEST_DATA_BIT                 (INT8U)(2)   		        /* Bit two is the lowest order data bit                     */
#define  LCD_BIT_RS                          (INT8U)(1 <<  0)		    /* LCD Screen bit RS maps to PORTK, bit 0                   */   
#define  LCD_BIT_E                           (INT8U)(1 <<  1)           /* LCD Screen bit EN maps to PORTK, bit 1                   */   
#define  LCD_BIT_DATA0                       (INT8U)(1 <<  2)           /* LCD Screen bit D4 maps to PORTK, bit 2                   */   
#define  LCD_BIT_DATA1                       (INT8U)(1 <<  3)           /* LCD Screen bit D5 maps to PORTK, bit 3                   */   
#define  LCD_BIT_DATA2                       (INT8U)(1 <<  4)			/* LCD Screen bit D6 maps to PORTK, bit 4                   */   
#define  LCD_BIT_DATA3                       (INT8U)(1 <<  5)    	    /* LCD Screen bit D7 maps to PORTK, bit 5                   */


/*
*********************************************************************************************************
*                                         GLOBALS
*********************************************************************************************************
*/

static  INT16U  OSTickCnts;			                                    /* Holds the number of timer increments for the OS Ticker   */  


/*
*********************************************************************************************************
*                                        PROTOTYPES
*********************************************************************************************************
*/

static  void     PLL_Init(void);                                        /* Initialize the CPU's PLL                                 */
static  void     OSTickISR_Init(void);                                  /* Initialize the OS Ticker                                 */
static  void     LED_Init(void);                                        /* Initialize the LED hardware                              */
static  void     Sw_Init(void);                                         /* Initialize Switch hardware                               */
static  void     BSP_SetECT_Prescaler(INT8U prescaler);                 /* Initialize the ECT Prescaler                             */


/*
*********************************************************************************************************
*                                        BSP_Init()
*
* Description: Initialize BSP, called from app.c instead of calling all of the internal bsp init functions
*              seperately, they are grouped together here.
*********************************************************************************************************
*/

void BSP_Init (void)
{
#if PLL_EN > 0
    PLL_Init();                                                         /* Initialize the PLL. This must come before CalcPrescaler  */
    BSP_SetECT_Prescaler(4);                                            /* When using the PLL, an ECT prescaler > 4 MUST be set in  */    
#endif                                                                  /* order to prevent OSTickCnts overflow during Tick Init    */ 
    
    OSTickISR_Init();
    LED_Init();   
}


/*
*********************************************************************************************************
*                                        PLL_Init()
*
* Notes: Will HANG the application if PLL fails to initialize!
*********************************************************************************************************
*/

static void PLL_Init (void)
{  
    BDMSTS |=   BDMSTS_CLKSW_MASK;                                      /* Avoid MC9S12DP256B BDM Looses Sync errata when PLL on    */
                                                                        /* This errata can be avoided by not using a const clk src  */
    
    CLKSEL  = 0x00;                                                     /* Meaning for CLKSEL:
                                                                            Bit 7: PLLSEL = 0 Use OSCCLK until ready to switch to PLLCLK
                                                                            Bit 6: PSTP   = 0 Do not need to go to Pseudo-Stop Mode
                                                                            Bit 5: SYSWAI = 0 In wait mode system clocks stop.
                                                                            Bit 4: ROAWAI = 0 Do not reduce oscillator amplitude in wait mode.
                                                                            Bit 3: PLLWAI = 0 Do not turn off PLL in wait mode
                                                                            Bit 2: CWAI	= 0 Do not stop the core during wait mode
                                                                            Bit 1: RTIWAI = 0 Do not stop the RTI in wait mode
                                                                            Bit 0: COPWAI = 0 Do not stop the COP in wait mode
                                                                        */  

 
    SYNR    = PLL_CLK_MUL;                                              /* Set the desired clock multiplier                         */
    REFDV   = PLL_CLK_DIV;                                              /* Set the desired clock divider                            */

 
    PLLCTL  = 0xC0;                                                     /* Meaning for PLLCTL:
                                                                            Bit 7: CME   = 1; Clock monitor enable
                                                                            Bit 6: PLLON = 1; PLL On bit
                                                                            Bit 5: AUTO  = 0; No automatic control of bandwidth, manual through ACQ
                                                                            Bit 4: ACQ   = 1; 1 for high bandwidth filter (acquisition); 0 for low (tracking)
                                                                            Bit 3:            (Not Used by MC9S12C32)
                                                                            Bit 2: PRE   = 0; RTI stops during Pseudo Stop Mode
                                                                            Bit 1: PCE   = 0; COP diabled during Pseudo STOP mode
                                                                            Bit 0: SCME  = 1; Crystal Clock Failure -> Use Self Clock mode.                                                  
                                                                        */
  
    while((CRGFLG & 0x08) == 0) { 	                                    /* Wait for PLLCLK to stabilize.                            */
        ;				                                                /* If the PLL never stabilizes, this will hang forever      */
    }  
  
    CLKSEL_PLLSEL = 1;                                                  /* Switch to PLL clock                                      */
}


/*
*********************************************************************************************************
*                                        BSP_CPU_ClkFreq()
*
* Description : Returns the CPU operating frequency. (This is NOT the CPU BUS frequency)
*               However, the bus frequency is (clk_frq / 2)
*********************************************************************************************************
*/

INT32U  BSP_CPU_ClkFreq (void)
{
    INT32U clk_frq;
    
    
    if ((CLKSEL & CLKSEL_PLLSEL_MASK) == CLKSEL_PLLSEL_MASK) {
        clk_frq = ((OSCFREQ * 2) * (PLL_CLK_MUL + 1) / (PLL_CLK_DIV + 1));
    } else {
        clk_frq =  (OSCFREQ);
    }
        
    return clk_frq;        
}


/*
*********************************************************************************************************
*                             LED Init (Modify to init appropriate LED Port)
*
* Description : Initialize the data direction registers for any ports that have LEDs attached.
*********************************************************************************************************
*/

void LED_Init (void)
{
    DDRB |=  0xFF;                                                      /* Set the LED pins to output mode                          */
    DDRJ |=  (1 << 1);                                                  /* PTJ Pin1 Controls the LED selection, set for output      */
    PTJ  &= ~(1 << 1);                                                  /* Clear PTJ Pin1 to enable the onboard LED's               */
}


/*
*********************************************************************************************************
*                                        LED Toggle (Using PORTB)
*
* Description : Toggle an LED Pin
*********************************************************************************************************
*/

void LED_Toggle (INT8U led)
{
    if (led <= 7) {
        DDRJ |=  (1 << 1);                                              /* PTJ Pin1 Controls the LED selection, set for output      */
        PTJ  &= ~(1 << 1);                                              /* Clear PTJ Pin1 to enable the onboard LED's               */    
        PORTB ^= (1 << led);					      
    }
}


/*
*********************************************************************************************************
*                                        LED Off (Using PORTB)
*
* Description : Turn off an LED
*********************************************************************************************************
*/

void  LED_Off (INT8U led)
{
    if (led <= 7) {
        DDRJ |=  (1 << 1);                                              /* PTJ Pin1 Controls the LED selection, set for output      */
        PTJ  &= ~(1 << 1);                                              /* Clear PTJ Pin1 to enable the onboard LED's               */
        PORTB &= ~(1 << led);
    }
}


/*
*********************************************************************************************************
*                                        LED On (Using PORTB)
*
* Description : Turn On an LED
*********************************************************************************************************
*/

void  LED_On (INT8U led)
{
    if (led <= 7) {
        DDRJ |=  (1 << 1);                                              /* PTJ Pin1 Controls the LED selection, set for output      */
        PTJ  &= ~(1 << 1);                                              /* Clear PTJ Pin1 to enable the onboard LED's               */
        PORTB |= (1 << led);
    }
}


/*
*********************************************************************************************************
*                                 BSP OS TIME DELAY (Milliseconds)
*
* Description : This function provides uC/OS-II Time Delays (0-255 ms) to portable application code
*********************************************************************************************************
*/

void  BSP_DlyMS (INT8U ms)
{
    OSTimeDlyHMSM (0, 0, 0, ms);    
}


/*
*********************************************************************************************************
*                                     uC/OS-II TICK ISR INITIALIZATION
*
* Description : This function is used to initialize one of the eight output compares to generate an
*               interrupt at the desired tick rate.  You must decide which output compare you will be
*               using by setting the configuration variable OS_TICK_OC (see OS_CFG.H and also OS_CPU_A.S) 
*               to 0..7 depending on which output compare to use.
*                   OS_TICK_OC set to 0 chooses output compare #0 as the ticker source
*                   OS_TICK_OC set to 1 chooses output compare #1 as the ticker source
*                   OS_TICK_OC set to 2 chooses output compare #2 as the ticker source
*                   OS_TICK_OC set to 3 chooses output compare #3 as the ticker source
*                   OS_TICK_OC set to 4 chooses output compare #4 as the ticker source
*                   OS_TICK_OC set to 5 chooses output compare #5 as the ticker source
*                   OS_TICK_OC set to 6 chooses output compare #6 as the ticker source
*                   OS_TICK_OC set to 7 chooses output compare #7 as the ticker source
*
* Arguments   : None
*********************************************************************************************************
*/

static void  OSTickISR_Init (void)
{
    INT32U cpu_frq;
    INT32U bus_frq;
    INT8U  ECT_Prescaler;    


    cpu_frq = BSP_CPU_ClkFreq();                                        /* Get the current CPU frequency                            */
    bus_frq = cpu_frq / 2;                                              /* Derive the BUS frequency from the CPU frequency          */
      
    ECT_Prescaler = TSCR2 & 0x07;                                       /* Get the prescaler value in the control register          */
    
    ECT_Prescaler = (1 << ECT_Prescaler);                               /* Calculate the correct prescaler value from the reg val   */
    
                                                                        /* Calculate the nbr of ticks for the interrupt period      */ 
    OSTickCnts    = (INT16U)((bus_frq / (ECT_Prescaler * OS_TICKS_PER_SEC)) - 1); 
  
#if OS_TICK_OC == 0
    TIOS  |= 0x01;                                                      /* Make channel an output compare                           */
    TC0    = TCNT + OSTickCnts;                                         /* Set TC0 to present time + OS_TICK_OC_CNTS                */
    TIE |= 0x01;                                                        /* Enable OC4 interrupt.                                    */
#endif

#if OS_TICK_OC == 1
    TIOS  |= 0x02;                                                      /* Make channel an output compare                           */
    TC1    = TCNT + OSTickCnts;                                         /* Set TC1 to present time + OS_TICK_OC_CNTS                */
    TIE |= 0x02;                                                        /* Enable OC4 interrupt.                                    */
#endif

#if OS_TICK_OC == 2
    TIOS  |= 0x04;                                                      /* Make channel an output compare                           */
    TC2    = TCNT + OSTickCnts;                                         /* Set TC2 to present time + OS_TICK_OC_CNTS                */
    TIE |= 0x04;                                                        /* Enable OC4 interrupt.                                    */
#endif

#if OS_TICK_OC == 3
    TIOS  |= 0x08;                                                      /* Make channel an output compare                           */
    TC3    = TCNT + OSTickCnts;                                         /* Set TC3 to present time + OS_TICK_OC_CNTS                */
    TIE |= 0x08;                                                        /* Enable OC4 interrupt.                                    */
#endif

#if OS_TICK_OC == 4
    TIOS  |= 0x10;                                                      /* Make channel an output compare                           */
    TC4    = TCNT + OSTickCnts;                                         /* Set TC4 to present time + OS_TICK_OC_CNTS                */
    TIE |= 0x10;                                                        /* Enable OC4 interrupt.                                    */
#endif

#if OS_TICK_OC == 5
    TIOS  |= 0x20;                                                      /* Make channel an output compare                           */
    TC5    = TCNT + OSTickCnts;                                         /* Set TC5 to present time + OS_TICK_OC_CNTS                */
    TIE |= 0x20;                                                        /* Enable OC5 interrupt.                                    */
#endif

#if OS_TICK_OC == 6
    TIOS  |= 0x40;                                                      /* Make channel an output compare                           */
    TC6    = TCNT + OSTickCnts;                                         /* Set TC6 to present time + OS_TICK_OC_CNTS                */
    TIE |= 0x40;                                                        /* Enable OC6 interrupt.                                    */
#endif

#if OS_TICK_OC == 7
    TIOS  |= 0x80;                                                      /* Make channel an output compare                           */
    TC7    = TCNT + OSTickCnts;                                         /* Set TC7 to present time + OS_TICK_OC_CNTS                */
    TIE |= 0x80;                                                        /* Enable OC7 interrupt.                                    */
#endif

    TSCR1 = 0xC0;                                                       /* Enable counter & disable counter in background mode      */
}


/*
*********************************************************************************************************
*                                      uC/OS-II TICK ISR HANDLER
*
* Description : This function is called by OSTickISR() (located in the OS_CPU_C.C)
*               when a tick interrupt occurs.
*
* Arguments   : none
*********************************************************************************************************
*/

void  OSTickISR_Handler (void)
{
#if OS_TICK_OC == 0
    TFLG1 |= 0x01;                                                      /* Clear interrupt                                          */
    TC0   += OSTickCnts;                                                /* Set TC0 to present time + OS_TICK_OC_CNTS                */
#endif

#if OS_TICK_OC == 1 
    TFLG1 |= 0x02;                                                      /* Clear interrupt                                          */
    TC1   += OSTickCnts;                                                /* Set TC1 to present time + OS_TICK_OC_CNTS                */
#endif

#if OS_TICK_OC == 2
    TFLG1 |= 0x04;                                                      /* Clear interrupt                                          */
    TC2   += OSTickCnts;                                                /* Set TC2 to present time + OS_TICK_OC_CNTS                */
#endif

#if OS_TICK_OC == 3
    TFLG1 |= 0x08;                                                      /* Clear interrupt                                          */
    TC3   += OSTickCnts;                                                /* Set TC3 to present time + OS_TICK_OC_CNTS                */
#endif

#if OS_TICK_OC == 4
    TFLG1 |= 0x10;                                                      /* Clear interrupt                                          */
    TC4   += OSTickCnts;                                                /* Set TC4 to present time + OS_TICK_OC_CNTS                */
#endif

#if OS_TICK_OC == 5
    TFLG1 |= 0x20;                                                      /* Clear interrupt                                          */
    TC5   += OSTickCnts;                                                /* Set TC5 to present time + OS_TICK_OC_CNTS                */
#endif

#if OS_TICK_OC == 6
    TFLG1 |= 0x40;                                                      /* Clear interrupt                                          */
    TC6   += OSTickCnts;                                                /* Set TC6 to present time + OS_TICK_OC_CNTS                */
#endif

#if OS_TICK_OC == 7
    TFLG1 |= 0x80;                                                      /* Clear interrupt                                          */
    TC7   += OSTickCnts;                                                /* Set TC7 to present time + OS_TICK_OC_CNTS                */
#endif

    OSTimeTick();                                                       /* Inform the OS about the Time Tick                        */
}


/*
*********************************************************************************************************
*                                 Set the ECT Prescaler
*
* Description : This function configures the ECT prescaler during SYSTEM initialization.
*
* Callers     : BSP_Init()
*
* Notes       : This function should be called during system init, ideally fro BSP_Init().
*               Changing the Prescaler during run-time could impact several modules. Be
*               sure to use extreme caution when calling this function.
*********************************************************************************************************
*/

static  void  BSP_SetECT_Prescaler (INT8U prescaler)
{
    TSCR2 &= ~TSCR2_PR_MASK;                                            /* Clear all prescaler bits                                 */
    
    switch (prescaler) {
        case 1:
             TSCR2 &= ~TSCR2_PR_MASK;                                   /* Set a prescaler of 1                                     */
             break;

        case   2:
             TSCR2 |= 0x01;                                             /* Set a prescaler of 2                                     */        
             break;

        case   4:
             TSCR2 |= 0x02;                                             /* Set a prescaler of 4                                     */        
             break;

        case   8:
             TSCR2 |= 0x03;                                             /* Set a prescaler of 8                                     */        
             break;

        case  16:
             TSCR2 |= 0x04;                                             /* Set a prescaler of 16                                    */        
             break;

        case  32:
             TSCR2 |= 0x05;                                             /* Set a prescaler of 32                                    */        
             break;

        case  64:
             TSCR2 |= 0x06;                                             /* Set a prescaler of 64                                    */        
             break;

        case 128:
             TSCR2 |= 0x07;                                             /* Set a prescaler of 128                                   */        
             break;

        default:
             TSCR2 |= 0x02;                                             /* Set a prescaler of 4 if the passed value is invalid      */        
             break;             
             
    }
}


/*
*********************************************************************************************************
*                                 uC/LCD Display Hardware Initialization
*
* Description : DispInitPort() is responsible for initializing the hardware used to interface with the 
*               LCD module. DispInitPort() is called by DispInit().
*
* Arguments   : None
*
* Callers     : DispInit() from lcd.c
*
* Notes       : 1) RW is permanently pulled LOW in hardware. Under normal circumstances, it too would 
*                  have to be configured as an output pin.
*********************************************************************************************************
*/
#if (uC_LCD_MODULE > 0)
void DispInitPort (void)
{                                                                       
    DDRK |= LCD_BIT_RS    | LCD_BIT_E     | LCD_BIT_DATA0 |             /* Setup RS, E and Data bit 0 lines as outputs              */
            LCD_BIT_DATA1 | LCD_BIT_DATA2 | LCD_BIT_DATA3;				/* Setup the Data Lines 1, 2, 3 as outputs                  */
}
#endif


/*
*********************************************************************************************************
*                                 uC/LCD Display Register Select
*
* Description : DispSel() determines whether data written to the HD44780 goes to the control or data 
*               register.
*
* Arguments   : sel determines whether data written using DispDataWr() goes to the command register 
*               (when sel == DISP_SEL_CMD_REG) or the data register (when sel == DISP_SEL_DATA_REG).
*
* Callers     : Various from lcd.c
*********************************************************************************************************
*/
#if (uC_LCD_MODULE > 0)
void DispSel (INT8U sel)
{
    if (sel == DISP_SEL_CMD_REG) {
        PORTK &= ~LCD_BIT_RS;                                           /* Set the RS control line LOW                              */
    } else {
        PORTK |=  LCD_BIT_RS;                                           /* Set the RS control line HIGH                             */
    } 
}
#endif


/*
*********************************************************************************************************
*                                 uC/LCD Display Data Write
*
* Description : DispDataWr() is used to write a single byte to the LCD module. Depending on the state 
*               of the RS line, the byte will be either sent to the data (RS is 1) or control register 
*               (RS is 0) of the LCD controller.
*
* Arguments   : data is the byte value to write to the LCD controller module. The destination ‘inside’ 
*               the HD44780 or compatible controller depends on whether RS is high or low.
*
* Callers     : Various from lcd.c
*
* Notes       : 1) RS is determined prior to this function call. Therefore, software must
*                  not overwrite the current state of this bit.
*               2) RW is permanently pulled LOW in hardware
*********************************************************************************************************
*/
#if (uC_LCD_MODULE > 0)
void DispDataWr (INT8U data)
{ 
    PORTK &=    LCD_BIT_RS;                                             /* Clear all PORTK data bits, RW = 0, preserve RS           */
    PORTK |= (((data >> 4) & 0x0F) << LCD_LOWEST_DATA_BIT);             /* Write the UPPER nibble of ‘data’ to D7..D4               */ 
    PORTK |=    LCD_BIT_E;                                              /* Set the E control line HIGH                              */
    DispDly_uS(100);                                                    /* Delay for about 100 uS                                   */
    PORTK &=   ~LCD_BIT_E;                                              /* Set the E control line LOW                               */
    DispDly_uS(100);                                                    /* Delay for about 100 uS                                   */
    PORTK &=    LCD_BIT_RS;                                             /* Clear all PORTK data bits, RW = 0, preserve RS           */
    PORTK |=  ((data & 0x0F)       << LCD_LOWEST_DATA_BIT);             /* Write the LOWER nibble of ‘data’ to D7..D4               */
    PORTK |=    LCD_BIT_E;                                              /* Set the E control line HIGH                              */
    DispDly_uS(100);                                                    /* Delay for about 100 uS                                   */    
    PORTK &=   ~LCD_BIT_E;                                              /* Set the E control line LOW                               */
}
#endif


/*
*********************************************************************************************************
*                                 uC/LCD Display Data Write
*
* Description : DispDataWrOneNibble() is used to write a single 4-bit value to the LCD module. 
*               Depending on the state of the RS line, the byte will be either sent to the 
8               data (RS is 1) or control register (RS is 0) of the LCD controller.
*
* Arguments   : data is the 4-bit value to write to the LCD controller module. The destination ‘inside’ 
*               the HD44780 or compatible controller depends on whether RS is high or low.
*
* Callers     : DispInit() from lcd.c
*
* Notes       : 1) RS is determined prior to this function call. Therefore, software must
*                  not overwrite the current state of this bit.
*               2) RW is permanently pulled LOW in hardware
*********************************************************************************************************
*/
#if (uC_LCD_MODULE > 0)
void  DispDataWrOneNibble (INT8U data) 
{
    PORTK &=    LCD_BIT_RS;                                             /* Clear all PORTK data bits, RW = 0, preserve RS           */
    PORTK |= (((data >> 4) & 0x0F) << LCD_LOWEST_DATA_BIT);             /* Write the UPPER nibble of ‘data’ to D7..D4               */     
    PORTK |=    LCD_BIT_E;                                              /* Set the E control line HIGH                              */        
    DispDly_uS(100);                                                    /* Delay for about 100 uS                                   */    
    PORTK &=   ~LCD_BIT_E;                                              /* Set the E control line LOW                               */            
}
#endif


/*
*********************************************************************************************************
*                                 uC/LCD Delay Functionality
*
* Description : DispDly_uS() allows the code to delay for the execution for a certain amount of time to 
*               allow the data to ‘stabilize’ and for the HD44780 to complete it’s operation. The delay 
*               is specified in microseconds (uS). This operation is easy to perform if you have a 
*               real-time kernel such as uC/OS-II.
*
* Arguments   : us determines the amount of delay (in microseconds)
*
* Callers     : lcd.c: DispInit(), DispClrScr()
*********************************************************************************************************
*/
#if (uC_LCD_MODULE > 0)
void DispDly_uS (INT32U us)
{
    INT32U  us_per_tick;
    INT32U  ticks;
							

    us_per_tick =  1000000L / OS_TICKS_PER_SEC;
    ticks       =  us / us_per_tick + 1;
    OSTimeDly(ticks); 
}
#endif


/*
*********************************************************************************************************
*                                   OSProbe_TmrInit()
*
* Description : This function is called to by uC/Probe Plug-In for uC/OS-II to initialize the
*               free running timer that is used to make time measurements.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

#if (uC_PROBE_OS_PLUGIN > 0) && (OS_PROBE_HOOKS_EN == 1)
void  OSProbe_TmrInit (void)
{
}
#endif

/*
*********************************************************************************************************
*                                   OSProbe_TmrRd()
*
* Description : This function is called to read the current counts of a 16 bit free running timer.
*
* Arguments   : none
*
* Returns     ; The 16 bit count (in a 32 bit variable) of the timer assuming the timer is an UP counter.
*********************************************************************************************************
*/

#if (uC_PROBE_OS_PLUGIN > 0) && (OS_PROBE_HOOKS_EN == 1)
CPU_INT32U  OSProbe_TmrRd (void)
{
    return (TCNT);                                                      /* Return the current timer value                           */
}
#endif





