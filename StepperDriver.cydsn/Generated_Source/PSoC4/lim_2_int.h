/*******************************************************************************
* File Name: lim_2_int.h
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
#if !defined(CY_ISR_lim_2_int_H)
#define CY_ISR_lim_2_int_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void lim_2_int_Start(void);
void lim_2_int_StartEx(cyisraddress address);
void lim_2_int_Stop(void);

CY_ISR_PROTO(lim_2_int_Interrupt);

void lim_2_int_SetVector(cyisraddress address);
cyisraddress lim_2_int_GetVector(void);

void lim_2_int_SetPriority(uint8 priority);
uint8 lim_2_int_GetPriority(void);

void lim_2_int_Enable(void);
uint8 lim_2_int_GetState(void);
void lim_2_int_Disable(void);

void lim_2_int_SetPending(void);
void lim_2_int_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the lim_2_int ISR. */
#define lim_2_int_INTC_VECTOR            ((reg32 *) lim_2_int__INTC_VECT)

/* Address of the lim_2_int ISR priority. */
#define lim_2_int_INTC_PRIOR             ((reg32 *) lim_2_int__INTC_PRIOR_REG)

/* Priority of the lim_2_int interrupt. */
#define lim_2_int_INTC_PRIOR_NUMBER      lim_2_int__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable lim_2_int interrupt. */
#define lim_2_int_INTC_SET_EN            ((reg32 *) lim_2_int__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the lim_2_int interrupt. */
#define lim_2_int_INTC_CLR_EN            ((reg32 *) lim_2_int__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the lim_2_int interrupt state to pending. */
#define lim_2_int_INTC_SET_PD            ((reg32 *) lim_2_int__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the lim_2_int interrupt. */
#define lim_2_int_INTC_CLR_PD            ((reg32 *) lim_2_int__INTC_CLR_PD_REG)



#endif /* CY_ISR_lim_2_int_H */


/* [] END OF FILE */
