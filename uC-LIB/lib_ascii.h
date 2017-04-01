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
* Filename      : lib_ascii.h
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


/*$PAGE*/
/*
*********************************************************************************************************
*                                                 MODULE
*********************************************************************************************************
*/

#ifndef  LIB_ASCII_MODULE_PRESENT
#define  LIB_ASCII_MODULE_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*
* Note(s) : (1) The following common software files are located in the following directories :
*
*               (a) \<Custom Library Directory>\lib*.*
*
*               (b) (1) \<CPU-Compiler Directory>\cpu_def.h
*
*                   (2) \<CPU-Compiler Directory>\<cpu>\<compiler>\cpu*.*
*
*                           where
*                                   <Custom Library Directory>      directory path for custom   library      software
*                                   <CPU-Compiler Directory>        directory path for common   CPU-compiler software
*                                   <cpu>                           directory name for specific processor (CPU)
*                                   <compiler>                      directory name for specific compiler
*
*           (2) Compiler MUST be configured to include the '\<Custom Library Directory>\uC-LIB\',
*               '\<CPU-Compiler Directory>\' directory, & the specific CPU-compiler directory as
*               additional include path directories.
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   LIB_ASCII_MODULE
#define  LIB_ASCII_EXT
#else
#define  LIB_ASCII_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         ASCII CHARACTER DEFINES
*********************************************************************************************************
*/
                                                                /* -------------------- C0 CONTROLS ------------------- */
