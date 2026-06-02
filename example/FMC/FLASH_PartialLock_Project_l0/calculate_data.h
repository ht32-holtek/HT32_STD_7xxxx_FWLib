/*********************************************************************************************************//**
 * @file    FMC/FLASH_PartialLock_Project_l0/calculate_data.h
 * @version $Rev:: 381          $
 * @date    $Date:: 2025-09-23 #$
 * @brief   The header file of the flash parameters.
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
#ifndef __CALCULATE_DATA_H
#define __CALCULATE_DATA_H

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

typedef struct{
  s32 data[6];
  u32 size;
  s32 checkdata;
}Calculate_InitTypeDef;

#endif
