;/*---------------------------------------------------------------------------------------------------------*/
;/* Holtek Semiconductor Inc.                                                                               */
;/*                                                                                                         */
;/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
;/* All rights reserved.                                                                                    */
;/*                                                                                                         */
;/*-----------------------------------------------------------------------------------------------------------
;  File Name        : ht32_op2.s
;  Version          : V0.02
;  Date             : 2025-04-11
;  Description      : HT32 Series Flash Option Bytes Block.
;-----------------------------------------------------------------------------------------------------------*/

;/****************************************************************************                              */
;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */
;/****************************************************************************                              */

;// <e> Program Partial Lock Option Byte
;// <i> Program Partial Lock Option Byte settings into Flash (Must enable for write any one of the following settings into Partial Lock Option Byte Flash).
;// <i> -- Protection Key (OB_KEYn)
;// <i> -- Maximum Error Key Mismatch Counter (OB_KPCNT)
;// <i> -- Key Protection Control (OB_KPCTL)
;// <i> -- Page Erase/Program Protection (OB_KPPPn)
;// <i> -- Double Check Protection Key (For double check OB_KEYn).
FLASH_OPT_PARTIALLOCK    EQU     1
;// </e>

;// <h> ------------------------------------------------------------------------------------------------------
;// </h>
;// <o0> -- Protection Key Value: OB_KEY0 (0x1FF00080)
;// <i> Protection Key 0 (OB_KEY0)
;// <o1> -- Protection Key Value: OB_KEY1 (0x1FF00084)
;// <i> Protection Key 1 (OB_KEY1)
;// <o2> -- Protection Key Value: OB_KEY2 (0x1FF00088)
;// <i> Protection Key 2 (OB_KEY2)
;// <o3> -- Protection Key Value: OB_KEY3 (0x1FF0008C)
;// <i> Protection Key 3 (OB_KEY3)
;// <h> -- !!! Note: Save your password and do not disclose it to others.
;// </h>
OB_KEY0                  EQU     0x5555AAAA
OB_KEY1                  EQU     0x5555AAAA
OB_KEY2                  EQU     0x5555AAAA
OB_KEY3                  EQU     0x5555AAAA

;// <h> ------------------------------------------------------------------------------------------------------
;// </h>
;// <o0> -- Maximum Error Key Mismatch Counter: OB_KPCNT (0x1FF00094) <0x00-0xFF>
;// <i> Set to permit the maximum error key entry mismatch counter at each power-on
KPCNT_OPT                EQU     0xFF
;// <h> -- !!! Note: The OB_KPCNT setting 0 means completely locked and cannot be unlocked.
;// </h>

;// <h> ------------------------------------------------------------------------------------------------------
;// </h>
;// <e> -- Disable Mass Erase: OB_KPCTL[15:8] (0x1FF00090)
;// <i> When flash protection key is enabled,
;// <i> setting disable mass erase will temporarily block mass erase commands to protect Flash to do the mass erase operation
KPCTL_MASSERASE_OPT      EQU     0
;// </e>

;// <e> -- Invalid Key Protection When Key Value Match: OB_KPCTL[23:16] (0x1FF00090)
;// <i> Temporarily disables OB_KPPP protection when the security key matches
KPCTL_KPINVALID_OPT      EQU     1
;// </e>

;// <o0> -- Maximum Error Key Mismatch Trigger Option: OB_KPCTL[31:24] (0x1FF00090)
;//   <0=> Return Key un-match flag
;//   <1=> Hold MCU
;//   <2=> Mass Erase
;// <i> The next activity occurs when the error key input count reaches the value set by OB_KPCNT
;// <i> -- Return Key un-match flag: The key comparison functionality will be halted and always return key un-match flag
;// <i> -- Hold MCU: Reset MCU core until the MCU power on occurs
;// <i> -- Mass Erase: Mass erase main flash
KPCTL_MAXMISMATCH_OPT    EQU     1

