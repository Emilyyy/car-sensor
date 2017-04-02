/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                         (c) Copyright 1998-2003, Jean J. Labrosse, Weston, FL
*                                          All Rights Reserved
*
*                                          Sample code
*                                          MC9S12DP256B 
*                                       Wytec Dragon12 EVB
*
* File : app.c
* By   : Eric Shufro
*********************************************************************************************************
*/

#include    <includes.h>
#define MY_LCD_TASK_STK_SIZE 1000



/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                CONSTANTS
*********************************************************************************************************
*/
   
   
/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

    OS_STK        AppStartTaskStk[APP_TASK_START_STK_SIZE];
    OS_STK        LCD_TestTaskStk[LCD_TASK_STK_SIZE];
  
     
  


/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppStartTask(void *p_arg);
static  void  AppTaskCreate(void);
static  void  change_LCD(void *p_arg);
static unsigned int get_ir_range(unsigned int atd_result);
static void atd_init(void);
static void pwm_init(void);

#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
extern  void  AppProbeInit(void);
#endif



/*Converts values from ATD and returns range in centimeters*/
static unsigned int get_ir_range(unsigned int atd_result)
{
	int range = 0 ; //range is in cm

	if (atd_result >= 519) {  range = 10;  }
	else if (atd_result >= 483) {  range = 11;  }
        else if (atd_result >= 447) {  range = 12;  }
        else if (atd_result >= 418) {  range = 13;  }
        else if (atd_result >= 390) {  range = 14; }
        else if (atd_result >= 369) {  range = 15;  }
        else if (atd_result >= 348) {  range = 16; }  
        else if (atd_result >= 331) {  range = 17;  }
        else if (atd_result >= 315) {  range = 18; }  
        else if (atd_result >= 299) {  range = 19;  }
        else if (atd_result >= 284) {  range = 20; }
        else if (atd_result >= 271) {  range = 21;  }
        else if (atd_result >= 259) {  range = 22; }
        else if (atd_result >= 253) {  range = 23;  }
        else if (atd_result >= 247) {  range = 24; }
        else if (atd_result >= 237) {  range = 25;  }
        else if (atd_result >= 227) {  range = 26; }  
        else if (atd_result >= 218) {  range = 27;  }
        else if (atd_result >= 210) {  range = 28; }  
        else if (atd_result >= 203) {  range = 29; }
        else if (atd_result >= 197) {  range = 30; }
        else if (atd_result >= 192) {  range = 31; }
        else if (atd_result >= 187) {  range = 32; }
        else if (atd_result >= 182) {  range = 33; }
        else if (atd_result >= 178) {  range = 34; }
        else if (atd_result >= 171) {  range = 35; }
 	else if (atd_result >= 165) {  range = 36; }
 	else if (atd_result >= 161) {  range = 38; }
 	else if (atd_result >= 152) {  range = 40; }
 	else if (atd_result >= 149) {  range = 42; }
 	else if (atd_result >= 133) {  range = 44; }
 	else if (atd_result >= 134) {  range = 46; }
 	else if (atd_result >= 132) {  range = 48; }
 	else if (atd_result >= 124) {  range = 50; }
 	else if (atd_result >= 118) {  range = 52; }
 	else if (atd_result >= 115) {  range = 54; }
 	else if (atd_result >= 106) {  range = 56; }	 
	else if (atd_result >= 104) {  range = 58; }
 	else if (atd_result >= 107) {  range = 60; }
 	else if (atd_result >= 102) {  range = 62; }
 	else if (atd_result >= 101) {  range = 64; }
 	else if (atd_result >= 98) {  range = 66; }
 	else if (atd_result >= 94) {  range = 68; }
 	else if (atd_result >= 86) {  range = 70; }
 	else if (atd_result >= 83) {  range = 72; }
 	else if (atd_result >= 82) {  range = 74; }
 	else if (atd_result >= 86) {  range = 76; }
 	else if (atd_result >= 84) {  range = 78; }
 	else if (atd_result >= 82) {  range = 80; }
 	
	
	return range;
}


////////////////////////////////////////////////////

