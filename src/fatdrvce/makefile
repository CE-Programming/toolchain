#----------------------------
# Makefile
#----------------------------

# set NAME to the name of the library
NAME :=fatdrvce

# defult locations
FASMG ?=fasmg

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL       =cmd.exe
NATIVEPATH  =$(subst /,\,$(1))
RM          =del /f 2>nul
MKDIR       =mkdir
CP          =copy /y
PREFIX     ?=C:
else
NATIVEPATH  =$(subst \,/,$(1))
RM          =rm -f
MKDIR       =mkdir -p
CP          =cp
PREFIX     ?=$(HOME)
endif

SRC        +=$(NAME).asm
DEV        ?=$(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?=$(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC :=$(call NATIVEPATH,$(DESTDIR)$(DEV))
H_LOC      :=$(call NATIVEPATH,$(INSTALLLOC)/include)
I_LOC      :=$(call NATIVEPATH,$(INSTALLLOC)/lib/libload)

LIB        :=$(NAME).lib
LIB_8XV    :=$(NAME).8xv
LIB_H      :=$(NAME).h

all: $(LIB_8XV)

$(LIB_8XV): $(SRC) fat.asm
	$(FASMG) $< $@

clean:
	$(RM) $(LIB) $(LIB_8XV)

install:
	$(CP) $(LIB_H) $(H_LOC)
	$(CP) $(LIB) $(I_LOC)

.PHONY: all clean install
