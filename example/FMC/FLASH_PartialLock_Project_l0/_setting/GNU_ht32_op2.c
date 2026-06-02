/*********************************************************************************************************//**
 * @file    ht32_op2.c
 * @version V0.02
 * @date    2025-04-11
 * @brief   The option byre settings of HT32 Series.
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

/* How to use-----------------------------------------------------------------------------------------------*/
/*
    Step1:  Modify the Option Bytes values below.
            OB_KEY0 ~ OB_KEY3
            KPCTL_MASSERASE_OPT
            KPCTL_KPINVALID_OPT
            KPCTL_MAXMISMATCH_OPT
            OB_KPPP0 ~ OB_KPPP3
            D_OB_KEY0 ~ D_OB_KEY3
            FLASH_MPREGnCR_OPT
            FLASH_MPREGnCR_CONTROL
            FLASH_MPREGnCR_MODE
            FLASH_MPREGn_STARTPAGE
            FLASH_MPREGn_ENDPAGE

    Step2:  Make sure the FLASH_OPT_PARTIALLOCK = 1. It designed to disable Flash Option byte setting (when
            FLASH_OPT_PARTIALLOCK = 0).

    Notice: If the Output format is set to "Raw binary" (in Output Converter of IAR Project Options), the
            conversion time may be too long (since the address is from main flash to option bytes, 0x0 to
            0x1ff0xxxx, 512 MB). Please change the Output format to "Intel Extended hex" and use third party
            Hex to Bin tool to convert binary file if need.
*/

/* Settings ------------------------------------------------------------------------------------------------*/
#define FLASH_OPT_PARTIALLOCK   (1)    /*!< 0: Disable Flash Option Bytes setting                           */
                                       /*!< 1: Enable Option Bytes setting                                  */

#define OB_KEY0        (0x5555AAAA)    /*!< Protection Key Value                                            */
#define OB_KEY1        (0x5555AAAA)    /*!< Protection Key Value                                            */
#define OB_KEY2        (0x5555AAAA)    /*!< Protection Key Value                                            */
#define OB_KEY3        (0x5555AAAA)    /*!< Protection Key Value                                            */

/* !!! Note: Setting 0 means completely locked and cannot be unlocked.                                      */
#define KPCNT_OPT      (0xFF)          /*!< Maximum Error Key Mismatch Counter: OB_KPCNT (0x1FF00094)       */

#define KPCTL_MASSERASE_OPT     (0)    /*!< 0: Enable Mass Erase, 1: Disable Mass Erase                     */

#define KPCTL_KPINVALID_OPT     (1)    /*!< Invalid Key Protection When Key Value Match                     */
#define KPCTL_MAXMISMATCH_OPT   (1)    /*!< Maximum Error Key Mismatch Trigger Option                       */
                                       /*!< 0: Return Mismatch                                              */
                                       /*!< 1: Hold MCU                                                     */
                                       /*!< 2: Mass Erase                                                   */

/* !!! Note: One OB_KPPP bit for setting n Pages. Check FMC chapter of User Manual for detailed.            */
#define OB_KPPP0       (0x00000030)    /*!< Main Flash Key Page Erase/Program Protection                    */
#define OB_KPPP1       (0x00000000)    /*!< Main Flash Key Page Erase/Program Protection                    */
#define OB_KPPP2       (0x00000000)    /*!< Main Flash Key Page Erase/Program Protection                    */
#define OB_KPPP3       (0x00000000)    /*!< Main Flash Key Page Erase/Program Protection                    */

#define D_OB_KEY0      (0x5555AAAA)    /*!< Double Check Protection Key Value                               */
#define D_OB_KEY1      (0x5555AAAA)    /*!< Double Check Protection Key Value                               */
#define D_OB_KEY2      (0x5555AAAA)    /*!< Double Check Protection Key Value                               */
#define D_OB_KEY3      (0x5555AAAA)    /*!< Double Check Protection Key Value                               */

