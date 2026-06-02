/*********************************************************************************************************//**
 * @file    RAMECC/SingleDouble_Error/main.c
 * @version $Rev:: 184          $
 * @date    $Date:: 2025-04-24 #$
 * @brief   Main program.
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
// <<< Use Configuration Wizard in Context Menu >>>

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup RAMECC_Examples RAMECC
  * @{
  */

/** @addtogroup SingleDouble_Error
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
void SimulateSingleError(void);
void SimulateDoubleError(void);

/* Private variables ---------------------------------------------------------------------------------------*/
extern u32 gSingleErrAddress;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{

  #if 0 // Interrupt handling is implemented in the SystemInit() function.
  RAMECC_IntConfig(RAMECC_INT_ECCSEIE|RAMECC_INT_ECCDEIE, ENABLE);
  #endif

  #if 1 // This block is intended to simulate the occurrence of the Single and Double bit error.
  RETARGET_Configuration();           /* Retarget Related configuration                                     */

  SimulateSingleError();              /* Simulate Single Bit Error                                          */

  SimulateDoubleError();              /* Simulate Double Bit Error                                          */
  #endif

  while(1);

}

/*********************************************************************************************************//**
  * @brief  Simulate Single Bit Error,and then trigget Error Correction Code
  * @retval None
  ***********************************************************************************************************/
void SimulateSingleError(void)
{
  vu32 testVal = 1;

  RAMECC_SetUnProtectKey(RAMCR_UNPROTECT_KEY);

  RAMECC_UnprotectConfig();
  RAMECC_Cmd(DISABLE);

  testVal = 3;

  RAMECC_UnprotectConfig();
  RAMECC_Cmd(ENABLE);


  RAMECC_SetUnProtectKey(0x0);

  /* Read testVal                                                                                            */
  printf("testVal = %d, &testVal = 0x%08X\r\n", testVal, (u32)&testVal);

  /* Read testVal, trigger Single Bit Error                                                                  */
  printf("Single Bit Error Address: 0x%x\r\n", gSingleErrAddress);

}

/*********************************************************************************************************//**
  * @brief  Simulate Double Bit Error,and then trigget Error Correction Code
  * @retval None
  ***********************************************************************************************************/
void SimulateDoubleError(void)
{
  vu32 testVal = 1;

  RAMECC_SetUnProtectKey(RAMCR_UNPROTECT_KEY);

  RAMECC_UnprotectConfig();
  RAMECC_Cmd(DISABLE);

  testVal = 2;

  RAMECC_UnprotectConfig();
  RAMECC_Cmd(ENABLE);

  RAMECC_SetUnProtectKey(0x0);

  /* Read testVal, trigger Double Bit Error                                                                 */
  printf("Double Bit Error,testVal = %d\r\n", testVal);
}

#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
  }
}
#endif


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
