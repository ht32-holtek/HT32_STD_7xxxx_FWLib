/*********************************************************************************************************//**
 * @file    ht32f7xxxx_dac.h
 * @version $Rev:: 610          $
 * @date    $Date:: 2026-11-10 #$
 * @brief   The header file of the DAC library.
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
#ifndef __HT32F7XXXX_DAC_H
#define __HT32F7XXXX_DAC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F7xxxx_Peripheral_Driver HT32F7xxxx Peripheral Driver
  * @{
  */

/** @addtogroup DAC
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup DAC_Exported_Types DAC exported types
  * @{
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup DAC_Exported_Constants DAC exported constants
  * @{
  */
#define ASYNC_MODE                      (0x00000000)
#define SYNC_MODE                       (0x00000001)

#if (LIBCFG_DAC1)
#define IS_DAC(DAC)                     (((DAC) == HT_DAC0) || ((DAC) == HT_DAC1))
#else
#define IS_DAC(DAC)                     ((DAC) == HT_DAC0)
#endif


#define IS_DAC_CONVERSION_MODE(MODE)    (((MODE) == ASYNC_MODE) || ((MODE) == SYNC_MODE))


#define DAC_CH0                         (0)
#define DAC_CH1                         (1)

#define IS_DAC_CHANNEL(CHANNEL)         (((CHANNEL) == DAC_CH0) || ((CHANNEL) == DAC_CH1))



#define DAC_REFERENCE_VDDA              (0)
#define DAC_REFERENCE_VREF              (1UL << 14)

#define IS_DAC_REFERENCE(REF)           (((REF) == DAC_REFERENCE_VDDA) || ((REF) == DAC_REFERENCE_VREF))


#define DAC_RESOLUTION_12BIT            (0)
#define DAC_RESOLUTION_8BIT             (1UL << 2)

#define IS_DAC_RESOLUTION(RES)          (((RES) == DAC_RESOLUTION_8BIT) || ((RES) == DAC_RESOLUTION_12BIT))

#define DAC_INT_CH1UD                   (0x00000008)
#define DAC_INT_CH0UD                   (0x00000004)
#define DAC_INT_CH1DOR                  (0x00000002)
#define DAC_INT_CH0DOR                  (0x00000001)

#define IS_DAC_INT(INT)                 ((((INT) & 0xFFFFFFF0) == 0) && ((INT) != 0))

#define DAC_TRIG_SOFTWARE                       (1UL << 0)

/* (DACTCR[1] << 1) | (DACTSR[11:8] << 8)                                                                   */
#define DAC_TRIG_EXTI_0                         ((1UL << 1) | ( 0UL << 8))
#define DAC_TRIG_EXTI_1                         ((1UL << 1) | ( 1UL << 8))
#define DAC_TRIG_EXTI_2                         ((1UL << 1) | ( 2UL << 8))
#define DAC_TRIG_EXTI_3                         ((1UL << 1) | ( 3UL << 8))
#define DAC_TRIG_EXTI_4                         ((1UL << 1) | ( 4UL << 8))
#define DAC_TRIG_EXTI_5                         ((1UL << 1) | ( 5UL << 8))
#define DAC_TRIG_EXTI_6                         ((1UL << 1) | ( 6UL << 8))
#define DAC_TRIG_EXTI_7                         ((1UL << 1) | ( 7UL << 8))
#define DAC_TRIG_EXTI_8                         ((1UL << 1) | ( 8UL << 8))
#define DAC_TRIG_EXTI_9                         ((1UL << 1) | ( 9UL << 8))
#define DAC_TRIG_EXTI_10                        ((1UL << 1) | (10UL << 8))
#define DAC_TRIG_EXTI_11                        ((1UL << 1) | (11UL << 8))
#define DAC_TRIG_EXTI_12                        ((1UL << 1) | (12UL << 8))
#define DAC_TRIG_EXTI_13                        ((1UL << 1) | (13UL << 8))
#define DAC_TRIG_EXTI_14                        ((1UL << 1) | (14UL << 8))
#define DAC_TRIG_EXTI_15                        ((1UL << 1) | (15UL << 8))

/* ((DACTCR[3] << 3) | (DACTSR[14] << 14))                                          */
#define DAC_TRIG_BFTM0                          ((1UL << 3) | (0UL << 14))
#if (LIBCFG_BFTM1)
#define DAC_TRIG_BFTM1                          ((1UL << 3) | (1UL << 14))
#endif

/* ((DACTCR[2] << 2) | (DACTSR[13:12] << 14) | (DACTSR[18:16] << 24))                                       */
#if (LIBCFG_PWM0)
#define DAC_TRIG_PWM0_MTO                       ((1UL << 3) | (2UL << 14) | (0UL << 24))
#define DAC_TRIG_PWM0_CH0O                      ((1UL << 3) | (2UL << 14) | (1UL << 24))
#define DAC_TRIG_PWM0_CH1O                      ((1UL << 3) | (2UL << 14) | (2UL << 24))
#define DAC_TRIG_PWM0_CH2O                      ((1UL << 3) | (2UL << 14) | (3UL << 24))
#define DAC_TRIG_PWM0_CH3O                      ((1UL << 3) | (2UL << 14) | (4UL << 24))
#endif

