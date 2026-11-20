/*********************************************************************************************************//**
 * @file    DAC/TMTrigger_PDMA/main.c
 * @version $Rev:: 606          $
 * @date    $Date:: 2026-11-05 #$
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
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup DAC_example DAC
  * @{
  */

/** @addtogroup TMTrigger_PDMA
  * @{
  */

/* Settings ------------------------------------------------------------------------------------------------*/
#define WAVE_DATA_LENGTH  (10)

/* Private function prototypes -----------------------------------------------------------------------------*/
void PDMA_Configuration(void);
void DAC_Configuration(void);
void TM_Configuration(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 gWaveTable[WAVE_DATA_LENGTH] = {0, 4095, 0, 4095, 0, 4095, 0, 4095, 0, 4095};

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  PDMA_Configuration();

  DAC_Configuration();

  TM_Configuration();

  /* Enable DAC                                                                                             */
  DAC_Cmd(HTCFG_DAC_PORT, HTCFG_DAC_CH, ENABLE);

  TM_Cmd(HTCFG_TM_PORT, ENABLE);

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  PDMA configuration.
  * @retval None
  ***********************************************************************************************************/
void PDMA_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.PDMA = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Configure PDMA channel to move ADC result from ADC->DR[0] to TM CHnCCR                               */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    PDMACH_InitTypeDef PDMACH_InitStructure;
    HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HTCFG_DAC_PORT->DACCH0 + HTCFG_DAC_CH * 8 * 4);

    PDMACH_InitStructure.PDMACH_SrcAddr = (u32)gWaveTable;
    PDMACH_InitStructure.PDMACH_DstAddr = (u32)&DACnCH->DHR;
    PDMACH_InitStructure.PDMACH_BlkCnt = WAVE_DATA_LENGTH;
    PDMACH_InitStructure.PDMACH_BlkLen = 1;
    PDMACH_InitStructure.PDMACH_DataSize = WIDTH_32BIT;
    PDMACH_InitStructure.PDMACH_Priority = VH_PRIO;
    PDMACH_InitStructure.PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_FIX | AUTO_RELOAD;
    PDMA_Config(HTCFG_DAC_PDMA_CH, &PDMACH_InitStructure);
    PDMA_EnaCmd(HTCFG_DAC_PDMA_CH, ENABLE);
  }
}

/*********************************************************************************************************//**
  * @brief  DAC configuration.
  * @retval None
  ***********************************************************************************************************/
void DAC_Configuration(void)
{
  {
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    /* Enable peripherals clocks of DAC, AFIO                                                               */
    CKCUClock.Bit.AFIO                = 1;
    CKCUClock.Bit.HTCFG_DAC_IPN       = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Config DAC pins function                                                                               */
  AFIO_GPxConfig(HTCFG_DAC_GPIO_ID, HTCFG_DAC_AFIO_PIN, HTCFG_DAC_AFIO_MODE);

  /* Configure DAC0 channel 0                                                                               */
  /* Configure the VDDA to DAC channel reference voltage                                                    */
  DAC_ReferenceConfig(HTCFG_DAC_PORT, HTCFG_DAC_CH, DAC_REFERENCE_VDDA);

  /* Configure the 12-bit resolution to DAC channel                                                         */
  DAC_ResolutionConfig(HTCFG_DAC_PORT, HTCFG_DAC_CH, DAC_RESOLUTION_12BIT);

  /* Provide DAC channel output with driver                                                                 */
  DAC_OutBufCmd(HTCFG_DAC_PORT, HTCFG_DAC_CH, ENABLE);

  /* !!! NOTICE !!!
     The trigger source must be kept inactive before DAC enable. Since the "TM_TimeBaseInit()" will
     generate an Update Event via the MTO pin, you shall configure the DAC trigger source after
     "TM_Configuration()" when the DAC trigger source is MTO.
  */
  /* Set TM MTO as DAC trigger source                                                                       */
  DAC_TrigSourceConfig(HTCFG_DAC_PORT, HTCFG_DAC_CH, HTCFG_DAC_TRIG_TM);

  /* Enable DAC trigger                                                                                     */
  DAC_TrigCmd(HTCFG_DAC_PORT, HTCFG_DAC_CH, ENABLE);

  /* Enable PDMA Channel                                                                                    */
  DAC_PDMACmd(HTCFG_DAC_PORT, HTCFG_DAC_CH, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  TM configuration.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  /* Configure timer channel n as PWM output mode used to represent potentiometer's level                   */

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_TM_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = 100 - 1;
    TimeBaseInit.CounterReload = 4096 - 1;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    /* !!! NOTICE !!!
       "PSCReloadTime = TM_PSC_RLD_IMMEDIATE" writes the TM EVRG UEV1G bit and generates a Update Event via
       the MTO pin (MTO default is in Reset mode).
    */
    TM_TimeBaseInit(HTCFG_TM_PORT, &TimeBaseInit);
  }

  /* Update event 1 is used as MTO trigger output.                                                          */
  TM_MMSELConfig(HTCFG_TM_PORT, TM_MMSEL_UPDATE);
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
