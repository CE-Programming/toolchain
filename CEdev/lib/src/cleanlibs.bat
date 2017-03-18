@echo off

REM ----------------------------------------------------
REM  Deletes built shared libraries for release cleanup
REM  By Matt "MateoConLechuga" Waltz
REM ----------------------------------------------------

echo -- Deleting built shared libs...
cd fileio
rmdir /S /Q lib
cd ..
cd keypad
rmdir /S /Q lib
cd ..
cd graphics/graphc
rmdir /S /Q lib
cd ../graphx
rmdir /S /Q lib
cd ../..