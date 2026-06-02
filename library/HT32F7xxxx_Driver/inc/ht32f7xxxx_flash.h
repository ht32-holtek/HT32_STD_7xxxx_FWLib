/*********************************************************************************************************//**
 * @file    ht32f7xxxx_flash.h
 * @version $Rev:: 470          $
 * @date    $Date:: 2026-06-01 #$
 * @brief   The header file of the FLASH library.
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
#ifndef __HT32F7XXXX_FLASH_H
#define __HT32F7XXXX_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F7xxxx_Peripheral_Driver HT32F7xxxx Peripheral Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Types FLASH exported types
  * @{
  */

/**
 * @brief  Enumeration of FLASH return status.
 */
typedef enum
{
  FLASH_COMPLETE              = 0,
  FLASH_ERR_ADDR_OUT_OF_RANGE,
  FLASH_ERR_WRITE_PROTECTED,
  FLASH_TIME_OUT
} FLASH_State;

/**
 * @brief  Enumeration of FLASH boot mode.
 */
typedef enum
{
  FLASH_BOOT_LOADER           = 1,
  FLASH_BOOT_MAIN             = 2
} FLASH_Vector;

typedef struct
{
  u32 WriteProtect[4];
  u32 MainSecurity;
  u32 OptionProtect;
} FLASH_OptionByte;

typedef struct
{
  u32 OB_MPREGCR_Control;
  u32 OB_MPREGCR_Mode;
  u32 OB_MPREG_StartPage;
  u32 OB_MPREG_EndPage;
} FLASH_RegionOption;