//get_ir_range_and_change_servo_motor_accordingly(ATD0DR0); // read the IR sensor values and change the servo's position accordingly every 300 ms 



void  main (void)
{
    INT8U   err;


    OSInit();                                                           /* Initialize "uC/OS-II, The Real-Time Kernel"              */

    OSTaskCreateExt(AppStartTask,
                    (void *)0,
                    (OS_STK *)&AppStartTaskStk[APP_TASK_START_STK_SIZE - 1],
                    APP_TASK_START_PRIO,
                    APP_TASK_START_PRIO,
                    (OS_STK *)&AppStartTaskStk[0],
                    APP_TASK_START_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

    OSTaskNameSet(APP_TASK_START_PRIO, "Start Task", &err);

    OSStart();                                                          /* Start multitasking (i.e. give control to uC/OS-II)       */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
* 3) After this created from main(), it runs and initializes additional application
*                  modules and tasks. Rather than deleting the task, it is simply suspended
*                  periodically. This tasks body could be used for additional work if desired.
*********************************************************************************************************
*/

static  void  AppStartTask (void *p_arg)
{ 
   (void)p_arg;
     
    BSP_Init();                                                         /* Initialize the ticker, and other BSP related functions   */

#if OS_TASK_STAT_EN > 0
    OSStatInit();                                                       /* Start stats task                                         */
#endif

#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
    AppProbeInit();                                                     /* Initialize uC/Probe modules                              */
#endif
    
    AppTaskCreate();                                                    /* Create additional tasks using this user defined function */
    
    while (TRUE) {                                                      /* Task body, always written as an infinite loop            */
        OSTimeDlyHMSM(0, 0, 5, 0);                                      /* Delay the task                                           */
    }
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                     CREATE APPLICATION TASKS
*
* Description : This function demonstrates how to create a new application task. 
* 
* Notes:        1) Each task should be a unique function prototypes as 
*                  static  void  mytaskname (void *p_arg). 
*               2) Additionally, each task should contain an infinite loop and call at least one
*                  OS resource on each pass of the loop. An OS resource may be a call to OSTimeDly(),
*                  OSTimeDlyHMSM(), or one of the message box, semaphore or other OS handled resource.
*               3) Each task must have its own stack. Be sure that the stack is declared large
*                  enough or the entire system may crash or experience erradic results if your stack
*                  grows and overwrites other variables in memory.
*               
* Arguments   : none
* Notes       : none
*********************************************************************************************************
*/

