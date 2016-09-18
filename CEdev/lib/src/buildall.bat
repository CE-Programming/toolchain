@echo off

REM ----------------------------------------------------
REM  Batch file to build all runtime libraries 
REM 
REM  (c) Zilog, Inc.
REM  Modified by Matt Waltz for CE support
REM ----------------------------------------------------

REM +--Setting environment variables-------------------+
set BIN=%CEDEV%\bin
set INC=%CEDEV%\include
set LIBPATH=%CEDEV%\lib
set SRC=.

set ASM=%BIN%\ez80asm.exe
set CC=%BIN%\eZ80cc.exe
set LIB=%BIN%\ez80lib.exe

set RTL_C_SRC=bsearch.c maptab.c modf.c qsort.c strtod.c strtol.c strtoul.c ufltinfo.c ufltrnd.c ureverse.c
set RTL_ST_C_SRC=uitoa.c ultoa.c ustoa.c uuitoa.c uultoa.c uustoa.c vsprintf.c

set RTL_NOKERNEL_C_SRC=free.c malloc.c realloc.c
set RTL_ASM_SRC=atoi.asm atol.asm atos.asm abs.asm calloc.asm isalnum.asm isalpha.asm iscntrl.asm isdigit.asm isgraph.asm islower.asm isprint.asm ispunct.asm isspace.asm isupper.asm isxdigit.asm isascii.asm labs.asm sprintf.asm strtok.asm longjmp.asm memchr.asm memcmp.asm memcpy.asm memmove.asm memset.asm sbrk.asm setjmp.asm strcat.asm strchr.asm strcmp.asm strcpy.asm strcspn.asm strlen.asm strncat.asm strncmp.asm strncpy.asm strpbrk.asm strrchr.asm strspn.asm strstr.asm div.asm ldiv.asm tolower.asm toupper.asm strncasecmp.asm srand.asm rand.asm strdup.asm

set HLP_C_SRC=
set HLP_ASM_SRC=bdivs.asm bdivu.asm bldix.asm bldiy.asm bmuls.asm brems.asm bremu.asm bshl.asm bshrs.asm bshru.asm bstix.asm bstiy.asm case.asm iand.asm idivs.asm idivu.asm ildix.asm ildiy.asm imulu.asm indcall.asm ineg.asm inot.asm ior.asm irems.asm iremu.asm ishl.asm ishrs.asm ishru.asm istix.asm istiy.asm itol.asm ixor.asm ladd.asm land.asm lcmpu.asm lcmps.asm ldivs.asm ldivu.asm lldix.asm lldiy.asm lmulu.asm lmuls.asm lneg.asm lnot.asm lor.asm lrems.asm lremu.asm lshl.asm lshrs.asm lshru.asm lstix.asm lstiy.asm lsub.asm lxor.asm sand.asm sdivs.asm sdivu.asm sldix.asm sldiy.asm smulu.asm sneg.asm snot.asm sor.asm srems.asm sremu.asm sshl.asm sshrs.asm sshru.asm sstix.asm sstiy.asm stoi.asm stoiu.asm sxor.asm frbmuls.asm frbtof.asm frftob.asm frftoi.asm frftos.asm frftoub.asm frftoui.asm frftous.asm frimuls.asm frimulu.asm fritof.asm frsmuls.asm frsmulu.asm frstof.asm frubtof.asm fruitof.asm frustof.asm frameset0.asm frameset.asm setflag.asm scmpzero.asm icmpzero.asm lcmpzero.asm seqcase.asm seqcaseD.asm case24.asm case24D.asm case16.asm case16D.asm case8.asm case8D.asm

set FP_C_SRC=acos.c asin.c atan.c atan2.c exp.c floor.c fmod.c fpdata.c frexp.c ldexp.c log.c log10.c modf.c pow.c sin.c sinh.c sqrt.c tan.c tanh.c gamma.c udtoe.c
set FP_ST_C_SRC=udtof.c udtog.c
set FP_ASM_SRC=atof.asm ceil.asm cos.asm fabs.asm finite.asm fpadd.asm fpcmp.asm fpdiv.asm fpftol.asm fpltof.asm fpmul.asm fpneg.asm fppack.asm fpsub.asm fpultof.asm fpupop1.asm fpupop2.asm sqrtf.asm isnan.asm isinf.asm

set DEBUG_C_SRC=
set DEBUG_ASM_SRC=debugger.asm removeallbreakpoints.asm removeallwatchpoints.asm removebreakpoint.asm removewatchpoint.asm setbreakpoint.asm setreadwatchpoint.asm setwritewatchpoint.asm setreadwritewatchpoint.asm  setwatchpoint.asm
set TICE_C_SRC=
set TICE_ASM_SRC=tice.asm memset_fast.asm prgmcleanup.asm abort.asm os.asm

