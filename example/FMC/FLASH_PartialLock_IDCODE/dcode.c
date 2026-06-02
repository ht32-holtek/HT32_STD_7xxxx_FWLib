/*********************************************************************************************************//**
 * @file    FMC/FLASH_PartialLock_IDCODE/dcode.c
 * @version $Rev:: 381          $
 * @date    $Date:: 2025-09-23 #$
 * @brief   The flash parameters.
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
#include "dcode.h"

/* Parameter -----------------------------------------------------------------------------------------------*/
const DCODE_Perameter_InitTypeDef DCODE_Parameters = {{10,  20,  30,  40, -50, -60},  6,  -10};

s32 DCODE_Sum(s32 *data, u32 size)
{
  u32 i;
  s32 sum = 0;
  for(i = 0; i < size; i++)
  {
    sum += *data++;
  }
  return (sum);
}
