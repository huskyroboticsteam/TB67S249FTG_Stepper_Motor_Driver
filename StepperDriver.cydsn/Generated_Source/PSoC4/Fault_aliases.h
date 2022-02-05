/*******************************************************************************
* File Name: Fault.h  
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

#if !defined(CY_PINS_Fault_ALIASES_H) /* Pins Fault_ALIASES_H */
#define CY_PINS_Fault_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Fault_0			(Fault__0__PC)
#define Fault_0_PS		(Fault__0__PS)
#define Fault_0_PC		(Fault__0__PC)
#define Fault_0_DR		(Fault__0__DR)
#define Fault_0_SHIFT	(Fault__0__SHIFT)
#define Fault_0_INTR	((uint16)((uint16)0x0003u << (Fault__0__SHIFT*2u)))

#define Fault_INTR_ALL	 ((uint16)(Fault_0_INTR))


#endif /* End Pins Fault_ALIASES_H */


/* [] END OF FILE */
