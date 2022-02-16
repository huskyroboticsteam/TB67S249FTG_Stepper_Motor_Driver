/*******************************************************************************
* File Name: StepClk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_StepClk_H)
#define CY_CLOCK_StepClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void StepClk_StartEx(uint32 alignClkDiv);
#define StepClk_Start() \
    StepClk_StartEx(StepClk__PA_DIV_ID)

#else

void StepClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void StepClk_Stop(void);

void StepClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 StepClk_GetDividerRegister(void);
uint8  StepClk_GetFractionalDividerRegister(void);

#define StepClk_Enable()                         StepClk_Start()
#define StepClk_Disable()                        StepClk_Stop()
#define StepClk_SetDividerRegister(clkDivider, reset)  \
    StepClk_SetFractionalDividerRegister((clkDivider), 0u)
#define StepClk_SetDivider(clkDivider)           StepClk_SetDividerRegister((clkDivider), 1u)
#define StepClk_SetDividerValue(clkDivider)      StepClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define StepClk_DIV_ID     StepClk__DIV_ID

#define StepClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define StepClk_CTRL_REG   (*(reg32 *)StepClk__CTRL_REGISTER)
#define StepClk_DIV_REG    (*(reg32 *)StepClk__DIV_REGISTER)

#define StepClk_CMD_DIV_SHIFT          (0u)
#define StepClk_CMD_PA_DIV_SHIFT       (8u)
#define StepClk_CMD_DISABLE_SHIFT      (30u)
#define StepClk_CMD_ENABLE_SHIFT       (31u)

#define StepClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << StepClk_CMD_DISABLE_SHIFT))
#define StepClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << StepClk_CMD_ENABLE_SHIFT))

#define StepClk_DIV_FRAC_MASK  (0x000000F8u)
#define StepClk_DIV_FRAC_SHIFT (3u)
#define StepClk_DIV_INT_MASK   (0xFFFFFF00u)
#define StepClk_DIV_INT_SHIFT  (8u)

#else 

#define StepClk_DIV_REG        (*(reg32 *)StepClk__REGISTER)
#define StepClk_ENABLE_REG     StepClk_DIV_REG
#define StepClk_DIV_FRAC_MASK  StepClk__FRAC_MASK
#define StepClk_DIV_FRAC_SHIFT (16u)
#define StepClk_DIV_INT_MASK   StepClk__DIVIDER_MASK
#define StepClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_StepClk_H) */

/* [] END OF FILE */