/* Flash ROM Region 0 Protection                                                                            */
#define FLASH_MPREG0CR_OPT      (1)    /*!< 0: Disable Region 0 Flash Option Bytes setting                  */
                                       /*!< 1: Enable Region 0 Option Bytes setting                         */
#define MPREG0CR_ACCESSTYPE_OPT (0)    /*!< 0: Protection, 1: Debug                                         */
#define MPREG0CR_MODE_OPT       (0)    /*!< 0: ICODE, 1: DCODE, 2: Access by Key                            */
#define MPREG0_STARTPAGE_OPT   (32)    /*!< Start Page Range: 8 ~ 1022                                      */
#define MPREG0_ENDPAGE_OPT     (39)    /*!< End Page Range: 8 ~ 1022                                        */

/* Flash ROM Region 1 Protection                                                                            */
#define FLASH_MPREG1CR_OPT      (1)    /*!< 1: Enable Region 0 Option Bytes setting,
                                            0: Disable Region 0 Flash Option Bytes setting                  */
#define MPREG1CR_ACCESSTYPE_OPT (0)    /*!< 0: Protection, 1: Debug                                         */
#define MPREG1CR_MODE_OPT       (1)    /*!< 0: ICODE, 1: DCODE, 2: Access by Key                            */
#define MPREG1_STARTPAGE_OPT   (40)    /*!< Start Page Range: 8 ~ 1022                                      */
#define MPREG1_ENDPAGE_OPT     (47)    /*!< End Page Range: 8 ~ 1022                                        */

/* Flash ROM Region 2 Protection                                                                            */
#define FLASH_MPREG2CR_OPT      (0)    /*!< 1: Enable Region 0 Option Bytes setting,
                                            0: Disable Region 0 Flash Option Bytes setting                  */
#define MPREG2CR_ACCESSTYPE_OPT (0)    /*!< 0: Protection, 1: Debug                                         */
#define MPREG2CR_MODE_OPT       (0)    /*!< 0: ICODE, 1: DCODE, 2: Access by Key                            */
#define MPREG2_STARTPAGE_OPT    (8)    /*!< Start Page Range: 8 ~ 1022                                      */
#define MPREG2_ENDPAGE_OPT      (8)    /*!< End Page Range: 8 ~ 1022                                        */

/* Flash ROM Region 3 Protection                                                                            */
#define FLASH_MPREG3CR_OPT      (0)    /*!< 1: Enable Region 0 Option Bytes setting,
                                            0: Disable Region 0 Flash Option Bytes setting                  */
#define MPREG3CR_ACCESSTYPE_OPT (0)    /*!< 0: Protection, 1: Debug                                         */
#define MPREG3CR_MODE_OPT       (0)    /*!< 0: ICODE, 1: DCODE, 2: Access by Key                            */
#define MPREG3_STARTPAGE_OPT    (8)    /*!< Start Page (8 ~ 1022)                                           */
#define MPREG3_ENDPAGE_OPT      (8)    /*!< End Page (8 ~ 1022)                                             */

/*----------------------------------------------------------------------------------------------------------*/
/* DO NOT MODIFY                                                                                            */
/*----------------------------------------------------------------------------------------------------------*/
#define OPT_RES   (0xFFFFFFFF)

#if (FLASH_OPT_PARTIALLOCK == 1)
  #if ((OB_KEY0 != D_OB_KEY0) || (OB_KEY1 != D_OB_KEY1) || (OB_KEY2 != D_OB_KEY2) || (OB_KEY3 != D_OB_KEY3))
    #error "The value of ProtectionKey(OB_KEYn) does not match the DoubleCheckProtectionKey(D_OB_KEYn)."
  #endif
#endif

// Set OB_KPCTL
#if (FLASH_OPT_PARTIALLOCK == 1)
  #define OB_KPCTL_OPT          (0x0000005A)
#else
  #define OB_KPCTL_OPT          (0x000000FF)
#endif

#if (KPCTL_MASSERASE_OPT == 1)
  #define OB_KPCTL_MASSERASE    (0x00005A00)
#else
  #define OB_KPCTL_MASSERASE    (0x0000FF00)
#endif

