/*******************************************************************************
* File Name: Step_Timer.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 Step_Timer_initVar = 0u;


/*******************************************************************************
* Function Name: Step_Timer_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Step_Timer_Init(void) 
{
        #if (!Step_Timer_UsingFixedFunction && !Step_Timer_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!Step_Timer_UsingFixedFunction && !Step_Timer_ControlRegRemoved) */
        
        #if(!Step_Timer_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 Step_Timer_interruptState;
        #endif /* (!Step_Timer_UsingFixedFunction) */
        
        #if (Step_Timer_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            Step_Timer_CONTROL &= Step_Timer_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                Step_Timer_CONTROL2 &= ((uint8)(~Step_Timer_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                Step_Timer_CONTROL3 &= ((uint8)(~Step_Timer_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (Step_Timer_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                Step_Timer_CONTROL |= Step_Timer_ONESHOT;
            #endif /* (Step_Timer_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            Step_Timer_CONTROL2 |= Step_Timer_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            Step_Timer_RT1 &= ((uint8)(~Step_Timer_RT1_MASK));
            Step_Timer_RT1 |= Step_Timer_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            Step_Timer_RT1 &= ((uint8)(~Step_Timer_SYNCDSI_MASK));
            Step_Timer_RT1 |= Step_Timer_SYNCDSI_EN;

        #else
            #if(!Step_Timer_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = Step_Timer_CONTROL & ((uint8)(~Step_Timer_CTRL_CMPMODE_MASK));
            Step_Timer_CONTROL = ctrl | Step_Timer_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = Step_Timer_CONTROL & ((uint8)(~Step_Timer_CTRL_CAPMODE_MASK));
            
            #if( 0 != Step_Timer_CAPTURE_MODE_CONF)
                Step_Timer_CONTROL = ctrl | Step_Timer_DEFAULT_CAPTURE_MODE;
            #else
                Step_Timer_CONTROL = ctrl;
            #endif /* 0 != Step_Timer_CAPTURE_MODE */ 
            
            #endif /* (!Step_Timer_ControlRegRemoved) */
        #endif /* (Step_Timer_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!Step_Timer_UsingFixedFunction)
            Step_Timer_ClearFIFO();
        #endif /* (!Step_Timer_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        Step_Timer_WritePeriod(Step_Timer_INIT_PERIOD_VALUE);
        #if (!(Step_Timer_UsingFixedFunction && (CY_PSOC5A)))
            Step_Timer_WriteCounter(Step_Timer_INIT_COUNTER_VALUE);
        #endif /* (!(Step_Timer_UsingFixedFunction && (CY_PSOC5A))) */
        Step_Timer_SetInterruptMode(Step_Timer_INIT_INTERRUPTS_MASK);
        
        #if (!Step_Timer_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)Step_Timer_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            Step_Timer_WriteCompare(Step_Timer_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Step_Timer_interruptState = CyEnterCriticalSection();
            
            Step_Timer_STATUS_AUX_CTRL |= Step_Timer_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(Step_Timer_interruptState);
            
        #endif /* (!Step_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Step_Timer_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void Step_Timer_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Step_Timer_UsingFixedFunction)
        Step_Timer_GLOBAL_ENABLE |= Step_Timer_BLOCK_EN_MASK;
        Step_Timer_GLOBAL_STBY_ENABLE |= Step_Timer_BLOCK_STBY_EN_MASK;
    #endif /* (Step_Timer_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!Step_Timer_ControlRegRemoved || Step_Timer_UsingFixedFunction)
        Step_Timer_CONTROL |= Step_Timer_CTRL_ENABLE;                
    #endif /* (!Step_Timer_ControlRegRemoved || Step_Timer_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: Step_Timer_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  Step_Timer_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Step_Timer_Start(void) 
{
    if(Step_Timer_initVar == 0u)
    {
        Step_Timer_Init();
        
        Step_Timer_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    Step_Timer_Enable();        
}


/*******************************************************************************
* Function Name: Step_Timer_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void Step_Timer_Stop(void) 
{
    /* Disable Counter */
    #if(!Step_Timer_ControlRegRemoved || Step_Timer_UsingFixedFunction)
        Step_Timer_CONTROL &= ((uint8)(~Step_Timer_CTRL_ENABLE));        
    #endif /* (!Step_Timer_ControlRegRemoved || Step_Timer_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (Step_Timer_UsingFixedFunction)
        Step_Timer_GLOBAL_ENABLE &= ((uint8)(~Step_Timer_BLOCK_EN_MASK));
        Step_Timer_GLOBAL_STBY_ENABLE &= ((uint8)(~Step_Timer_BLOCK_STBY_EN_MASK));
    #endif /* (Step_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Step_Timer_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void Step_Timer_SetInterruptMode(uint8 interruptsMask) 
{
    Step_Timer_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: Step_Timer_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   Step_Timer_ReadStatusRegister(void) 
{
    return Step_Timer_STATUS;
}


#if(!Step_Timer_ControlRegRemoved)
/*******************************************************************************
* Function Name: Step_Timer_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   Step_Timer_ReadControlRegister(void) 
{
    return Step_Timer_CONTROL;
}


/*******************************************************************************
* Function Name: Step_Timer_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    Step_Timer_WriteControlRegister(uint8 control) 
{
    Step_Timer_CONTROL = control;
}

#endif  /* (!Step_Timer_ControlRegRemoved) */


#if (!(Step_Timer_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: Step_Timer_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void Step_Timer_WriteCounter(uint32 counter) \
                                   
{
    #if(Step_Timer_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (Step_Timer_GLOBAL_ENABLE & Step_Timer_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        Step_Timer_GLOBAL_ENABLE |= Step_Timer_BLOCK_EN_MASK;
        CY_SET_REG16(Step_Timer_COUNTER_LSB_PTR, (uint16)counter);
        Step_Timer_GLOBAL_ENABLE &= ((uint8)(~Step_Timer_BLOCK_EN_MASK));
    #else
        CY_SET_REG24(Step_Timer_COUNTER_LSB_PTR, counter);
    #endif /* (Step_Timer_UsingFixedFunction) */
}
#endif /* (!(Step_Timer_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: Step_Timer_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) The present value of the counter.
*
*******************************************************************************/
uint32 Step_Timer_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(Step_Timer_UsingFixedFunction)
		(void)CY_GET_REG16(Step_Timer_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(Step_Timer_COUNTER_LSB_PTR_8BIT);
	#endif/* (Step_Timer_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(Step_Timer_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Step_Timer_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG24(Step_Timer_STATICCOUNT_LSB_PTR));
    #endif /* (Step_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Step_Timer_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint32) Present Capture value.
*
*******************************************************************************/
uint32 Step_Timer_ReadCapture(void) 
{
    #if(Step_Timer_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Step_Timer_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG24(Step_Timer_STATICCOUNT_LSB_PTR));
    #endif /* (Step_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Step_Timer_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint32) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void Step_Timer_WritePeriod(uint32 period) 
{
    #if(Step_Timer_UsingFixedFunction)
        CY_SET_REG16(Step_Timer_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG24(Step_Timer_PERIOD_LSB_PTR, period);
    #endif /* (Step_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Step_Timer_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) Present period value.
*
*******************************************************************************/
uint32 Step_Timer_ReadPeriod(void) 
{
    #if(Step_Timer_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Step_Timer_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG24(Step_Timer_PERIOD_LSB_PTR));
    #endif /* (Step_Timer_UsingFixedFunction) */
}


#if (!Step_Timer_UsingFixedFunction)
/*******************************************************************************
* Function Name: Step_Timer_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void Step_Timer_WriteCompare(uint32 compare) \
                                   
{
    #if(Step_Timer_UsingFixedFunction)
        CY_SET_REG16(Step_Timer_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG24(Step_Timer_COMPARE_LSB_PTR, compare);
    #endif /* (Step_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Step_Timer_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint32) Present compare value.
*
*******************************************************************************/
uint32 Step_Timer_ReadCompare(void) 
{
    return (CY_GET_REG24(Step_Timer_COMPARE_LSB_PTR));
}


#if (Step_Timer_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Step_Timer_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Step_Timer_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    Step_Timer_CONTROL &= ((uint8)(~Step_Timer_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    Step_Timer_CONTROL |= compareMode;
}
#endif  /* (Step_Timer_COMPARE_MODE_SOFTWARE) */


#if (Step_Timer_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Step_Timer_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Step_Timer_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    Step_Timer_CONTROL &= ((uint8)(~Step_Timer_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    Step_Timer_CONTROL |= ((uint8)((uint8)captureMode << Step_Timer_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (Step_Timer_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: Step_Timer_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void Step_Timer_ClearFIFO(void) 
{

    while(0u != (Step_Timer_ReadStatusRegister() & Step_Timer_STATUS_FIFONEMP))
    {
        (void)Step_Timer_ReadCapture();
    }

}
#endif  /* (!Step_Timer_UsingFixedFunction) */


/* [] END OF FILE */

