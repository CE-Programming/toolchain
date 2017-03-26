#----------------------------
# Makefile
#----------------------------

# set LIB_LIB to the name of the library
LIB_LIB := cce

# common/os specific things
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
RM         = del /f 2>nul
ASM        = $(call NATIVEPATH,$(BIN)/ez80asm.exe)
LIB        = $(call NATIVEPATH,$(BIN)/ez80lib.exe)
CP         = xcopy
PREFIX    ?= C:
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath --windows $(1)))
RM         = rm --force
ASM        = $(call NATIVEPATH,wine $(BIN)/ez80asm.exe)
LIB        = $(call NATIVEPATH,wine $(BIN)/ez80lib.exe)
CP         = cp
PREFIX    ?= $(HOME)
endif

DEV        ?= $(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?= $(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(DEV))
LIB_LOC    := $(call NATIVEPATH,$(INSTALLLOC)/lib)
H_LOC      := $(call NATIVEPATH,$(INSTALLLOC)/include/ce)

LIB_H      := $(wildcard *.h)

ASMFLGS := -genobj -NOigcase -NOlist -NOlistmac -quiet -sdiopt -cpu:EZ80F91 -NOdebug
LIBFLGS := -quiet -warn

all: $(patsubst %.asm,%.obj,$(wildcard *.asm))
	$(LIB) $(LIBFLGS) $(LIB_LIB)=+$<

%.obj: %.asm
	$(ASM) $(ASMFLGS) $(call WINPATH,$<)

clean:
	$(RM) $(LIB_LIB) *.obj

install:
	$(CP) $(LIB_H) $(H_LOC)
	$(CP) $(LIB_LIB).lib $(LIB_LOC)

uninstall:
	$(RM) $(call NATIVEPATH,$(H_LOC)/$(LIB_H))
	$(RM) $(call NATIVEPATH,$(LIB_LOC)/$(LIB_LIB).lib)

.PHONY: all clean install uninstall

