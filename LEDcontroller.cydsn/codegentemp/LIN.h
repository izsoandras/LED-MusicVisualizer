/*******************************************************************************
* File Name: LIN.h  
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

#if !defined(CY_PINS_LIN_H) /* Pins LIN_H */
#define CY_PINS_LIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LIN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LIN__PORT == 15 && ((LIN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LIN_Write(uint8 value);
void    LIN_SetDriveMode(uint8 mode);
uint8   LIN_ReadDataReg(void);
uint8   LIN_Read(void);
void    LIN_SetInterruptMode(uint16 position, uint16 mode);
uint8   LIN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LIN_SetDriveMode() function.
     *  @{
     */
        #define LIN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LIN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LIN_DM_RES_UP          PIN_DM_RES_UP
        #define LIN_DM_RES_DWN         PIN_DM_RES_DWN
        #define LIN_DM_OD_LO           PIN_DM_OD_LO
        #define LIN_DM_OD_HI           PIN_DM_OD_HI
        #define LIN_DM_STRONG          PIN_DM_STRONG
        #define LIN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LIN_MASK               LIN__MASK
#define LIN_SHIFT              LIN__SHIFT
#define LIN_WIDTH              1u

/* Interrupt constants */
#if defined(LIN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LIN_SetInterruptMode() function.
     *  @{
     */
        #define LIN_INTR_NONE      (uint16)(0x0000u)
        #define LIN_INTR_RISING    (uint16)(0x0001u)
        #define LIN_INTR_FALLING   (uint16)(0x0002u)
        #define LIN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LIN_INTR_MASK      (0x01u) 
#endif /* (LIN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LIN_PS                     (* (reg8 *) LIN__PS)
/* Data Register */
#define LIN_DR                     (* (reg8 *) LIN__DR)
/* Port Number */
#define LIN_PRT_NUM                (* (reg8 *) LIN__PRT) 
/* Connect to Analog Globals */                                                  
#define LIN_AG                     (* (reg8 *) LIN__AG)                       
/* Analog MUX bux enable */
#define LIN_AMUX                   (* (reg8 *) LIN__AMUX) 
/* Bidirectional Enable */                                                        
#define LIN_BIE                    (* (reg8 *) LIN__BIE)
/* Bit-mask for Aliased Register Access */
#define LIN_BIT_MASK               (* (reg8 *) LIN__BIT_MASK)
/* Bypass Enable */
#define LIN_BYP                    (* (reg8 *) LIN__BYP)
/* Port wide control signals */                                                   
#define LIN_CTL                    (* (reg8 *) LIN__CTL)
/* Drive Modes */
#define LIN_DM0                    (* (reg8 *) LIN__DM0) 
#define LIN_DM1                    (* (reg8 *) LIN__DM1)
#define LIN_DM2                    (* (reg8 *) LIN__DM2) 
/* Input Buffer Disable Override */
#define LIN_INP_DIS                (* (reg8 *) LIN__INP_DIS)
/* LCD Common or Segment Drive */
#define LIN_LCD_COM_SEG            (* (reg8 *) LIN__LCD_COM_SEG)
/* Enable Segment LCD */
#define LIN_LCD_EN                 (* (reg8 *) LIN__LCD_EN)
/* Slew Rate Control */
#define LIN_SLW                    (* (reg8 *) LIN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LIN_PRTDSI__CAPS_SEL       (* (reg8 *) LIN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LIN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LIN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LIN_PRTDSI__OE_SEL0        (* (reg8 *) LIN__PRTDSI__OE_SEL0) 
#define LIN_PRTDSI__OE_SEL1        (* (reg8 *) LIN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LIN_PRTDSI__OUT_SEL0       (* (reg8 *) LIN__PRTDSI__OUT_SEL0) 
#define LIN_PRTDSI__OUT_SEL1       (* (reg8 *) LIN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LIN_PRTDSI__SYNC_OUT       (* (reg8 *) LIN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LIN__SIO_CFG)
    #define LIN_SIO_HYST_EN        (* (reg8 *) LIN__SIO_HYST_EN)
    #define LIN_SIO_REG_HIFREQ     (* (reg8 *) LIN__SIO_REG_HIFREQ)
    #define LIN_SIO_CFG            (* (reg8 *) LIN__SIO_CFG)
    #define LIN_SIO_DIFF           (* (reg8 *) LIN__SIO_DIFF)
#endif /* (LIN__SIO_CFG) */

/* Interrupt Registers */
#if defined(LIN__INTSTAT)
    #define LIN_INTSTAT            (* (reg8 *) LIN__INTSTAT)
    #define LIN_SNAP               (* (reg8 *) LIN__SNAP)
    
	#define LIN_0_INTTYPE_REG 		(* (reg8 *) LIN__0__INTTYPE)
#endif /* (LIN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LIN_H */


/* [] END OF FILE */