#define  ASCII_CHAR_NULL                                0x00    /* '\0'                                                 */
#define  ASCII_CHAR_NUL                                 ASCII_CHAR_NULL
#define  ASCII_CHAR_START_OF_HEADING                    0x01
#define  ASCII_CHAR_SOH                                 ASCII_CHAR_START_OF_HEADING
#define  ASCII_CHAR_START_OF_TEXT                       0x02
#define  ASCII_CHAR_STX                                 ASCII_CHAR_START_OF_TEXT
#define  ASCII_CHAR_END_OF_TEXT                         0x03
#define  ASCII_CHAR_ETX                                 ASCII_CHAR_END_OF_TEXT
#define  ASCII_CHAR_END_OF_TRANSMISSION                 0x04
#define  ASCII_CHAR_EOT                                 ASCII_CHAR_END_OF_TRANSMISSION
#define  ASCII_CHAR_ENQUIRY                             0x05
#define  ASCII_CHAR_ENQ                                 ASCII_CHAR_ENQUIRY
#define  ASCII_CHAR_ACKNOWLEDGE                         0x06
#define  ASCII_CHAR_ACK                                 ASCII_CHAR_ACKNOWLEDGE
#define  ASCII_CHAR_BELL                                0x07    /* '\a'                                                 */
#define  ASCII_CHAR_BEL                                 ASCII_CHAR_BELL
#define  ASCII_CHAR_BACKSPACE                           0x08    /* '\b'                                                 */
#define  ASCII_CHAR_BS                                  ASCII_CHAR_BACKSPACE
#define  ASCII_CHAR_CHARACTER_TABULATION                0x09    /* '\t'                                                 */
#define  ASCII_CHAR_HT                                  ASCII_CHAR_CHARACTER_TABULATION
#define  ASCII_CHAR_LINE_FEED                           0x0A    /* '\n'                                                 */
#define  ASCII_CHAR_LF                                  ASCII_CHAR_LINE_FEED
#define  ASCII_CHAR_LINE_TABULATION                     0x0B    /* '\v'                                                 */
#define  ASCII_CHAR_VT                                  ASCII_CHAR_LINE_TABULATION
#define  ASCII_CHAR_FORM_FEED                           0x0C    /* '\f'                                                 */
#define  ASCII_CHAR_FF                                  ASCII_CHAR_FORM_FEED
#define  ASCII_CHAR_CARRIAGE_RETURN                     0x0D    /* '\r'                                                 */
#define  ASCII_CHAR_CR                                  ASCII_CHAR_CARRIAGE_RETURN
#define  ASCII_CHAR_SHIFT_OUT                           0x0E
#define  ASCII_CHAR_SO                                  ASCII_CHAR_SHIFT_OUT
#define  ASCII_CHAR_SHIFT_IN                            0x0F
#define  ASCII_CHAR_SI                                  ASCII_CHAR_SHIFT_IN
#define  ASCII_CHAR_DATA_LINK_ESCAPE                    0x10
#define  ASCII_CHAR_DLE                                 ASCII_CHAR_DATA_LINK_ESCAPE
#define  ASCII_CHAR_DEVICE_CONTROL_ONE                  0x11
#define  ASCII_CHAR_DC1                                 ASCII_CHAR_DEVICE_CONTROL_ONE
#define  ASCII_CHAR_DEVICE_CONTROL_TWO                  0x12
#define  ASCII_CHAR_DC2                                 ASCII_CHAR_DEVICE_CONTROL_TWO
#define  ASCII_CHAR_DEVICE_CONTROL_THREE                0x13
#define  ASCII_CHAR_DC3                                 ASCII_CHAR_DEVICE_CONTROL_THREE
#define  ASCII_CHAR_DEVICE_CONTROL_FOUR                 0x14
#define  ASCII_CHAR_DC4                                 ASCII_CHAR_DEVICE_CONTROL_FOUR
#define  ASCII_CHAR_NEGATIVE_ACKNOWLEDGE                0x15
#define  ASCII_CHAR_NAK                                 ASCII_CHAR_NEGATIVE_ACKNOWLEDGE
#define  ASCII_CHAR_SYNCHRONOUS_IDLE                    0x16
#define  ASCII_CHAR_SYN                                 ASCII_CHAR_SYNCHRONOUS_IDLE
#define  ASCII_CHAR_END_OF_TRANSMISSION_BLOCK           0x17
#define  ASCII_CHAR_ETB                                 ASCII_CHAR_END_OF_TRANSMISSION_BLOCK
#define  ASCII_CHAR_CANCEL                              0x18
#define  ASCII_CHAR_CAN                                 ASCII_CHAR_CANCEL
#define  ASCII_CHAR_END_OF_MEDIUM                       0x19
#define  ASCII_CHAR_EM                                  ASCII_CHAR_END_OF_MEDIUM
#define  ASCII_CHAR_SUBSITUTE                           0x1A
#define  ASCII_CHAR_SUB                                 ASCII_CHAR_SUBSITUTE
#define  ASCII_CHAR_ESCAPE                              0x1B
#define  ASCII_CHAR_ESC                                 ASCII_CHAR_ESCAPE
#define  ASCII_CHAR_INFO_SEPARATOR_FOUR                 0x1C
#define  ASCII_CHAR_IS4                                 ASCII_CHAR_INFO_SEPARATOR_FOUR
#define  ASCII_CHAR_INFO_SEPARATOR_THREE                0x1D
#define  ASCII_CHAR_IS3                                 ASCII_CHAR_INFO_SEPARATOR_THREE
#define  ASCII_CHAR_INFO_SEPARATOR_TWO                  0x1E
#define  ASCII_CHAR_IS2                                 ASCII_CHAR_INFO_SEPARATOR_TWO
#define  ASCII_CHAR_INFO_SEPARATOR_ONE                  0x1F
#define  ASCII_CHAR_IS1                                 ASCII_CHAR_INFO_SEPARATOR_ONE

                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_SPACE                               0x20    /* ' '                                                  */
