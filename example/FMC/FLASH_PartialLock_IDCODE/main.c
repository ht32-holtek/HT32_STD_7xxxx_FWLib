/*********************************************************************************************************//**
 * @file    FMC/FLASH_PartialLock_IDCODE/main.c
 * @version $Rev:: 203          $
 * @date    $Date:: 2025-04-30 #$
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

#include "icode.h"
#include "dcode.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup FMC_Examples FMC
  * @{
  */

/** @addtogroup FLASH_PartialLock_IDCODE
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------------------------------------*/
void Run_ICODE_Function0(void);
void Run_ICODE_Function1(void);
void Read_DCODE_Data(void);

void Read_ICODE_Data(void);
void Run_DCODE_Function(void);

/* Global variables ----------------------------------------------------------------------------------------*/
extern DCODE_Perameter_InitTypeDef DCODE_Parameters;
extern ICODE_Perameter_InitTypeDef ICODE_Parameters;

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

  /* Partial Lock memory region is configured with 'Debug' access type to validate correct region usage
     during debug sessions.                                                                                 */
  FLASH_IntConfig(FLASH_INT_PREIEN, ENABLE);
  FLASH_ClearIntFlag(FLASH_FLAG_PREF);

  #if(1)
  /* Proper access to the memory region.                                                                    */
  Run_ICODE_Function0();
  Run_ICODE_Function1();
  Read_DCODE_Data();
  #endif

  #if(1)
  /* Improper access to the memory region.                                                                  */
  Read_ICODE_Data();
  Run_DCODE_Function();
  #endif

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief Try to run ICODE function by RAM data.
  * @retval None
 ************************************************************************************************************/
void Run_ICODE_Function0(void)
{
  s32 sum;
  u32 i;

  for(i=0; i<datasize-1; i++)
  {
    printf("Data%d = %d,", i, data[i]);
  }
  printf("Data%d = %d.\r\n", i, data[i]);

  sum = ICODE_Sum(data, datasize);
  if (FLASH_GetIntStatus(FLASH_FLAG_PREF))
  {
    while(1); /* ICODE Error                                                                                */
  }

  printf("Sum = %d.\r\n", sum);

}

/*********************************************************************************************************//**
  * @brief Try to run ICODE function by DCODE data.
  * @retval None
 ************************************************************************************************************/
void Run_ICODE_Function1(void)
{
  s32 sum;
  u32 i;

  for(i=0; i<DCODE_Parameters.size-1; i++)
  {
    printf("Data%d = %d,", i, DCODE_Parameters.data[i]);
  }
  printf("Data%d = %d.\r\n", i, DCODE_Parameters.data[i]);

  sum = ICODE_Sum(DCODE_Parameters.data, DCODE_Parameters.size);
  if (FLASH_GetIntStatus(FLASH_FLAG_PREF))
  {
    while(1); /* ICODE Error                                                                                */
  }

  printf("Sum = %d.\r\n", sum);
  if(sum != DCODE_Parameters.checkdata)
  {
    printf("Compute or Parameters have Error!!!");
  }
}

/*********************************************************************************************************//**
  * @brief Try to read DCODE data.
  * @retval None
 ************************************************************************************************************/
void Read_DCODE_Data(void)
{
  u32 i;
  DCODE_Perameter_InitTypeDef DCODE_Data;
  DCODE_Data = DCODE_Parameters;
  if (FLASH_GetIntStatus(FLASH_FLAG_PREF))
  {
    while(1); /* DCODE Error                                                                                */
  }

  for(i=0; i<DCODE_Data.size; i++)
  {
    printf("Data%d = %d,", i, DCODE_Data.data[i]);
  }
  printf("Size = %d,", DCODE_Data.size);
  printf("Checkdata = %d.\r\n", DCODE_Data.checkdata);
}

/*********************************************************************************************************//**
  * @brief Try to read ICODE data.
  * @retval None
 ************************************************************************************************************/
void Read_ICODE_Data(void)
{
  u32 i;
  ICODE_Perameter_InitTypeDef ICODE_Data;
  ICODE_Data = ICODE_Parameters;
  if (FLASH_GetIntStatus(FLASH_FLAG_PREF))
  {
    while(1); /* ICODE Error                                                                                */
  }

  for(i=0; i<ICODE_Data.size; i++)
  {
    printf("Data%d = %d,", i, ICODE_Data.data[i]);
  }
  printf("Size = %d,", ICODE_Data.size);
  printf("Checkdata = %d,", ICODE_Data.checkdata);
}

/*********************************************************************************************************//**
  * @brief Try to run DCODE function.
  * @retval None
 ************************************************************************************************************/
void Run_DCODE_Function(void)
{
  s32 sum;
  u32 i;

  for(i=0; i<datasize-1; i++)
  {
    printf("Data%d = %d,", i, data[i]);
  }
  printf("Data%d = %d.\r\n", i, data[i]);

  sum = DCODE_Sum(data, datasize);
  if (FLASH_GetIntStatus(FLASH_FLAG_PREF))
  {
    while(1); /* DCODE Error                                                                                */
  }
  else
  {
    printf("Sum = %d.\r\n", sum);
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
