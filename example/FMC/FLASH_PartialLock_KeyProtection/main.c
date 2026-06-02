/*********************************************************************************************************//**
 * @file    FMC/FLASH_PartialLock_KeyProtection/main.c
 * @version $Rev:: 293          $
 * @date    $Date:: 2025-09-03 #$
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup FMC_Examples FMC
  * @{
  */

/** @addtogroup FLASH_PartialLock_KeyProtection
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
/* !!! Note: The partial Lock configuration has already been set in "ht32_op2.s"                            */
/*           The following code only demonstrates the locking procedure.                                    */
#if 0
#define PARTIALLOCK_BYCODE      (0)
#endif
#define MASEERASS_INPARTIALLOCK (0)

#define KEY_VALUE0              (0x5555AAAA)
#define KEY_VALUE1              (0x5555AAAA)
#define KEY_VALUE2              (0x5555AAAA)
#define KEY_VALUE3              (0x5555AAAA)

#define MAX_MISMATCH_VALUE      (0xFF)
#define REGION_OPT              (0x00)

/* Private constants ---------------------------------------------------------------------------------------*/
#define StartAddress            (1024 * 16)
#define EndAddress              (StartAddress + (LIBCFG_FLASH_PAGESIZE * 8))
#define TEST_DATA               (0x12345678)


/* Private function prototypes -----------------------------------------------------------------------------*/
#if (PARTIALLOCK_BYCODE)
void PartialLockInit(void);
void ComputeKPPPBit(u32 *KPPP, u32 StartAdd, u32 EndAdd);
#endif

#if (MASEERASS_INPARTIALLOCK)
void MassErass(void);
#endif

void KeyMatch_Program(void);
void Mismatch_Program(void);
void MaxMismatch(void);

void FLASH_Erase(void);
void FLASH_Program(void);
void FLASH_Check(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 err;
FLASH_PartialLockOptionByte PartialLockOption;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();
  HT32_DVB_LEDInit(HT_LED1);
  HT32_DVB_LEDInit(HT_LED2);

  if(FLASH_GetPartialLockStatus() == RESET)
  {
    #if(PARTIALLOCK_BYCODE)
    PartialLockInit();
    #endif
    while(1); /* Partial Lock is either not activated or failed to take effect.                             */
  }
  else
  {
    #if(MASEERASS_INPARTIALLOCK)
    MassErass();
    #endif
  }
  FLASH_GetPartialLockOptionByte(&PartialLockOption);

  #if(1)
  KeyMatch_Program();
  Mismatch_Program();
  #endif

  while (1)
  {
    #if(1)
    MaxMismatch();
    #endif
  }
}

#if (PARTIALLOCK_BYCODE)
/*********************************************************************************************************//**
  * @brief Control, program, and enable partial lock.
  * @retval None
 ************************************************************************************************************/
void PartialLockInit(void)
{
  u32 KPPP[4] = {0};
  FLASH_PartialLockOptionByte PartialLockOptionByte;
  ComputeKPPPBit(KPPP, StartAddress, EndAddress);

  PartialLockOptionByte.OB_KEY_KeyValue[0]           = KEY_VALUE0;
  PartialLockOptionByte.OB_KEY_KeyValue[1]           = KEY_VALUE1;
  PartialLockOptionByte.OB_KEY_KeyValue[2]           = KEY_VALUE2;
  PartialLockOptionByte.OB_KEY_KeyValue[3]           = KEY_VALUE3;

  PartialLockOptionByte.OB_KPCTL_MassErase           = FLASH_MASSERASE_ENABLE;
  PartialLockOptionByte.OB_KPCTL_KeyProtectInvalid   = FLASH_KEYPROTECT_INVALID;
  PartialLockOptionByte.OB_KPCTL_MaxMismatch         = FLASH_MAXMISMATCH_RETURNMISMATCH;

  PartialLockOptionByte.OB_KPCNT_MaxMismatchValue    = MAX_MISMATCH_VALUE;

  PartialLockOptionByte.OB_KPPP_KeyProtectPage[0]    = KPPP[0];
  PartialLockOptionByte.OB_KPPP_KeyProtectPage[1]    = KPPP[1];
  PartialLockOptionByte.OB_KPPP_KeyProtectPage[2]    = KPPP[2];
  PartialLockOptionByte.OB_KPPP_KeyProtectPage[3]    = KPPP[3];
  PartialLockOptionByte.RegionOPT                    = REGION_OPT;

  FLASH_ProgramPartialLockOptionByte(&PartialLockOptionByte);
  NVIC_SystemReset();
}

/*********************************************************************************************************//**
  * @brief Compute partial lock protect page.
  * @param KPPP: Struct pointer of partial lock page protect.
  * @param StartAdd: Protect start address.
  * @param EndAdd: Protect end address.
  * @retval None
 ************************************************************************************************************/
