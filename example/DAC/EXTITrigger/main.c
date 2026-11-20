/*********************************************************************************************************//**
 * @file    DAC/EXTITrigger/main.c
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

/** @addtogroup EXTITrigger
  * @{
  */

/* Settings ------------------------------------------------------------------------------------------------*/
#define MIN_MILLI_V                      (0)     /* 0V                                                      */
#define MAX_MILLI_V                      (3300)  /* 3.3V                                                    */

/* Private macro -------------------------------------------------------------------------------------------*/
#define DAC_CONV_DATA(VALUE)             ((VALUE * 4095)/3300)              /* DAC use 12-bit scaler        */

/* Private function prototypes -----------------------------------------------------------------------------*/
void DAC_Configuration(void);
void EXTI_Configuration(void);
void DAC_MainRoutine(void);

/* Global variables ----------------------------------------------------------------------------------------*/
bool gWaveTrigger = FALSE;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  DAC_Configuration();

  EXTI_Configuration();

  /* Enable DAC                                                                                             */
  DAC_Cmd(HTCFG_DAC_PORT, HTCFG_DAC_CH, ENABLE);

  /* Enable EXTI channel                                                                                    */
  EXTI_IntConfig(HTCFG_KEY1_EXTI_CH, ENABLE);

  while (1)
  {
    DAC_MainRoutine();
  }
}

/*********************************************************************************************************//**
  * @brief  DAC main routine.
  * @retval None
  ***********************************************************************************************************/
void DAC_MainRoutine(void)
{
  if (gWaveTrigger == TRUE)
  {
    DAC_SetData(HTCFG_DAC_PORT, HTCFG_DAC_CH, DAC_CONV_DATA(MAX_MILLI_V));
  }
  else
  {
    DAC_SetData(HTCFG_DAC_PORT, HTCFG_DAC_CH, DAC_CONV_DATA(MIN_MILLI_V));
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

  /* Set EXTI as DAC trigger source                                                                         */
  DAC_TrigSourceConfig(HTCFG_DAC_PORT, HTCFG_DAC_CH, HTCFG_DAC_TRIG_EXTI);

  /* Enable DAC trigger                                                                                     */
  DAC_TrigCmd(HTCFG_DAC_PORT, HTCFG_DAC_CH, ENABLE);

  /* Enable DAC channel interrupt                                                                           */
  DAC_IntConfig(HTCFG_DAC_PORT, DAC_INT_CH0DOR, ENABLE);

  /* Enable COMP_DAC interrupt in NVIC                                                                      */
  NVIC_EnableIRQ(DAC_IRQn);
}

/*********************************************************************************************************//**
  * @brief  EXTI configuration.
  * @retval None
  ***********************************************************************************************************/
void EXTI_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_KEY1_GPIO_CK = 1;
    CKCUClock.Bit.EXTI = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode of input pins                                                                      */
  AFIO_GPxConfig(HTCFG_KEY1_GPIO_ID, HTCFG_KEY1_AFIO_PIN, AFIO_FUN_GPIO);

  /* Enable GPIO input                                                                                      */
  GPIO_InputConfig(HTCFG_KEY1_GPIO_PORT, HTCFG_KEY1_GPIO_PIN, ENABLE);

  /* Configure GPIO pull resistor of input pins                                                             */
  GPIO_PullResistorConfig(HTCFG_KEY1_GPIO_PORT, HTCFG_KEY1_GPIO_PIN, GPIO_PR_DISABLE);

  /* Connect EXTI channel to GPIO Pin                                                                       */
  AFIO_EXTISourceConfig(HTCFG_KEY1_AFIO_EXTI_CH, HTCFG_KEY1_AFIO_ESS);

  { /* Configure EXTI channel n as falling edge trigger                                                     */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    EXTI_InitTypeDef EXTI_InitStruct;

    EXTI_InitStruct.EXTI_Channel = HTCFG_KEY1_EXTI_CH;
    EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;
    EXTI_InitStruct.EXTI_DebounceCnt = 0;
    EXTI_InitStruct.EXTI_IntType = EXTI_NEGATIVE_EDGE;
    EXTI_Init(&EXTI_InitStruct);
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
