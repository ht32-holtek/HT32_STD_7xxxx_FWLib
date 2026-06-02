/*********************************************************************************************************//**
 * @file    ht32f7xxxx_ramecc.c
 * @version $Rev:: 130          $
 * @date    $Date:: 2025-02-26 #$
 * @brief   This file provides all the RAMECC firmware functions.
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f7xxxx_ramecc.h"

/** @addtogroup HT32F7xxxx_Peripheral_Driver HT32F7xxxx Peripheral Driver
  * @{
  */

/** @defgroup RAMECC RAMECC
  * @brief RAMECC driver modules
  * @{
  */

/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup RNG_Private_Define RNG private definitions
  * @{
  */
#define IS_RAMECC_INT(INT)                         ((((INT) & 0xFFFFFFF8) == 0) && ((INT) != 0))

/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/
static u32 _RAMCRUnProtectKey = 0;

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Functions RAMECC exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Set the unprotect key.
 * @param uUnProtectKey: protect key, shall be RAMCR_UNPROTECT_KEY
 * @retval None
 ************************************************************************************************************/
void RAMECC_SetUnProtectKey(u32 uUnProtectKey)
{
  _RAMCRUnProtectKey = uUnProtectKey << 16;
}

/*********************************************************************************************************//**
 * @brief Protect the RAMECC before setting the RAMECC Control Register.
 * @retval None
 ************************************************************************************************************/
void RAMECC_ProtectConfig(void)
{
  /* Write any value to bit 16 ~ 31 (PROTECT) and keep the other control bit                                */
  HT_SYSTEM->RAMCR = HT_SYSTEM->RAMCR;
}

/*********************************************************************************************************//**
 * @brief Unprotect the RAMECC before setting the RAMECC Control Register.
 * @retval None
 ************************************************************************************************************/
void RAMECC_UnprotectConfig(void)
{
  u32 CRValue;

  /* Set the unlock code corresponding to RAMECC                                                            */
  CRValue = HT_SYSTEM->RAMCR & 0x0000FFFF;
  HT_SYSTEM->RAMCR = (_RAMCRUnProtectKey | CRValue);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified RAMECC peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void RAMECC_Cmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_SYSTEM->RAMCR |= ENABLE;
  }
  else
  {
    HT_SYSTEM->RAMCR &= ~(u32)ENABLE;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified RAMECC interrupts.
 * @param RAMECC_INT_x: Specify the RAMECC interrupt sources that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg RAMECC_INT_ECCSEIE        :
 *     @arg RAMECC_INT_ECCDEIE        :
 *     @arg RAMECC_INT_ECCNMIIE       :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 *************************************************************************************************************/
void RAMECC_IntConfig(u32 RAMECC_INT_x, ControlStatus NewState)
{
  /* Check the parameters                                                                                    */
  Assert_Param(IS_RAMECC_INT(RAMECC_INT_x));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if(NewState != DISABLE)
  {
    HT_SYSTEM->RAMICR |= RAMECC_INT_x;
  }
  else
  {
    HT_SYSTEM->RAMICR &= ~RAMECC_INT_x;
  }
}

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