typedef struct
{
  u32 OB_KEY_KeyValue[4];
  u32 OB_KPCTL_MassErase;
  u32 OB_KPCTL_KeyProtectInvalid;
  u32 OB_KPCTL_MaxMismatch;
  u8 OB_KPCNT_MaxMismatchValue;
  u32 OB_KPPP_KeyProtectPage[4];
  u8 RegionOPT;
  FLASH_RegionOption Region[4];
} FLASH_PartialLockOptionByte;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH exported constants
  * @{
  */

/* Flash Information                                                                                        */
#define FLASH_PAGE_SIZE               (LIBCFG_FLASH_PAGESIZE)   /* Flash page size                          */

/* Flash Wait State                                                                                         */
#define FLASH_WAITSTATE_0             (0x00000001)   /* FLASH zero wait state                               */
#define FLASH_WAITSTATE_1             (0x00000002)   /* FLASH one wait state                                */
#if (LIBCFG_FMC_WAIT_STATE_2)
#define FLASH_WAITSTATE_2             (0x00000003)   /* FLASH two wait state                                */
#endif

#if (LIBCFG_FMC_WAIT_STATE_2)
#define FLASH_WAITSTATE_MAX           (FLASH_WAITSTATE_2)
#else
#define FLASH_WAITSTATE_MAX           (FLASH_WAITSTATE_1)
#endif



/* FLASH OISR Flags                                                                                         */
#define FLASH_FLAG_ORFF               (0x00000001)   /* Operation Finished Flag                             */
#define FLASH_FLAG_ITADF              (0x00000002)   /* Invalid Target Address Flag                         */
#define FLASH_FLAG_OBEF               (0x00000004)   /* Option Byte Check Sum Error Flag                    */
#define FLASH_FLAG_IOCMF              (0x00000008)   /* Invalid Operation Command Flag                      */
#define FLASH_FLAG_OREF               (0x00000010)   /* Operation Error Flag                                */
#define FLASH_FLAG_PREF               (0x00000020)   /* Protection Region Access Error Flag                 */
#define FLASH_FLAG_RORFF              (0x00010000)   /* Raw Operation Finished Flag                         */
#define FLASH_FLAG_PPEF               (0x00020000)   /* Page Erase/Program Protected Error Flag             */

/* FLASH OIER                                                                                               */
#define FLASH_INT_ORFIEN              (0x00000001)   /* Flash Operation Finished Interrupt Enable           */
#define FLASH_INT_ITADIEN             (0x00000002)   /* Invalid Target Address Interrupt Enable             */
#define FLASH_INT_OBEIEN              (0x00000004)   /* Option Byte Checksum Error Interrupt Enable         */
#define FLASH_INT_IOCMIEN             (0x00000008)   /* Invalid Operation Command Interrupt Enable          */
#define FLASH_INT_OREIEN              (0x00000010)   /* Operation Error Interrupt Enable                    */
#define FLASH_INT_PREIEN              (0x00000020)   /* Protection Region Access Error Interrupt Enable     */
#define FLASH_INT_ALL                 (0x0000003F)   /* Flash all Interrupt Enable                          */

/* Option Bytes Address                                                                                     */
#define OPTION_BYTE_BASE              (0x1FF00000)   /* Option Byte Base Address                            */
#define OB_PP0                        (0x1FF00000)   /* Option Byte: Write Protection 0                     */
#define OB_PP1                        (0x1FF00004)   /* Option Byte: Write Protection 1                     */
#define OB_PP2                        (0x1FF00008)   /* Option Byte: Write Protection 2                     */
#define OB_PP3                        (0x1FF0000C)   /* Option Byte: Write Protection 3                     */
#define OB_CP                         (0x1FF00010)   /* Option Byte: Security Protection                    */
#define OB_CHECKSUM                   (0x1FF00020)   /* Option Byte: Checksum                               */
#define OB_SYSCFG                     (0x1FF00028)   /* Flash Option ECC RAM Function Active                */
#define OB_WDT                        (0x1FF0002C)   /* Flash Option for Watchdog Timer Enable              */

/* Partial Lock Option Bytes Address                                                                        */
#define OB_KEY0                       (0x1FF00080)   /* Flash Protection Key 0                              */
#define OB_KEY1                       (0x1FF00084)   /* Flash Protection Key 1                              */
#define OB_KEY2                       (0x1FF00088)   /* Flash Protection Key 2                              */
#define OB_KEY3                       (0x1FF0008C)   /* Flash Protection Key 3                              */
#define OB_KPCTL                      (0x1FF00090)   /* Key Comparison Function                             */
#define OB_KPCNT                      (0x1FF00094)   /* Maximum Error Key Entry Counter at Each Power-on    */
#define OB_KPPP0                      (0x1FF000A0)   /* Write Protection 0 When Key Protection Mode         */
#define OB_KPPP1                      (0x1FF000A4)   /* Write Protection 1 When Key Protection Mode         */
#define OB_KPPP2                      (0x1FF000A8)   /* Write Protection 2 When Key Protection Mode         */
#define OB_KPPP3                      (0x1FF000AC)   /* Write Protection 3 When Key Protection Mode         */
#define OB_MPREG0CR                   (0x1FF000B0)   /* Flash ROM Region 0 Protection Control               */
#define OB_MPREG0                     (0x1FF000B4)   /* Flash Macro Region 0 Protection                     */
#define OB_MPREG1CR                   (0x1FF000B8)   /* Flash ROM Region 1 Protection Control               */
#define OB_MPREG1                     (0x1FF000BC)   /* Flash Macro Region 1 Protection                     */
#define OB_MPREG2CR                   (0x1FF000C0)   /* Flash ROM Region 2 Protection Control               */
#define OB_MPREG2                     (0x1FF000C4)   /* Flash Macro Region 2 Protection                     */
#define OB_MPREG3CR                   (0x1FF000C8)   /* Flash ROM Region 3 Protection Control               */
#define OB_MPREG3                     (0x1FF000CC)   /* Flash Macro Region 3 Protection                     */

/* Flash Write Protection Page Mask                                                                         */
#define FLASH_WP_PAGE_SET(OP, PAGE)     (OP.WriteProtect[PAGE / 256] |= 1 << ((PAGE % 256) / 8))
#define FLASH_WP_PAGE_CLEAR(OP, PAGE)   (OP.WriteProtect[PAGE / 256] &= ~(1 << ((PAGE % 256) / 8)))
#define FLASH_IS_WP_PAGE(OP, PAGE)      (OP.WriteProtect[PAGE / 256] & (1 << ((PAGE % 256) / 8)))
#define FLASH_WP_ALLPAGE_SET(OP)      {u32 i; for (i = 0; i < 4; i++) { OP.WriteProtect[i] = 0xFFFFFFFF; } }

/* Flash Partial Lock                                                                                       */
#define FLASH_PARTIALLOCK_ENABLE         (0xFFFFFF5A)
#define FLASH_MASSERASE_DISABLE          (0xFFFF5AFF)
#define FLASH_MASSERASE_ENABLE           (0xFFFFFFFF)
#define FLASH_KEYPROTECT_INVALID         (0xFF5AFFFF)
#define FLASH_KEYPROTECT_VALID           (0xFFFFFFFF)
#define FLASH_MAXMISMATCH_HOLDMCU        (0x5AFFFFFF)
#define FLASH_MAXMISMATCH_MASSERASE      (0xA5FFFFFF)
#define FLASH_MAXMISMATCH_RETURNMISMATCH (0xFFFFFFFF)
#define FLASH_REGIONCONTROL_PROTECTION   (0xFFFFFF5A)
#define FLASH_REGIONCONTROL_DEBUG        (0xFFFFFF35)
#define FLASH_REGIONMODE_ICODE           (0xFFFF5AFF)
#define FLASH_REGIONMODE_DCODE           (0xFFFF35FF)
#define FLASH_REGIONMODE_ACCESSBYKEY     (0xFFFFA3FF)

#define FLASH_PARTIALLOCK_DEFAULT        (0xFFFFFFFF)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Functions FLASH exported functions
  * @{
  */
void FLASH_SetWaitState(u32 FLASH_WAITSTATE_n);
#if (LIBCFG_FMC_CACHE)
void FLASH_CacheCmd(ControlStatus NewState);
#endif
#if (LIBCFG_FMC_EATF)
void FLASH_ExecuteAtCmd(ControlStatus NewState);
#else
#define FLASH_ExecuteAtCmd(...)
#endif
void FLASH_SetRemappingMode(FLASH_Vector FLASH_BOOT_x);
FLASH_State FLASH_ErasePage(u32 PageAddress);
FLASH_State FLASH_EraseOptionByte(void);
FLASH_State FLASH_MassErase(void);
FLASH_State FLASH_ProgramWordData(u32 Address, u32 Data);
FLASH_State FLASH_ProgramOptionByte(FLASH_OptionByte *Option);
void FLASH_GetOptionByteStatus(FLASH_OptionByte *Option);
void FLASH_IntConfig(u32 FLASH_INT, ControlStatus Cmd);
FlagStatus FLASH_GetIntStatus(u32 FLASH_FLAG_x);
void FLASH_ClearIntFlag(u32 FLASH_FLAG_x);
FLASH_State FLASH_WaitForOperationEnd(void);
void FLASH_ProgramPartialLockOptionByte(FLASH_PartialLockOptionByte *Option);
void FLASH_GetPartialLockOptionByte(FLASH_PartialLockOptionByte *Option);
void FLASH_CompareKey(u32 *KeyValue);
FlagStatus FLASH_GetPartialLockStatus(void);
FlagStatus FLASH_GetKeyCompareStatus(void);
u32 FLASH_GetMismatchCount(void);
void FLASH_LowVoltageReadCmd(ControlStatus NewState);

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
