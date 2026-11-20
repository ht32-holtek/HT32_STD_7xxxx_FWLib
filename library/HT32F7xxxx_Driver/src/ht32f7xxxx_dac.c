/*********************************************************************************************************//**
 * @file    ht32f7xxxx_dac.c
 * @version $Rev:: 617          $
 * @date    $Date:: 2026-11-11 #$
 * @brief   This file provides all the DAC firmware functions.
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
#include "ht32f7xxxx_dac.h"

/** @addtogroup HT32F7xxxx_Peripheral_Driver HT32F7xxxx Peripheral Driver
  * @{
  */

/** @defgroup DAC DAC
  * @brief DAC driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup DAC_Private_Define DAC private definitions
  * @{
  */

#define DAC_ENABLE_BIT                   (0x00000001)
#define DAC_ENABLE_TRIG_BIT              (0x00000008)
#define DAC_ENABLE_PDMA_BIT              (0x00000010)
#define DAC_ENABLE_SWTRIG_BIT            (0x00000001)

/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup DAC_Exported_Functions DAC exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the HT_DACn peripheral registers to their default reset values.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @retval None
 ************************************************************************************************************/
void DAC_DeInit(HT_DAC_TypeDef* HT_DACn)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));

  if (HT_DACn == HT_DAC0)
  {
    RSTCUReset.Bit.DAC0 = 1;
  }
  #if (LIBCFG_DAC1)
  else if (HT_DACn == HT_DAC1)
  {
    RSTCUReset.Bit.DAC1 = 1;
  }
  #endif
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Configure the DAC conversion mode.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param ModeSel: specify the conversion mode
 *   This parameter can be one of the following values:
 *     @arg ASYNC_MODE : asynchronous conversion mode
 *     @arg SYNC_MODE  : synchronous conversion mode
 * @retval None
 ************************************************************************************************************/
void DAC_ModeConfig(HT_DAC_TypeDef* HT_DACn, u8 ModeSel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CONVERSION_MODE(ModeSel));

  HT_DACn->CFGR = ModeSel;
}

/*********************************************************************************************************//**
 * @brief Configure the specified DAC channel reference voltage.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @param RefSel: DAC reference voltage source
 *   This parameter can be one of the following values:
 *     @arg DAC_REFERENCE_VDDA : VDDA
 *     @arg DAC_REFERENCE_VREF : VREF
 * @retval None
 ************************************************************************************************************/
void DAC_ReferenceConfig(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 RefSel)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_DAC_REFERENCE(RefSel));

  DACnCH->CR = (DACnCH->CR & ~(3UL << 14)) | RefSel;
}

/*********************************************************************************************************//**
 * @brief Configure the specified DAC channel resolution.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @param ResoSel: DAC Channel Resolution
 *   This parameter can be one of the following values:
 *     @arg DAC_RESOLUTION_8BIT  : 8-bit resolution
 *     @arg DAC_RESOLUTION_12BIT : 12-bit resolution
 * @retval None
 ************************************************************************************************************/
void DAC_ResolutionConfig(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 ResoSel)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_DAC_RESOLUTION(ResoSel));

  DACnCH->CR = (DACnCH->CR & ~(1UL << 2)) | ResoSel;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified DAC Channel output buffer.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void DAC_OutBufCmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    DACnCH->CR = (DACnCH->CR & ~(3UL << 6)) | (2UL << 6);
  }
  else
  {
    DACnCH->CR = (DACnCH->CR & ~(3UL << 6)) | (1UL << 6);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified DAC channel.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void DAC_Cmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    DACnCH->CR |= DAC_ENABLE_BIT;
  }
  else
  {
    DACnCH->CR &= ~(DAC_ENABLE_BIT);
  }
}

/*********************************************************************************************************//**
 * @brief Set the data holding register value for the specified DAC channel.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @param Data: next conversion data.
 * @retval None
 ************************************************************************************************************/
void DAC_SetData(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 Data)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));

  DACnCH->DHR = Data;
}

/*********************************************************************************************************//**
 * @brief Return the data output register value of the specified DAC channel.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @return The selected DAC channel data output value.
 ************************************************************************************************************/
