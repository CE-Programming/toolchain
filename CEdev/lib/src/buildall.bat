@echo off
setlocal enabledelayedexpansion

REM ----------------------------------------------------
REM  Batch file to build all runtime libraries 
REM 
REM  (c) Zilog, Inc.
REM  Modified by Matt "MateoConLechuga" Waltz for CE support
REM ----------------------------------------------------

REM +--Setting environment variables-------------------+

set SRC=.
set BIN=%CEDEV%\bin
set INC=%CEDEV%\include
set LIBPATH=%CEDEV%\lib
set SHARED_PATH=std\shared
set STATIC_PATH=std\static
set LINKED_PATH=std\linked
set CE_PATH=ce

set ASM=%BIN%\ez80asm.exe
set CC=%BIN%\eZ80cc.exe
set LIB=%BIN%\ez80lib.exe

REM -- Static and linked hold the same file names --

call :setfiles RTL_STATIC_C_SRC %STATIC_PATH%\*.c
call :setfiles RTL_STATIC_ASM_SRC %STATIC_PATH%\*.asm

call :setfiles RTL_LINKED_C_SRC %LINKED_PATH%\*.c
call :setfiles RTL_LINKED_ASM_SRC %LINKED_PATH%\*.asm

call :setfiles RTL_SHARED_C_SRC %SHARED_PATH%\*.c
call :setfiles RTL_SHARED_ASM_SRC %SHARED_PATH%\*.asm


set INT_C_SRC=
set INT_ASM_SRC=interrupts.asm

set USB_C_SRC=
set USB_ASM_SRC=usb.asm

set DEBUG_C_SRC=
set DEBUG_ASM_SRC=debugger.asm removeallbreakpoints.asm removeallwatchpoints.asm removebreakpoint.asm removewatchpoint.asm setbreakpoint.asm setreadwatchpoint.asm setwritewatchpoint.asm setreadwritewatchpoint.asm  setwatchpoint.asm

set TICE_C_SRC=
set TICE_ASM_SRC=dzx7_standard.asm dzx7_turbo.asm tice.asm memset_fast.asm prgmcleanup.asm abort.asm os.asm

set CPU=EZ80F91
set STDINC=%INC%\lib\std
set CEINC=%CEDEV%\include\lib\ce
set ZLGINC=%SRC%\include
set CFLG_REL=-NOdebug -optsize -NOkeeplst -promote -quiet -fplib
set AFLG=-genobj -NOigcase -include:%STDINC% -include:%ZLGINC% -NOlist -NOlistmac -pagelen:55 -pagewidth:100 -quiet -sdiopt -warn -NOzmasm

REM ---make sure dir exists
mkdir %LIBPATH%
mkdir %LIBPATH%\std
mkdir %LIBPATH%\std\ce

REM --- CE Libraries

set C_FLG=%CFLG_REL% -cpu:%CPU% -asmsw:"-cpu:%CPU% -include:%STDINC% -include:%ZLGINC%" -define:_%CPU%
set ASM_FLG=%AFLG% -cpu:%CPU% -NOdebug

echo -- Building CE Debugger library...
set MY_PATH=%CE_PATH%
set C_SRC=%DEBUG_C_SRC%
set ASM_SRC=%DEBUG_ASM_SRC%
call buildlib.bat cdebug.lib

echo -- Building TICE library...
set MY_PATH=%CE_PATH%
set C_SRC=%TICE_C_SRC%
set ASM_SRC=%TICE_ASM_SRC%
call buildlib.bat ctice.lib

echo -- Building Interrupt library...
set MY_PATH=%CE_PATH%
set C_SRC=%INT_C_SRC%
set ASM_SRC=%INT_ASM_SRC%
call buildlib.bat cintce.lib

echo -- Building USB library...
set MY_PATH=%CE_PATH%
set C_SRC=%USB_C_SRC%
set ASM_SRC=%USB_ASM_SRC%
call buildlib.bat cusbce.lib

echo -- Building RTL...
set MY_PATH=%SHARED_PATH%
set C_SRC=%RTL_SHARED_C_SRC%
set ASM_SRC=%RTL_SHARED_ASM_SRC%
call buildlib.bat crt.lib

echo -- Building RT Linked Library Portion...
set MY_PATH=%LINKED_PATH%
set C_SRC=%RTL_LINKED_C_SRC%
set ASM_SRC=%RTL_LINKED_ASM_SRC%
call buildlib.bat crt_linked.lib

echo -- Building RT Static Library Portion...
set MY_PATH=%STATIC_PATH%
set C_SRC=%RTL_STATIC_C_SRC%
set ASM_SRC=%RTL_STATIC_ASM_SRC%
call buildlib.bat crt_static.lib

echo -- Building Libraries...
cd fileio
call build.bat
cd ..
cd keypad
call build.bat
cd ..
cd graphics/graphc
call build.bat
cd ../graphx
call build.bat
cd ../..

echo -- Copying the libraries...

REM -- copy the libraries --
copy /Y *.lib %LIBPATH%\std
move /Y %LIBPATH%\std\ctice.lib %LIBPATH%\std\ce\ctice.lib
move /Y %LIBPATH%\std\cdebug.lib %LIBPATH%\std\ce\cdebug.lib
move /Y %LIBPATH%\std\cintce.lib %LIBPATH%\std\ce\cintce.lib
move /Y %LIBPATH%\std\cusbce.lib %LIBPATH%\std\ce\cusbce.lib

REM -- cleanup intermediate files --
if exist *.lib del *.lib
if exist *.obj del *.obj

pause
goto :eof

:setfiles
set %1=
for %%a in (%2) do set %1=!%1! %%~nxa
goto :eof
