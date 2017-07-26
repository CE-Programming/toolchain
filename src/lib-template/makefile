#----------------------------
# Makefile
#----------------------------

# set NAME to the name of the library
NAME :=template

# defult locations
FASMG ?=fasmg

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL       =cmd.exe
NATIVEPATH  =$(subst /,\,$(1))
RM          =del /f 2>nul
MKDIR       =mkdir
CP          =xcopy /y
PREFIX     ?=C:
else
NATIVEPATH  =$(subst \,/,$(1))
RM          =rm -f
MKDIR       =mkdir -p
CP          =cp
PREFIX     ?=$(HOME)
endif

ASM        +=$(NAME).asm
DEV        ?=$(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?=$(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC :=$(call NATIVEPATH,$(DESTDIR)$(DEV))
H_LOC      :=$(call NATIVEPATH,$(INSTALLLOC)/include)

LIB_8XV    :=$(NAME).8xv
LIB_SRC    :=$(NAME).src
LIB_H      :=$(NAME).h

LIB_OBJ    :=$(NAME)_header.obj

all: $(LIB_8XV) $(LIB_SRC)

$(LIB_8XV): $(ASM)
	$(FASMG) $< $@

$(LIB_SRC): $(ASM)
	$(FASMG) $< $@

clean:
	$(RM) $(LIB_8XV) $(LIB_SRC)

install:
	$(CP) $(LIB_H) $(H_LOC)

uninstall:
	$(RM) $(call NATIVEPATH,$(H_LOC)/$(LIB_H))

.PHONY: all clean install uninstall
