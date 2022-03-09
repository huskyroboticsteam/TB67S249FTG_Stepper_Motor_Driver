/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "math.h"

#define min(a,b) (a < b) ? a : b

#define Print(message) DBG_UART_UartPutString(message)
#define Println(message) Print(message);Print("\n\r")
#define PrintChar(character) DBG_UART_UartPutChar(character)
#define PrintInt(integer) DBG_UART_UartPutString(itoa(integer, debugOutput, 10))
#define PrintIntBin(integer) DBG_UART_UartPutString(itoa(integer, debugOutput, 2))
#define BlinkDBG() DBG_Write( ! DBG_Read() )

char debugOutput[32];

#define LEFT 97
#define UP 119
#define RIGHT 100
#define DOWN 115
#define STATUS 113

#define IDLE 0
#define POSITION 1
#define VELOCITY 2

/* [] END OF FILE */