#define  ASCII_CHAR_EXCLAMATION_MARK                    0x21    /* '!'                                                  */
#define  ASCII_CHAR_QUOTATION_MARK                      0x22    /* '\"'                                                 */
#define  ASCII_CHAR_NUMBER_SIGN                         0x23    /* '#'                                                  */
#define  ASCII_CHAR_DOLLAR_SIGN                         0x24    /* '$'                                                  */
#define  ASCII_CHAR_PERCENTAGE_SIGN                     0x25    /* '%'                                                  */
#define  ASCII_CHAR_AMPERSAND                           0x26    /* '&'                                                  */
#define  ASCII_CHAR_APOSTROPHE                          0x27    /* '\''                                                 */
#define  ASCII_CHAR_LEFT_PARENTHESIS                    0x28    /* '('                                                  */
#define  ASCII_CHAR_RIGHT_PARENTHESIS                   0x29    /* ')'                                                  */
#define  ASCII_CHAR_ASTERISK                            0x2A    /* '*'                                                  */
#define  ASCII_CHAR_PLUS_SIGN                           0x2B    /* '+'                                                  */
#define  ASCII_CHAR_COMMA                               0x2C    /* ','                                                  */
#define  ASCII_CHAR_HYPHEN_MINUS                        0x2D    /* '-'                                                  */
#define  ASCII_CHAR_FULL_STOP                           0x2E    /* '.'                                                  */
#define  ASCII_CHAR_SOLIDUS                             0x2F    /* '/'                                                  */

                                                                /* ------------------- ASCII DIGITS ------------------- */
#define  ASCII_CHAR_DIGIT_ZERO                          0x30    /* '0'                                                  */
#define  ASCII_CHAR_DIGIT_ONE                           0x31    /* '1'                                                  */
#define  ASCII_CHAR_DIGIT_TWO                           0x32    /* '2'                                                  */
#define  ASCII_CHAR_DIGIT_THREE                         0x33    /* '3'                                                  */
#define  ASCII_CHAR_DIGIT_FOUR                          0x34    /* '4'                                                  */
#define  ASCII_CHAR_DIGIT_FIVE                          0x35    /* '5'                                                  */
#define  ASCII_CHAR_DIGIT_SIX                           0x36    /* '6'                                                  */
#define  ASCII_CHAR_DIGIT_SEVEN                         0x37    /* '7'                                                  */
#define  ASCII_CHAR_DIGIT_EIGHT                         0x38    /* '8'                                                  */
#define  ASCII_CHAR_DIGIT_NINE                          0x39    /* '9'                                                  */

                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_COLON                               0x3A    /* ':'                                                  */
#define  ASCII_CHAR_SEMICOLON                           0x3B    /* ';'                                                  */
#define  ASCII_CHAR_LESS_THAN_SIGN                      0x3C    /* '<'                                                  */
#define  ASCII_CHAR_EQUALS_SIGN                         0x3D    /* '='                                                  */
#define  ASCII_CHAR_GREATER_THAN_SIGN                   0x3E    /* '>'                                                  */
#define  ASCII_CHAR_QUESTION_MARK                       0x3F    /* '\?'                                                 */
#define  ASCII_CHAR_COMMERCIAL_AT                       0x40    /* '@'                                                  */

                                                                /* ------------- UPPERCASE LATIN ALPHABET ------------- */
#define  ASCII_CHAR_LATIN_CAPITAL_A                     0x41    /* 'A'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_B                     0x42    /* 'B'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_C                     0x43    /* 'C'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_D                     0x44    /* 'D'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_E                     0x45    /* 'E'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_F                     0x46    /* 'F'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_G                     0x47    /* 'G'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_H                     0x48    /* 'H'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_I                     0x49    /* 'I'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_J                     0x4A    /* 'J'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_K                     0x4B    /* 'K'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_L                     0x4C    /* 'L'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_M                     0x4D    /* 'M'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_N                     0x4E    /* 'N'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_O                     0x4F    /* 'O'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_P                     0x50    /* 'P'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_Q                     0x51    /* 'Q'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_R                     0x52    /* 'R'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_S                     0x53    /* 'S'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_T                     0x54    /* 'T'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_U                     0x55    /* 'U'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_V                     0x56    /* 'V'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_W                     0x57    /* 'W'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_X                     0x58    /* 'X'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_Y                     0x59    /* 'Y'                                                  */
#define  ASCII_CHAR_LATIN_CAPITAL_Z                     0x5A    /* 'Z'                                                  */

                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_LEFT_SQUARE_BRACKET                 0x5B    /* '['                                                  */