#if (LIBCFG_PWM1)
#define DAC_TRIG_PWM1_MTO                       ((1UL << 3) | (3UL << 14) | (0UL << 24))
#define DAC_TRIG_PWM1_CH0O                      ((1UL << 3) | (3UL << 14) | (1UL << 24))
#define DAC_TRIG_PWM1_CH1O                      ((1UL << 3) | (3UL << 14) | (2UL << 24))
#define DAC_TRIG_PWM1_CH2O                      ((1UL << 3) | (3UL << 14) | (3UL << 24))
#define DAC_TRIG_PWM1_CH3O                      ((1UL << 3) | (3UL << 14) | (4UL << 24))
#endif

/* ((DACTCR[2] << 2) | (DACTSR[13:12] << 12) | (DACTSR[18:16] << 16))                                       */
#if (LIBCFG_MCTM0)
#define DAC_TRIG_MCTM0_MTO                      ((1UL << 2) | (0UL << 12) | (0UL << 16))
#define DAC_TRIG_MCTM0_CH0O                     ((1UL << 2) | (0UL << 12) | (1UL << 16))
#define DAC_TRIG_MCTM0_CH1O                     ((1UL << 2) | (0UL << 12) | (2UL << 16))
#define DAC_TRIG_MCTM0_CH2O                     ((1UL << 2) | (0UL << 12) | (3UL << 16))
#define DAC_TRIG_MCTM0_CH3O                     ((1UL << 2) | (0UL << 12) | (4UL << 16))
#endif

#if (LIBCFG_MCTM1)
#define DAC_TRIG_MCTM1_MTO                      ((1UL << 2) | (1UL << 12) | (0UL << 16))
#define DAC_TRIG_MCTM1_CH0O                     ((1UL << 2) | (1UL << 12) | (1UL << 16))
#define DAC_TRIG_MCTM1_CH1O                     ((1UL << 2) | (1UL << 12) | (2UL << 16))
#define DAC_TRIG_MCTM1_CH2O                     ((1UL << 2) | (1UL << 12) | (3UL << 16))
#define DAC_TRIG_MCTM1_CH3O                     ((1UL << 2) | (1UL << 12) | (4UL << 16))
#endif

#if (LIBCFG_NO_GPTM0)
#define IS_DAC_TRIG_GPTM0(x)                    (0)
#else
#define DAC_TRIG_GPTM0_MTO                      ((1UL << 2) | (2UL << 12) | (0UL << 16))
#define DAC_TRIG_GPTM0_CH0O                     ((1UL << 2) | (2UL << 12) | (1UL << 16))
#define DAC_TRIG_GPTM0_CH1O                     ((1UL << 2) | (2UL << 12) | (2UL << 16))
#define DAC_TRIG_GPTM0_CH2O                     ((1UL << 2) | (2UL << 12) | (3UL << 16))
#define DAC_TRIG_GPTM0_CH3O                     ((1UL << 2) | (2UL << 12) | (4UL << 16))

#define IS_DAC_TRIG_GPTM0(REGTRIG)              (((REGTRIG) == DAC_TRIG_GPTM0_MTO)          || \
                                                 ((REGTRIG) == DAC_TRIG_GPTM0_CH0O)         || \
                                                 ((REGTRIG) == DAC_TRIG_GPTM0_CH1O)         || \
                                                 ((REGTRIG) == DAC_TRIG_GPTM0_CH2O)         || \
                                                 ((REGTRIG) == DAC_TRIG_GPTM0_CH3O))
#endif

#if (LIBCFG_GPTM1)
#define DAC_TRIG_GPTM1_MTO                      ((1UL << 2) | (3UL << 12) | (0UL << 16))
#define DAC_TRIG_GPTM1_CH0O                     ((1UL << 2) | (3UL << 12) | (1UL << 16))
#define DAC_TRIG_GPTM1_CH1O                     ((1UL << 2) | (3UL << 12) | (2UL << 16))
#define DAC_TRIG_GPTM1_CH2O                     ((1UL << 2) | (3UL << 12) | (3UL << 16))
#define DAC_TRIG_GPTM1_CH3O                     ((1UL << 2) | (3UL << 12) | (4UL << 16))
#endif

#define IS_DAC_TRIG(REGTRIG)                    (IS_DAC_TRIG1(REGTRIG)                      || \
                                                 IS_DAC_TRIG2(REGTRIG)                      || \
                                                 IS_DAC_TRIG3(REGTRIG)                      || \
                                                 IS_DAC_TRIG4(REGTRIG)                      || \
                                                 IS_DAC_TRIG5(REGTRIG)                      || \
                                                 IS_DAC_TRIG6(REGTRIG)                      || \
                                                 IS_DAC_TRIG8(REGTRIG))

