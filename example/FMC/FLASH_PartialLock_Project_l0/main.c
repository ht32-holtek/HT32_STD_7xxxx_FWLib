/*********************************************************************************************************//**
 * @file    FMC/FLASH_PartialLock_Project_l0/main.c
 * @version $Rev:: 243          $
 * @date    $Date:: 2025-05-22 #$
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"

#include "calculate.h"
#include "calculate_data.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup FMC_Examples FMC
  * @{
  */

/** @addtogroup FLASH_PartialLock_Project_l0
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------------------------------------*/
void Calculate_Test(void);
void Calculate_Function(void);

/* Global variables ----------------------------------------------------------------------------------------*/
s32 data[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9};
u32 datasize = sizeof(data)/sizeof(s32);

/* Global functions ----------------------------------------------------------------------------------------*/

/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  if (FLASH_GetPartialLockStatus() == RESET)
  {
    while(1); /* Partial Lock is either not activated or failed to take effect.                             */
  }

  Calculate_Test();
  Calculate_Function();

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  Verify the calculate
  * @retval None
  ***********************************************************************************************************/
void Calculate_Test(void)
{
  if(CalculateTest() == RESET)
  {
    while(1); /* Algorithm test failed.                                                                     */
  }
  printf("Calculate test PASS.");
}

/*********************************************************************************************************//**
  * @brief  Use the calculate
  * @retval None
  ***********************************************************************************************************/
void Calculate_Function(void)
{
  u32 i;
  s32 Sum;

  for(i=0; i<(datasize-1); i++)
  {
    printf("Data%d = %d,", i, data[i]);
  }
  printf("Data%d = %d.\r\n", i, data[i]);

  Sum = S32Sum(data, datasize);
  printf("Sum = %d.\r\n", Sum);
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