#define  ASCII_CHAR_REVERSE_SOLIDUS                     0x5C    /* '\\'                                                 */
#define  ASCII_CHAR_RIGHT_SQUARE_BRACKET                0x5D    /* ']'                                                  */
#define  ASCII_CHAR_CIRCUMFLEX_ACCENT                   0x5E    /* '^'                                                  */
#define  ASCII_CHAR_LOW_LINE                            0x5F    /* '_'                                                  */
#define  ASCII_CHAR_GRAVE_ACCENT                        0x60    /* '`'                                                  */

                                                                /* ------------- LOWERCASE LATIN ALPHABET ------------- */
#define  ASCII_CHAR_LATIN_SMALL_A                       0x61    /* 'a'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_B                       0x62    /* 'b'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_C                       0x63    /* 'c'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_D                       0x64    /* 'd'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_E                       0x65    /* 'e'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_F                       0x66    /* 'f'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_G                       0x67    /* 'g'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_H                       0x68    /* 'h'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_I                       0x69    /* 'i'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_J                       0x6A    /* 'j'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_K                       0x6B    /* 'k'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_L                       0x6C    /* 'l'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_M                       0x6D    /* 'm'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_N                       0x6E    /* 'n'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_O                       0x6F    /* 'o'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_P                       0x70    /* 'p'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_Q                       0x71    /* 'q'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_R                       0x72    /* 'r'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_S                       0x73    /* 's'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_T                       0x74    /* 't'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_U                       0x75    /* 'u'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_V                       0x76    /* 'v'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_W                       0x77    /* 'w'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_X                       0x78    /* 'x'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_Y                       0x79    /* 'y'                                                  */
#define  ASCII_CHAR_LATIN_SMALL_Z                       0x7A    /* 'z'                                                  */

                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_LEFT_CURLY_BRACKET                  0x7B    /* '{'                                                  */
#define  ASCII_CHAR_VERTICAL_LINE                       0x7C    /* '|'                                                  */
#define  ASCII_CHAR_RIGHT_CURLY_BRACKET                 0x7D    /* '}'                                                  */
#define  ASCII_CHAR_TILDE                               0x7E    /* '~'                                                  */

                                                                /* ----------------- CONTROL CHARACTER ---------------- */
#define  ASCII_CHAR_DELETE                              0x7F
#define  ASCII_CHAR_DEL                                 ASCII_CHAR_DELETE


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                 ASCII CHARACTER CLASSIFICATION MACRO's
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            ASCII_IS_ALNUM()
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
* Note(s)     : (1) 'ASCII_IS_ALNUM()' returns TRUE if EITHER 'ASCII_IS_ALPHA()' or 'ASCII_IS_DIGIT()'
*                   would return TRUE for the argument character.
*********************************************************************************************************
*/

#define  ASCII_IS_ALNUM(c)           (((((c) >= ASCII_CHAR_LATIN_CAPITAL_A) && ((c) <= ASCII_CHAR_LATIN_CAPITAL_Z)) || \
                                       (((c) >= ASCII_CHAR_LATIN_SMALL_A  ) && ((c) <= ASCII_CHAR_LATIN_SMALL_Z  )) || \
                                       (((c) >= ASCII_CHAR_DIGIT_ZERO     ) && ((c) <= ASCII_CHAR_DIGIT_NINE     )))   ? (DEF_YES) : (DEF_NO))

