/*********************************************************************************************************//**
 * @file    CAN/Recv_REMOTE_ManualReply/ht32_board_config.h
 * @version $Rev:: 397          $
 * @date    $Date:: 2025-11-05 #$
 * @brief   The header file of board configuration.
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
#ifndef __HT32_BOARD_CONFIG_H
#define __HT32_BOARD_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#if defined(USE_HT32F72388_SK)
  #define HTCFG_CAN_IPN                           CAN0
  #define _HTCFG_CAN_TX_GPIOX                     A
  #define _HTCFG_CAN_TX_GPION                     0
  #define _HTCFG_CAN_RX_GPIOX                     A
  #define _HTCFG_CAN_RX_GPION                     1
#endif

#define HTCFG_CAN_TX_GPIO_ID                      STRCAT2(GPIO_P,         _HTCFG_CAN_TX_GPIOX)
#define HTCFG_CAN_RX_GPIO_ID                      STRCAT2(GPIO_P,         _HTCFG_CAN_RX_GPIOX)
#define HTCFG_CAN_TX_AFIO_PIN                     STRCAT2(AFIO_PIN_,      _HTCFG_CAN_TX_GPION)
#define HTCFG_CAN_RX_AFIO_PIN                     STRCAT2(AFIO_PIN_,      _HTCFG_CAN_RX_GPION)
#define HTCFG_CAN_PORT                            STRCAT2(HT_,            HTCFG_CAN_IPN)
#define HTCFG_CAN_CKCU_PCLK                       STRCAT2(CKCU_PCLK_,     HTCFG_CAN_IPN)

#define HTCFG_CAN_STB_GPIO_CK                     STRCAT2(P,              _HTCFG_CAN_STB_GPIOX)
#define HTCFG_CAN_STB_GPIO_ID                     STRCAT2(GPIO_P,         _HTCFG_CAN_STB_GPIOX)
#define HTCFG_CAN_STB_AFIO_PIN                    STRCAT2(AFIO_PIN_,      _HTCFG_CAN_STB_GPION)
#define HTCFG_CAN_STB_GPIO_PORT                   STRCAT2(HT_GPIO,        _HTCFG_CAN_STB_GPIOX)

#ifdef __cplusplus
}
#endif

#endif
