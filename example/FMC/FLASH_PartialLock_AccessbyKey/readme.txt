/**
 @page FLASH_PartialLock_AccessbyKey

 @verbatim
 * @file    FMC/FLASH_PartialLock_AccessbyKey/readme.txt
 * @version V1.00
 * @date    2025-09-22
 * @brief   Description of FLASH Partial Lock example.
 @endverbatim

@par Example Description:

This example demonstrates how to verify Partial Lock memory protection for "Access by key" regions
on HT32 devices.

Partial Lock is configured via ht32_op2.s/.c.

Flow:
1. Check if Partial Lock is enabled.
2. Perform access to the "Access by Key" region after a successful key match.
3. Perform access to the "Access by Key" region after a key mismatch.

@par Directory Contents:

- FMC/FLASH_PartialLock_IDCODE/main.c               Main program
- FMC/FLASH_PartialLock_IDCODE/ht32fxxxxx_nn_it.c   Interrupt handlers
- FMC/FLASH_PartialLock_IDCODE/linker.lin,icf,ld    Linker script
- FMC/FLASH_PartialLock_IDCODE/accessbykey.c        Partial lock "Access by key" region function and parameters

@par Hardware and Software Environment:

- This example can be run on HT32 Series development board.

@par Firmware Disclaimer Information

1. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
   proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
   other intellectual property laws.

2. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
   other than HOLTEK and the customer.

3. The program technical documentation, including the code, is provided "as is" and for customer reference
   only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
   the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
   the warranties of merchantability, satisfactory quality and fitness for a particular purpose.

 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 */