#if (KPCTL_KPINVALID_OPT == 1)
  #define OB_KPCTL_KPINVALID    (0x005A0000)
#else
  #define OB_KPCTL_KPINVALID    (0x00FF0000)
#endif

#if (KPCTL_MAXMISMATCH_OPT == 1)
  #define OB_KPCTL_MAXMISMATCH  (0x5A000000)
#elif (KPCTL_MAXMISMATCH_OPT == 2)
  #define OB_KPCTL_MAXMISMATCH  (0xA5000000)
#else
  #define OB_KPCTL_MAXMISMATCH  (0xFF000000)
#endif

#define OB_KPCTL                (OB_KPCTL_OPT | OB_KPCTL_MASSERASE | OB_KPCTL_KPINVALID | OB_KPCTL_MAXMISMATCH)

#define OB_KPCNT                (KPCNT_OPT | 0xFFFFFF00)

// Set OB_MPREG0
#if (FLASH_MPREG0CR_OPT == 1)
  #if (MPREG0CR_ACCESSTYPE_OPT == 0)
    #define OB_MPREG0CR_CONTROL (0x0000005A)
  #elif (MPREG0CR_ACCESSTYPE_OPT == 1)
    #define OB_MPREG0CR_CONTROL (0x00000035)
  #else
    #define OB_MPREG0CR_CONTROL (0x000000FF)
  #endif

  #if (MPREG0CR_MODE_OPT == 0)
    #define OB_MPREG0CR_MODE    (0x00005A00)
  #elif (MPREG0CR_MODE_OPT == 1)
    #define OB_MPREG0CR_MODE    (0x00003500)
  #elif (MPREG0CR_MODE_OPT == 2)
    #define OB_MPREG0CR_MODE    (0x0000A300)
  #else
    #define OB_MPREG0CR_MODE    (0x0000FF00)
  #endif
#endif

#if (FLASH_MPREG0CR_OPT == 1)
  #define OB_MPREG0CR           (0xFFFF0000 | OB_MPREG0CR_CONTROL | OB_MPREG0CR_MODE)
  #define OB_MPREG0             ((0xFC000000 | MPREG0_ENDPAGE_OPT << 16) | 0x0000FC00 | MPREG0_STARTPAGE_OPT)
#else
  #define OB_MPREG0CR           (0xFFFFFFFF)
  #define OB_MPREG0             (0xFFFFFFFF)
#endif

// Set OB_MPREG1
#if (FLASH_MPREG1CR_OPT == 1)
  #if (MPREG1CR_ACCESSTYPE_OPT == 0)
    #define OB_MPREG1CR_CONTROL (0x0000005A)
  #elif (MPREG1CR_ACCESSTYPE_OPT == 1)
    #define OB_MPREG1CR_CONTROL (0x00000035)
  #else
    #define OB_MPREG1CR_CONTROL (0x000000FF)
  #endif

  #if (MPREG1CR_MODE_OPT == 0)
    #define OB_MPREG1CR_MODE    (0x00005A00)
  #elif (MPREG1CR_MODE_OPT == 1)
    #define OB_MPREG1CR_MODE    (0x00003500)
  #elif (MPREG1CR_MODE_OPT == 2)
    #define OB_MPREG1CR_MODE    (0x0000A300)
  #else
    #define OB_MPREG1CR_MODE    (0x0000FF00)
  #endif
#endif

#if (FLASH_MPREG1CR_OPT == 1)
  #define OB_MPREG1CR           (0xFFFF0000 | OB_MPREG1CR_CONTROL | OB_MPREG1CR_MODE)
  #define OB_MPREG1             ((0xFC000000 | MPREG1_ENDPAGE_OPT << 16) | 0x0000FC00 | MPREG1_STARTPAGE_OPT)
#else
  #define OB_MPREG1CR           (0xFFFFFFFF)
  #define OB_MPREG1             (0xFFFFFFFF)
#endif

