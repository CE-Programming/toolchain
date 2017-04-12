#----------------------------
# Makefile
#----------------------------

# set NAME to the name of the library
NAME := cce

# common/os specific things
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
RM         = del /f 2>nul
ASM        = $(call NATIVEPATH,$(BIN)/ez80asm.exe)
LIB        = $(call NATIVEPATH,$(BIN)/ez80lib.exe)
CP         = xcopy /y
PREFIX    ?= C:
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath --windows $(1)))
RM         = rm -f
ASM        = $(call NATIVEPATH,wine $(BIN)/ez80asm.exe)
LIB        = $(call NATIVEPATH,wine $(BIN)/ez80lib.exe)
CP         = cp
PREFIX    ?= $(HOME)
endif

DEV        ?= $(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?= $(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(DEV))
LIB_LOC    := $(call NATIVEPATH,$(INSTALLLOC)/lib)
LOC_H      := $(call NATIVEPATH,$(INSTALLLOC)/include/ce)

ASMFLGS    := -genobj -NOigcase -NOlist -NOlistmac -quiet -sdiopt -cpu:EZ80F91 -NOdebug
LIBFLGS    := -quiet -warn
LIB_H      := $(wildcard *.h)

LIB_LIB    := $(NAME).lib
EZC         = $(wildcard *.c)
EZSRC       = $(wildcard *.src)
EZOBJ       = $(wildcard *.obj)

ifeq ($(OS),Windows_NT)
COPY_HEADERS = (robocopy . $(LOC_H) $(LIB_H) /njh /njs /ndl /nc /ns) ^& exit 0
else
COPY_HEADERS = $(CP) $(LIB_H) $(LOC_H)
endif

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
	$(RM) $(LIB_LIB) $(EZOBJ)

$(LIB_LIB)():
	
install:
	$(COPY_HEADERS)
	$(CP) $(LIB_LIB) $(LIB_LOC)

uninstall:
	$(RM) $(call NATIVEPATH,$(LOC_H)/*.h)
	$(RM) $(call NATIVEPATH,$(LIB_LOC)/$(LIB_LIB))

.PHONY: all clean clean_lib install uninstall $(LIB_LIB)()

