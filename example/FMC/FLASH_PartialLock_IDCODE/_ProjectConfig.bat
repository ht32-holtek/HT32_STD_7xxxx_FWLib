REM /*********************************************************************************************************//**
REM * @file    _ProjectConfig.bat
REM * @version $Rev:: 9096         $
REM * @date    $Date:: 2025-06-17 #$
REM * @brief   Project configure file.
REM *************************************************************************************************************

REM README
REM This file provides the function below. It shall be use with "_CreateProject.bat"
REM  1. Remove Project_xxxxx files that do not supported by the example/application code (xxxxx is model name).
REM  2. Change RO, RW Based address.
REM  3. Change Stack and Heap Size.
REM  4. Change the C include path.
REM  5. Change the C define
REM  6. Change the linker Script usage or name
REM  7. Apply specify modification by customer.
REM


REM Remove Project_xxxxx files that do not supported by the example/application code
REM ============================================================================
REM For device support, see _ProjectConfig.ini

rmdir /S /Q "emStudiov4"
rem rmdir /S /Q "EWARM"
rem rmdir /S /Q "EWARMv8"
rem rmdir /S /Q "GNU_ARM"
rem rmdir /S /Q "HT32-IDE"
rmdir /S /Q "MDK_ARM"
rem rmdir /S /Q "MDK_ARMv5"
rmdir /S /Q "MDK_ARMv537"
rmdir /S /Q "SourceryG++Lite"
REM ============================================================================




REM !!! NOTICE: Do not put any space between the "=" !!!
REM !!!         "SET VAR=VALUE" is OK
REM !!!         "SET VAR = VALUE" is not allowed




REM Change RO, RW Based address
REM ============================================================================
SET HT_CHANGE_RO_RW=0
SET HT_RO_ADDR=0x00000000
SET HT_RW_ADDR=0x20000000
REM ============================================================================


REM Change Stack and Heap Size
REM ============================================================================
SET HT_CHANGE_STACK_HEAP=0
SET HT_STACK_SIZE=512
SET HT_HEAP_SIZE=0
REM ============================================================================


REM Change include path
REM Note:
REM     1. HT_EXTRA_INCLUDE shall be separated by semicolons (;)
REM        Example HT_EXTRA_INCLUDE=..\Test1;..\Extra_Include
REM ============================================================================
SET HT_CHANGE_INCLUDE=0
SET HT_EXTRA_INCLUDE=..\PATH1;..\PATH2
REM ============================================================================


REM Change C define
REM Note:
REM     1. HT_EXTRA_CDEFINE shall be separated by comma and space (, )
REM        Example HT_EXTRA_CDEFINE=DEFINE1, DEFINE2
REM ============================================================================
SET HT_CHANGE_CDEFINE=0
SET HT_EXTRA_CDEFINE=DEFINE1, DEFINE2
REM ============================================================================


REM Change Linker Script file
REM Note:
REM     1. The path is relative to the project file folder, such as "HT32-IDE\" or "MDK_ARMv5\".
REM ============================================================================
SET HT_CHANGE_LINKER_SCRIPT=1
SET HT_LINKER_NAME_KEIL=linker.lin
SET HT_LINKER_NAME_IAR=linker.icf
SET HT_LINKER_NAME_GNU=linker.ld
SET HT_LINKER_NAME_HT32_IDE=GNU_ARM\linker.ld
SET HT_LINKER_NAME_SES=../SES/linker_test.icf
SET HT_LINKER_NAME_SourceryG=..\SourceryG\linker_test.ld
REM ============================================================================


REM Apply specify modification
REM Example: (":x0a" for newline "\n")
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" MDK_ARM\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" MDK_ARMv5\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" MDK_ARMv537\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" EWARM\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" EWARMv8\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" GNU_ARM\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" SourceryG++Lite\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
REM ============================================================================
rem Edit your code here....
REM ============================================================================
copy /Y "_setting\EWARM_ht32_op2.c" "EWARM\ht32_op2.c"
copy /Y "_setting\EWARM_ht32_op2.c" "EWARMv8\ht32_op2.c"
copy /Y "_setting\GNU_ht32_op2.c" "GNU_ARM\ht32_op2.c"
copy /Y "_setting\GNU_ht32_op2.c" "HT32-IDE\GNU_ARM\ht32_op2.c"
rem copy /Y "_setting\MDK_ht32_op2.s" "MDK_ARM\ht32_op2.s"
copy /Y "_setting\MDK_ht32_op2.s" "MDK_ARMv5\ht32_op2.s"
rem copy /Y "_setting\MDK_ht32_op2.s" "MDK_ARMv537\ht32_op2.s"

copy /Y "_setting\EWARM_linker.icf" "EWARM\linker.icf"
copy /Y "_setting\EWARM_linker.icf" "EWARMv8\linker.icf"
copy /Y "_setting\GNU_linker.ld" "GNU_ARM\linker.ld"
copy /Y "_setting\GNU_linker.ld" "HT32-IDE\GNU_ARM\linker.ld"
rem copy /Y "_setting\MDK_linker.lin" "MDK_ARM\linker.lin"
copy /Y "_setting\MDK_linker.lin" "MDK_ARMv5\linker.lin"
rem copy /Y "_setting\MDK_linker.lin" "MDK_ARMv537\linker.lin"

rem gsar.exe -s"<ScatterFile></ScatterFile>" -r"<ScatterFile>.\linker.lin</ScatterFile>" MDK_ARM\*.uvproj -o
rem gsar.exe -s"<ScatterFile></ScatterFile>" -r"<ScatterFile>.\linker.lin</ScatterFile>" MDK_ARMv5\*.uvprojx -o
rem gsar.exe -s"<ScatterFile></ScatterFile>" -r"<ScatterFile>.\linker.lin</ScatterFile>" MDK_ARMv537\*.uvprojx -o

gsar.exe -s"    <name>User</name>" -r"    <name>User</name>:x0a"TFILE":x0a      <name>$PROJ_DIR$\..\icode.c</name>:x0a"TCONFIGURATION":x0a"NAMEHT32":x0a"TSETTINGS":x0a"NAMEICCARM":x0a"TDATA":x0a"TOPTION":x0a"CCNAME0":x0a"STATE0":x0a"OPTION":x0a"TOPTION":x0a"CCNAME1":x0a"STATE1":x0a"OPTION":x0a"DATA":x0a"SETTINGS":x0a"CONFIGURATION":x0a"UFILE"" EWARM\*.ewp -o
gsar.exe -s"TFILE" -r"    <file>" EWARM\*.ewp -o
gsar.exe -s"TCONFIGURATION" -r"        <configuration>" EWARM\*.ewp -o
gsar.exe -s"NAMEHT32" -r"          <name>HT32</name>" EWARM\*.ewp -o
gsar.exe -s"TSETTINGS" -r"          <settings>" EWARM\*.ewp -o
gsar.exe -s"NAMEICCARM" -r"            <name>ICCARM</name>" EWARM\*.ewp -o
gsar.exe -s"TDATA" -r"            <data>" EWARM\*.ewp -o
gsar.exe -s"TOPTION" -r"              <option>" EWARM\*.ewp -o
gsar.exe -s"CCNAME0" -r"                <name>IExtraOptionsCheck</name>" EWARM\*.ewp -o
gsar.exe -s"STATE0" -r"                <state>1</state>" EWARM\*.ewp -o
gsar.exe -s"CCNAME1" -r"                <name>IExtraOptions</name>" EWARM\*.ewp -o
gsar.exe -s"STATE1" -r"                <state>--no_literal_pool</state>" EWARM\*.ewp -o
gsar.exe -s"OPTION" -r"              </option>" EWARM\*.ewp -o
gsar.exe -s"DATA" -r"            </data>" EWARM\*.ewp -o
gsar.exe -s"SETTINGS" -r"          </settings>" EWARM\*.ewp -o
gsar.exe -s"CONFIGURATION" -r"        </configuration>" EWARM\*.ewp -o
gsar.exe -s"UFILE" -r"    </file>" EWARM\*.ewp -o

gsar.exe -s"        <name>User</name>" -r"        <name>User</name>:x0a"TFILE":x0a            <name>$PROJ_DIR$\..\icode.c</name>:x0a"TCONFIGURATION":x0a"NAMEHT32":x0a"TSETTINGS":x0a"NAMEICCARM":x0a"TDATA":x0a"TOPTION":x0a"CCNAME":x0a"STATE":x0a"OPTION":x0a"DATA":x0a"SETTINGS":x0a"CONFIGURATION":x0a"UFILE"" EWARMv8\*.ewp -o
gsar.exe -s"TFILE" -r"        <file>" EWARMv8\*.ewp -o
gsar.exe -s"TCONFIGURATION" -r"                <configuration>" EWARMv8\*.ewp -o
gsar.exe -s"NAMEHT32" -r"                    <name>HT32</name>" EWARMv8\*.ewp -o
gsar.exe -s"TSETTINGS" -r"                    <settings>" EWARMv8\*.ewp -o
gsar.exe -s"NAMEICCARM" -r"                        <name>ICCARM</name>" EWARMv8\*.ewp -o
gsar.exe -s"TDATA" -r"                        <data>" EWARMv8\*.ewp -o
gsar.exe -s"TOPTION" -r"                            <option>" EWARMv8\*.ewp -o
gsar.exe -s"CCNAME" -r"                                <name>CCNoLiteralPool</name>" EWARMv8\*.ewp -o
gsar.exe -s"STATE" -r"                                <state>1</state>" EWARMv8\*.ewp -o
gsar.exe -s"OPTION" -r"                            </option>" EWARMv8\*.ewp -o
gsar.exe -s"DATA" -r"                        </data>" EWARMv8\*.ewp -o
gsar.exe -s"SETTINGS" -r"                    </settings>" EWARMv8\*.ewp -o
gsar.exe -s"CONFIGURATION" -r"                </configuration>" EWARMv8\*.ewp -o
gsar.exe -s"UFILE" -r"        </file>" EWARMv8\*.ewp -o

gsar.exe -s"              <FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>:x0a" -r"              <FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>:x0a            <File>:x0a              <FileName>icode.c</FileName>:x0a              <FileType>1</FileType>:x0a              <FilePath>..\icode.c</FilePath>:x0a            </File>:x0a" GNU_ARM\*.uvprojx -o
rem gsar.exe -s"              <FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>:x0a" -r"              <FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>:x0a            <File>:x0a              <FileName>icode.c</FileName>:x0a              <FileType>1</FileType>:x0a              <FilePath>..\icode.c</FilePath>:x0a            </File>:x0a" MDK_ARM\*.uvproj -o
gsar.exe -s"              <FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>:x0a" -r"              <FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>:x0a            <File>:x0a              <FileName>icode.c</FileName>:x0a              <FileType>1</FileType>:x0a              <FilePath>..\icode.c</FilePath>:x0a            </File>:x0a" MDK_ARMv5\*.uvprojx -o

gsar.exe -s"              <FilePath>..\icode.c</FilePath>" -r"              <FilePath>..\icode.c</FilePath>:x0aTFILEOPTION:x0aTFILEARM:x0aTCARM:x0aTVARIOUSCONTROLS:x0aTMISCCONTROLS:x0aUVARIOUSCONTROLS:x0aUCARM:x0aUFILEARM:x0aUFILEOPTION" GNU_ARM\*.uvprojx -o
gsar.exe -s"TFILEOPTION" -r"              <FileOption>" GNU_ARM\*.uvprojx -o
gsar.exe -s"TFILEARM" -r"                <FileArm>" GNU_ARM\*.uvprojx -o
gsar.exe -s"TCARM" -r"                  <Carm>" GNU_ARM\*.uvprojx -o
gsar.exe -s"TVARIOUSCONTROLS" -r"                    <VariousControls>" GNU_ARM\*.uvprojx -o
gsar.exe -s"TMISCCONTROLS" -r"                      <MiscControls>-mpure-code</MiscControls>" GNU_ARM\*.uvprojx -o
gsar.exe -s"UVARIOUSCONTROLS" -r"                    </VariousControls>" GNU_ARM\*.uvprojx -o
gsar.exe -s"UCARM" -r"                  </Carm>" GNU_ARM\*.uvprojx -o
gsar.exe -s"UFILEARM" -r"                </FileArm>" GNU_ARM\*.uvprojx -o
gsar.exe -s"UFILEOPTION" -r"              </FileOption>" GNU_ARM\*.uvprojx -o

rem gsar.exe -s"              <FilePath>..\icode.c</FilePath>:x0a" -r"              <FilePath>..\icode.c</FilePath>:x0a              <FileOption>:x0a                <FileArmAds>:x0a                  <Cads>:x0a                    <useXO>1</useXO>:x0a                  </Cads>:x0a                </FileArmAds>:x0a              </FileOption>:x0a" MDK_ARM\*.uvproj -o
gsar.exe -s"              <FilePath>..\icode.c</FilePath>:x0a" -r"              <FilePath>..\icode.c</FilePath>:x0a              <FileOption>:x0a                <FileArmAds>:x0a                  <Cads>:x0a                    <useXO>1</useXO>:x0a                  </Cads>:x0a                </FileArmAds>:x0a              </FileOption>:x0a" MDK_ARMv5\*.uvprojx -o

for /D %%d in (HT32-IDE\Project_*) do (
  gsar.exe -s"	<linkedResources>" -r"	<linkedResources>:x0a		<link>:x0aNAME:x0aTYPE:x0aLOCATIONURI:x0a		</link>" %%d\*.project -o
  gsar.exe -s"NAME" -r"			<name>User/icode.c</name>" %%d\*.project -o
  gsar.exe -s"TYPE" -r"			<type>1</type>" %%d\*.project -o
  gsar.exe -s"LOCATIONURI" -r"			<locationURI>PARENT-2-PROJECT_LOC/icode.c</locationURI>" %%d\*.project -o

  gsar.exe -s"</folderInfo>" -r"</folderInfo>:x0a					<fileInfo FILEINFO>:x0a						<tool TOOL>:x0a							<option OPTION/>:x0a						</tool>:x0a					</fileInfo>" %%d\.cproject -o
  gsar.exe -s"FILEINFO" -r"id=:x22ilg.gnuarmeclipse.managedbuild.cross.config.elf.debug.2102899455.1307405103:x22 name=:x22icode.c:x22 rcbsApplicability=:x22disable:x22 resourcePath=:x22User/icode.c:x22 toolsToInvoke=:x22ilg.gnuarmeclipse.managedbuild.cross.tool.c.compiler.989711717.139317847:x22" %%d\.cproject -o
  gsar.exe -s"TOOL" -r"id=:x22ilg.gnuarmeclipse.managedbuild.cross.tool.c.compiler.989711717.139317847:x22 name=:x22GNU Arm Cross C Compiler:x22 superClass=:x22ilg.gnuarmeclipse.managedbuild.cross.tool.c.compiler.989711717:x22" %%d\.cproject -o
  gsar.exe -s"OPTION" -r"id=:x22ilg.gnuarmeclipse.managedbuild.cross.option.c.compiler.other.1637302212:x22 superClass=:x22ilg.gnuarmeclipse.managedbuild.cross.option.c.compiler.other:x22 value=:x22-c -MD -mapcs-frame --param=min-pagesize=0 -mpure-code:x22 valueType=:x22string:x22" %%d\.cproject -o
)