#define IS_DAC_TRIG1(REGTRIG)                   (IS_DAC_TRIG_GPTM0(REGTRIG)         || \
                                                 ((REGTRIG) == DAC_TRIG_BFTM0)      || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_0)     || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_1)     || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_2)     || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_3)     || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_4)     || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_5)     || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_6)     || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_7)     || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_8)     || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_9)     || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_10)    || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_11)    || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_12)    || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_13)    || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_14)    || \
                                                 ((REGTRIG) == DAC_TRIG_EXTI_15)    || \
                                                 ((REGTRIG) == DAC_TRIG_SOFTWARE))

#if (LIBCFG_BFTM1)
#define IS_DAC_TRIG2(REGTRIG)                   ((REGTRIG) == DAC_TRIG_BFTM1)
#else
#define IS_DAC_TRIG2(REGTRIG)                   (0)
#endif

#if (LIBCFG_MCTM0)
#define IS_DAC_TRIG3(REGTRIG)                   (((REGTRIG) == DAC_TRIG_MCTM0_MTO)     || \
                                                 ((REGTRIG) == DAC_TRIG_MCTM0_CH0O)    || \
                                                 ((REGTRIG) == DAC_TRIG_MCTM0_CH1O)    || \
                                                 ((REGTRIG) == DAC_TRIG_MCTM0_CH2O)    || \
                                                 ((REGTRIG) == DAC_TRIG_MCTM0_CH3O))
#else
#define IS_DAC_TRIG3(REGTRIG)                   (0)
#endif

#if (LIBCFG_GPTM1)
#define IS_DAC_TRIG4(REGTRIG)                   (((REGTRIG) == DAC_TRIG_GPTM1_MTO)     || \
                                                 ((REGTRIG) == DAC_TRIG_GPTM1_CH0O)    || \
                                                 ((REGTRIG) == DAC_TRIG_GPTM1_CH1O)    || \
                                                 ((REGTRIG) == DAC_TRIG_GPTM1_CH2O)    || \
                                                 ((REGTRIG) == DAC_TRIG_GPTM1_CH3O))
#else
#define IS_DAC_TRIG4(REGTRIG)                   (0)
#endif

#if (LIBCFG_PWM0)
#define IS_DAC_TRIG5(REGTRIG)                   (((REGTRIG) == DAC_TRIG_PWM0_MTO)      || \
                                                 ((REGTRIG) == DAC_TRIG_PWM0_CH0O)     || \
                                                 ((REGTRIG) == DAC_TRIG_PWM0_CH1O)     || \
                                                 ((REGTRIG) == DAC_TRIG_PWM0_CH2O)     || \
                                                 ((REGTRIG) == DAC_TRIG_PWM0_CH3O))
#else
#define IS_DAC_TRIG5(REGTRIG)                   (0)
#endif

#if (LIBCFG_PWM1)
#define IS_DAC_TRIG6(REGTRIG)                   (((REGTRIG) == DAC_TRIG_PWM1_MTO)     || \
                                                  ((REGTRIG) == DAC_TRIG_PWM1_CH0O)    || \
                                                  ((REGTRIG) == DAC_TRIG_PWM1_CH1O)    || \
                                                  ((REGTRIG) == DAC_TRIG_PWM1_CH2O)    || \
                                                  ((REGTRIG) == DAC_TRIG_PWM1_CH3O))
#else
#define IS_DAC_TRIG6(REGTRIG)                   (0)
#endif

#if (LIBCFG_MCTM1)
#define IS_DAC_TRIG8(REGTRIG)                   (((REGTRIG) == DAC_TRIG_MCTM1_MTO)     || \
                                                 ((REGTRIG) == DAC_TRIG_MCTM1_CH0O)    || \
                                                 ((REGTRIG) == DAC_TRIG_MCTM1_CH1O)    || \
                                                 ((REGTRIG) == DAC_TRIG_MCTM1_CH2O)    || \
                                                 ((REGTRIG) == DAC_TRIG_MCTM1_CH3O))
#else
#define IS_DAC_TRIG8(REGTRIG)                   (0)
#endif
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup DAC_Exported_Functions DAC exported functions
  * @{
  */
void DAC_DeInit(HT_DAC_TypeDef* HT_DACn);

void DAC_ModeConfig(HT_DAC_TypeDef* HT_DACn, u8 ModeSel);

void DAC_ReferenceConfig(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 RefSel);
void DAC_ResolutionConfig(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 ResoSel);

void DAC_OutBufCmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState);
void DAC_Cmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState);

void DAC_SetData(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 Data);
u16 DAC_GetOutData(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch);

void DAC_IntConfig(HT_DAC_TypeDef* HT_DACn, u32 DAC_INT_x, ControlStatus NewState);
FlagStatus DAC_GetIntStatus(HT_DAC_TypeDef* HT_DACn, u32 DAC_INT_x);
void DAC_ClearIntPendingBit(HT_DAC_TypeDef* HT_DACn, u32 DAC_INT_x);
void DAC_PDMACmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState);
void DAC_TrigSourceConfig(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 DAC_TRIG_x);
void DAC_TrigCmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState);
void DAC_SoftwareStartConvCmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState);

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