;// <h> ------------------------------------------------------------------------------------------------------
;// </h>
;// <h> -- Main Flash Page Erase/Program Protection by Key (OB_KPPP0 bits)
;// <i> Enable page erase/program protection by key to prevent unwanted change of Flash contents.
;// <i> One bit for n pages. Check FMC chapter of User Manual for detailed.
;//   <o0.0 >  Enable Page Erase/Program Protection by Key 0   - OB_KPPP[0]
;//   <o0.1 >  Enable Page Erase/Program Protection by Key 1   - OB_KPPP[1]
;//   <o0.2 >  Enable Page Erase/Program Protection by Key 2   - OB_KPPP[2]
;//   <o0.3 >  Enable Page Erase/Program Protection by Key 3   - OB_KPPP[3]
;//   <o0.4 >  Enable Page Erase/Program Protection by Key 4   - OB_KPPP[4]
;//   <o0.5 >  Enable Page Erase/Program Protection by Key 5   - OB_KPPP[5]
;//   <o0.6 >  Enable Page Erase/Program Protection by Key 6   - OB_KPPP[6]
;//   <o0.7 >  Enable Page Erase/Program Protection by Key 7   - OB_KPPP[7]
;//   <o0.8 >  Enable Page Erase/Program Protection by Key 8   - OB_KPPP[8]
;//   <o0.9 >  Enable Page Erase/Program Protection by Key 9   - OB_KPPP[9]
;//   <o0.10 > Enable Page Erase/Program Protection by Key 10  - OB_KPPP[10]
;//   <o0.11 > Enable Page Erase/Program Protection by Key 11  - OB_KPPP[11]
;//   <o0.12 > Enable Page Erase/Program Protection by Key 12  - OB_KPPP[12]
;//   <o0.13 > Enable Page Erase/Program Protection by Key 13  - OB_KPPP[13]
;//   <o0.14 > Enable Page Erase/Program Protection by Key 14  - OB_KPPP[14]
;//   <o0.15 > Enable Page Erase/Program Protection by Key 15  - OB_KPPP[15]
;//   <o0.16 > Enable Page Erase/Program Protection by Key 16  - OB_KPPP[16]
;//   <o0.17 > Enable Page Erase/Program Protection by Key 17  - OB_KPPP[17]
;//   <o0.18 > Enable Page Erase/Program Protection by Key 18  - OB_KPPP[18]
;//   <o0.19 > Enable Page Erase/Program Protection by Key 19  - OB_KPPP[19]
;//   <o0.20 > Enable Page Erase/Program Protection by Key 20  - OB_KPPP[20]
;//   <o0.21 > Enable Page Erase/Program Protection by Key 21  - OB_KPPP[21]
;//   <o0.22 > Enable Page Erase/Program Protection by Key 22  - OB_KPPP[22]
;//   <o0.23 > Enable Page Erase/Program Protection by Key 23  - OB_KPPP[23]
;//   <o0.24 > Enable Page Erase/Program Protection by Key 24  - OB_KPPP[24]
;//   <o0.25 > Enable Page Erase/Program Protection by Key 25  - OB_KPPP[25]
;//   <o0.26 > Enable Page Erase/Program Protection by Key 26  - OB_KPPP[26]
;//   <o0.27 > Enable Page Erase/Program Protection by Key 27  - OB_KPPP[27]
;//   <o0.28 > Enable Page Erase/Program Protection by Key 28  - OB_KPPP[28]
;//   <o0.29 > Enable Page Erase/Program Protection by Key 29  - OB_KPPP[29]
;//   <o0.30 > Enable Page Erase/Program Protection by Key 30  - OB_KPPP[30]
;//   <o0.31 > Enable Page Erase/Program Protection by Key 31  - OB_KPPP[31]
;// </h>
;// <h> -- Main Flash Page Erase/Program Protection by Key (OB_KPPP1 bits)
;// <i> Enable page erase/program protection by key to prevent unwanted change of Flash contents.
;// <i> One bit for n pages. Check FMC chapter of User Manual for detailed.
;//   <o1.0 >  Enable Page Erase/Program Protection by Key 32  - OB_KPPP[32]
;//   <o1.1 >  Enable Page Erase/Program Protection by Key 33  - OB_KPPP[33]
;//   <o1.2 >  Enable Page Erase/Program Protection by Key 34  - OB_KPPP[34]
;//   <o1.3 >  Enable Page Erase/Program Protection by Key 35  - OB_KPPP[35]
;//   <o1.4 >  Enable Page Erase/Program Protection by Key 36  - OB_KPPP[36]
;//   <o1.5 >  Enable Page Erase/Program Protection by Key 37  - OB_KPPP[37]
;//   <o1.6 >  Enable Page Erase/Program Protection by Key 38  - OB_KPPP[38]
;//   <o1.7 >  Enable Page Erase/Program Protection by Key 39  - OB_KPPP[39]
;//   <o1.8 >  Enable Page Erase/Program Protection by Key 40  - OB_KPPP[40]
;//   <o1.9 >  Enable Page Erase/Program Protection by Key 41  - OB_KPPP[41]
;//   <o1.10 > Enable Page Erase/Program Protection by Key 42  - OB_KPPP[42]
;//   <o1.11 > Enable Page Erase/Program Protection by Key 43  - OB_KPPP[43]
;//   <o1.12 > Enable Page Erase/Program Protection by Key 44  - OB_KPPP[44]
;//   <o1.13 > Enable Page Erase/Program Protection by Key 45  - OB_KPPP[45]
;//   <o1.14 > Enable Page Erase/Program Protection by Key 46  - OB_KPPP[46]
;//   <o1.15 > Enable Page Erase/Program Protection by Key 47  - OB_KPPP[47]
;//   <o1.16 > Enable Page Erase/Program Protection by Key 48  - OB_KPPP[48]
;//   <o1.17 > Enable Page Erase/Program Protection by Key 49  - OB_KPPP[49]
;//   <o1.18 > Enable Page Erase/Program Protection by Key 50  - OB_KPPP[50]
;//   <o1.19 > Enable Page Erase/Program Protection by Key 51  - OB_KPPP[51]
;//   <o1.20 > Enable Page Erase/Program Protection by Key 52  - OB_KPPP[52]
;//   <o1.21 > Enable Page Erase/Program Protection by Key 53  - OB_KPPP[53]
;//   <o1.22 > Enable Page Erase/Program Protection by Key 54  - OB_KPPP[54]
;//   <o1.23 > Enable Page Erase/Program Protection by Key 55  - OB_KPPP[55]
;//   <o1.24 > Enable Page Erase/Program Protection by Key 56  - OB_KPPP[56]
;//   <o1.25 > Enable Page Erase/Program Protection by Key 57  - OB_KPPP[57]
;//   <o1.26 > Enable Page Erase/Program Protection by Key 58  - OB_KPPP[58]
;//   <o1.27 > Enable Page Erase/Program Protection by Key 59  - OB_KPPP[59]
;//   <o1.28 > Enable Page Erase/Program Protection by Key 60  - OB_KPPP[60]
;//   <o1.29 > Enable Page Erase/Program Protection by Key 61  - OB_KPPP[61]
;//   <o1.30 > Enable Page Erase/Program Protection by Key 62  - OB_KPPP[62]
;//   <o1.31 > Enable Page Erase/Program Protection by Key 63  - OB_KPPP[63]
;// </h>
;// <h> -- Main Flash Page Erase/Program Protection by Key (OB_KPPP2 bits)
;// <i> Enable page erase/program protection by key to prevent unwanted change of Flash contents.
;// <i> One bit for n pages. Check FMC chapter of User Manual for detailed.
;//   <o2.0 >  Enable Page Erase/Program Protection by Key 64  - OB_KPPP[64]
;//   <o2.1 >  Enable Page Erase/Program Protection by Key 65  - OB_KPPP[65]
;//   <o2.2 >  Enable Page Erase/Program Protection by Key 66  - OB_KPPP[66]
;//   <o2.3 >  Enable Page Erase/Program Protection by Key 67  - OB_KPPP[67]
;//   <o2.4 >  Enable Page Erase/Program Protection by Key 68  - OB_KPPP[68]
;//   <o2.5 >  Enable Page Erase/Program Protection by Key 69  - OB_KPPP[69]
;//   <o2.6 >  Enable Page Erase/Program Protection by Key 70  - OB_KPPP[70]
;//   <o2.7 >  Enable Page Erase/Program Protection by Key 71  - OB_KPPP[71]
;//   <o2.8 >  Enable Page Erase/Program Protection by Key 72  - OB_KPPP[72]
;//   <o2.9 >  Enable Page Erase/Program Protection by Key 73  - OB_KPPP[73]
;//   <o2.10 > Enable Page Erase/Program Protection by Key 74  - OB_KPPP[74]
;//   <o2.11 > Enable Page Erase/Program Protection by Key 75  - OB_KPPP[75]
;//   <o2.12 > Enable Page Erase/Program Protection by Key 76  - OB_KPPP[76]
;//   <o2.13 > Enable Page Erase/Program Protection by Key 77  - OB_KPPP[77]
;//   <o2.14 > Enable Page Erase/Program Protection by Key 78  - OB_KPPP[78]
;//   <o2.15 > Enable Page Erase/Program Protection by Key 79  - OB_KPPP[79]
;//   <o2.16 > Enable Page Erase/Program Protection by Key 80  - OB_KPPP[80]
;//   <o2.17 > Enable Page Erase/Program Protection by Key 81  - OB_KPPP[81]
;//   <o2.18 > Enable Page Erase/Program Protection by Key 82  - OB_KPPP[82]
;//   <o2.19 > Enable Page Erase/Program Protection by Key 83  - OB_KPPP[83]
;//   <o2.20 > Enable Page Erase/Program Protection by Key 84  - OB_KPPP[84]
;//   <o2.21 > Enable Page Erase/Program Protection by Key 85  - OB_KPPP[85]
;//   <o2.22 > Enable Page Erase/Program Protection by Key 86  - OB_KPPP[86]
;//   <o2.23 > Enable Page Erase/Program Protection by Key 87  - OB_KPPP[87]
;//   <o2.24 > Enable Page Erase/Program Protection by Key 88  - OB_KPPP[88]
;//   <o2.25 > Enable Page Erase/Program Protection by Key 89  - OB_KPPP[89]
;//   <o2.26 > Enable Page Erase/Program Protection by Key 90  - OB_KPPP[90]
;//   <o2.27 > Enable Page Erase/Program Protection by Key 91  - OB_KPPP[91]
;//   <o2.28 > Enable Page Erase/Program Protection by Key 92  - OB_KPPP[92]
;//   <o2.29 > Enable Page Erase/Program Protection by Key 93  - OB_KPPP[93]
;//   <o2.30 > Enable Page Erase/Program Protection by Key 94  - OB_KPPP[94]
;//   <o2.31 > Enable Page Erase/Program Protection by Key 95  - OB_KPPP[95]
;// </h>
;// <h> -- Main Flash Page Erase/Program Protection by Key (OB_KPPP3 bits)
;// <i> Enable page erase/program protection by key to prevent unwanted change of Flash contents.
;// <i> One bit for n pages. Check FMC chapter of User Manual for detailed.
;//   <o3.0 >  Enable Page Erase/Program Protection by Key 96  - OB_KPPP[96]
;//   <o3.1 >  Enable Page Erase/Program Protection by Key 97  - OB_KPPP[97]
;//   <o3.2 >  Enable Page Erase/Program Protection by Key 98  - OB_KPPP[98]
;//   <o3.3 >  Enable Page Erase/Program Protection by Key 99  - OB_KPPP[99]
;//   <o3.4 >  Enable Page Erase/Program Protection by Key 100 - OB_KPPP[100]
;//   <o3.5 >  Enable Page Erase/Program Protection by Key 101 - OB_KPPP[101]
;//   <o3.6 >  Enable Page Erase/Program Protection by Key 102 - OB_KPPP[102]
;//   <o3.7 >  Enable Page Erase/Program Protection by Key 103 - OB_KPPP[103]
;//   <o3.8 >  Enable Page Erase/Program Protection by Key 104 - OB_KPPP[104]
;//   <o3.9 >  Enable Page Erase/Program Protection by Key 105 - OB_KPPP[105]
;//   <o3.10 > Enable Page Erase/Program Protection by Key 106 - OB_KPPP[106]
;//   <o3.11 > Enable Page Erase/Program Protection by Key 107 - OB_KPPP[107]
;//   <o3.12 > Enable Page Erase/Program Protection by Key 108 - OB_KPPP[108]
;//   <o3.13 > Enable Page Erase/Program Protection by Key 109 - OB_KPPP[109]
;//   <o3.14 > Enable Page Erase/Program Protection by Key 110 - OB_KPPP[110]
;//   <o3.15 > Enable Page Erase/Program Protection by Key 111 - OB_KPPP[111]
;//   <o3.16 > Enable Page Erase/Program Protection by Key 112 - OB_KPPP[112]
;//   <o3.17 > Enable Page Erase/Program Protection by Key 113 - OB_KPPP[113]
;//   <o3.18 > Enable Page Erase/Program Protection by Key 114 - OB_KPPP[114]
;//   <o3.19 > Enable Page Erase/Program Protection by Key 115 - OB_KPPP[115]
;//   <o3.20 > Enable Page Erase/Program Protection by Key 116 - OB_KPPP[116]
;//   <o3.21 > Enable Page Erase/Program Protection by Key 117 - OB_KPPP[117]
;//   <o3.22 > Enable Page Erase/Program Protection by Key 118 - OB_KPPP[118]
;//   <o3.23 > Enable Page Erase/Program Protection by Key 119 - OB_KPPP[119]
;//   <o3.24 > Enable Page Erase/Program Protection by Key 120 - OB_KPPP[120]
;//   <o3.25 > Enable Page Erase/Program Protection by Key 121 - OB_KPPP[121]
;//   <o3.26 > Enable Page Erase/Program Protection by Key 122 - OB_KPPP[122]
;//   <o3.27 > Enable Page Erase/Program Protection by Key 123 - OB_KPPP[123]
;//   <o3.28 > Enable Page Erase/Program Protection by Key 124 - OB_KPPP[124]
;//   <o3.29 > Enable Page Erase/Program Protection by Key 125 - OB_KPPP[125]
;//   <o3.30 > Enable Page Erase/Program Protection by Key 126 - OB_KPPP[126]
;//   <o3.31 > Enable Page Erase/Program Protection by Key 127 - OB_KPPP[127]
;// </h>

