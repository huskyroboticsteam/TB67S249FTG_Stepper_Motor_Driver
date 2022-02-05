/*******************************************************************************
* File Name: Step_Pin.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Step_Pin_ALIASES_H) /* Pins Step_Pin_ALIASES_H */
#define CY_PINS_Step_Pin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Step_Pin_0			(Step_Pin__0__PC)
#define Step_Pin_0_PS		(Step_Pin__0__PS)
#define Step_Pin_0_PC		(Step_Pin__0__PC)
#define Step_Pin_0_DR		(Step_Pin__0__DR)
#define Step_Pin_0_SHIFT	(Step_Pin__0__SHIFT)
#define Step_Pin_0_INTR	((uint16)((uint16)0x0003u << (Step_Pin__0__SHIFT*2u)))

#define Step_Pin_INTR_ALL	 ((uint16)(Step_Pin_0_INTR))


#endif /* End Pins Step_Pin_ALIASES_H */


/* [] END OF FILE */