void ComputeKPPPBit(u32 *KPPP, u32 StartAdd, u32 EndAdd)
{
  u32 i, StartPage, EndPage;
  u32 uWPStatus = 0;

  StartPage = StartAdd / LIBCFG_FLASH_PAGESIZE;
  EndPage = EndAdd / LIBCFG_FLASH_PAGESIZE;

  for(i=0; i<(EndPage-StartPage); i++)
  {
    uWPStatus |= KPPP[StartPage+i / 256] & (1 << ((StartPage+i % 256) / 8));
  }

  if(uWPStatus)
  {
    for(i=0; i<(EndPage-StartPage); i++)
    {
      KPPP[(StartPage+i) / 256] |= 1 << (((StartPage+i) % 256) / 8);
    }
  }
}
#endif

#if (MASEERASS_INPARTIALLOCK)
/*********************************************************************************************************//**
  * @brief Key Match and Mass Erass.
  * @retval None
 ************************************************************************************************************/
void MassErass(void)
{
  u32 Key[] = {KEY_VALUE0, KEY_VALUE1, KEY_VALUE2, KEY_VALUE3};
  FLASH_CompareKey(Key);
  if(FLASH_GetKeyCompareStatus())
  {
    FLASH_MassErase();
  }
}
#endif

/*********************************************************************************************************//**
  * @brief Key Match and Try Program.
  * @retval None
 ************************************************************************************************************/
void KeyMatch_Program(void)
{
  u32 Key[] = {KEY_VALUE0, KEY_VALUE1, KEY_VALUE2, KEY_VALUE3};
  err = 0;
  FLASH_CompareKey(Key);
  if(FLASH_GetKeyCompareStatus())
  {
    printf("Key Match!\r\n");
  }
  else
  {
    printf("Key Mismatch! Mismatch Count: %d / %d.\r\n", FLASH_GetMismatchCount(), PartialLockOption.OB_KPCNT_MaxMismatchValue);
  }

  /* Erase Flash pages before program data                                                                  */
  FLASH_Erase();
  /* Program Word data                                                                                      */
  FLASH_Program();
  /* Check Flash data                                                                                       */
  FLASH_Check();

  if (err != 0)
  {
    HT32_DVB_LEDOn(HT_LED1);/* Test Failed                                                                 */
  }
}

/*********************************************************************************************************//**
  * @brief Key Mismatch and Try Program.
  * @retval None
 ************************************************************************************************************/
void Mismatch_Program(void)
{
  u32 Key[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
  err = 0;
  FLASH_CompareKey(Key);
  if(FLASH_GetKeyCompareStatus())
  {
    printf("Key Match!\r\n");
  }
  else
  {
    printf("Key Mismatch! Mismatch Count: %d / %d.\r\n", FLASH_GetMismatchCount(), PartialLockOption.OB_KPCNT_MaxMismatchValue);
  }

  /* Erase Flash pages before program data                                                                  */
  FLASH_Erase();
  /* Program Word data                                                                                      */
  FLASH_Program();
  /* Check Flash data                                                                                       */
  FLASH_Check();

  if (err != 0)
  {
    HT32_DVB_LEDOn(HT_LED2);/* Test Failed                                                                 */
  }
}

/*********************************************************************************************************//**
  * @brief Trigger Key Max Mismatch.
  * @retval None
 ************************************************************************************************************/
void MaxMismatch(void)
{
  u32 Key[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
  FLASH_CompareKey(Key);
  if(FLASH_GetKeyCompareStatus())
  {
    printf("Key Match!\r\n");
  }
  else
  {
    printf("Key Mismatch! Mismatch Count: %d / %d.\r\n", FLASH_GetMismatchCount(), PartialLockOption.OB_KPCNT_MaxMismatchValue);
  }
}

/*********************************************************************************************************//**
  * @brief Erase FLASH Byte page.
  * @retval None
 ************************************************************************************************************/
void FLASH_Erase(void)
{
  u32 Addr;
  FLASH_State FLASHState;
  for (Addr = StartAddress; Addr < EndAddress; Addr += FLASH_PAGE_SIZE)
  {
    FLASHState = FLASH_ErasePage(Addr);
    if (FLASHState != FLASH_COMPLETE)
    {
      err++;
    }
  }
}

/*********************************************************************************************************//**
  * @brief Program FLASH Byte page.
  * @retval None
 ************************************************************************************************************/
void FLASH_Program(void)
{
  u32 Addr;
  FLASH_State FLASHState;
  for (Addr = StartAddress; Addr < EndAddress; Addr += 4)
  {
    FLASHState = FLASH_ProgramWordData(Addr, TEST_DATA);
    if (FLASHState != FLASH_COMPLETE)
    {
      err++;
    }
  }
}

/*********************************************************************************************************//**
  * @brief Check FLASH Byte page.
  * @retval None
 ************************************************************************************************************/
void FLASH_Check(void)
{
  u32 Addr;

  for (Addr = StartAddress; Addr < EndAddress; Addr += 4)
  {
    if (rw(Addr) != TEST_DATA)
    {
      err++;
    }
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