;// <o0> -- Option Byte value: OB_KPPP0 (0x1FF000A0)
;// <o1> -- Option Byte value: OB_KPPP1 (0x1FF000A4)
;// <o2> -- Option Byte value: OB_KPPP2 (0x1FF000A8)
;// <o3> -- Option Byte value: OB_KPPP3 (0x1FF000AC)
;// <h> -- !!! Note: One OB_KPPP bit for setting n Pages. Check FMC chapter of User Manual for detailed.
;// </h>
OB_KPPP0                 EQU     0x00000030
OB_KPPP1                 EQU     0x00000000
OB_KPPP2                 EQU     0x00000000
OB_KPPP3                 EQU     0x00000000

;// <h> ------------------------------------------------------------------------------------------------------
;// </h>
;// <o0> -- Double Check Protection Key Value: D_OB_KEY0
;// <i> For double check Protection Key 0 (need to same as OB_KEY0)
;// <o1> -- Double Check Protection Key Value: D_OB_KEY1
;// <i> For double check Protection Key 1 (need to same as OB_KEY1)
;// <o2> -- Double Check Protection Key Value: D_OB_KEY2
;// <i> For double check Protection Key 2 (need to same as OB_KEY2)
;// <o3> -- Double Check Protection Key Value: D_OB_KEY3
;// <i> For double check Protection Key 3 (need to same as OB_KEY3)
;// <h> -- !!! Note: For double check protection key, do not disclose it to others.
;// </h>
D_OB_KEY0                EQU     0x5555AAAA
D_OB_KEY1                EQU     0x5555AAAA
D_OB_KEY2                EQU     0x5555AAAA
D_OB_KEY3                EQU     0x5555AAAA

