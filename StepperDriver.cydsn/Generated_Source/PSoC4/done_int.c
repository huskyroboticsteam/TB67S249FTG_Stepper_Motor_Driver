/*******************************************************************************
* File Name: done_int.c  
* Version 1.71
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <done_int.h>
#include "cyapicallbacks.h"

#if !defined(done_int__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START done_int_intc` */

/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: done_int_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void done_int_Start(void)
{
    /* For all we know the interrupt is active. */
    done_int_Disable();

    /* Set the ISR to point to the done_int Interrupt. */
    done_int_SetVector(&done_int_Interrupt);

    /* Set the priority. */
    done_int_SetPriority((uint8)done_int_INTC_PRIOR_NUMBER);

    /* Enable it. */
    done_int_Enable();
}


/*******************************************************************************
* Function Name: done_int_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void done_int_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    done_int_Disable();

    /* Set the ISR to point to the done_int Interrupt. */
    done_int_SetVector(address);

    /* Set the priority. */
    done_int_SetPriority((uint8)done_int_INTC_PRIOR_NUMBER);

    /* Enable it. */
    done_int_Enable();
}


/*******************************************************************************
* Function Name: done_int_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void done_int_Stop(void)
{
    /* Disable this interrupt. */
    done_int_Disable();

    /* Set the ISR to point to the passive one. */
    done_int_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: done_int_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for done_int.
*
*   Add custom code between the START and END comments to keep the next version
*   of this file from over-writing your code.
*
*   Note You may use either the default ISR by using this API, or you may define
*   your own separate ISR through ISR_StartEx().
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(done_int_Interrupt)
{
    #ifdef done_int_INTERRUPT_INTERRUPT_CALLBACK
        done_int_Interrupt_InterruptCallback();
    #endif /* done_int_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START done_int_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: done_int_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling done_int_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use done_int_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void done_int_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + done_int__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: done_int_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress done_int_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + done_int__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: done_int_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling done_int_Start or done_int_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after done_int_Start or done_int_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void done_int_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((done_int__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *done_int_INTC_PRIOR = (*done_int_INTC_PRIOR & (uint32)(~(uint32)done_int__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: done_int_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 done_int_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((done_int__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*done_int_INTC_PRIOR & done_int__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: done_int_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void done_int_Enable(void)
{
    /* Enable the general interrupt. */
    *done_int_INTC_SET_EN = done_int__INTC_MASK;
}


/*******************************************************************************
* Function Name: done_int_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 done_int_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*done_int_INTC_SET_EN & (uint32)done_int__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: done_int_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void done_int_Disable(void)
{
    /* Disable the general interrupt. */
    *done_int_INTC_CLR_EN = done_int__INTC_MASK;
}


/*******************************************************************************
* Function Name: done_int_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void done_int_SetPending(void)
{
    *done_int_INTC_SET_PD = done_int__INTC_MASK;
}


/*******************************************************************************
* Function Name: done_int_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void done_int_ClearPending(void)
{
    *done_int_INTC_CLR_PD = done_int__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
