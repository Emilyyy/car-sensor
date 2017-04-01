/*
*********************************************************************************************************
*                               Freescale MC9S12 Processor Support
*   
*                                Non Volatile Memory Read / Write
*
* File       : nvm.c
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
*                                        INCLUDES
*********************************************************************************************************
*/

#include <includes.h> 

/*
*********************************************************************************************************
*                                       CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        EEPROM INITIALIZATION
*
* Description : This function initializes the Non Volatile EEPROM control registers and must be called
*               before attempting to write or erase an EEPROM sector.
*
* Arguments   : sysclk, the CPU clock frequency (SYSCLK) driven by the onboard oscillator or the 
*               PLL if enabled.
*
* Returns     : None.
*
* Notes       : 1) See bsp.c, BSP_CPU_ClkFreq(), as this function may be used to determine the SYSCLK
*                  frequency.
*********************************************************************************************************
*/

void  EEPROM_Init (INT32U sysclk)
{
    INT8U  eclk_val;
	
	
    if (sysclk >= 12000) {                                              /* If the SYSCLK is > 12MHz, then set FDIV8 bit             */          
        eclk_val  =  (sysclk  / (8*200)) - 1;                           /* Compute the correct divider value                        */
        ECLKDIV  |=   ECLKDIV_PRDIV8_MASK | eclk_val;                   /* Write the ECLKDIV register with the correct settings     */
    } else {
        eclk_val  =  (sysclk / 200) - 1;                                /* Compute the correct divider value                        */
        ECLKDIV  |=   eclk_val;                                         /* Write the ECLKDIV register with the correct settings     */
    }

    ESTAT        |=  (ESTAT_PVIOL_MASK | ESTAT_ACCERR_MASK);              /* Clear any error flags                                  */
}

/*
*********************************************************************************************************
*                                        EEPROM WRITE
*
* Description : This function writes a 16-bit word to EEPROM
*
* Arguments   : address, the destination EEPROM address to write the data
*               data,    the data to write to argument address.
*
* Returns     : NVM_NO_ERR           - EEPROM Write Success
*               NVM_ODD_ACCESS_ERR   - EEPROM Write Error, Address not on an even address boundry
*               NVM_ACCESS_ERR       - EEPROM Write Error, Access Violation
*               NVM_PROTECTION_ERR   - EEPROM Write Error, Attempted to write a protected sector
*
* Notes       : None.
*********************************************************************************************************
*/

INT8S  EEPROM_Write_Word (INT16U address, INT16U data)
{
    while (!ESTAT_CBEIF) {                                              /* Wait for EEPROM access controller to become ready        */
        ;
    }
    
    ESTAT = (ESTAT_ACCERR_MASK | ESTAT_PVIOL_MASK);                     /* Clear existing error flags                               */
    
    if (address & 0x0001) {
        return (NVM_ODD_ACCESS_ERR);                                    /* Address is NOT aligned on an even boundry?               */
    }
    
    (*(INT16U *)address) = data;                                        /* Write the data to the specified address                  */

    ECMD = ECMD_CMDB5_MASK;	                                            /* Store programming command in FCMD                        */
    ESTAT_CBEIF = 1;                                                    /* Execute the command                                      */

    if (ESTAT_ACCERR) {                                                 /* Check if there has been an access error                  */
        return (NVM_ACCESS_ERR);                                        /* Return an Access Error code                              */
    }
    
    if (ESTAT_PVIOL) {                                                  /* Check if there has been a protection error               */
        return (NVM_PROTECTION_ERR);                                    /* Return a Protection Error code                           */
    }
    
    return (NVM_NO_ERR);                                                /* Return No Error                                          */
}

/*
*********************************************************************************************************
*                                        EEPROM ERASE SECTOR
*
* Description : This function erases a 4-byte sector of EEPROM
*
* Arguments   : address, the start of the 4-byte sector to address
*
* Returns     : NVM_NO_ERR           - EEPROM Write Success
*               NVM_ODD_ACCESS_ERR   - EEPROM Write Error, Address not on an even address boundry
*               NVM_ACCESS_ERR       - EEPROM Write Error, Access Violation
*               NVM_PROTECTION_ERR   - EEPROM Write Error, Attempted to write a protected sector
*
* Notes       : None.
*********************************************************************************************************
*/

