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
SET HT_CHANGE_LINKER_SCRIPT=0
SET HT_LINKER_NAME_KEIL=linker.lin
SET HT_LINKER_NAME_IAR=linker.icf
SET HT_LINKER_NAME_GNU=..\GNU\linker.ld
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
gsar.exe -s"    <name>User</name>" -r"    <name>User</name>:x0a    <file>:x0a      <name>$PROJ_DIR$\..\calculate_symbol_EWARM.o</name>:x0a    </file>" EWARM\*.ewp -o
gsar.exe -s"        <name>User</name>" -r"        <name>User</name>:x0a        <file>:x0a            <name>$PROJ_DIR$\..\calculate_symbol_EWARMv8.o</name>:x0a        </file>" EWARMv8\*.ewp -o
gsar.exe -s"<FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>:x0a            <File>:x0aTFILENAME:x0aTFILETYPE:x0aTFILEPATH:x0a            </File>" GNU_ARM\*.uvprojx -o
gsar.exe -s"TFILENAME" -r"              <FileName>calculate_symbol_GNU.ld</FileName>" GNU_ARM\*.uvprojx -o
gsar.exe -s"TFILETYPE" -r"              <FileType>4</FileType>" GNU_ARM\*.uvprojx -o
gsar.exe -s"TFILEPATH" -r"              <FilePath>..\calculate_symbol_GNU.ld</FilePath>" GNU_ARM\*.uvprojx -o
rem gsar.exe -s"<FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>:x0a            <File>:x0aTFILENAME:x0aTFILETYPE:x0aTFILEPATH:x0a            </File>" MDK_ARM\*.uvproj -o
rem gsar.exe -s"TFILENAME" -r"              <FileName>calculate_symbol_MDK.o</FileName>" MDK_ARM\*.uvproj -o
rem gsar.exe -s"TFILETYPE" -r"              <FileType>3</FileType>" MDK_ARM\*.uvproj -o
rem gsar.exe -s"TFILEPATH" -r"              <FilePath>..\calculate_symbol_MDK.o</FilePath>" MDK_ARM\*.uvproj -o
gsar.exe -s"<FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f7xxxx_01_it.c</FilePath>:x0a            </File>:x0a            <File>:x0aTFILENAME:x0aTFILETYPE:x0aTFILEPATH:x0a            </File>" MDK_ARMv5\*.uvprojx -o
gsar.exe -s"TFILENAME" -r"              <FileName>calculate_symbol_MDKv5.o</FileName>" MDK_ARMv5\*.uvprojx -o
gsar.exe -s"TFILETYPE" -r"              <FileType>3</FileType>" MDK_ARMv5\*.uvprojx -o
gsar.exe -s"TFILEPATH" -r"              <FilePath>..\calculate_symbol_MDKv5.o</FilePath>" MDK_ARMv5\*.uvprojx -o

for /D %%d in (HT32-IDE\Project_*) do (
  gsar.exe -s"	<linkedResources>" -r"	<linkedResources>:x0a		<link>:x0aNAME:x0aTYPE:x0aLOCATIONURI:x0a		</link>" %%d\*.project -o
  gsar.exe -s"NAME" -r"			<name>User/calculate_symbol_HT32.ld</name>" %%d\*.project -o
  gsar.exe -s"TYPE" -r"			<type>1</type>" %%d\*.project -o
  gsar.exe -s"LOCATIONURI" -r"			<locationURI>PARENT-2-PROJECT_LOC/calculate_symbol_HT32.ld</locationURI>" %%d\*.project -o

  gsar.exe -s"<option id=:x22ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.otherobjs.39189245:x22 name=:x22Other objects:x22 superClass=:x22ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.otherobjs:x22/>" -r"OPTION1:x0a									OPTION2:x0a								</option>" %%d\.cproject -o
  gsar.exe -s"OPTION1" -r"<option IS_BUILTIN_EMPTY=:x22false:x22 IS_VALUE_EMPTY=:x22false:x22 id=:x22ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.otherobjs.39189245:x22 name=:x22Other objects:x22 superClass=:x22ilg.gnuarmeclipse.managedbuild.cross.option.cpp.linker.otherobjs:x22 valueType=:x22userObjs:x22>" %%d\.cproject -o
  gsar.exe -s"OPTION2" -r"<listOptionValue builtIn=:x22false:x22 value=:x22:x26quot;..\..\..\calculate_symbol_HT32.ld:x26quot;:x22/>" %%d\.cproject -o
)