/*Initializes the task with needed variables such as stack size, priority*/
static  void  AppTaskCreate (void)
{
    INT8U  err;

     
    OSTaskCreateExt(change_LCD,
                    (void *)0,
                    (OS_STK *)&LCD_TestTaskStk[LCD_TASK_STK_SIZE-1],
                    LCD_TEST_TASK_PRIO,
                    LCD_TEST_TASK_PRIO,
                    (OS_STK *)&LCD_TestTaskStk[0],
                    LCD_TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
                              
}


static  void  change_LCD(void *p_arg)
{    
  /*String to map to the LCD display*/
  const  CPU_INT08U  RangeStr[46][18]  = {"Range: 0cm", "Range: 1cm",                                                                          
                                         "Range: 2cm", "Range: 3cm",  
                                         "Range: 4cm", "Range: 5cm",
                                         "Range: 6cm","Range: 7cm",
                                         "Range: 8cm","Range: 9cm",
                                         "Range: 10cm","Range: 11cm",
                                         "Range: 12cm","Range: 13cm",
                                         "Range: 14cm","Range: 15cm",
                                         "Range: 16cm","Range: 17cm",
                                         "Range: 18cm","Range: 19cm",
                                         "Range: 20cm","Range: 21cm",
                                         "Range: 22cm","Range: 23cm",
                                         "Range: 24cm","Range: 25cm",
                                         "Range: 26cm","Range: 27cm",
                                         "Range: 28cm","Range: 29cm",
                                         "Range: 30cm","Range: 31cm",
                                         "Range: 32cm","Range: 33cm",
                                         "Range: 34cm","Range: 35cm",
                                         "Range: 36cm","Range: 37cm",
                                         "Range: 38cm","Range: 39cm",
                                         "Range: 40cm","Range: 41cm",
                                         "Range: 42cm","Range: 43cm",
                                         "Range: 44cm","Range: 45cm"};
  int range_cm;
  (void)p_arg;
  /*Initialize ATD and LCD Display 2-rows and 16-coloumns*/
  atd_init();
DispInit(2, 16);
range_cm = 0;
pwm_init();
PWMPRCLK=0x04; //ClockA=Fbus/2**4=24MHz/16=1.5MHz 
PWMSCLA=125; //ClockSA=1.5MHz/2x125=6000 Hz
PWMCLK=0b00100000; //ClockSA for chan 5
PWMPOL=0x20;     //high then low for polarity
PWMCAE=0x0;     //left aligned
PWMCTL=0x0;         //8-bit chan, pwm during freeze and wait

PWMDTY5=50; //50% duty cycle                        AND THIS TO GET DIFFERENT SOUND
PWMCNT5=0; //clear initial counter. This is optional
PWME=0x20;   //Enable chan 5 PWM
/*assigns portB to output*/  
  DDRB = 0xFF;  
while (DEF_TRUE) { /* All tasks bodies include an infinite loop */           

          /*Acquire range from function get_ir_range, input is ATD0DR6 because we are using channel 6 of ATD*/
          range_cm = get_ir_range(ATD0DR6);
          if (range_cm == 0) {
             DispClrLine(1);
             DispStr(1,0,"CRASH");
             PORTB=0xFF;
          }
          /*limits the IR detection range to 35cm*/
          else if(range_cm <= 80 && range_cm > 0) 
          {
              /*Displays the Range on LCD*/
              DispStr(0,0,RangeStr[range_cm]);
              OSTimeDlyHMSM(0,0,1,0);
              
              /*clears the screen to make it readable*/
              if(range_cm == 0) DispClrScr();
              /*If range is greater then 20cm then turn on motor*/
              if(range_cm >= 20) {
                DispClrLine(1);
                DispStr(1,0,"SAFE");
                PORTB=0xFF;
                PWMPER5=50; //PWM_Freq=ClockSA/100=6000Hz/100=60Hz.
                PWMCNT5=0;
              }
              /*If range is between 20 and 13 then slow down*/ 
              else if(range_cm >= 13) {
                DispClrLine(1);
                DispStr(1,0,"SLOW DOWN");
                PWMPER5=250; //PWM_Freq=ClockSA/100=6000Hz/100=60Hz. 
              }
              /*if range is less then 13cm then stop the motor*/
              else {
                DispClrLine(1);
                DispStr(1,0,"DANGEROUS");
                PORTB=0x00;
                PWMPER5=600; //PWM_Freq=ClockSA/100=6000Hz/100=60Hz.
              }
              
          } else {
                DispClrLine(1);
                DispStr(1,0,"Moving...");
                PORTB=0xFF;
          }
                

  }
}
/*Initialize Analog-to-Digital converter at PAD06*/
static void atd_init(void)
{
ATD0CTL2 = 0x80;     /* Power up A/D, no interrupts */
ATD0CTL3 = 0x00;     /* Doe eight conversions */
//ATD0CTL4 = 0x85;   /* 8-bit mode */
ATD0CTL4 = 0x05;     /* 10-bit mode */
ATD0CTL5 = 0xA6;     /* 1 0 1 0 0 1 0 0
            | | | |   \___/
            | | | |     |
           | | | |     \__ Bit 4 of Port AD --> PAD06
           | | | \________ MULT = 0 => one channel only
           | | \__________ Scan = 1 => continuous conversion
           | \____________ DSGN = 0 => unsigned
           \______________ DJM = 1 => right justified */
}

static void pwm_init(void)
{
    PWME = 0x01;    //Enable PWM channel 0
    PWMPOL = 0X01;    //Signal starts high then goes low when duty count is reached
    PWMCLK = 0x01;    //Clock for channel 0 - Select 1 for SB clock and 0 for B
                    //Output is left alligned - PWMCAE
    //Clock prescalars
    PWMPRCLK = 0x07;
    PWMSCLA = 0x06;   
    PWMPER0 = 0x84;    
}