u16 DAC_GetOutData(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));

  return ((u16)DACnCH->DOR);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified DAC interrupts.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_INT_x: Specify the DAC interrupt sources that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg DAC_INT_CH1UD        :
 *     @arg DAC_INT_CH0UD        :
 *     @arg DAC_INT_CH1DOR       :
 *     @arg DAC_INT_CH0DOR       :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void DAC_IntConfig(HT_DAC_TypeDef* HT_DACn, u32 DAC_INT_x, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_INT(DAC_INT_x));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_DACn->IER |= DAC_INT_x;
  }
  else
  {
    HT_DACn->IER &= ~DAC_INT_x;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified DAC interrupt has occurred.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_INT_x: Specify the interrupt status to check.
 *   This parameter can be any combination of the following values:
 *     @arg DAC_INT_CH1UD        :
 *     @arg DAC_INT_CH0UD        :
 *     @arg DAC_INT_CH1DOR       :
 *     @arg DAC_INT_CH0DOR       :
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus DAC_GetIntStatus(HT_DAC_TypeDef* HT_DACn, u32 DAC_INT_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_INT(DAC_INT_x));

  if (HT_DACn->ISR & DAC_INT_x)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear the DAC interrupt flag.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_INT_x: Specify the interrupt status to check.
 *   This parameter can be any combination of the following values:
 *     @arg DAC_INT_CH1UD        :
 *     @arg DAC_INT_CH0UD        :
 *     @arg DAC_INT_CH1DOR       :
 *     @arg DAC_INT_CH0DOR       :
 * @retval None
 ************************************************************************************************************/
void DAC_ClearIntPendingBit(HT_DAC_TypeDef* HT_DACn, u32 DAC_INT_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_INT(DAC_INT_x));

  HT_DACn->ISR = DAC_INT_x;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified DAC Channel for PDMA request.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
 *   This parameter can be one of the following values:
 *     @arg DAC_CH0 : DAC channel 0
 *     @arg DAC_CH1 : DAC channel 1
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void DAC_PDMACmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    DACnCH->CR |= DAC_ENABLE_PDMA_BIT;
  }
  else
  {
    DACnCH->CR &= ~(DAC_ENABLE_PDMA_BIT);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the DAC trigger source for regular channels conversion.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
 *   This parameter can be one of the following values:
 *     @arg DAC_CH0 : DAC channel 0
 *     @arg DAC_CH1 : DAC channel 1
 * @param DAC_TRIG_x:
 *   This parameter can be one of the following values:
 *     @arg DAC_TRIG_SOFTWARE        : S/W trigger
 *     @arg DAC_TRIG_EXTI_n          : where n can be 0 ~ 15
 *     @arg DAC_TRIG_MCTMn_MTO       : where n can be 0 ~ 1
 *     @arg DAC_TRIG_MCTMn_CH0O      : where n can be 0 ~ 1
 *     @arg DAC_TRIG_MCTMn_CH1O      : where n can be 0 ~ 1
 *     @arg DAC_TRIG_MCTMn_CH2O      : where n can be 0 ~ 1
 *     @arg DAC_TRIG_MCTMn_CH3O      : where n can be 0 ~ 1
 *     @arg DAC_TRIG_GPTMn_MTO       : where n can be 0 ~ 1
 *     @arg DAC_TRIG_GPTMn_CH0O      : where n can be 0 ~ 1
 *     @arg DAC_TRIG_GPTMn_CH1O      : where n can be 0 ~ 1
 *     @arg DAC_TRIG_GPTMn_CH2O      : where n can be 0 ~ 1
 *     @arg DAC_TRIG_GPTMn_CH3O      : where n can be 0 ~ 1
 *     @arg DAC_TRIG_BFTMn           : where n can be 0 ~ 1
 *     @arg DAC_TRIG_PWMn_MTO        : where n can be 0 ~ 1
 *     @arg DAC_TRIG_PWMn_CH0O       : where n can be 0 ~ 1
 *     @arg DAC_TRIG_PWMn_CH1O       : where n can be 0 ~ 1
 *     @arg DAC_TRIG_PWMn_CH2O       : where n can be 0 ~ 1
 *     @arg DAC_TRIG_PWMn_CH3O       : where n can be 0 ~ 1
 * @retval None
 ************************************************************************************************************/
void DAC_TrigSourceConfig(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 DAC_TRIG_x)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_DAC_TRIG(DAC_TRIG_x));

  /* Config external trigger conversion source of regular group                                             */
  DACnCH->TCR = DAC_TRIG_x & 0x0000000F;
  DACnCH->TSR = DAC_TRIG_x & (~0x0000000F);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified DAC Channel for regular trigger.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
 *   This parameter can be one of the following values:
 *     @arg DAC_CH0 : DAC channel 0
 *     @arg DAC_CH1 : DAC channel 1
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void DAC_TrigCmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    DACnCH->CR |= DAC_ENABLE_TRIG_BIT;
  }
  else
  {
    DACnCH->CR &= ~(DAC_ENABLE_TRIG_BIT);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable software start of the regular channel conversion of the selected DAC.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
 *   This parameter can be one of the following values:
 *     @arg DAC_CH0 : DAC channel 0
 *     @arg DAC_CH1 : DAC channel 1
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void DAC_SoftwareStartConvCmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Start Conversion                                                                                       */
  if (NewState != DISABLE)
  {
    DACnCH->TSR |= DAC_ENABLE_SWTRIG_BIT;
  }
  else
  {
    DACnCH->TSR &= ~(DAC_ENABLE_SWTRIG_BIT);
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
