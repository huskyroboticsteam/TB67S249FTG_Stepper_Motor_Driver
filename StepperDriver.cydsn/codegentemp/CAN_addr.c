/*******************************************************************************
* File Name: CAN_addr.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CAN_addr.h"

#if !defined(CAN_addr_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: CAN_addr_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 CAN_addr_Read(void) 
{ 
    return CAN_addr_Status;
}


/*******************************************************************************
* Function Name: CAN_addr_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void CAN_addr_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    CAN_addr_Status_Aux_Ctrl |= CAN_addr_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CAN_addr_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void CAN_addr_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    CAN_addr_Status_Aux_Ctrl &= (uint8)(~CAN_addr_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CAN_addr_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void CAN_addr_WriteMask(uint8 mask) 
{
    #if(CAN_addr_INPUTS < 8u)
    	mask &= ((uint8)(1u << CAN_addr_INPUTS) - 1u);
	#endif /* End CAN_addr_INPUTS < 8u */
    CAN_addr_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: CAN_addr_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 CAN_addr_ReadMask(void) 
{
    return CAN_addr_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
