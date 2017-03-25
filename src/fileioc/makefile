#----------------------------
# Makefile
#----------------------------

# set NAME to the name of the library
# set SRC to the assembly source of the library
NAME := fileioc
SRC  := fileioc.asm

# defult locations
SPASM ?= spasm

# common/os specific things
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
RM         = del /f 2>nul
RMI        = del /f 2>nul $(1)
CEDEV     ?= C:\CEdev
BIN       ?= $(CEDEV)/bin
ASM        = $(call NATIVEPATH,$(BIN)/ez80asm.exe)
LIB        = $(call NATIVEPATH,$(BIN)/ez80lib.exe)
TOUCH      = copy /b $(1)+,, $(1)
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath --windows $(1)))
RM         = rm --force
RMI        = find . -maxdepth 1 -iname $(1) -exec rm {} \;
CEDEV     ?= $(HOME)/CEdev
BIN       ?= $(CEDEV)/bin
ASM        = $(call NATIVEPATH,wine $(BIN)/ez80asm.exe)
LIB        = $(call NATIVEPATH,wine $(BIN)/ez80lib.exe)
TOUCH      = touch $(1)
endif

EZOBJ = $(wildcard *.obj)
EZSRC = $(wildcard *.src)
TBL   = relocation_table

LIB_LIB := $(NAME).lib
LIB_8XV := $(NAME).8xv
LIB_ASM := $(NAME)_header.asm
LIB_JMP := $(NAME)_equates.asm

ASMFLGS := -genobj -NOigcase -NOlist -NOlistmac -quiet -sdiopt -cpu:EZ80F91 -NOdebug
LIBFLGS := -quiet -warn

all: $(LIB_8XV)
	$(RM) $(TBL)

$(LIB_8XV): $(SRC)
	$(RM) $(LIB_LIB)
	$(SPASM) -E $(SRC) $(LIB_8XV)
	$(MAKE) $(LIB_LIB)

$(LIB_LIB): $(LIB_LIB)($(EZSRC:.src=.obj))

(%.obj): %.obj
	$(LIB) $(LIBFLGS) $@=+-$%

%.obj: %.src
	$(ASM) $(ASMFLGS) $(call WINPATH,$<)
	$(RM) $<

clean:
	$(RM) $(LIB_8XV) $(LIB_LIB) $(LIB_8XV) $(LIB_JMP) $(EZOBJ) $(EZSRC) $(TBL)
	$(call RMI,$(LIB_ASM))
	$(call RMI,$(LIB_JMP))

.PHONY: all clean

