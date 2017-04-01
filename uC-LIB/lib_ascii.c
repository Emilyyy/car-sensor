/*
*********************************************************************************************************
*                                               uC/LIB
*                                       CUSTOM LIBRARY MODULES
*
*                          (c) Copyright 2004-2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/LIB is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/LIB in a commercial
*               product you need to contact Micrium to properly license its use in your
*               product.  We provide ALL the source code for your convenience and to
*               help you experience uC/LIB.  The fact that the source code is provided
*               does NOT mean that you can use it without paying a licensing fee.
*
*               Knowledge of the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                       ASCII CHARACTER DEFINITIONS
*
* Filename      : lib_ascii.c
* Version       : V1.25
* Programmer(s) : BAN
* Note(s)       : (1) ECMA-6 '7-Bit coded Character Set' (6th edition), which corresponds to the
*                     3rd edition of ISO 646, specifies several versions of a 7-bit character set :
*
*                     (a) THE GENERAL VERSION, which allows characters at 0x23 and 0x24 to be given
*                         a set alternate form and allows the characters 0x40, 0x5B, 0x5D, 0x60, 0x7B &
*                         0x7D to be assigned a "unique graphic character" or to be declared as unused.
*                         All other characters are explicitly specified.
*
*                     (b) THE INTERNATIONAL REFERENCE VERSION, which explicitly specifies all characters
*                         in the 7-bit character set.
*
*                     (c) NATIONAL & APPLICATION-ORIENTED VERSIONS, which may be derived from the
*                         standard in specified ways.
*
*                     The character set represented in this file reproduces the Internation Reference
*                     Version.  This is identical to the 7-bit character set which occupies Unicode
*                     characters 0x0000 through 0x007F.  The character names are taken from v5.0 of the
*                     Unicode specification, with certain abbreviations so that the resulting #define
*                     names will not violate ANSI C naming restriction :
*
*                     (a) For the Latin capital & lowercase letters, the name component 'LETTER_'
*                         is left out.
*********************************************************************************************************
* Note(s)       : (1) NO compiler-supplied standard library functions are used in library or product software.
*
*                     (a) ALL standard library functions are implemented in the custom library modules :
*
*                         (1) \<Custom Library Directory>\lib*.*
*
*                         (2) \<Custom Library Directory>\Ports\<cpu>\<compiler>\lib*_a.*
*
*                               where
*                                       <Custom Library Directory>      directory path for custom library software
*                                       <cpu>                           directory name for specific processor (CPU)
*                                       <compiler>                      directory name for specific compiler
*
*                     (b) Product-specific library functions are implemented in individual products.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    LIB_ASCII_MODULE
#include  <lib_ascii.h>


/*$PAGE*/
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            ASCII_IsAlnum()
*
* Description : Determine whether character is an alphanumeric character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an alphanumeric character.
*
*               DEF_NO,	 if character is NOT an alphanumeric character.
*
* Caller(s)   : various.
*
* Note(s)     : (1) 'ASCII_IsAlnum()' returns TRUE if EITHER 'ASCII_IsAlpha()' or 'ASCII_IsDigit()'
*                   would return TRUE for the argument character.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsAlnum (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = ((((c >= ASCII_CHAR_LATIN_CAPITAL_A) && (c <= ASCII_CHAR_LATIN_CAPITAL_Z)) ||
            ((c >= ASCII_CHAR_LATIN_SMALL_A  ) && (c <= ASCII_CHAR_LATIN_SMALL_Z  )) ||
            ((c >= ASCII_CHAR_DIGIT_ZERO     ) && (c <= ASCII_CHAR_DIGIT_NINE     ))) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsAlpha()
*
* Description : Determine whether character is an alphabetic character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an alphabetic character.
*
*               DEF_NO,	 if character is NOT an alphabetic character.
*
* Caller(s)   : various.
*
* Note(s)     : (1) 'ASCII_IsAlpha()' returns TRUE if EITHER 'ASCII_IsLower()' or 'ASCII_IsUpper()'
*                   would return TRUE for the argument character.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsAlpha (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = ((((c >= ASCII_CHAR_LATIN_CAPITAL_A) && (c <= ASCII_CHAR_LATIN_CAPITAL_Z)) ||
            ((c >= ASCII_CHAR_LATIN_SMALL_A  ) && (c <= ASCII_CHAR_LATIN_SMALL_Z  ))) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsBlank()
*
* Description : Determine whether character is a standard blank character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a standard blank character.
*
*               DEF_NO,	 if character is NOT a standard blank character.
*
* Caller(s)   : various.
*
* Note(s)     : (1) ISO/IEC 9899, Section 7.4.1.3.2 defines the 'standard blank characters' as the space
*                   (' ') and the horizontal tab ('\t').
*
*               (2) 'ASCII_IsBlank()' returns TRUE if the argument character is a space or horizontal
*                   tab.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsBlank (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = (((c == ASCII_CHAR_SPACE) || (c == ASCII_CHAR_HT)) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsCtrl()
*
* Description : Determine whether character is a control character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a control character.
*
*               DEF_NO,	 if character is NOT a control character.
*
* Caller(s)   : various.
*
* Note(s)     : (1) ISO/IEC 9899, Note 170, states that in the 'seven-bit ASCII character set, the
*                   control characters are those whose values lie from 0 (NUL) through 0x1F (US) and
*                   the character 0x7F (DEL)'.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsCtrl (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = (((c <= ASCII_CHAR_IS1) || (c == ASCII_CHAR_DELETE))  ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsDigit()
*
* Description : Determine whether character is an decimal-digit character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an decimal-digit character.
*
*               DEF_NO,	 if character is NOT an decimal-digit character.
*
* Caller(s)   : various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsDigit (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = (((c >= ASCII_CHAR_DIGIT_ZERO) && (c <= ASCII_CHAR_DIGIT_NINE)) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsGraph()
*
* Description : Determine whether character is any printing character except space (' ').
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an graphic character.
*
*               DEF_NO,	 if character is NOT an graphic character.
*
* Caller(s)   : various.
*
* Note(s)     : (1) See 'ASCII_IsPrint() Note #1'.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsGraph (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = (((c >= ASCII_CHAR_EXCLAMATION_MARK) && (c <= ASCII_CHAR_TILDE)) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsLower()
*
* Description : Determine whether character is a lowercase alphabetic character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an lowercase alphabetic character.
*
*               DEF_NO,	 if character is NOT an lowercase alphabetic character.
*
* Caller(s)   : various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsLower (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = (((c >= ASCII_CHAR_LATIN_SMALL_A) && (c <= ASCII_CHAR_LATIN_SMALL_Z)) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsPrint()
*
* Description : Determine whether character is a printing character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an printing character.
*
*               DEF_NO,	 if character is NOT an printing character.
*
* Caller(s)   : various.
*
* Note(s)     : (1) ISO/IEC 9899, Note 170, states that in the 'seven-bit US ASCII character set, the
*                   printing characters are those whose values lie from 0x20 (space) through 0x7E
*                   (tilde).'
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsPrint (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = (((c >= ASCII_CHAR_SPACE) && (c <= ASCII_CHAR_TILDE)) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsPunct()
*
* Description : Determine whether character is a punctuation character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an punctuation character.
*
*               DEF_NO,	 if character is NOT an punctuation character.
*
* Caller(s)   : various.
*
* Note(s)     : (1) 'ASCII_IsPunct()' returns TRUE if 'ASCII_IsPrint()' would return TRUE for the
*                   argument character, but BOTH 'ASCII_IsSpace()' AND 'ASCII_IsAlnum()' would return
*                   FALSE.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsPunct (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = ((((c >= ASCII_CHAR_EXCLAMATION_MARK   ) && (c <= ASCII_CHAR_SOLIDUS      )) ||
            ((c >= ASCII_CHAR_COLON              ) && (c <= ASCII_CHAR_COMMERCIAL_AT)) ||
            ((c >= ASCII_CHAR_LEFT_SQUARE_BRACKET) && (c <= ASCII_CHAR_GRAVE_ACCENT )) ||
            ((c >= ASCII_CHAR_LEFT_CURLY_BRACKET ) && (c <= ASCII_CHAR_TILDE        ))) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsSpace()
*
* Description : Determine whether character is a white-space character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a white-space character.
*
*               DEF_NO,	 if character is NOT a white-space character.
*
* Caller(s)   : various.
*
* Note(s)     : (1) ISO/IEC 9899, Section 7.4.1.10.2 defines the 'standard white-space characters' as the
*                   space (' '), the form feed ('\f'), the new-line ('\n'), the carriage return ('\r'),
*                   the horizontal tab ('\t') & the vertical tab ('\v').
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsSpace (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = (((c == ASCII_CHAR_SPACE) || (c == ASCII_CHAR_FF) ||
            (c == ASCII_CHAR_LF   ) || (c == ASCII_CHAR_CR) ||
            (c == ASCII_CHAR_HT   ) || (c == ASCII_CHAR_VT)) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsUpper()
*
* Description : Determine whether character is a uppercase alphabetic character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an uppercase alphabetic character.
*
*               DEF_NO,	 if character is NOT an uppercase alphabetic character.
*
* Caller(s)   : various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsUpper (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = (((c >= ASCII_CHAR_LATIN_CAPITAL_A) && (c <= ASCII_CHAR_LATIN_CAPITAL_Z)) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_IsXDigit()
*
* Description : Determine whether character is a hexadecimal-digit character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a hexadecimal-digit character.
*
*               DEF_NO,	 if character is NOT a hexadecimal-digit character.
*
* Caller(s)   : various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsXDigit (CPU_CHAR  c)
{
    CPU_BOOLEAN  rtn;


    rtn = ((((c >= ASCII_CHAR_DIGIT_ZERO     ) && (c <= ASCII_CHAR_DIGIT_NINE     )) ||
            ((c >= ASCII_CHAR_LATIN_CAPITAL_A) && (c <= ASCII_CHAR_LATIN_CAPITAL_F)) ||
            ((c >= ASCII_CHAR_LATIN_SMALL_A  ) && (c <= ASCII_CHAR_LATIN_SMALL_F  ))) ? (DEF_YES) : (DEF_NO));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_ToLower()
*
* Description : Convert uppercase letter to a corresponding lowercase letter.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : If 'ASCII_IsUpper()' would return TRUE for the argument character, the lowercase
*               equivalent is returned.  Otherwise, the argument character is returned.
*
* Caller(s)   : various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_CHAR  ASCII_ToLower (CPU_CHAR  c)
{
    CPU_CHAR  rtn;


    rtn = (((c >= ASCII_CHAR_LATIN_CAPITAL_A) && (c <= ASCII_CHAR_LATIN_CAPITAL_Z)) ? (c + 0x20) : (c));

    return (rtn);
}


/*
*********************************************************************************************************
*                                            ASCII_ToUpper()
*
* Description : Convert lowercase letter to a corresponding uppercase letter.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : If 'ASCII_IsLower()' would return TRUE for the argument character, the uppercase
*               equivalent is returned.  Otherwise, the argument character is returned.
*
* Caller(s)   : various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_CHAR  ASCII_ToUpper (CPU_CHAR  c)
{
    CPU_CHAR  rtn;


    rtn = (((c >= ASCII_CHAR_LATIN_SMALL_A) && (c <= ASCII_CHAR_LATIN_SMALL_Z)) ? (c - 0x20) : (c));

    return (rtn);
}


/*
*********************************************************************************************************
*                                               ASCII_Cmp()
*
* Description : Determine if two characters are identical (case-insensitive).
*
* Argument(s) : c1          First character.
*
*               c2          Second character.
*
* Return(s)   : DEF_TRUE,  if the characters are     identical.
*               DEF_FALSE, if the characters are NOT identical.
*
* Caller(s)   : various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_Cmp (CPU_CHAR  c1,
                        CPU_CHAR  c2)
{
    CPU_CHAR  c1_cap;
    CPU_CHAR  c2_cap;


    if (c1 == c2) {
        return (DEF_YES);
    }

    c1_cap = ASCII_TO_UPPER(c1);
    c2_cap = ASCII_TO_UPPER(c2);

    if (c1_cap == c2_cap) {
        return (DEF_YES);
    } else {
        return (DEF_NO);
    }
}