/*
*********************************************************************************************************
*                                            ASCII_IS_ALPHA()
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
* Note(s)     : (1) 'ASCII_IS_ALPHA()' returns TRUE if EITHER 'ASCII_IS_LOWER()' or 'ASCII_IS_UPPER()'
*                   would return TRUE for the argument character.
*********************************************************************************************************
*/

#define  ASCII_IS_ALPHA(c)           (((((c) >= ASCII_CHAR_LATIN_CAPITAL_A) && ((c) <= ASCII_CHAR_LATIN_CAPITAL_Z)) || \
                                       (((c) >= ASCII_CHAR_LATIN_SMALL_A  ) && ((c) <= ASCII_CHAR_LATIN_SMALL_Z  )))   ? (DEF_YES) : (DEF_NO))

/*
*********************************************************************************************************
*                                            ASCII_IS_BLANK()
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
*               (2) 'ASCII_IS_BLANK()' returns TRUE if the argument character is a space or horizontal
*                   tab.
*********************************************************************************************************
*/

#define  ASCII_IS_BLANK(c)            ((((c) == ASCII_CHAR_SPACE) || ((c) == ASCII_CHAR_HT)) ? (DEF_YES) : (DEF_NO))

/*
*********************************************************************************************************
*                                            ASCII_IS_CTRL()
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

#define  ASCII_IS_CTRL(c)            (((((c) >= ASCII_CHAR_NULL  ) && ((c) <= ASCII_CHAR_IS1)) || \
                                       (((c) == ASCII_CHAR_DELETE)                           ))   ? (DEF_YES) : (DEF_NO))


/*
*********************************************************************************************************
*                                            ASCII_IS_DIGIT()
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

#define  ASCII_IS_DIGIT(c)            ((((c) >= ASCII_CHAR_DIGIT_ZERO) && ((c) <= ASCII_CHAR_DIGIT_NINE)) ? (DEF_YES) : (DEF_NO))

/*
*********************************************************************************************************
*                                            ASCII_IS_GRAPH()
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
* Note(s)     : (1) See 'ASCII_IS_PRINT() Note #1'.
*********************************************************************************************************
*/

#define  ASCII_IS_GRAPH(c)            ((((c) >= ASCII_CHAR_EXCLAMATION_MARK) && ((c) <= ASCII_CHAR_TILDE)) ? (DEF_YES) : (DEF_NO))

/*
*********************************************************************************************************
*                                            ASCII_IS_LOWER()
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

#define  ASCII_IS_LOWER(c)            ((((c) >= ASCII_CHAR_LATIN_SMALL_A) && ((c) <= ASCII_CHAR_LATIN_SMALL_Z)) ? (DEF_YES) : (DEF_NO))

/*
*********************************************************************************************************
*                                            ASCII_IS_PRINT()
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

#define  ASCII_IS_PRINT(c)            ((((c) >= ASCII_CHAR_SPACE) && ((c) <= ASCII_CHAR_TILDE)) ? (DEF_YES) : (DEF_NO))

/*
*********************************************************************************************************
*                                            ASCII_IS_PUNCT()
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
* Note(s)     : (1) 'ASCII_IS_PUNCT()' returns TRUE if 'ASCII_IS_PRINT()' would return TRUE for the
*                   argument character, but BOTH 'ASCII_IS_SPACE()' AND 'ASCII_IS_ALNUM()' would return
*                   FALSE.
*********************************************************************************************************
*/

#define  ASCII_IS_PUNCT(c)           (((((c) >= ASCII_CHAR_EXCLAMATION_MARK   ) && ((c) <= ASCII_CHAR_SOLIDUS      )) || \
                                       (((c) >= ASCII_CHAR_COLON              ) && ((c) <= ASCII_CHAR_COMMERCIAL_AT)) || \
                                       (((c) >= ASCII_CHAR_LEFT_SQUARE_BRACKET) && ((c) <= ASCII_CHAR_GRAVE_ACCENT )) || \
                                       (((c) >= ASCII_CHAR_LEFT_CURLY_BRACKET ) && ((c) <= ASCII_CHAR_TILDE        )))   ? (DEF_YES) : (DEF_NO))

