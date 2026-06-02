/**
 @page FLASH_PartialLock_IDCODE

 @verbatim
 * @file    FMC/FLASH_PartialLock_IDCODE/readme.txt
 * @version V1.01
 * @date    2026-05-21
 * @brief   Description of FLASH Partial Lock example.
 @endverbatim

@par Example Description:

This example demonstrates how to verify Partial Lock memory protection for the ICODE and DCODE regions
on HT32 devices, with the configuration defined in ht32_op2.s/.c.

It uses the "Debug" access type to facilitate observation of system behavior and validation of the
protection mechanism.

The flow includes checking whether Partial Lock is enabled, verifying valid code execution and data
access in the ICODE/DCODE regions, and performing invalid access tests to confirm the protection response.

@par Directory Contents:

- FMC/FLASH_PartialLock_IDCODE/main.c               Main program
- FMC/FLASH_PartialLock_IDCODE/ht32fxxxxx_nn_it.c   Interrupt handlers
- FMC/FLASH_PartialLock_IDCODE/linker.lin,icf,ld    Linker script
- FMC/FLASH_PartialLock_IDCODE/dcode.c              Partial lock DCODE region function and parameters
- FMC/FLASH_PartialLock_IDCODE/icode.c              Partial lock ICODE region function and parameters

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
