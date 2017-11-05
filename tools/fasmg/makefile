#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      =cmd.exe
NATIVEPATH =$(subst /,\,$(1))
RM         =del /f 2>nul
CP         =xcopy /y
PREFIX    ?=C:
else
NATIVEPATH =$(subst \,/,$(1))
RM         =rm -f
CP         =cp
PREFIX    ?=$(HOME)
ADDEXE     =chmod +x fasmg
endif

DEV ?=$(call NATIVEPATH,$(PREFIX)/CEdev)
BIN ?=$(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC :=$(call NATIVEPATH,$(DESTDIR)$(DEV))

INCDIR :=$(call NATIVEPATH,../../src/include/)
FILES :=$(addprefix $(INCDIR),ez80.inc ld.fasmg ti84pceg.inc tiformat.inc)

all: $(FILES)
	$(ADDEXE)

$(FILES):
	$(CP) $(call NATIVEPATH,fasmg-ez80/$(@F)) $(INCDIR)$(@F)

clean:
	$(RM) $(FILES)

install:

uninstall:

.PHONY: all clean install uninstall

