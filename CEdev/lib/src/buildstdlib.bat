@echo off

if exist *.obj del *.obj

if exist %1 del %1

set ALL_SRC=%C_SRC% %ASM_SRC%

for %%i in (%C_SRC%) do %CC% %C_FLG% -stdinc:"%STDINC%;%ZLGINC%" "%cd%\std\%%i"

for %%i in (%ASM_SRC%) do %ASM% %ASM_FLG% std\%%i 

for %%i in (%ALL_SRC%) do %LIB% -quiet -warn %1=+%%~ni.obj