set CPU=EZ80F91
set STDINC=%INC%\lib\std
set CEINC=%CEDEV%\include\lib\ce
set ZLGINC=%SRC%\std_include
set CFLG_REL=-NOdebug -optsize -NOkeeplst -promote -quiet -fplib
set AFLG=-genobj -NOigcase -include:%STDINC% -include:%ZLGINC% -NOlist -NOlistmac -pagelen:56 -pagewidth:100 -quiet -sdiopt -warn -NOzmasm

REM ---make sure dir exists
mkdir %LIBPATH%
mkdir %LIBPATH%\std
mkdir %LIBPATH%\std\ce

REM --- CE Libraries

echo --Building CE Debugger library...
set C_SRC=%DEBUG_C_SRC%
set ASM_SRC=%DEBUG_ASM_SRC%
set C_FLG=%CFLG_DBG% -cpu:%CPU% -asmsw:"-cpu:%CPU% -include:%STDINC% -include:%ZLGINC%" -define:_%CPU%
set ASM_FLG=%AFLG% -cpu:%CPU% -debug -include:%CEINC%
call buildcelib.bat cdebug.lib

echo --Building TICE library...
set C_SRC=%TICE_C_SRC%
set ASM_SRC=%TICE_ASM_SRC%
set C_FLG=%CFLG_DBG% -cpu:%CPU% -asmsw:"-cpu:%CPU% -include:%STDINC% -include:%ZLGINC%" -define:_%CPU%
set ASM_FLG=%AFLG% -cpu:%CPU% -debug -include:%CEINC%
call buildcelib.bat ctice.lib

echo --Building RTL libraries...
set C_SRC=%RTL_C_SRC%
set ASM_SRC=%RTL_ASM_SRC%
set C_FLG=%CFLG_REL% -cpu:%CPU% -asmsw:"-cpu:%CPU% -include:%STDINC% -include:%ZLGINC%" -define:_%CPU%
set ASM_FLG=%AFLG% -cpu:%CPU% -NOdebug
call buildstdlib.bat crt.lib

set C_SRC=%RTL_ST_C_SRC%
set ASM_SRC=
set C_FLG=%CFLG_REL% -cpu:%CPU% -asmsw:"-cpu:%CPU% -include:%STDINC% -include:%ZLGINC%" -define:_%CPU%
set ASM_FLG=%AFLG% -cpu:%CPU% -NOdebug
call buildstdlib.bat crtS.lib

set C_SRC=%RTL_NOKERNEL_C_SRC%
set ASM_SRC=
set C_FLG=%CFLG_REL% -cpu:%CPU% -asmsw:"-cpu:%CPU% -include:%STDINC% -include:%ZLGINC%" -define:_%CPU%
set ASM_FLG=%AFLG% -cpu:%CPU% -NOdebug
call buildstdlib.bat nokernel.lib

echo --Building CHLP libraries...
set C_SRC=%HLP_C_SRC%
set ASM_SRC=%HLP_ASM_SRC%
set C_FLG=%CFLG_REL% -cpu:%CPU% -asmsw:"-cpu:%CPU% -include:%STDINC% -include:%ZLGINC%"
set ASM_FLG=%AFLG% -cpu:%CPU% -NOdebug
call buildstdlib.bat chelp.lib

echo --Building FPLIB libraries...
set C_SRC=%FP_C_SRC%
set ASM_SRC=%FP_ASM_SRC%
set C_FLG=%CFLG_REL% -cpu:%CPU% -asmsw:"-cpu:%CPU% -include:%STDINC% -include:%ZLGINC%"
set ASM_FLG=%AFLG% -cpu:%CPU% -NOdebug
call buildstdlib.bat fplib.lib

set C_SRC=%FP_ST_C_SRC%
set ASM_SRC=
set C_FLG=%CFLG_REL% -cpu:%CPU% -asmsw:"-cpu:%CPU% -include:%STDINC% -include:%ZLGINC%"
set ASM_FLG=%AFLG% -cpu:%CPU% -NOdebug
call buildstdlib.bat fplibS.lib

echo --Copying the libraries...
REM -- copy the libraries --
copy /Y *.lib %LIBPATH%\std
move /Y %LIBPATH%\std\ctice.lib %LIBPATH%\std\ce\ctice.lib
move /Y %LIBPATH%\std\cdebug.lib %LIBPATH%\std\ce\cdebug.lib

REM -- cleanup intermediate files --
if exist *.lib del *.lib
if exist *.obj del *.obj

pause
