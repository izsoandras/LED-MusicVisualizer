/*******************************************************************************
* File Name: SW_mode.h  
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

#if !defined(CY_PINS_SW_mode_H) /* Pins SW_mode_H */
#define CY_PINS_SW_mode_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SW_mode_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SW_mode__PORT == 15 && ((SW_mode__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SW_mode_Write(uint8 value);
void    SW_mode_SetDriveMode(uint8 mode);
uint8   SW_mode_ReadDataReg(void);
uint8   SW_mode_Read(void);
void    SW_mode_SetInterruptMode(uint16 position, uint16 mode);
uint8   SW_mode_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SW_mode_SetDriveMode() function.
     *  @{
     */
        #define SW_mode_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SW_mode_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SW_mode_DM_RES_UP          PIN_DM_RES_UP
        #define SW_mode_DM_RES_DWN         PIN_DM_RES_DWN
        #define SW_mode_DM_OD_LO           PIN_DM_OD_LO
        #define SW_mode_DM_OD_HI           PIN_DM_OD_HI
        #define SW_mode_DM_STRONG          PIN_DM_STRONG
        #define SW_mode_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SW_mode_MASK               SW_mode__MASK
#define SW_mode_SHIFT              SW_mode__SHIFT
#define SW_mode_WIDTH              1u

/* Interrupt constants */
#if defined(SW_mode__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SW_mode_SetInterruptMode() function.
     *  @{
     */
        #define SW_mode_INTR_NONE      (uint16)(0x0000u)
        #define SW_mode_INTR_RISING    (uint16)(0x0001u)
        #define SW_mode_INTR_FALLING   (uint16)(0x0002u)
        #define SW_mode_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SW_mode_INTR_MASK      (0x01u) 
#endif /* (SW_mode__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SW_mode_PS                     (* (reg8 *) SW_mode__PS)
/* Data Register */
#define SW_mode_DR                     (* (reg8 *) SW_mode__DR)
/* Port Number */
#define SW_mode_PRT_NUM                (* (reg8 *) SW_mode__PRT) 
/* Connect to Analog Globals */                                                  
#define SW_mode_AG                     (* (reg8 *) SW_mode__AG)                       
/* Analog MUX bux enable */
#define SW_mode_AMUX                   (* (reg8 *) SW_mode__AMUX) 
/* Bidirectional Enable */                                                        
#define SW_mode_BIE                    (* (reg8 *) SW_mode__BIE)
/* Bit-mask for Aliased Register Access */
#define SW_mode_BIT_MASK               (* (reg8 *) SW_mode__BIT_MASK)
/* Bypass Enable */
#define SW_mode_BYP                    (* (reg8 *) SW_mode__BYP)
/* Port wide control signals */                                                   
#define SW_mode_CTL                    (* (reg8 *) SW_mode__CTL)
/* Drive Modes */
#define SW_mode_DM0                    (* (reg8 *) SW_mode__DM0) 
#define SW_mode_DM1                    (* (reg8 *) SW_mode__DM1)
#define SW_mode_DM2                    (* (reg8 *) SW_mode__DM2) 
/* Input Buffer Disable Override */
#define SW_mode_INP_DIS                (* (reg8 *) SW_mode__INP_DIS)
/* LCD Common or Segment Drive */
#define SW_mode_LCD_COM_SEG            (* (reg8 *) SW_mode__LCD_COM_SEG)
/* Enable Segment LCD */
#define SW_mode_LCD_EN                 (* (reg8 *) SW_mode__LCD_EN)
/* Slew Rate Control */
#define SW_mode_SLW                    (* (reg8 *) SW_mode__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SW_mode_PRTDSI__CAPS_SEL       (* (reg8 *) SW_mode__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SW_mode_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SW_mode__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SW_mode_PRTDSI__OE_SEL0        (* (reg8 *) SW_mode__PRTDSI__OE_SEL0) 
#define SW_mode_PRTDSI__OE_SEL1        (* (reg8 *) SW_mode__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SW_mode_PRTDSI__OUT_SEL0       (* (reg8 *) SW_mode__PRTDSI__OUT_SEL0) 
#define SW_mode_PRTDSI__OUT_SEL1       (* (reg8 *) SW_mode__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SW_mode_PRTDSI__SYNC_OUT       (* (reg8 *) SW_mode__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SW_mode__SIO_CFG)
    #define SW_mode_SIO_HYST_EN        (* (reg8 *) SW_mode__SIO_HYST_EN)
    #define SW_mode_SIO_REG_HIFREQ     (* (reg8 *) SW_mode__SIO_REG_HIFREQ)
    #define SW_mode_SIO_CFG            (* (reg8 *) SW_mode__SIO_CFG)
    #define SW_mode_SIO_DIFF           (* (reg8 *) SW_mode__SIO_DIFF)
#endif /* (SW_mode__SIO_CFG) */

/* Interrupt Registers */
#if defined(SW_mode__INTSTAT)
    #define SW_mode_INTSTAT            (* (reg8 *) SW_mode__INTSTAT)
    #define SW_mode_SNAP               (* (reg8 *) SW_mode__SNAP)
    
	#define SW_mode_0_INTTYPE_REG 		(* (reg8 *) SW_mode__0__INTTYPE)
#endif /* (SW_mode__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SW_mode_H */


/* [] END OF FILE */