// Set OB_MPREG2
#if (FLASH_MPREG2CR_OPT == 1)
  #if (MPREG2CR_ACCESSTYPE_OPT == 0)
    #define OB_MPREG2CR_CONTROL (0x0000005A)
  #elif (MPREG2CR_ACCESSTYPE_OPT == 1)
    #define OB_MPREG2CR_CONTROL (0x00000035)
  #else
    #define OB_MPREG2CR_CONTROL (0x000000FF)
  #endif

  #if (MPREG2CR_MODE_OPT == 0)
    #define OB_MPREG2CR_MODE    (0x00005A00)
  #elif (MPREG2CR_MODE_OPT == 1)
    #define OB_MPREG2CR_MODE    (0x00003500)
  #elif (MPREG2CR_MODE_OPT == 2)
    #define OB_MPREG2CR_MODE    (0x0000A300)
  #else
    #define OB_MPREG2CR_MODE    (0x0000FF00)
  #endif
#endif

#if (FLASH_MPREG2CR_OPT == 1)
  #define OB_MPREG2CR           (0xFFFF0000 | OB_MPREG2CR_CONTROL | OB_MPREG2CR_MODE)
  #define OB_MPREG2             ((0xFC000000 | MPREG2_ENDPAGE_OPT << 16) | 0x0000FC00 | MPREG2_STARTPAGE_OPT)
#else
  #define OB_MPREG2CR           (0xFFFFFFFF)
  #define OB_MPREG2             (0xFFFFFFFF)
#endif

// Set OB_MPREG3
#if (FLASH_MPREG3CR_OPT == 1)
  #if (MPREG3CR_ACCESSTYPE_OPT == 0)
    #define OB_MPREG3CR_CONTROL (0x0000005A)
  #elif (MPREG3CR_ACCESSTYPE_OPT == 1)
    #define OB_MPREG3CR_CONTROL (0x00000035)
  #else
    #define OB_MPREG3CR_CONTROL (0x000000FF)
  #endif

  #if (MPREG3CR_MODE_OPT == 0)
    #define OB_MPREG3CR_MODE    (0x00005A00)
  #elif (MPREG3CR_MODE_OPT == 1)
    #define OB_MPREG3CR_MODE    (0x00003500)
  #elif (MPREG3CR_MODE_OPT == 2)
    #define OB_MPREG3CR_MODE    (0x0000A300)
  #else
    #define OB_MPREG3CR_MODE    (0x0000FF00)
  #endif
#endif

#if (FLASH_MPREG3CR_OPT == 1)
  #define OB_MPREG3CR           (0xFFFF0000 | OB_MPREG3CR_CONTROL | OB_MPREG3CR_MODE)
  #define OB_MPREG3             ((0xFC000000 | MPREG3_ENDPAGE_OPT << 16) | 0x0000FC00 | MPREG3_STARTPAGE_OPT)
#else
  #define OB_MPREG3CR           (0xFFFFFFFF)
  #define OB_MPREG3             (0xFFFFFFFF)
#endif

