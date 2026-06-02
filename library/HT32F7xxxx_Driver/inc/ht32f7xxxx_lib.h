/*********************************************************************************************************//**
 * @file    ht32f7xxxx_lib.h
 * @version $Rev:: 212          $
 * @date    $Date:: 2025-05-06 #$
 * @brief   The header file includes all the header files of the libraries.
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
#ifndef __HT32F7XXXX_LIB_H
#define __HT32F7XXXX_LIB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#define HT32_FWLIB_VER                  (999999) // Auto update when package
#define HT32_FWLIB_SVN                  (999999) // Auto update when package

#if defined(USE_HT32F72368_78_88)
  #include "ht32f72368_78_88_libcfg.h"
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "ht32f7xxxx_conf.h"

#if (HT32_LIB_DEBUG == 1)
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed.
  *   If expr is true, it returns no value.
  * @retval None
  */
#define Assert_Param(expr) ((expr) ? (void)0 : assert_error((u8 *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- ------------------------------*/
void assert_error(u8* file, u32 line);
#else

#define Assert_Param(expr) ((void)0)

#endif /* DEBUG --------------------------------------------------------------------------------------------*/


#if _ADC
  #include "ht32f7xxxx_adc.h"
#endif

#if _AES && LIBCFG_AES
  #include "ht32f7xxxx_aes.h"
#endif

#if _BFTM
  #include "ht32f7xxxx_bftm.h"
#endif

#if _CAN && LIBCFG_CAN0
  #include "ht32f7xxxx_can.h"
#endif

#if _CKCU
  #include "ht32f7xxxx_ckcu.h"
#endif

#if _CMP && LIBCFG_CMP
  #include "ht32f7xxxx_cmp.h"
#endif

#if _CORDIC && LIBCFG_CORDIC
  #include "ht32f7xxxx_cordic.h"
#endif

#if _CRC && LIBCFG_CRC
  #include "ht32f7xxxx_crc.h"
#endif

#if _DAC && (LIBCFG_DAC0 || LIBCFG_DAC1)
  #include "ht32f7xxxx_dac.h"
#endif

#if _DAC && LIBCFG_DACDUAL16
  #include "ht32f7xxxx_dac_dual16.h"
#endif

#if _DIV && LIBCFG_DIV
  #include "ht32f7xxxx_div.h"
#endif

#if _EBI && LIBCFG_EBI
  #include "ht32f7xxxx_ebi.h"
#endif

#if _EXTI
  #include "ht32f7xxxx_exti.h"
#endif

#if _FLASH
  #include "ht32f7xxxx_flash.h"
#endif

#if _GPIO
  #include "ht32f7xxxx_gpio.h"
#endif

#if _GPTM
  #include "ht32f7xxxx_tm_type.h"
  #include "ht32f7xxxx_tm.h"
#endif

#if _I2C
  #include "ht32f7xxxx_i2c.h"
#endif

#if _I2S && LIBCFG_I2S
  #include "ht32f7xxxx_i2s.h"
#endif

#if _LCD && LIBCFG_LCD
  #include "ht32f7xxxx_lcd.h"
#endif

#if _LEDC && LIBCFG_LEDC
  #include "ht32f7xxxx_ledc.h"
#endif

#if _MCTM && LIBCFG_MCTM0
  #include "ht32f7xxxx_tm_type.h"
  #include "ht32f7xxxx_tm.h"
  #include "ht32f7xxxx_mctm.h"
#endif

#if _MIDI && LIBCFG_MIDI
  #include "ht32f7xxxx_midi.h"
#endif

#if _OPA && LIBCFG_OPA
  #include "ht32f7xxxx_opa.h"
#endif

#if _PDMA && LIBCFG_PDMA
  #include "ht32f7xxxx_pdma.h"
#endif

#if _PGA && LIBCFG_PGA
  #include "ht32f7xxxx_pga.h"
#endif

#if _PID && LIBCFG_PID
  #include "ht32f7xxxx_pid.h"
#endif

#if _PWRCU
  #include "ht32f7xxxx_pwrcu.h"
#endif

#if _RAMECC && LIBCFG_RAMECC
  #include "ht32f7xxxx_ramecc.h"
#endif

#if _RSTCU
  #include "ht32f7xxxx_rstcu.h"
#endif

#if _RTC
  #include "ht32f7xxxx_rtc.h"
#endif

#if _SCI && LIBCFG_SCI0
  #include "ht32f7xxxx_sci.h"
#endif

#if _SCTM
  #include "ht32f7xxxx_tm_type.h"
  #include "ht32f7xxxx_tm.h"
#endif

#if _SLED && LIBCFG_SLED0
  #include "ht32f7xxxx_sled.h"
#endif

#if _SPI
  #include "ht32f7xxxx_spi.h"
#endif

#if _TKEY && LIBCFG_TKEY
  #include "ht32f7xxxx_tkey.h"
#endif

#if _RNG && LIBCFG_RNG
  #include "ht32f7xxxx_rng.h"
#endif

#if _USART
  #include "ht32f7xxxx_usart.h"
#endif

#if _USB && LIBCFG_USBD
  #include "ht32f7xxxx_usbd.h"
#endif

#if _WDT
  #include "ht32f7xxxx_wdt.h"
#endif

#if _MISC
  #include "ht32_cm0plus_misc.h"
#endif

#if _SERIAL
  #include "ht32_serial.h"
#endif

#if _SWDIV
  #include "ht32_div.h"
#endif

#if _SWRAND
  #include "ht32_rand.h"
#endif

#if (_RETARGET)
  #if defined (__GNUC__)
    #undef getchar
    #define getchar SERIAL_GetChar
  #endif
#endif

#ifdef HTCFG_TIME_IPSEL
#include "ht32_time.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
