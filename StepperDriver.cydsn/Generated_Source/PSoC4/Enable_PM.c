/*******************************************************************************
* File Name: Enable_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Enable.h"

/* Check for removal by optimization */
#if !defined(Enable_Sync_ctrl_reg__REMOVED)

static Enable_BACKUP_STRUCT  Enable_backup = {0u};

    
/*******************************************************************************
* Function Name: Enable_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Enable_SaveConfig(void) 
{
    Enable_backup.controlState = Enable_Control;
}


/*******************************************************************************
* Function Name: Enable_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Enable_RestoreConfig(void) 
{
     Enable_Control = Enable_backup.controlState;
}


/*******************************************************************************
* Function Name: Enable_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Enable_Sleep(void) 
{
    Enable_SaveConfig();
}


/*******************************************************************************
* Function Name: Enable_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Enable_Wakeup(void)  
{
    Enable_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
