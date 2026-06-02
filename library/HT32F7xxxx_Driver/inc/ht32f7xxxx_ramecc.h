/*********************************************************************************************************//**
 * @file    ht32f7xxxx_ramecc.h
 * @version $Rev:: 106          $
 * @date    $Date:: 2025-02-12 #$
 * @brief   The header file of the RAMECC library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F7XXXX_RAMECC_H
#define __HT32F7XXXX_RAMECC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F7xxxx_Peripheral_Driver HT32F7xxxx Peripheral Driver
  * @{
  */

/** @addtogroup RAMECC
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Types RAMECC exported types
  * @{
  */

/**
 * @brief Enumeration of RAM Error Correction Code type.
 */
typedef enum
{
  RAMECC_ErrorType_SINGLE = 0,
  RAMECC_ErrorType_DOUBLE = 1
} RAMECC_ErrorType_Enum;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Constants RAMECC exported constants
  * @{
  */

/* Definitions of RAMECC Protection Key                                                                     */
#define RAMCR_UNPROTECT_KEY                        ((u32)0x7AC5)

#define RAMECC_INT_ECCSEIE                         0x00000001
#define RAMECC_INT_ECCDEIE                         0x00000002
#define RAMECC_INT_ECCNMIIE                        0x00000004

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Functions RAMECC exported functions
  * @{
  */
void RAMECC_SetUnProtectKey(u32 uUnProtectKey);
void RAMECC_ProtectConfig(void);
void RAMECC_UnprotectConfig(void);
void RAMECC_Cmd(ControlStatus NewState);
void RAMECC_IntConfig(u32 RAMECC_INT_x, ControlStatus NewState);

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
