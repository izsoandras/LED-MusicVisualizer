/*******************************************************************************
* File Name: OnboardLED.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_OnboardLED_H) /* Pins OnboardLED_H */
#define CY_PINS_OnboardLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "OnboardLED_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 OnboardLED__PORT == 15 && ((OnboardLED__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    OnboardLED_Write(uint8 value);
void    OnboardLED_SetDriveMode(uint8 mode);
uint8   OnboardLED_ReadDataReg(void);
uint8   OnboardLED_Read(void);
void    OnboardLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   OnboardLED_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the OnboardLED_SetDriveMode() function.
     *  @{
     */
        #define OnboardLED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define OnboardLED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define OnboardLED_DM_RES_UP          PIN_DM_RES_UP
        #define OnboardLED_DM_RES_DWN         PIN_DM_RES_DWN
        #define OnboardLED_DM_OD_LO           PIN_DM_OD_LO
        #define OnboardLED_DM_OD_HI           PIN_DM_OD_HI
        #define OnboardLED_DM_STRONG          PIN_DM_STRONG
        #define OnboardLED_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define OnboardLED_MASK               OnboardLED__MASK
#define OnboardLED_SHIFT              OnboardLED__SHIFT
#define OnboardLED_WIDTH              1u

/* Interrupt constants */
#if defined(OnboardLED__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in OnboardLED_SetInterruptMode() function.
     *  @{
     */
        #define OnboardLED_INTR_NONE      (uint16)(0x0000u)
        #define OnboardLED_INTR_RISING    (uint16)(0x0001u)
        #define OnboardLED_INTR_FALLING   (uint16)(0x0002u)
        #define OnboardLED_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define OnboardLED_INTR_MASK      (0x01u) 
#endif /* (OnboardLED__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OnboardLED_PS                     (* (reg8 *) OnboardLED__PS)
/* Data Register */
#define OnboardLED_DR                     (* (reg8 *) OnboardLED__DR)
/* Port Number */
#define OnboardLED_PRT_NUM                (* (reg8 *) OnboardLED__PRT) 
/* Connect to Analog Globals */                                                  
#define OnboardLED_AG                     (* (reg8 *) OnboardLED__AG)                       
/* Analog MUX bux enable */
#define OnboardLED_AMUX                   (* (reg8 *) OnboardLED__AMUX) 
/* Bidirectional Enable */                                                        
#define OnboardLED_BIE                    (* (reg8 *) OnboardLED__BIE)
/* Bit-mask for Aliased Register Access */
#define OnboardLED_BIT_MASK               (* (reg8 *) OnboardLED__BIT_MASK)
/* Bypass Enable */
#define OnboardLED_BYP                    (* (reg8 *) OnboardLED__BYP)
/* Port wide control signals */                                                   
#define OnboardLED_CTL                    (* (reg8 *) OnboardLED__CTL)
/* Drive Modes */
#define OnboardLED_DM0                    (* (reg8 *) OnboardLED__DM0) 
#define OnboardLED_DM1                    (* (reg8 *) OnboardLED__DM1)
#define OnboardLED_DM2                    (* (reg8 *) OnboardLED__DM2) 
/* Input Buffer Disable Override */
#define OnboardLED_INP_DIS                (* (reg8 *) OnboardLED__INP_DIS)
/* LCD Common or Segment Drive */
#define OnboardLED_LCD_COM_SEG            (* (reg8 *) OnboardLED__LCD_COM_SEG)
/* Enable Segment LCD */
#define OnboardLED_LCD_EN                 (* (reg8 *) OnboardLED__LCD_EN)
/* Slew Rate Control */
#define OnboardLED_SLW                    (* (reg8 *) OnboardLED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define OnboardLED_PRTDSI__CAPS_SEL       (* (reg8 *) OnboardLED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define OnboardLED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) OnboardLED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define OnboardLED_PRTDSI__OE_SEL0        (* (reg8 *) OnboardLED__PRTDSI__OE_SEL0) 
#define OnboardLED_PRTDSI__OE_SEL1        (* (reg8 *) OnboardLED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define OnboardLED_PRTDSI__OUT_SEL0       (* (reg8 *) OnboardLED__PRTDSI__OUT_SEL0) 
#define OnboardLED_PRTDSI__OUT_SEL1       (* (reg8 *) OnboardLED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define OnboardLED_PRTDSI__SYNC_OUT       (* (reg8 *) OnboardLED__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(OnboardLED__SIO_CFG)
    #define OnboardLED_SIO_HYST_EN        (* (reg8 *) OnboardLED__SIO_HYST_EN)
    #define OnboardLED_SIO_REG_HIFREQ     (* (reg8 *) OnboardLED__SIO_REG_HIFREQ)
    #define OnboardLED_SIO_CFG            (* (reg8 *) OnboardLED__SIO_CFG)
    #define OnboardLED_SIO_DIFF           (* (reg8 *) OnboardLED__SIO_DIFF)
#endif /* (OnboardLED__SIO_CFG) */

/* Interrupt Registers */
#if defined(OnboardLED__INTSTAT)
    #define OnboardLED_INTSTAT            (* (reg8 *) OnboardLED__INTSTAT)
    #define OnboardLED_SNAP               (* (reg8 *) OnboardLED__SNAP)
    
	#define OnboardLED_0_INTTYPE_REG 		(* (reg8 *) OnboardLED__0__INTTYPE)
#endif /* (OnboardLED__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_OnboardLED_H */


/* [] END OF FILE */
