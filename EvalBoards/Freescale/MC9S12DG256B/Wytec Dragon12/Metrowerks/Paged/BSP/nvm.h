#ifndef  NVM_H
#define  NVM_H

/*
*********************************************************************************************************
*                               Freescale MC9S12 Processor Support
*   
*                                Non Volatile Memory Read / Write
*
* File       : nvm.h
*
* By         : GeorgeWong
*            : Eric Shufro
*
* Rev. Hist. : 08/12/2005 - Created
*              08/25/2005 - EEPROM_Erase_Sector
*                           Flash_Erase_Block
*              09/17/2006 - Cleaned up
*
* Description: Provides low level hardware functions for use with portable application code
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       CONSTANTS
*********************************************************************************************************
*/

#define  NVM_NO_ERR                (1)
#define  NVM_ODD_ACCESS_ERR       (-1)
#define  NVM_ACCESS_ERR           (-2)
#define  NVM_PROTECTION_ERR       (-3)

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void    EEPROM_Init(INT32U sysclk);
INT8S   EEPROM_Write_Word(INT16U address, INT16U data);
INT8S   EEPROM_Erase_Sector(INT16U address);
INT16U  EEPROM_Read_Word(INT16U address);

void    Flash_Init(INT32U sysclk);
INT8S   Flash_Write_Word(INT8U ppage, INT16U address, INT16U data);
INT8S   Flash_Erase_Block(INT8U block);
INT16U  Flash_Read_Word(INT8U ppage, INT16U address);



#endif                                                                  /* End of file                                              */


