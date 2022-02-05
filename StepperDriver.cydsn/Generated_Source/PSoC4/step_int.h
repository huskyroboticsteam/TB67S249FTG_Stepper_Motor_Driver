/*******************************************************************************
* File Name: step_int.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_step_int_H)
#define CY_ISR_step_int_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void step_int_Start(void);
void step_int_StartEx(cyisraddress address);
void step_int_Stop(void);

CY_ISR_PROTO(step_int_Interrupt);

void step_int_SetVector(cyisraddress address);
cyisraddress step_int_GetVector(void);

void step_int_SetPriority(uint8 priority);
uint8 step_int_GetPriority(void);

void step_int_Enable(void);
uint8 step_int_GetState(void);
void step_int_Disable(void);

void step_int_SetPending(void);
void step_int_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the step_int ISR. */
#define step_int_INTC_VECTOR            ((reg32 *) step_int__INTC_VECT)

/* Address of the step_int ISR priority. */
#define step_int_INTC_PRIOR             ((reg32 *) step_int__INTC_PRIOR_REG)

/* Priority of the step_int interrupt. */
#define step_int_INTC_PRIOR_NUMBER      step_int__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable step_int interrupt. */
#define step_int_INTC_SET_EN            ((reg32 *) step_int__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the step_int interrupt. */
#define step_int_INTC_CLR_EN            ((reg32 *) step_int__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the step_int interrupt state to pending. */
#define step_int_INTC_SET_PD            ((reg32 *) step_int__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the step_int interrupt. */
#define step_int_INTC_CLR_PD            ((reg32 *) step_int__INTC_CLR_PD_REG)



#endif /* CY_ISR_step_int_H */


/* [] END OF FILE */
