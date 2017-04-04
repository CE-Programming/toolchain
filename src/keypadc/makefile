#----------------------------
# Makefile
#----------------------------

# set NAME to the name of the library
# set SRC to the assembly source of the library
NAME := keypadc
SRC  := keypadc.asm

# defult locations
SPASM ?= spasm

# common/os specific things
ifeq ($(OS),Windows_NT)
NATIVEPATH  = $(subst /,\,$(1))
WINPATH     = $(NATIVEPATH)
RM          = del /f 2>nul
MKDIR       = mkdir
ASM         = $(call NATIVEPATH,$(BIN)/ez80asm.exe)
LIB         = $(call NATIVEPATH,$(BIN)/ez80lib.exe)
TOUCH       = copy /y /b $(1)+,, $(1)
CP          = xcopy /y
PREFIX     ?= C:
else
NATIVEPATH  = $(subst \,/,$(1))
WINPATH     = $(subst \,\\,$(shell winepath --windows $(1)))
RM          = rm -f
MKDIR       = mkdir -p
ASM         = $(call NATIVEPATH,wine $(BIN)/ez80asm.exe)
LIB         = $(call NATIVEPATH,wine $(BIN)/ez80lib.exe)
TOUCH       = touch $(1)
CP          = cp
PREFIX     ?= $(HOME)
endif

DEV        ?= $(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?= $(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(DEV))
LIB_LOC    := $(call NATIVEPATH,$(INSTALLLOC)/lib)
LIBH_LOC   := $(call NATIVEPATH,$(INSTALLLOC)/lib/asm)
H_LOC      := $(call NATIVEPATH,$(INSTALLLOC)/include/ce/libs)

EZOBJ       = $(wildcard *.obj)
EZSRC       = $(wildcard *.src)
TBL         = relocation_table

LIB_LIB    := $(NAME).lib
LIB_8XV    := $(NAME).8xv
LIB_ASM    := $(NAME)_header.asm
LIB_JMP    := $(NAME)_equates.asm
LIB_H      := $(NAME).h

ASMFLGS    := -genobj -NOigcase -NOlist -NOlistmac -quiet -sdiopt -cpu:EZ80F91 -NOdebug
LIBFLGS    := -quiet -warn

all: $(LIB_8XV)

$(LIB_8XV): $(SRC)
	$(RM) $(LIB_LIB)
	$(SPASM) -E $(SRC) $(LIB_8XV)
	$(MAKE) $(LIB_LIB)

$(LIB_LIB): $(LIB_LIB)($(EZSRC:.src=.obj))

(%.obj): %.obj
	$(LIB) $(LIBFLGS) $@=+$%

%.obj: %.src
	$(ASM) $(ASMFLGS) $(call WINPATH,$<)
	$(RM) $<

clean:
	$(RM) $(LIB_8XV) $(LIB_LIB) $(LIB_8XV) $(LIB_ASM) $(LIB_JMP) $(EZOBJ) $(EZSRC) $(TBL)

install:
	$(CP) $(LIB_H) $(H_LOC)
	$(CP) $(LIB_LIB) $(LIB_LOC)
	$(CP) $(LIB_ASM) $(LIBH_LOC)

uninstall:
	$(RM) $(call NATIVEPATH,$(H_LOC)/$(LIB_H))
	$(RM) $(call NATIVEPATH,$(LIB_LOC)/$(LIB_LIB))

.PHONY: all clean install uninstall

