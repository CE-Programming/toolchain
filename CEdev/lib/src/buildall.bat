@echo off

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
set STATIC_PATH=std\os_functions_static
set LINKED_PATH=std\os_functions_linked
set CE_PATH=ce

set ASM=%BIN%\ez80asm.exe
set CC=%BIN%\eZ80cc.exe
set LIB=%BIN%\ez80lib.exe

REM -- Static and linked hold the same file names --

set RTL_STATIC_C_SRC=asin.c atan.c atan2.c exp.c floor.c fmod.c frexp.c ldexp.c log.c log10.c modf.c pow.c sin.c sinh.c sqrt.c strtod.c tan.c tanh.c ufltinfo.c ufltrnd.c
set RTL_STATIC_ASM_SRC=acos.asm atof.asm ceil.asm cos.asm fabs.asm isalnum.asm isalpha.asm iscntrl.asm isdigit.asm isgraph.asm islower.asm isprint.asm ispunct.asm isspace.asm isupper.asm isxdigit.asm

set RTL_LINKED_C_SRC=
set RTL_LINKED_ASM_SRC=acos.asm asin.asm atan.asm atan2.asm atof.asm ceil.asm cos.asm cosh.asm exp.asm fabs.asm floor.asm fmod.asm frexp.asm isalnum.asm isalpha.asm iscntrl.asm isdigit.asm isgraph.asm islower.asm isprint.asm ispunct.asm isspace.asm isupper.asm isxdigit.asm ldexp.asm log.asm log10.asm modf.asm pow.asm sin.asm sinh.asm sqrt.asm strtod.asm tan.asm tanh.asm ufltinfo.asm ufltrnd.asm

set RTL_SHARED_C_SRC=bsearch.c fpdata.c free.c gamma.c malloc.c maptab.c qsort.c realloc.c strtol.c strtoul.c udtoe.c udtof.c udtog.c uitoa.c ultoa.c ureverse.c ustoa.c uuitoa.c uultoa.c uustoa.c vsprintf.c
set RTL_SHARED_ASM_SRC=abs.asm atoi.asm atol.asm atos.asm calloc.asm div.asm finite.asm fpadd.asm fpcmp.asm fpdiv.asm fpftol.asm fpltof.asm fpmul.asm fpneg.asm fppack.asm fpsub.asm fpultof.asm fpupop1.asm fpupop2.asm isascii.asm isinf.asm isnan.asm log2.asm longjmp.asm memchr.asm memcmp.asm memcpy.asm memmove.asm memset.asm rand.asm round.asm sbrk.asm setjmp.asm sprintf.asm sqrtf.asm srand.asm stoi.asm strcasecmp.asm strcat.asm strchr.asm strcmp.asm strcpy.asm strcspn.asm strdup.asm strlen.asm strncasecmp.asm strncat.asm strncmp.asm strncpy.asm strndup.asm strnlen.asm strpbrk.asm strrchr.asm strspn.asm strstr.asm strtok.asm tolower.asm toupper.asm uldiv.asm

set HLP_C_SRC=
set HLP_ASM_SRC=bdivs.asm bdivu.asm bldix.asm bldiy.asm bmuls.asm brems.asm bremu.asm bshl.asm bshrs.asm bshru.asm bstix.asm bstiy.asm case.asm case24.asm case24D.asm case16.asm case16D.asm case8.asm case8D.asm iand.asm idivs.asm idivu.asm ildix.asm ildiy.asm imulu.asm imuls.asm indcall.asm ineg.asm inot.asm ior.asm irems.asm iremu.asm ishl.asm ishrs.asm ishru.asm istix.asm istiy.asm itol.asm ixor.asm ladd.asm land.asm lcmpu.asm lcmps.asm ldivs.asm ldivu.asm lldix.asm lldiy.asm lmulu.asm lmuls.asm lneg.asm lnot.asm lor.asm lrems.asm lremu.asm lshl.asm lshrs.asm lshru.asm lstix.asm lstiy.asm lsub.asm lxor.asm sand.asm sdivs.asm sdivu.asm sldix.asm sldiy.asm smulu.asm sneg.asm snot.asm sor.asm srems.asm sremu.asm sshl.asm sshrs.asm sshru.asm sstix.asm sstiy.asm stoi.asm stoiu.asm sxor.asm frbmuls.asm frbtof.asm frftob.asm frftoi.asm frftos.asm frftoub.asm frftoui.asm frftous.asm frimuls.asm frimulu.asm fritof.asm frsmuls.asm frsmulu.asm frstof.asm frubtof.asm fruitof.asm frustof.asm frameset0.asm frameset.asm setflag.asm scmpzero.asm icmpzero.asm lcmpzero.asm seqcase.asm seqcaseD.asm

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

echo -- Building CHLP libraries...
set MY_PATH=%SHARED_PATH%
set C_SRC=%HLP_C_SRC%
set ASM_SRC=%HLP_ASM_SRC%
call buildlib.bat chelp.lib

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
