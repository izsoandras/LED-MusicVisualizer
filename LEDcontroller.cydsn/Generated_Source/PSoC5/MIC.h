/*******************************************************************************
* File Name: MIC.h  
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

#if !defined(CY_PINS_MIC_H) /* Pins MIC_H */
#define CY_PINS_MIC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MIC_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MIC__PORT == 15 && ((MIC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MIC_Write(uint8 value);
void    MIC_SetDriveMode(uint8 mode);
uint8   MIC_ReadDataReg(void);
uint8   MIC_Read(void);
void    MIC_SetInterruptMode(uint16 position, uint16 mode);
uint8   MIC_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MIC_SetDriveMode() function.
     *  @{
     */
        #define MIC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MIC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MIC_DM_RES_UP          PIN_DM_RES_UP
        #define MIC_DM_RES_DWN         PIN_DM_RES_DWN
        #define MIC_DM_OD_LO           PIN_DM_OD_LO
        #define MIC_DM_OD_HI           PIN_DM_OD_HI
        #define MIC_DM_STRONG          PIN_DM_STRONG
        #define MIC_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MIC_MASK               MIC__MASK
#define MIC_SHIFT              MIC__SHIFT
#define MIC_WIDTH              1u

/* Interrupt constants */
#if defined(MIC__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MIC_SetInterruptMode() function.
     *  @{
     */
        #define MIC_INTR_NONE      (uint16)(0x0000u)
        #define MIC_INTR_RISING    (uint16)(0x0001u)
        #define MIC_INTR_FALLING   (uint16)(0x0002u)
        #define MIC_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MIC_INTR_MASK      (0x01u) 
#endif /* (MIC__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MIC_PS                     (* (reg8 *) MIC__PS)
/* Data Register */
#define MIC_DR                     (* (reg8 *) MIC__DR)
/* Port Number */
#define MIC_PRT_NUM                (* (reg8 *) MIC__PRT) 
/* Connect to Analog Globals */                                                  
#define MIC_AG                     (* (reg8 *) MIC__AG)                       
/* Analog MUX bux enable */
#define MIC_AMUX                   (* (reg8 *) MIC__AMUX) 
/* Bidirectional Enable */                                                        
#define MIC_BIE                    (* (reg8 *) MIC__BIE)
/* Bit-mask for Aliased Register Access */
#define MIC_BIT_MASK               (* (reg8 *) MIC__BIT_MASK)
/* Bypass Enable */
#define MIC_BYP                    (* (reg8 *) MIC__BYP)
/* Port wide control signals */                                                   
#define MIC_CTL                    (* (reg8 *) MIC__CTL)
/* Drive Modes */
#define MIC_DM0                    (* (reg8 *) MIC__DM0) 
#define MIC_DM1                    (* (reg8 *) MIC__DM1)
#define MIC_DM2                    (* (reg8 *) MIC__DM2) 
/* Input Buffer Disable Override */
#define MIC_INP_DIS                (* (reg8 *) MIC__INP_DIS)
/* LCD Common or Segment Drive */
#define MIC_LCD_COM_SEG            (* (reg8 *) MIC__LCD_COM_SEG)
/* Enable Segment LCD */
#define MIC_LCD_EN                 (* (reg8 *) MIC__LCD_EN)
/* Slew Rate Control */
#define MIC_SLW                    (* (reg8 *) MIC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MIC_PRTDSI__CAPS_SEL       (* (reg8 *) MIC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MIC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MIC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MIC_PRTDSI__OE_SEL0        (* (reg8 *) MIC__PRTDSI__OE_SEL0) 
#define MIC_PRTDSI__OE_SEL1        (* (reg8 *) MIC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MIC_PRTDSI__OUT_SEL0       (* (reg8 *) MIC__PRTDSI__OUT_SEL0) 
#define MIC_PRTDSI__OUT_SEL1       (* (reg8 *) MIC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MIC_PRTDSI__SYNC_OUT       (* (reg8 *) MIC__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MIC__SIO_CFG)
    #define MIC_SIO_HYST_EN        (* (reg8 *) MIC__SIO_HYST_EN)
    #define MIC_SIO_REG_HIFREQ     (* (reg8 *) MIC__SIO_REG_HIFREQ)
    #define MIC_SIO_CFG            (* (reg8 *) MIC__SIO_CFG)
    #define MIC_SIO_DIFF           (* (reg8 *) MIC__SIO_DIFF)
#endif /* (MIC__SIO_CFG) */

/* Interrupt Registers */
#if defined(MIC__INTSTAT)
    #define MIC_INTSTAT            (* (reg8 *) MIC__INTSTAT)
    #define MIC_SNAP               (* (reg8 *) MIC__SNAP)
    
	#define MIC_0_INTTYPE_REG 		(* (reg8 *) MIC__0__INTTYPE)
#endif /* (MIC__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MIC_H */


/* [] END OF FILE */
