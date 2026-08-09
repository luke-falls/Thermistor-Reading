/*******************************************************************************
* File Name: Ametherm_1DC103K_EC.h
* Version 1.20
*
* Description:
*  This header file provides registers and constants associated with the
*  ThermistorCalc component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_THERMISTOR_CALC_Ametherm_1DC103K_EC_H)
#define CY_THERMISTOR_CALC_Ametherm_1DC103K_EC_H

#include "cyfitter.h"
#include "CyLib.h"

#define Ametherm_1DC103K_EC_IMPLEMENTATION         (0u)
#define Ametherm_1DC103K_EC_EQUATION_METHOD        (0u)
#define Ametherm_1DC103K_EC_LUT_METHOD             (1u)

#if (Ametherm_1DC103K_EC_IMPLEMENTATION == Ametherm_1DC103K_EC_EQUATION_METHOD)
    #include <math.h>
#endif /* (Ametherm_1DC103K_EC_IMPLEMENTATION == Ametherm_1DC103K_EC_EQUATION_METHOD) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Ametherm_1DC103K_EC_REF_RESISTOR           (10000)
#define Ametherm_1DC103K_EC_REF_RES_SHIFT          (0u)
#define Ametherm_1DC103K_EC_ACCURACY               (10u)
#define Ametherm_1DC103K_EC_MIN_TEMP               (0 * Ametherm_1DC103K_EC_SCALE)


/***************************************
*        Function Prototypes
***************************************/

uint32 Ametherm_1DC103K_EC_GetResistance(int16 vReference, int16 vThermistor)
                                      ;
int16 Ametherm_1DC103K_EC_GetTemperature(uint32 resT) ;


/***************************************
*           API Constants
***************************************/

#define Ametherm_1DC103K_EC_K2C                    (273.15)
#define Ametherm_1DC103K_EC_SCALE                  (100)

#define Ametherm_1DC103K_EC_THA               (0.001225014)
#define Ametherm_1DC103K_EC_THB               (0.0002197765)
#define Ametherm_1DC103K_EC_THC               (1.341153E-07)


#endif /* CY_THERMISTOR_CALC_Ametherm_1DC103K_EC_H */


/* [] END OF FILE */
