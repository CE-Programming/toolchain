#----------------------------
# Makefile
#----------------------------

# set NAME to the name of the library
NAME := cshared

# common/os specific things
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
RM         = del /f 2>nul
CEDEV     ?= C:\CEdev
BIN       ?= $(CEDEV)/bin
ASM        = $(call NATIVEPATH,$(BIN)/ez80asm.exe)
LIB        = $(call NATIVEPATH,$(BIN)/ez80lib.exe)
CC         = $(call NATIVEPATH,$(BIN)/ez80cc.exe)
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath --windows $(1)))
RM         = rm --force
CEDEV     ?= $(HOME)/CEdev
BIN       ?= $(CEDEV)/bin
ASM        = $(call NATIVEPATH,wine $(BIN)/ez80asm.exe)
LIB        = $(call NATIVEPATH,wine $(BIN)/ez80lib.exe)
CC         = $(call NATIVEPATH,wine $(BIN)/ez80cc.exe)
endif

ASMFLGS   := -genobj -NOigcase -NOlist -NOlistmac -quiet -sdiopt -cpu:EZ80F91 -NOdebug -include:..
CCFLGS    := -NOdebug -NOkeeplst -promote -quiet -fplib -optsize -cpu:EZ80F91 -stdinc:.. -define:_EZ80F91 -asmsw:"$(ASMFLGS)"
LIBFLGS   := -quiet -warn
LIB_LIB   := $(NAME).lib

EZC        = $(wildcard *.c)
EZSRC      = $(wildcard *.src)

all: clean_lib $(LIB_LIB)

$(LIB_LIB): $(LIB_LIB)($(EZSRC:.src=.obj)) $(LIB_LIB)($(EZC:.c=.obj))

.PRECIOUS: %.obj
(%.obj): %.obj
	$(LIB) $(LIBFLGS) $@=+$%

%.obj: %.c
	$(CC) $(CCFLGS) $(call WINPATH,$<)

%.obj: %.src
	$(ASM) $(ASMFLGS) $(call WINPATH,$<)

clean_lib:
	$(RM) $(LIB_LIB)

clean:
	$(RM) $(LIB_LIB) *.obj

$(LIB_LIB)():
	
.PHONY: all clean clean_lib $(LIB_LIB)()

