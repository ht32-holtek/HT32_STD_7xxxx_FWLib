/*********************************************************************************************************//**
 * @file    FMC/FLASH_PartialLock_AccessbyKey/main.c
 * @version $Rev:: 365          $
 * @date    $Date:: 2025-09-22 #$
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

#include "accessbykey.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup FMC_Examples FMC
  * @{
  */

/** @addtogroup FLASH_PartialLock_AccessbyKey
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
#define KEY_VALUE0              (0x5555AAAA)
#define KEY_VALUE1              (0x5555AAAA)
#define KEY_VALUE2              (0x5555AAAA)
#define KEY_VALUE3              (0x5555AAAA)

/* Private function prototypes -----------------------------------------------------------------------------*/
void KeyMatch_Run_AccessbyKey_Function(void);
void KeyMismatch_Run_AccessbyKey_Function(void);

/* Global variables ----------------------------------------------------------------------------------------*/
extern Perameter_InitTypeDef Parameters;
FLASH_PartialLockOptionByte PartialLockOption;

/* Global functions ----------------------------------------------------------------------------------------*/

/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  if(FLASH_GetPartialLockStatus() == RESET)
  {
    while(1); /* Partial Lock is either not activated or failed to take effect.                             */
  }
  FLASH_GetPartialLockOptionByte(&PartialLockOption);

  /* Partial Lock memory region is configured with 'Debug' access type to validate correct region usage
     during debug sessions.                                                                                 */
  FLASH_IntConfig(FLASH_INT_PREIEN, ENABLE);
  FLASH_ClearIntFlag(FLASH_FLAG_PREF);

  #if(1)
  KeyMatch_Run_AccessbyKey_Function();
  KeyMismatch_Run_AccessbyKey_Function();
  #endif

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief Key Match and try to run AccessbyKey function.
  * @retval None
 ************************************************************************************************************/
void KeyMatch_Run_AccessbyKey_Function(void)
{
  u32 i;
  s32 sum;
  u32 Key[] = {KEY_VALUE0, KEY_VALUE1, KEY_VALUE2, KEY_VALUE3};
  Perameter_InitTypeDef Data = {0};

  FLASH_CompareKey(Key);
  if(FLASH_GetKeyCompareStatus())
  {
    printf("Key Match!\r\n");
  }
  else
  {
    printf("Key Mismatch! Mismatch Count: %d / %d.\r\n", FLASH_GetMismatchCount(), PartialLockOption.OB_KPCNT_MaxMismatchValue);
  }

  /* Start run AccessbyKey                                                                                  */
  Data = Parameters;
  if (FLASH_GetIntStatus(FLASH_FLAG_PREF))
  {
    while(1); /* AccessbyKey Error                                                                          */
  }

  for (i=0; i<(Data.size-1); i++)
  {
    printf("Data%d = %d,", i, Data.data[i]);
  }
  printf("Data%d = %d.\r\n", i, Data.data[i]);

  sum = S32Sum(Data.data, Data.size);
  printf("Sum = %d.\r\n", sum);
  if(sum != Data.checkdata)
  {
    printf("Compute or Parameters have Error!!!");
  }
}

 /*********************************************************************************************************//**
  * @brief Key Match and Try to run AccessbyKey function.
  * @retval None
 ************************************************************************************************************/
void KeyMismatch_Run_AccessbyKey_Function(void)
{
  u32 i;
  s32 sum;
  u32 Key[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
  Perameter_InitTypeDef Data = {0};

  FLASH_CompareKey(Key);
  if(FLASH_GetKeyCompareStatus())
  {
    printf("Key Match!\r\n");
  }
  else
  {
    printf("Key Mismatch! Mismatch Count: %d / %d.\r\n", FLASH_GetMismatchCount(), PartialLockOption.OB_KPCNT_MaxMismatchValue);
  }

  /* Start run AccessbyKey                                                                                  */
  Data = Parameters;
  if (FLASH_GetIntStatus(FLASH_FLAG_PREF))
  {
    while(1); /* AccessbyKey Error                                                                          */
  }

  for (i=0; i<(Data.size-1); i++)
  {
    printf("Data%d = %d,", i, Data.data[i]);
  }
  printf("Data%d = %d.\r\n", i, Data.data[i]);

  sum = S32Sum(Data.data, Data.size);
  printf("Sum = %d.\r\n", sum);
  if(sum != Data.checkdata)
  {
    printf("Compute or Parameters have Error!!!");
  }
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