;// <h> ------------------------------------------------------------------------------------------------------
;// </h>
;// <e> -- Flash ROM Region 0 Protection
;// <i> Protect Flash ROM Region 0 Control (OB_MPREG0CR) (0x1FF000B0)
;// <i> -- Access Type: OB_MPREG0CR[7:0]
;// <i> -- Mode: OB_MPREG0CR[15:8]
;// <i> Setting Protection Flash ROM Region 0 Range (OB_MPREG0) (0x1FF000B4)
;// <i> -- Start Page (0x008~0x3FE): OB_MPREG0[9:0]
;// <i> -- End Page (0x008~0x3FE): OB_MPREG0[25:16]
FLASH_MPREG0CR_OPT       EQU     1
;// <o0> -- Access Type
;// <i> Access Type of Protection, illegal access returns all 1 and triggers a hard fault
;// <i> Access Type of Debug, in debug mode, access is allowed but triggers an FMC error interrupt
;//   <0=> Protection
;//   <1=> Debug
;// <o1> -- Mode
;// <i> Mode can be select ICODE, DCODE or Access by Key
;//   <0=> ICODE
;//   <1=> DCODE
;//   <2=> Access by Key
;// <o2> -- Start Page (0x008~0x3FE) <0x008-0x3FE>
;// <i> Start of page number for Flash macro region protection
;// <o3> -- End Page (0x008~0x3FE) <0x008-0x3FE>
;// <i> End of page number for Flash macro region protection
MPREG0CR_ACCESSTYPE_OPT  EQU     1
MPREG0CR_MODE_OPT        EQU     0
MPREG0_STARTPAGE_OPT     EQU     0x020
MPREG0_ENDPAGE_OPT       EQU     0x027
;// </e>