INT8S  EEPROM_Erase_Sector (INT16U address)
{
    while (!ESTAT_CBEIF) {                                              /* Wait for EEPROM access controller to become ready        */
        ;
    }
    
    ESTAT = (ESTAT_ACCERR_MASK | ESTAT_PVIOL_MASK);                     /* Clear existing error flags                               */
    
    if (address & 0x0001) {
        return (NVM_ODD_ACCESS_ERR);                                    /* Address is NOT aligned on an even boundry?               */
    }
    
    (*(INT16U *)address) = 0xFFFF;                                      /* Write the data to the specified address                  */

    ECMD = ECMD_CMDB6_MASK;	                                            /* Store programming command in FCMD                        */
    ESTAT_CBEIF = 1;                                                    /* Execute the command                                      */

    if (ESTAT_ACCERR) {                                                 /* Check if there has been an access error                  */
        return (NVM_ACCESS_ERR);                                        /* Return an Access Error code                              */
    }
    
    if (ESTAT_PVIOL) {                                                  /* Check if there has been a protection error               */
        return (NVM_PROTECTION_ERR);                                    /* Return a Protection Error code                           */
    }
    
    return (NVM_NO_ERR);                                                /* Return No Error                                          */
}

/*
*********************************************************************************************************
*                                        EEPROM Read
*
* Description : This function reads a 16-bit word from the specified address in EEPROM
*
* Arguments   : address, the start of the 16-bit data to read
*
* Returns     : The 16-bit word stored in location 'address'
*
* Notes       : None.
*********************************************************************************************************
*/

INT16U  EEPROM_Read_Word (INT16U address)
{
    INT16U  data;
    
    
    while (!ESTAT_CBEIF) {                                              /* Wait for EEPROM access controller to become ready        */
        ;
    }
	
	data = (*(INT16U *)address);                                        /* Read the data at location 'address'                      */
	return (data);                                                      /* Return the data                                          */
}

/*
*********************************************************************************************************
*                                        FLASH INITIALIZATION
*
* Description : This function initializes the Non Volatile Flash Memory control registers and must 
*               be called before attempting to write or erase a Flash Memory Sectors
*
* Arguments   : sysclk, the CPU clock frequency (SYSCLK) driven by the onboard oscillator or the 
*               PLL if enabled.
*
* Returns     : None.
*
* Notes       : 1) See bsp.c, BSP_CPU_ClkFreq(), as this function may be used to determine the SYSCLK
*                  frequency.
*               2) You MUST not attempt to erase a page of Flash memory that is either being currently
*                  executed from, or that contains source code binary data critical to the operation
*                  of the application in memory. You may erase non critical or unused areas of flash
*                  memory. It is always best to remove the flash pages that you wish to modify from
*                  your linkers configuration to ensure that code does not get linked to these 
*                  pages.
*********************************************************************************************************
*/

void  Flash_Init (INT32U sysclk)
{
    INT8U fclk_val;
	
	
    if (sysclk >= 12000) {                                              /* If the SYSCLK is > 12MHz, then set FDIV8 bit             */          
        fclk_val  =  (sysclk  / (8*200)) - 1;                           /* Compute the correct divider value                        */
        FCLKDIV  |=   FCLKDIV_PRDIV8_MASK | fclk_val;                   /* Write the FCLKDIV register with the correct settings     */
    } else {
        fclk_val  =  (sysclk / 200) - 1;                                /* Compute the correct divider value                        */
        FCLKDIV  |=   fclk_val;                                         /* Write the FCLKDIV register with the correct settings     */
    }

    FSTAT        |=  (FSTAT_PVIOL_MASK | FSTAT_ACCERR_MASK);            /* Clear any error flags                                    */   
}

/*
*********************************************************************************************************
*                                        FLASH WRITE
*
* Description : This function writes a 16-bit word to FLASH
*
* Arguments   : ppage,   the page number of the flash block to be written to
*               address, the destination FLASH address to write the data
*               data,    the data to write to argument address.
*
* Returns     : NVM_NO_ERR           - EEPROM Write Success
*               NVM_ODD_ACCESS_ERR   - EEPROM Write Error, Address not on an even address boundry
*               NVM_ACCESS_ERR       - EEPROM Write Error, Access Violation
*               NVM_PROTECTION_ERR   - EEPROM Write Error, Attempted to write a protected sector
*
* Notes       : None.
*********************************************************************************************************
*/

