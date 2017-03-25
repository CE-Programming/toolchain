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
CEDEV     ?= C:\CEdev
BIN       ?= $(CEDEV)/bin
ASM        = $(call NATIVEPATH,$(BIN)/ez80asm.exe)
LIB        = $(call NATIVEPATH,$(BIN)/ez80lib.exe)
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath --windows $(1)))
RM         = rm --force
CEDEV     ?= $(HOME)/CEdev
BIN       ?= $(CEDEV)/bin
ASM        = $(call NATIVEPATH,wine $(BIN)/ez80asm.exe)
LIB        = $(call NATIVEPATH,wine $(BIN)/ez80lib.exe)
endif

ASMFLGS := -genobj -NOigcase -NOlist -NOlistmac -quiet -sdiopt -cpu:EZ80F91 -NOdebug
LIBFLGS := -quiet -warn

all: $(patsubst %.asm,%.obj,$(wildcard *.asm))
	$(LIB) $(LIBFLGS) $(LIB_LIB)=+$<

%.obj: %.asm
	$(ASM) $(ASMFLGS) $(call WINPATH,$<)

clean:
	$(RM) $(LIB_LIB) *.obj

.PHONY: all clean