;// <e> -- Flash ROM Region 1 Protection
;// <i> Protect Flash ROM Region 1 Control (OB_MPREG1CR) (0x1FF000B8)
;// <i> -- Access Type: OB_MPREG1CR[7:0]
;// <i> -- Mode: OB_MPREG1CR[15:8]
;// <i> Setting Protection Flash ROM Region 1 Range (OB_MPREG1) (0x1FF000BC)
;// <i> -- Start Page (0x008~0x3FE): OB_MPREG1[9:0]
;// <i> -- End Page (0x008~0x3FE): OB_MPREG1[25:16]
FLASH_MPREG1CR_OPT       EQU     1
;// <o0> -- Access Type
;// <i> Access Type of Protection, illegal access returns all 1 and triggers a hard fault
;// <i> Access Type of Debug, in debug mode, access is allowed but triggers an FMC error interrupt
;//   <0=> Protection
;//   <1=> Debug
;// <o1> -- Mode
;// <i> Mode can be select ICODE, DCODE or Access by Key
;//   <0=> ICODE
;//   <1=> DCODE
;//   <2=> Access by Key
;// <o2> -- Start Page (0x008~0x3FE) <0x008-0x3FE>
;// <i> Start of page number for Flash macro region protection
;// <o3> -- End Page (0x008~0x3FE) <0x008-0x3FE>
;// <i> End of page number for Flash macro region protection
MPREG1CR_ACCESSTYPE_OPT  EQU     1
MPREG1CR_MODE_OPT        EQU     1
MPREG1_STARTPAGE_OPT     EQU     0x028
MPREG1_ENDPAGE_OPT       EQU     0x02F
;// </e>

;// <e> -- Flash ROM Region 2 Protection
;// <i> Protect Flash ROM Region 2 Control (OB_MPREG2CR) (0x1FF000C0)
;// <i> -- Access Type: OB_MPREG2CR[7:0]
;// <i> -- Mode: OB_MPREG2CR[15:8]
;// <i> Setting Protection Flash ROM Region 2 Range (OB_MPREG2) (0x1FF000C4)
;// <i> -- Start Page (0x008~0x3FE): OB_MPREG2[9:0]
;// <i> -- End Page (0x008~0x3FE): OB_MPREG2[25:16]
FLASH_MPREG2CR_OPT       EQU     0
;// <o0> -- Access Type
;// <i> Access Type of Protection, illegal access returns all 1 and triggers a hard fault
;// <i> Access Type of Debug, in debug mode, access is allowed but triggers an FMC error interrupt
;//   <0=> Protection
;//   <1=> Debug
;// <o1> -- Mode
;// <i> Mode can be select ICODE, DCODE or Access by Key
;//   <0=> ICODE
;//   <1=> DCODE
;//   <2=> Access by Key
;// <o2> -- Start Page (0x008~0x3FE) <0x008-0x3FE>
;// <i> Start of page number for Flash macro region protection
;// <o3> -- End Page (0x008~0x3FE) <0x008-0x3FE>
;// <i> End of page number for Flash macro region protection
MPREG2CR_ACCESSTYPE_OPT  EQU     0
MPREG2CR_MODE_OPT        EQU     0
MPREG2_STARTPAGE_OPT     EQU     0x008
MPREG2_ENDPAGE_OPT       EQU     0x008
;// </e>

;// <e> -- Flash ROM Region 3 Protection
;// <i> Protect Flash ROM Region 3 Control (OB_MPREG3CR) (0x1FF000C8)
;// <i> -- Access Type: OB_MPREG3CR[7:0]
;// <i> -- Mode: OB_MPREG3CR[15:8]
;// <i> Setting Protection Flash ROM Region 3 Range (OB_MPREG3) (0x1FF000CC)
;// <i> -- Start Page (0x008~0x3FE): OB_MPREG3[9:0]
;// <i> -- End Page (0x008~0x3FE): OB_MPREG3[25:16]
FLASH_MPREG3CR_OPT       EQU     0
;// <o0> -- Access Type
;// <i> Access Type of Protection, illegal access returns all 1 and triggers a hard fault
;// <i> Access Type of Debug, in debug mode, access is allowed but triggers an FMC error interrupt
;//   <0=> Protection
;//   <1=> Debug
;// <o1> -- Mode
;// <i> Mode can be select ICODE, DCODE or Access by Key
;//   <0=> ICODE
;//   <1=> DCODE
;//   <2=> Access by Key
;// <o2> -- Start Page (0x008~0x3FE) <0x008-0x3FE>
;// <i> Start of page number for Flash macro region protection
;// <o3> -- End Page (0x008~0x3FE) <0x008-0x3FE>
;// <i> End of page number for Flash macro region protection
MPREG3CR_ACCESSTYPE_OPT  EQU     0
MPREG3CR_MODE_OPT        EQU     0
MPREG3_STARTPAGE_OPT     EQU     0x008
MPREG3_ENDPAGE_OPT       EQU     0x008
;// </e>

;/*---------------------------------------------------------------------------------------------------------*/
;/* DO NOT MODIFY                                                                                           */
;/*---------------------------------------------------------------------------------------------------------*/
OPT_RES                  EQU     0xFFFFFFFF

    IF FLASH_OPT_PARTIALLOCK = 1
      IF OB_KEY0 != D_OB_KEY0 || OB_KEY1 != D_OB_KEY1 || OB_KEY2 != D_OB_KEY2 || OB_KEY3 != D_OB_KEY3
        The_value_of_ProtectionKey(OB_KEYn)_does_not_match_the_DoubleCheckProtectionKey(D_OB_KEYn).
      ENDIF
    ENDIF

    IF FLASH_OPT_PARTIALLOCK = 1
OB_KPCTL_OPT             EQU     0x0000005A
    ELSE
OB_KPCTL_OPT             EQU     0x000000FF
    ENDIF

    IF KPCTL_MASSERASE_OPT = 1
OB_KPCTL_MASSERASE       EQU     0x00005A00
    ELSE
OB_KPCTL_MASSERASE       EQU     0x0000FF00
    ENDIF

    IF KPCTL_KPINVALID_OPT = 1
