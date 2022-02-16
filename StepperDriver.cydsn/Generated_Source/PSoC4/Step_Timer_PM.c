/*******************************************************************************
* File Name: Step_Timer_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Step_Timer.h"

static Step_Timer_backupStruct Step_Timer_backup;


/*******************************************************************************
* Function Name: Step_Timer_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Step_Timer_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Step_Timer_SaveConfig(void) 
{
    #if (!Step_Timer_UsingFixedFunction)

        Step_Timer_backup.CounterUdb = Step_Timer_ReadCounter();

        #if(!Step_Timer_ControlRegRemoved)
            Step_Timer_backup.CounterControlRegister = Step_Timer_ReadControlRegister();
        #endif /* (!Step_Timer_ControlRegRemoved) */

    #endif /* (!Step_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Step_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Step_Timer_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Step_Timer_RestoreConfig(void) 
{      
    #if (!Step_Timer_UsingFixedFunction)

       Step_Timer_WriteCounter(Step_Timer_backup.CounterUdb);

        #if(!Step_Timer_ControlRegRemoved)
            Step_Timer_WriteControlRegister(Step_Timer_backup.CounterControlRegister);
        #endif /* (!Step_Timer_ControlRegRemoved) */

    #endif /* (!Step_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Step_Timer_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Step_Timer_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Step_Timer_Sleep(void) 
{
    #if(!Step_Timer_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Step_Timer_CTRL_ENABLE == (Step_Timer_CONTROL & Step_Timer_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Step_Timer_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Step_Timer_backup.CounterEnableState = 0u;
        }
    #else
        Step_Timer_backup.CounterEnableState = 1u;
        if(Step_Timer_backup.CounterEnableState != 0u)
        {
            Step_Timer_backup.CounterEnableState = 0u;
        }
    #endif /* (!Step_Timer_ControlRegRemoved) */
    
    Step_Timer_Stop();
    Step_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Step_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Step_Timer_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Step_Timer_Wakeup(void) 
{
    Step_Timer_RestoreConfig();
    #if(!Step_Timer_ControlRegRemoved)
        if(Step_Timer_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Step_Timer_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Step_Timer_ControlRegRemoved) */
    
}


/* [] END OF FILE */
