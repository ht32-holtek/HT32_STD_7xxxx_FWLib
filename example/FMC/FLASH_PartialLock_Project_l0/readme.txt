/**
 @page FLASH_PartialLock_Project_l0

 @verbatim
 * @file    FMC/FLASH_PartialLock_Project_l0/readme.txt
 * @version V1.00
 * @date    2025-09-22
 * @brief   Description of FLASH Partial Lock example.
 @endverbatim

@par Example Description:

This example demonstrates how to place algorithm functions and parameters into specific memory regions,
configure Partial Lock, and generate a function list for the algorithm.

Memory placement is controlled by linker.lin.

Partial Lock options are defined in ht32_op2.s/.c.

IDE Notes for EWARM and EWARMv8:

IDE Notes
To generate the function symbol list:
  For MDK_ARMv5:
  1. In Options for Target > Linker > Misc Controls, add: "--symdefs=calculate_symbol_MDKv5.o"
  2. After compilation, "calculate_symbol_MDKv5.o" will be generated under ./HT32/72388/Obj/.
  3. Manually remove unused functions from the list as needed.

  For EWARM:
  1. In Options > Build Actions > Post-build command line, add:
  "$TOOLKIT_DIR$\bin\isymexport.exe" --edit "$PROJ_DIR$\..\steering_file_IAR.txt" "$TARGET_PATH$" "$PROJ_DIR$\calculate_symbol_EWARM.o"
  2. In "steering_file_IAR.txt", list the functions to retain using the format: show function_name.
  3. After compilation, "calculate_symbol_EWARM.o" will be generated.

  For EWARMv8:
  1. In Options > Build Actions > Post-build command line, add:
  "$TOOLKIT_DIR$\bin\isymexport.exe" --edit "$PROJ_DIR$\..\steering_file_IAR.txt" "$TARGET_PATH$" "$PROJ_DIR$\calculate_symbol_EWARMv8.o"
  2. In "steering_file_IAR.txt", list the functions to retain using the format: show function_name.
  3. After compilation, "calculate_symbol_EWARMv8.o" will be generated.

  For GNU_ARM:
  1. In `steering_file_GNU.txt`, list the functions to retain using the format: function_name.
  2. Modify `afterbuild.bat` to parse `steering_file_GNU.txt` and generate a linker script
     ("calculate_symbol_GNU.ld") with the appropriate KEEP directives.
  3. After compilation, "calculate_symbol_GNU.ld" will be generated.

@par Directory Contents:

- FMC/FLASH_PartialLock_Project_l0/main.c               Main program
- FMC/FLASH_PartialLock_Project_l0/ht32fxxxxx_nn_it.c   Interrupt handlers
- FMC/FLASH_PartialLock_Project_l0/linker.lin,icf,ld    Linker script
- FMC/FLASH_PartialLock_Project_l0/calculate.c          Algorithm function
- FMC/FLASH_PartialLock_Project_l0/calculate_data.c     Algorithm parameters

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