OB_KPCTL_KPINVALID       EQU     0x005A0000
    ELSE
OB_KPCTL_KPINVALID       EQU     0x00FF0000
    ENDIF

    IF KPCTL_MAXMISMATCH_OPT = 1
OB_KPCTL_MAXMISMATCH     EQU     0x5A000000
    ELIF KPCTL_MAXMISMATCH_OPT = 2
OB_KPCTL_MAXMISMATCH     EQU     0xA5000000
    ELSE
OB_KPCTL_MAXMISMATCH     EQU     0xFF000000
    ENDIF

OB_KPCTL                 EQU     (OB_KPCTL_MAXMISMATCH:OR:OB_KPCTL_KPINVALID:OR:OB_KPCTL_MASSERASE:OR:OB_KPCTL_OPT)

OB_KPCNT                 EQU     KPCNT_OPT:OR:0xFFFFFF00

nOB_KPPP0                EQU     OB_KPPP0:EOR:0xFFFFFFFF
nOB_KPPP1                EQU     OB_KPPP1:EOR:0xFFFFFFFF
nOB_KPPP2                EQU     OB_KPPP2:EOR:0xFFFFFFFF
nOB_KPPP3                EQU     OB_KPPP3:EOR:0xFFFFFFFF

    IF FLASH_MPREG0CR_OPT = 1
      IF MPREG0CR_ACCESSTYPE_OPT = 0
OB_MPREG0CR_ACCESSTYPE   EQU     0x0000005A
      ELIF MPREG0CR_ACCESSTYPE_OPT = 1
OB_MPREG0CR_ACCESSTYPE   EQU     0x00000035
      ELSE
OB_MPREG0CR_ACCESSTYPE   EQU     0x000000FF
      ENDIF

      IF MPREG0CR_MODE_OPT = 0
OB_MPREG0CR_MODE         EQU     0x00005A00
      ELIF MPREG0CR_MODE_OPT = 1
OB_MPREG0CR_MODE         EQU     0x00003500
      ELIF MPREG0CR_MODE_OPT = 2
OB_MPREG0CR_MODE         EQU     0x0000A300
      ELSE
OB_MPREG0CR_MODE         EQU     0x0000FF00
      ENDIF
    ENDIF

    IF FLASH_MPREG0CR_OPT = 1
OB_MPREG0CR              EQU     (0xFFFF0000:OR:OB_MPREG0CR_MODE:OR:OB_MPREG0CR_ACCESSTYPE)
OB_MPREG0                EQU     (0xFC000000:OR:(MPREG0_ENDPAGE_OPT << 16):OR:0x0000FC00:OR:MPREG0_STARTPAGE_OPT)
    ELSE
OB_MPREG0CR              EQU     0xFFFFFFFF
OB_MPREG0                EQU     0xFFFFFFFF
    ENDIF

    IF FLASH_MPREG1CR_OPT = 1
      IF MPREG1CR_ACCESSTYPE_OPT = 0
OB_MPREG1CR_ACCESSTYPE   EQU     0x0000005A
      ELIF MPREG1CR_ACCESSTYPE_OPT = 1
OB_MPREG1CR_ACCESSTYPE   EQU     0x00000035
      ELSE
OB_MPREG1CR_ACCESSTYPE   EQU     0x000000FF
      ENDIF

      IF MPREG1CR_MODE_OPT = 0
OB_MPREG1CR_MODE         EQU     0x00005A00
      ELIF MPREG1CR_MODE_OPT = 1
OB_MPREG1CR_MODE         EQU     0x00003500
      ELIF MPREG1CR_MODE_OPT = 2
OB_MPREG1CR_MODE         EQU     0x0000A300
      ELSE
OB_MPREG1CR_MODE         EQU     0x0000FF00
      ENDIF
    ENDIF

    IF FLASH_MPREG1CR_OPT = 1
OB_MPREG1CR              EQU     (0xFFFF0000:OR:OB_MPREG1CR_MODE:OR:OB_MPREG1CR_ACCESSTYPE)
OB_MPREG1                EQU     (0xFC000000:OR:(MPREG1_ENDPAGE_OPT << 16):OR:0x0000FC00:OR:MPREG1_STARTPAGE_OPT)
    ELSE
OB_MPREG1CR              EQU     0xFFFFFFFF
OB_MPREG1                EQU     0xFFFFFFFF
    ENDIF

    IF FLASH_MPREG2CR_OPT = 1
      IF MPREG2CR_ACCESSTYPE_OPT = 0
OB_MPREG2CR_ACCESSTYPE   EQU     0x0000005A
      ELIF MPREG2CR_ACCESSTYPE_OPT = 1
OB_MPREG2CR_ACCESSTYPE   EQU     0x00000035
      ELSE
OB_MPREG2CR_ACCESSTYPE   EQU     0x000000FF
      ENDIF

      IF MPREG2CR_MODE_OPT = 0
OB_MPREG2CR_MODE         EQU     0x00005A00
      ELIF MPREG2CR_MODE_OPT = 1
OB_MPREG2CR_MODE         EQU     0x00003500
      ELIF MPREG2CR_MODE_OPT = 2
OB_MPREG2CR_MODE         EQU     0x0000A300
      ELSE
OB_MPREG2CR_MODE         EQU     0x0000FF00
      ENDIF
    ENDIF

    IF FLASH_MPREG2CR_OPT = 1
OB_MPREG2CR              EQU     (0xFFFF0000:OR:OB_MPREG2CR_MODE:OR:OB_MPREG2CR_ACCESSTYPE)
OB_MPREG2                EQU     (0xFC000000:OR:(MPREG2_ENDPAGE_OPT << 16):OR:0x0000FC00:OR:MPREG2_STARTPAGE_OPT)
    ELSE
