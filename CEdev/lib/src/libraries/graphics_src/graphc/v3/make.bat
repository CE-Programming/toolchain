@echo off

:: Set LIB_NAME to the name of your library
:: Set LIB_SRC to the assembly source of your library

set LIB_NAME=GRAPHC
set LIB_SRC=graphics_lib_old.asm

echo Assembling Library...
mkdir lib
set LIB_LIB=%LIB_NAME%.lib
set LIB_ASM=%LIB_NAME%.asm
set LIB_8XV=%LIB_NAME%.8xv
set LIB_JMP=%LIB_NAME%.jmp
set ASM_SRC=*.src
set BIN=%CEDEV%\bin
set ASM=%BIN%\ez80asm.exe
set LIB=%BIN%\ez80lib.exe
set ASM_FLG=-genobj -NOigcase -NOlist -NOlistmac -pagelen:56 -pagewidth:100 -quiet -sdiopt -cpu:EZ80F91 -NOdebug
..\..\..\include\spasm -E %LIB_SRC% %LIB_NAME%.8xv
echo Building library...
if exist *.obj del *.obj
if exist %LIB_LIB% del %LIB_LIB%
for %%i in (%ASM_SRC%) do %ASM% %ASM_FLG% %%i
for %%i in (%ASM_SRC%) do %LIB% -quiet -warn %LIB_LIB%=+%%~ni.obj
if exist *.obj del *.obj
if exist *.src del *.src
if exist relocation_table del relocation_table
move /Y %LIB_LIB% lib > nul
move /Y %LIB_ASM% lib > nul
move /Y %LIB_8XV% lib > nul
move /Y %LIB_JMP% lib > nul
cd lib
for /F %%a in ('dir /L /B') do rename %%a %%a