/*
*********************************************************************************************************
*                                            ASCII_IS_SPACE()
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
* Note(s)     : (1) ISO/IEC 9899, Section 7.4.1.10.2 defines the "standard white-space characters" as the
*                   space (' '), the form feed ('\f'), the new-line ('\n'), the carriage return ('\r'),
*                   the horizontal tab ('\t') & the vertical tab ('\v').
*********************************************************************************************************
*/

#define  ASCII_IS_SPACE(c)            ((((c) == ASCII_CHAR_SPACE) || ((c) == ASCII_CHAR_FF) ||  \
                                        ((c) == ASCII_CHAR_LF   ) || ((c) == ASCII_CHAR_CR) ||  \
                                        ((c) == ASCII_CHAR_HT   ) || ((c) == ASCII_CHAR_VT))    ? (DEF_YES) : (DEF_NO))

/*
*********************************************************************************************************
*                                            ASCII_IS_UPPER()
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

#define  ASCII_IS_UPPER(c)            ((((c) >= ASCII_CHAR_LATIN_CAPITAL_A) && ((c) <= ASCII_CHAR_LATIN_CAPITAL_Z)) ? (DEF_YES) : (DEF_NO))

/*
*********************************************************************************************************
*                                            ASCII_IS_XDIGIT()
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

#define  ASCII_IS_XDIGIT(c)          (((((c) >= ASCII_CHAR_DIGIT_ZERO     ) && ((c) <= ASCII_CHAR_DIGIT_NINE     )) || \
                                       (((c) >= ASCII_CHAR_LATIN_CAPITAL_A) && ((c) <= ASCII_CHAR_LATIN_CAPITAL_F)) || \
                                       (((c) >= ASCII_CHAR_LATIN_SMALL_A  ) && ((c) <= ASCII_CHAR_LATIN_SMALL_F  )))   ? (DEF_YES) : (DEF_NO))

/*$PAGE*/
/*
*********************************************************************************************************
*                                  ASCII CHARACTER CASE MAPPING MACRO's
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            ASCII_TO_LOWER()
*
* Description : Convert uppercase letter to a corresponding lowercase letter.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : If 'ASCII_IS_UPPER()' would return TRUE for the argument character, the lowercase
*               equivalent is returned.  Otherwise, the argument character is returned.
*
* Caller(s)   : various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

#define  ASCII_TO_LOWER(c)            ((((c) >= ASCII_CHAR_LATIN_CAPITAL_A) && ((c) <= ASCII_CHAR_LATIN_CAPITAL_Z)) ? ((c) + 0x20) : (c))

/*
*********************************************************************************************************
*                                            ASCII_TO_UPPER()
*
* Description : Convert lowercase letter to a corresponding uppercase letter.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : If 'ASCII_IS_LOWER()' would return TRUE for the argument character, the uppercase
*               equivalent is returned.  Otherwise, the argument character is returned.
*
* Caller(s)   : various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

#define  ASCII_TO_UPPER(c)            ((((c) >= ASCII_CHAR_LATIN_SMALL_A) && ((c) <= ASCII_CHAR_LATIN_SMALL_Z)) ? ((c) - 0x20) : (c))


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsAlnum (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsAlpha (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsBlank (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsCtrl  (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsDigit (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsGraph (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsLower (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsPrint (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsPunct (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsSpace (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsUpper (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsXDigit(CPU_CHAR  c);

CPU_CHAR     ASCII_ToLower (CPU_CHAR  c);

CPU_CHAR     ASCII_ToUpper (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_Cmp     (CPU_CHAR  c1,
                            CPU_CHAR  c2);

/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of lib ascii module include.                     */