OB_MPREG2CR              EQU     0xFFFFFFFF
OB_MPREG2                EQU     0xFFFFFFFF
    ENDIF

    IF FLASH_MPREG3CR_OPT = 1
      IF MPREG3CR_ACCESSTYPE_OPT = 0
OB_MPREG3CR_ACCESSTYPE   EQU     0x0000005A
      ELIF MPREG2CR_ACCESSTYPE_OPT = 1
OB_MPREG3CR_ACCESSTYPE   EQU     0x00000035
      ELSE
OB_MPREG3CR_ACCESSTYPE   EQU     0x000000FF
      ENDIF

      IF MPREG3CR_MODE_OPT = 0
OB_MPREG3CR_MODE         EQU     0x00005A00
      ELIF MPREG3CR_MODE_OPT = 1
OB_MPREG3CR_MODE         EQU     0x00003500
      ELIF MPREG3CR_MODE_OPT = 2
OB_MPREG3CR_MODE         EQU     0x0000A300
      ELSE
OB_MPREG3CR_MODE         EQU     0x0000FF00
      ENDIF
    ENDIF

    IF FLASH_MPREG3CR_OPT = 1
OB_MPREG3CR              EQU     (0xFFFF0000:OR:OB_MPREG3CR_MODE:OR:OB_MPREG3CR_ACCESSTYPE)
OB_MPREG3                EQU     (0xFC000000:OR:(MPREG3_ENDPAGE_OPT << 16):OR:0x0000FC00:OR:MPREG3_STARTPAGE_OPT)
    ELSE
