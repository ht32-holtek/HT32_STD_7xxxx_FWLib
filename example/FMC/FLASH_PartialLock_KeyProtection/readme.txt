/**
 @page FLASH_PartialLock_KeyProtection

 @verbatim
 * @file    FMC/FLASH_PartialLock_KeyProtection/readme.txt
 * @version V1.00
 * @date    2025-09-22
 * @brief   Description of FLASH Partial Lock example.
 @endverbatim

@par Example Description:

This example demonstrates how to enable and test Partial Lock on HT32 FLASH memory, including mass erase
behavior under Partial Lock.

Partial Lock settings are defined in ht32_op2.s/.c.
To use code-based configuration, disable FLASH_OPT_PARTIALLOCK in ht32_op2.s/.c and define PARTIALLOCK_BYCODE
in main.c.

To protect pages, call FLASH_ProgramPartialLockOptionByte() and specify the page mask.
A system reset (NVIC_SystemReset()) is required to apply the new Option Byte settings.

To allow mass erase while Partial Lock is enabled, define MASEERASS_INPARTIALLOCK in main.c.
If mass erase is disabled by Partial Lock, and the maximum key mismatch counter is not zero, mass erase
can proceed after a successful key match, which also clears the Partial Lock state.

Once the key is matched and the Partial Lock Invalid Key Protection is enable, protected pages can be erased
or programmed normally.

@par Directory Contents:

- FMC/FLASH_PartialLock_KeyProtection/main.c               Main program
- FMC/FLASH_PartialLock_KeyProtection/ht32fxxxxx_nn_it.c   Interrupt handlers

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
