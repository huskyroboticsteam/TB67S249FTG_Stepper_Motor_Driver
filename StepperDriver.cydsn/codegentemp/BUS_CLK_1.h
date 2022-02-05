/*******************************************************************************
* File Name: BUS_CLK_1.h
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

#if !defined(CY_CLOCK_BUS_CLK_1_H)
#define CY_CLOCK_BUS_CLK_1_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void BUS_CLK_1_StartEx(uint32 alignClkDiv);
#define BUS_CLK_1_Start() \
    BUS_CLK_1_StartEx(BUS_CLK_1__PA_DIV_ID)

#else

void BUS_CLK_1_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void BUS_CLK_1_Stop(void);

void BUS_CLK_1_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 BUS_CLK_1_GetDividerRegister(void);
uint8  BUS_CLK_1_GetFractionalDividerRegister(void);

#define BUS_CLK_1_Enable()                         BUS_CLK_1_Start()
#define BUS_CLK_1_Disable()                        BUS_CLK_1_Stop()
#define BUS_CLK_1_SetDividerRegister(clkDivider, reset)  \
    BUS_CLK_1_SetFractionalDividerRegister((clkDivider), 0u)
#define BUS_CLK_1_SetDivider(clkDivider)           BUS_CLK_1_SetDividerRegister((clkDivider), 1u)
#define BUS_CLK_1_SetDividerValue(clkDivider)      BUS_CLK_1_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define BUS_CLK_1_DIV_ID     BUS_CLK_1__DIV_ID

#define BUS_CLK_1_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define BUS_CLK_1_CTRL_REG   (*(reg32 *)BUS_CLK_1__CTRL_REGISTER)
#define BUS_CLK_1_DIV_REG    (*(reg32 *)BUS_CLK_1__DIV_REGISTER)

#define BUS_CLK_1_CMD_DIV_SHIFT          (0u)
#define BUS_CLK_1_CMD_PA_DIV_SHIFT       (8u)
#define BUS_CLK_1_CMD_DISABLE_SHIFT      (30u)
#define BUS_CLK_1_CMD_ENABLE_SHIFT       (31u)

#define BUS_CLK_1_CMD_DISABLE_MASK       ((uint32)((uint32)1u << BUS_CLK_1_CMD_DISABLE_SHIFT))
#define BUS_CLK_1_CMD_ENABLE_MASK        ((uint32)((uint32)1u << BUS_CLK_1_CMD_ENABLE_SHIFT))

#define BUS_CLK_1_DIV_FRAC_MASK  (0x000000F8u)
#define BUS_CLK_1_DIV_FRAC_SHIFT (3u)
#define BUS_CLK_1_DIV_INT_MASK   (0xFFFFFF00u)
#define BUS_CLK_1_DIV_INT_SHIFT  (8u)

#else 

#define BUS_CLK_1_DIV_REG        (*(reg32 *)BUS_CLK_1__REGISTER)
#define BUS_CLK_1_ENABLE_REG     BUS_CLK_1_DIV_REG
#define BUS_CLK_1_DIV_FRAC_MASK  BUS_CLK_1__FRAC_MASK
#define BUS_CLK_1_DIV_FRAC_SHIFT (16u)
#define BUS_CLK_1_DIV_INT_MASK   BUS_CLK_1__DIVIDER_MASK
#define BUS_CLK_1_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_BUS_CLK_1_H) */

/* [] END OF FILE */