OB_MPREG3CR              EQU     0xFFFFFFFF
OB_MPREG3                EQU     0xFFFFFFFF
    ENDIF

    IF FLASH_MPREG0CR_OPT = 1 || FLASH_MPREG1CR_OPT = 1 || FLASH_MPREG2CR_OPT = 1 || FLASH_MPREG3CR_OPT = 1
      IF FLASH_OPT_PARTIALLOCK = 0
        Protect_flash_rom_region_must_enable_flash_partial_lock.
      ENDIF
      IF KPCNT_OPT <= 1
        IF FLASH_MPREG0CR_OPT = 1 && MPREG0CR_MODE_OPT = 2
          Max_mismatch_value_must_greater_than_1_,_when_region_0_mode_is_access_by_key.
        ENDIF
        IF FLASH_MPREG1CR_OPT = 1 && MPREG1CR_MODE_OPT = 2
          Max_mismatch_value_must_greater_than_1_,_when_region_1_mode_is_access_by_key.
        ENDIF
        IF FLASH_MPREG2CR_OPT = 1 && MPREG2CR_MODE_OPT = 2
          Max_mismatch_value_must_greater_than_1_,_when_region_2_mode_is_access_by_key.
        ENDIF
        IF FLASH_MPREG3CR_OPT = 1 && MPREG3CR_MODE_OPT = 2
          Max_mismatch_value_must_greater_than_1_,_when_region_3_mode_is_access_by_key.
        ENDIF
      ENDIF
      IF (FLASH_MPREG0CR_OPT = 1 && \
          MPREG0_STARTPAGE_OPT <= 0x007 || MPREG0_ENDPAGE_OPT <= 0x007 || \
          MPREG0_STARTPAGE_OPT >= 0x3FF || MPREG0_ENDPAGE_OPT >= 0x3FF)
        Protect_flash_rom_region_0_start_and_end_Page_should_set_in_range_0x008_to_0x3FE.
      ENDIF
      IF (FLASH_MPREG1CR_OPT = 1 && \
          MPREG1_STARTPAGE_OPT <= 0x007 || MPREG1_ENDPAGE_OPT <= 0x007 || \
          MPREG1_STARTPAGE_OPT >= 0x3FF || MPREG1_ENDPAGE_OPT >= 0x3FF)
        Protect_flash_rom_region_1_start_and_end_Page_should_set_in_range_0x008_to_0x3FE.
      ENDIF
      IF (FLASH_MPREG2CR_OPT = 1 && \
          MPREG2_STARTPAGE_OPT <= 0x007 || MPREG2_ENDPAGE_OPT <= 0x007 || \
          MPREG2_STARTPAGE_OPT >= 0x3FF || MPREG2_ENDPAGE_OPT >= 0x3FF)
        Protect_flash_rom_region_2_start_and_end_Page_should_set_in_range_0x008_to_0x3FE.
      ENDIF
      IF (FLASH_MPREG3CR_OPT = 1 && \
          MPREG3_STARTPAGE_OPT <= 0x007 || MPREG3_ENDPAGE_OPT <= 0x007 || \
          MPREG3_STARTPAGE_OPT >= 0x3FF || MPREG3_ENDPAGE_OPT >= 0x3FF)
        Protect_flash_rom_region_3_start_and_end_Page_should_set_in_range_0x008_to_0x3FE.
      ENDIF
      IF (FLASH_MPREG0CR_OPT = 1 && \
          MPREG0_STARTPAGE_OPT > MPREG0_ENDPAGE_OPT)
        Protect_flash_rom_region_0_start_page_must_less_than_End_Page
      ENDIF
      IF (FLASH_MPREG1CR_OPT = 1 && \
          MPREG1_STARTPAGE_OPT > MPREG1_ENDPAGE_OPT)
        Protect_flash_rom_region_1_start_page_must_less_than_End_Page
      ENDIF
      IF (FLASH_MPREG2CR_OPT = 1 && \
          MPREG2_STARTPAGE_OPT > MPREG2_ENDPAGE_OPT)
        Protect_flash_rom_region_2_start_page_must_less_than_End_Page
      ENDIF
      IF (FLASH_MPREG3CR_OPT = 1 && \
          MPREG3_STARTPAGE_OPT > MPREG3_ENDPAGE_OPT)
        Protect_flash_rom_region_3_start_page_must_less_than_End_Page
      ENDIF
      IF (FLASH_MPREG0CR_OPT = 1 && FLASH_MPREG1CR_OPT = 1)
        IF (MPREG0_STARTPAGE_OPT >= MPREG1_STARTPAGE_OPT && MPREG0_STARTPAGE_OPT <= MPREG1_ENDPAGE_OPT) || \
           (MPREG0_ENDPAGE_OPT   >= MPREG1_STARTPAGE_OPT && MPREG0_ENDPAGE_OPT   <= MPREG1_ENDPAGE_OPT)
          Protect_flash_rom_region_0_range_overlaps_with_region_1_range.
        ENDIF
      ENDIF
      IF (FLASH_MPREG0CR_OPT = 1 && FLASH_MPREG2CR_OPT = 1)
        IF (MPREG0_STARTPAGE_OPT >= MPREG2_STARTPAGE_OPT && MPREG0_STARTPAGE_OPT <= MPREG2_ENDPAGE_OPT) || \
           (MPREG0_ENDPAGE_OPT   >= MPREG2_STARTPAGE_OPT && MPREG0_ENDPAGE_OPT   <= MPREG2_ENDPAGE_OPT)
          Protect_flash_rom_region_0_range_overlaps_with_region_2_range.
        ENDIF
      ENDIF
      IF (FLASH_MPREG0CR_OPT = 1 && FLASH_MPREG3CR_OPT = 1)
        IF (MPREG0_STARTPAGE_OPT >= MPREG3_STARTPAGE_OPT && MPREG0_STARTPAGE_OPT <= MPREG3_ENDPAGE_OPT) || \
           (MPREG0_ENDPAGE_OPT   >= MPREG3_STARTPAGE_OPT && MPREG0_ENDPAGE_OPT   <= MPREG3_ENDPAGE_OPT)
          Protect_flash_rom_region_0_range_overlaps_with_region_3_range.
        ENDIF
      ENDIF
      IF (FLASH_MPREG1CR_OPT = 1 && FLASH_MPREG2CR_OPT = 1)
        IF (MPREG1_STARTPAGE_OPT >= MPREG2_STARTPAGE_OPT && MPREG1_STARTPAGE_OPT <= MPREG2_ENDPAGE_OPT) || \
           (MPREG1_ENDPAGE_OPT   >= MPREG2_STARTPAGE_OPT && MPREG1_ENDPAGE_OPT   <= MPREG2_ENDPAGE_OPT)
          Protect_flash_rom_region_1_range_overlaps_with_region_2_range.
        ENDIF
      ENDIF
      IF (FLASH_MPREG1CR_OPT = 1 && FLASH_MPREG3CR_OPT = 1)
        IF (MPREG1_STARTPAGE_OPT >= MPREG3_STARTPAGE_OPT && MPREG1_STARTPAGE_OPT <= MPREG3_ENDPAGE_OPT) || \
           (MPREG1_ENDPAGE_OPT   >= MPREG3_STARTPAGE_OPT && MPREG1_ENDPAGE_OPT   <= MPREG3_ENDPAGE_OPT)
          Protect_flash_rom_region_1_range_overlaps_with_region_3_range.
        ENDIF
      ENDIF
      IF (FLASH_MPREG2CR_OPT = 1 && FLASH_MPREG3CR_OPT = 1)
        IF (MPREG2_STARTPAGE_OPT >= MPREG3_STARTPAGE_OPT && MPREG2_STARTPAGE_OPT <= MPREG3_ENDPAGE_OPT) || \
           (MPREG2_ENDPAGE_OPT   >= MPREG3_STARTPAGE_OPT && MPREG2_ENDPAGE_OPT   <= MPREG3_ENDPAGE_OPT)
          Protect_flash_rom_region_2_range_overlaps_with_region_3_range.
        ENDIF
      ENDIF
    ENDIF

    IF FLASH_OPT_PARTIALLOCK = 1
        AREA    |.ARM.__AT_0x1FF00080|, CODE, READONLY
        DCD   OB_KEY0         ; 0x1FF00080
        DCD   OB_KEY1         ; 0x1FF00084
        DCD   OB_KEY2         ; 0x1FF00088
        DCD   OB_KEY3         ; 0x1FF0008C
        DCD   OB_KPCTL        ; 0x1FF00090
        DCD   OB_KPCNT        ; 0x1FF00094
        DCD   OPT_RES         ; 0x1FF00098
        DCD   OPT_RES         ; 0x1FF0009C
        DCD   nOB_KPPP0       ; 0x1FF000A0
        DCD   nOB_KPPP1       ; 0x1FF000A4
        DCD   nOB_KPPP2       ; 0x1FF000A8
        DCD   nOB_KPPP3       ; 0x1FF000AC
        DCD   OB_MPREG0CR     ; 0x1FF000B0
        DCD   OB_MPREG0       ; 0x1FF000B4
        DCD   OB_MPREG1CR     ; 0x1FF000B8
        DCD   OB_MPREG1       ; 0x1FF000BC
        DCD   OB_MPREG2CR     ; 0x1FF000C0
        DCD   OB_MPREG2       ; 0x1FF000C4
        DCD   OB_MPREG3CR     ; 0x1FF000C8
        DCD   OB_MPREG3       ; 0x1FF000CC
    ENDIF

                END