#if ((FLASH_MPREG0CR_OPT == 1) || (FLASH_MPREG1CR_OPT == 1) || (FLASH_MPREG2CR_OPT == 1) || (FLASH_MPREG3CR_OPT == 1))
  #if (FLASH_OPT_PARTIALLOCK == 0)
    #error "Protect flash rom region must enable flash partial lock."
  #endif
  #if (KPCNT_OPT <= 1)
    #if ((FLASH_MPREG0CR_OPT == 1) && (MPREG0CR_MODE_OPT == 2))
      #error "Max mismatch value must greater than 1, when region 0 mode is access by key."
    #endif
    #if ((FLASH_MPREG1CR_OPT == 1) && (MPREG1CR_MODE_OPT == 2))
      #error "Max mismatch value must greater than 1, when region 1 mode is access by key."
    #endif
    #if ((FLASH_MPREG2CR_OPT == 1) && (MPREG2CR_MODE_OPT == 2))
      #error "Max mismatch value must greater than 1, when region 2 mode is access by key."
    #endif
    #if ((FLASH_MPREG3CR_OPT == 1) && (MPREG3CR_MODE_OPT == 2))
      #error "Max mismatch value must greater than 1, when region 3 mode is access by key."
    #endif
  #endif
  #if ((FLASH_MPREG0CR_OPT == 1) && \
       (MPREG0_STARTPAGE_OPT <= 0x007) || (MPREG0_ENDPAGE_OPT <= 0x007) || \
       (MPREG0_STARTPAGE_OPT >= 0x3FF) || (MPREG0_ENDPAGE_OPT >= 0x3FF))
    #error "Protect flash rom region 0 start and end Page should set in range 0x008 to 0x3FE."
  #endif
  #if ((FLASH_MPREG1CR_OPT == 1) && \
       (MPREG1_STARTPAGE_OPT <= 0x007) || (MPREG1_ENDPAGE_OPT <= 0x007) || \
       (MPREG1_STARTPAGE_OPT >= 0x3FF) || (MPREG1_ENDPAGE_OPT >= 0x3FF))
    #error "Protect flash rom region 1 start and end Page should set in range 0x008 to 0x3FE."
  #endif
  #if ((FLASH_MPREG2CR_OPT == 1) && \
       (MPREG2_STARTPAGE_OPT <= 0x007) || (MPREG2_ENDPAGE_OPT <= 0x007) || \
       (MPREG2_STARTPAGE_OPT >= 0x3FF) || (MPREG2_ENDPAGE_OPT >= 0x3FF))
    #error "Protect flash rom region 2 start and end Page should set in range 0x008 to 0x3FE."
  #endif
  #if ((FLASH_MPREG3CR_OPT == 1) && \
       (MPREG3_STARTPAGE_OPT <= 0x007) || (MPREG3_ENDPAGE_OPT <= 0x007) || \
       (MPREG3_STARTPAGE_OPT >= 0x3FF) || (MPREG3_ENDPAGE_OPT >= 0x3FF))
    #error "Protect flash rom region 3 start and end Page should set in range 0x008 to 0x3FE."
  #endif
  #if ((FLASH_MPREG0CR_OPT == 1) && \
       (MPREG0_STARTPAGE_OPT > MPREG0_ENDPAGE_OPT))
    #error "Protect flash_rom region 0 start page must less than End Page."
  #endif
  #if ((FLASH_MPREG1CR_OPT == 1) && \
       (MPREG1_STARTPAGE_OPT > MPREG1_ENDPAGE_OPT))
    #error "Protect flash rom region 1 start page must less than End Page."
  #endif
  #if ((FLASH_MPREG2CR_OPT == 1) && \
       (MPREG2_STARTPAGE_OPT > MPREG2_ENDPAGE_OPT))
    #error "Protect flash rom region 2 start page must less than End Page."
  #endif
  #if ((FLASH_MPREG3CR_OPT == 1) && \
       (MPREG3_STARTPAGE_OPT > MPREG3_ENDPAGE_OPT))
    #error "Protect flash rom region 3 start page must less than End Page."
  #endif
  #if ((FLASH_MPREG0CR_OPT == 1) && (FLASH_MPREG1CR_OPT == 1))
    #if (((MPREG0_STARTPAGE_OPT >= MPREG1_STARTPAGE_OPT) && (MPREG0_STARTPAGE_OPT <= MPREG1_ENDPAGE_OPT)) || \
         ((MPREG0_ENDPAGE_OPT   >= MPREG1_STARTPAGE_OPT) && (MPREG0_ENDPAGE_OPT   <= MPREG1_ENDPAGE_OPT)))
      #error "Protect_flash_rom_region_0_range_overlaps_with_region_1_range."
    #endif
  #endif
  #if ((FLASH_MPREG0CR_OPT == 1) && (FLASH_MPREG2CR_OPT == 1))
    #if (((MPREG0_STARTPAGE_OPT >= MPREG2_STARTPAGE_OPT) && (MPREG0_STARTPAGE_OPT <= MPREG2_ENDPAGE_OPT)) || \
         ((MPREG0_ENDPAGE_OPT   >= MPREG2_STARTPAGE_OPT) && (MPREG0_ENDPAGE_OPT   <= MPREG2_ENDPAGE_OPT)))
      #error "Protect flash rom region 0 range overlaps with region 2 range."
    #endif
  #endif
  #if ((FLASH_MPREG0CR_OPT == 1) && (FLASH_MPREG3CR_OPT == 1))
    #if (((MPREG0_STARTPAGE_OPT >= MPREG3_STARTPAGE_OPT) && (MPREG0_STARTPAGE_OPT <= MPREG3_ENDPAGE_OPT)) || \
         ((MPREG0_ENDPAGE_OPT   >= MPREG3_STARTPAGE_OPT) && (MPREG0_ENDPAGE_OPT   <= MPREG3_ENDPAGE_OPT)))
      #error "Protect flash rom region 0 range overlaps with region 3 range."
    #endif
  #endif
  #if ((FLASH_MPREG1CR_OPT == 1) && (FLASH_MPREG2CR_OPT == 1))
    #if (((MPREG1_STARTPAGE_OPT >= MPREG2_STARTPAGE_OPT) && (MPREG1_STARTPAGE_OPT <= MPREG2_ENDPAGE_OPT)) || \
         ((MPREG1_ENDPAGE_OPT   >= MPREG2_STARTPAGE_OPT) && (MPREG1_ENDPAGE_OPT   <= MPREG2_ENDPAGE_OPT)))
      #error "Protect flash rom region 1 range overlaps with region 2 range."
    #endif
  #endif
  #if ((FLASH_MPREG1CR_OPT == 1) && (FLASH_MPREG3CR_OPT == 1))
    #if (((MPREG1_STARTPAGE_OPT >= MPREG3_STARTPAGE_OPT) && (MPREG1_STARTPAGE_OPT <= MPREG3_ENDPAGE_OPT)) || \
         ((MPREG1_ENDPAGE_OPT   >= MPREG3_STARTPAGE_OPT) && (MPREG1_ENDPAGE_OPT   <= MPREG3_ENDPAGE_OPT)))
      #error "Protect flash rom region 1 range overlaps with region 3 range."
    #endif
  #endif
  #if ((FLASH_MPREG2CR_OPT == 1) && (FLASH_MPREG3CR_OPT == 1))
    #if (((MPREG2_STARTPAGE_OPT >= MPREG3_STARTPAGE_OPT) && (MPREG2_STARTPAGE_OPT <= MPREG3_ENDPAGE_OPT)) || \
         ((MPREG2_ENDPAGE_OPT   >= MPREG3_STARTPAGE_OPT) && (MPREG2_ENDPAGE_OPT   <= MPREG3_ENDPAGE_OPT)))
      #error "Protect flash rom region 2 range overlaps with region 3 range."
    #endif
  #endif
