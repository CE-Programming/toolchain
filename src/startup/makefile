#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      = cmd.exe
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
CP         = xcopy /y
PREFIX    ?= C:
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath --windows $(1)))
CP         = cp
PREFIX    ?= $(HOME)
endif

DEV        ?= $(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?= $(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(DEV))
OBJ_LOC    := $(call NATIVEPATH,$(INSTALLLOC)/lib/obj)

CSTARTUP_SRC  := cstartup.src
CCLEANUP_SRC  := ccleanup.src
LIBHEADER_SRC := libheader.src

all:
	
clean:
	
install:
	$(CP) $(CSTARTUP_SRC) $(LIB_LOC)
	$(CP) $(CCLEANUP_SRC) $(LIB_LOC)
	$(CP) $(LIBHEADER_SRC) $(LIB_LOC)

uninstall:
	
.PHONY: all clean install uninstall
