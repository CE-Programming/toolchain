#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      = cmd.exe
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
RM         = del /f 2>nul
ASM        = $(call NATIVEPATH,$(BIN)/ez80asm.exe)
CP         = xcopy /y
PREFIX    ?= C:
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath --windows $(1)))
RM         = rm -f
ASM        = $(call NATIVEPATH,wine $(BIN)/ez80asm.exe)
CP         = cp
PREFIX    ?= $(HOME)
endif

DEV        ?= $(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?= $(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(DEV))
OBJ_LOC    := $(call NATIVEPATH,$(INSTALLLOC)/lib/obj)

ASMFLGS    := -genobj -NOigcase -NOlist -NOlistmac -quiet -sdiopt -cpu:EZ80F91 -NOdebug

CSTARTUP_ASM  := cstartup.asm
CCLEANUP_ASM  := ccleanup.asm
LIBHEADER_ASM := libheader.asm

CSTARTUP_OBJ  := cstartup.obj
CCLEANUP_OBJ  := ccleanup.obj
LIBHEADER_OBJ := libheader.obj

all: $(CSTARTUP_OBJ) $(CCLEANUP_OBJ) $(LIBHEADER_OBJ)

$(CSTARTUP_OBJ): $(CSTARTUP_ASM)
	$(ASM) $(ASMFLGS) $(call WINPATH,$<)

$(CCLEANUP_OBJ): $(CCLEANUP_ASM)
	$(ASM) $(ASMFLGS) $(call WINPATH,$<)

$(LIBHEADER_OBJ): $(LIBHEADER_ASM)
	$(ASM) $(ASMFLGS) $(call WINPATH,$<)

clean:
	$(RM) $(CSTARTUP_OBJ) $(LIBHEADER_OBJ) $(CCLEANUP_OBJ)
	
install:
	$(CP) $(CSTARTUP_OBJ) $(LIB_LOC)
	$(CP) $(CCLEANUP_OBJ) $(LIB_LOC)
	$(CP) $(LIBHEADER_OBJ) $(LIB_LOC)

uninstall:
	$(RM) $(call NATIVEPATH,$(OBJ_LOC)/$(CSTARTUP_OBJ)) $(call NATIVEPATH,$(OBJ_LOC)/$(LIBHEADER_OBJ)) $(call NATIVEPATH,$(OBJ_LOC)/$(CCLEANUP_OBJ))

.PHONY: all clean install uninstall

