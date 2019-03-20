#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      =cmd.exe
NATIVEPATH =$(subst /,\,$(1))
CP         =copy /y
PREFIX    ?=C:
else
NATIVEPATH =$(subst \,/,$(1))
CP         =cp
PREFIX    ?=$(HOME)
endif

DEV        ?=$(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?=$(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC :=$(call NATIVEPATH,$(DESTDIR)$(DEV))
I_LOC      :=$(call NATIVEPATH,$(INSTALLLOC)/lib)

CSTARTUP_SRC  :=cstartup.src
CCLEANUP_SRC  :=ccleanup.src
LIBHEADER_SRC :=libheader.src

all:

clean:

install:
	$(CP) $(CSTARTUP_SRC) $(I_LOC)
	$(CP) $(CCLEANUP_SRC) $(I_LOC)
	$(CP) $(LIBHEADER_SRC) $(I_LOC)

.PHONY: all clean install uninstall
