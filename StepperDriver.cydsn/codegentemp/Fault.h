/*******************************************************************************
* File Name: Fault.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Fault_H) /* Pins Fault_H */
#define CY_PINS_Fault_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Fault_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Fault_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Fault_Read(void);
void    Fault_Write(uint8 value);
uint8   Fault_ReadDataReg(void);
#if defined(Fault__PC) || (CY_PSOC4_4200L) 
    void    Fault_SetDriveMode(uint8 mode);
#endif
void    Fault_SetInterruptMode(uint16 position, uint16 mode);
uint8   Fault_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Fault_Sleep(void); 
void Fault_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Fault__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Fault_DRIVE_MODE_BITS        (3)
    #define Fault_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Fault_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Fault_SetDriveMode() function.
         *  @{
         */
        #define Fault_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Fault_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Fault_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Fault_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Fault_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Fault_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Fault_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Fault_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Fault_MASK               Fault__MASK
#define Fault_SHIFT              Fault__SHIFT
#define Fault_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Fault_SetInterruptMode() function.
     *  @{
     */
        #define Fault_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Fault_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Fault_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Fault_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Fault__SIO)
    #define Fault_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Fault__PC) && (CY_PSOC4_4200L)
    #define Fault_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Fault_USBIO_DISABLE              ((uint32)(~Fault_USBIO_ENABLE))
    #define Fault_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Fault_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Fault_USBIO_ENTER_SLEEP          ((uint32)((1u << Fault_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Fault_USBIO_SUSPEND_DEL_SHIFT)))
    #define Fault_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Fault_USBIO_SUSPEND_SHIFT)))
    #define Fault_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Fault_USBIO_SUSPEND_DEL_SHIFT)))
    #define Fault_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Fault__PC)
    /* Port Configuration */
    #define Fault_PC                 (* (reg32 *) Fault__PC)
#endif
/* Pin State */
#define Fault_PS                     (* (reg32 *) Fault__PS)
/* Data Register */
#define Fault_DR                     (* (reg32 *) Fault__DR)
/* Input Buffer Disable Override */
#define Fault_INP_DIS                (* (reg32 *) Fault__PC2)

/* Interrupt configuration Registers */
#define Fault_INTCFG                 (* (reg32 *) Fault__INTCFG)
#define Fault_INTSTAT                (* (reg32 *) Fault__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Fault_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Fault__SIO)
    #define Fault_SIO_REG            (* (reg32 *) Fault__SIO)
#endif /* (Fault__SIO_CFG) */

/* USBIO registers */
#if !defined(Fault__PC) && (CY_PSOC4_4200L)
    #define Fault_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Fault_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Fault_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Fault_DRIVE_MODE_SHIFT       (0x00u)
#define Fault_DRIVE_MODE_MASK        (0x07u << Fault_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Fault_H */


/* [] END OF FILE */