INT8S  Flash_Write_Word (INT8U ppage, INT16U address, INT16U data)
{
    FCNFG  = ((~ppage & 0x0C) >> 2);
    PPAGE  =    ppage;                                                  /* Set the page to be written to                            */

    while (!FSTAT_CBEIF) {                                              /* Wait for EEPROM access controller to become ready        */
        ;
    }
    
    FSTAT = (FSTAT_ACCERR_MASK | FSTAT_PVIOL_MASK);                     /* Clear existing error flags                               */
    
    if (address & 0x0001) {
        return (NVM_ODD_ACCESS_ERR);                                    /* Address is NOT aligned on an even boundry?               */
    }
    
    (*(INT16U *)address) = data;                                        /* Write the data to the specified address                  */

    FCMD = FCMD_CMDB5_MASK;	                                            /* Store programming command in FCMD                        */
    FSTAT_CBEIF = 1;                                                    /* Execute the command                                      */

    if (FSTAT_ACCERR) {                                                 /* Check if there has been an access error                  */
        return (NVM_ACCESS_ERR);                                        /* Return an Access Error code                              */
    }
    
    if (FSTAT_PVIOL) {                                                  /* Check if there has been a protection error               */
        return (NVM_PROTECTION_ERR);                                    /* Return a Protection Error code                           */
    }
    
    return (NVM_NO_ERR);                                                /* Return No Error                                          */
}

/*
*********************************************************************************************************
*                                        FLASH ERASE BLOCK
*
* Description : This function erases a 4-byte sector of EEPROM
*
* Arguments   : address, the start of the 4-byte sector to address
*
* Returns     : NVM_NO_ERR           - EEPROM Write Success
*               NVM_ACCESS_ERR       - EEPROM Write Error, Access Violation
*               NVM_PROTECTION_ERR   - EEPROM Write Error, Attempted to write a protected sector
*
* Notes       : 1) Each flash block is 512 bytes and cannot be erased in smaller sections
*********************************************************************************************************
*/

INT8S  Flash_Erase_Block (INT8U block)
{
    FCNFG = block;                                                      /* Set the flash block that needs to be erased              */
 
    while (!FSTAT_CBEIF) {                                              /* Wait for Flash access controller to become ready         */
        ;
    }
    
    FSTAT = (FSTAT_ACCERR_MASK | FSTAT_PVIOL_MASK);                     /* Clear existing error flags                               */
    
    (*(INT16U *)0x8000) = 0xFFFF;                                       /* Write the data to the specified address                  */

    FCMD  = 0x41;                                                       /* Store programming command in FCMD                        */
    FSTAT_CBEIF = 1;                                                    /* Execute the command                                      */

    if (FSTAT_ACCERR) {                                                 /* Check if there has been an access error                  */
        return (NVM_ACCESS_ERR);                                        /* Return an Access Error code                              */
    }
    
    if (FSTAT_PVIOL) {                                                  /* Check if there has been a protection error               */
        return (NVM_PROTECTION_ERR);                                    /* Return a Protection Error code                           */
    }
    
    return (NVM_NO_ERR);                                                /* Return No Error                                          */
}

/*
*********************************************************************************************************
*                                        FLASH READ
*
* Description : This function reads a 16-bit word from the specified address in Flash
*
* Arguments   : address, the start of the 16-bit data to read
*
* Returns     : The 16-bit word stored in location 'address'
*
* Notes       : None.
*********************************************************************************************************
*/

INT16U  Flash_Read_Word (INT8U ppage, INT16U address)
{
    INT16U  data;
    
        
    FCNFG = ((~ppage & 0x0C) >> 2);                                     
    PPAGE =    ppage;                                                   /* Set the page to be read from                             */
    
    while (!FSTAT_CCIF) {                                               /* Wait until the Flash Controller is ready                 */
        ;
    }										
  
	data = (*(INT16U *)address);                                        /* Read the data at location 'address'                      */
	return (data);                                                      /* Return the data                                          */
}