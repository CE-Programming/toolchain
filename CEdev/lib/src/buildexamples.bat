@echo off

REM ----------------------------------------------------
REM  Builds all examples for easy compile testing
REM  By Matt "MateoConLechuga" Waltz
REM ----------------------------------------------------

echo -- Cleaning examples...
cd /D %CEDEV%\examples
for /D %%a in (demo*) do cd %%a && make -B && cd ..
cd /D %CEDEV%\examples\library_examples\fileio
for /D %%a in (demo*) do cd %%a && make -B && cd ..
cd /D %CEDEV%\examples\library_examples\graphics
for /D %%a in (demo*) do cd %%a && make -B && cd ..
cd /D %CEDEV%\examples\library_examples\keypad
for /D %%a in (demo*) do cd %%a && make -B && cd ..
cd %CEDEV%\lib\src