#endif

#if (FLASH_OPT_PARTIALLOCK == 1)
    const unsigned long HT32Option[20] __attribute__ ((section(".HT32_OPTIONS_PARTIALLOCK"))) = {
    OB_KEY0,                            // 0x1FF00080
    OB_KEY1,                            // 0x1FF00084
    OB_KEY2,                            // 0x1FF00088
    OB_KEY3,                            // 0x1FF0008C
    OB_KPCTL,                           // 0x1FF00090
    OB_KPCNT,                           // 0x1FF00094
    OPT_RES,                            // 0x1FF00098
    OPT_RES,                            // 0x1FF0009C
    ~OB_KPPP0,                          // 0x1FF000A0
    ~OB_KPPP1,                          // 0x1FF000A4
    ~OB_KPPP2,                          // 0x1FF000A8
    ~OB_KPPP3,                          // 0x1FF000AC
    OB_MPREG0CR,                        // 0x1FF000B0
    OB_MPREG0,                          // 0x1FF000B4
    OB_MPREG1CR,                        // 0x1FF000B8
    OB_MPREG1,                          // 0x1FF000BC
    OB_MPREG2CR,                        // 0x1FF000C0
    OB_MPREG2,                          // 0x1FF000C4
    OB_MPREG3CR,                        // 0x1FF000C8
    OB_MPREG3,                          // 0x1FF000CC
  };

#endif
