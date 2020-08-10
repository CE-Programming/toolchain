#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      =cmd.exe
NATIVEPATH =$(subst /,\,$(1))
RM         =( del /f /q $1 2>nul || call )
CP         =echo f|xcopy /y
PREFIX    ?=C:
NAME       =fasmg.exe
FASMGP     =windows\$(NAME)
else
NAME       =fasmg
ifeq ($(shell uname -s),Darwin)
FASMGP     =macos/$(NAME)
else
FASMGP     =linux/$(NAME)
endif
NATIVEPATH =$(subst \,/,$(1))
RM         =rm -f $1
CP         =cp
PREFIX    ?=$(HOME)
# This little hack causes the Win32 executable to be copied instead, supporting WSL
ifneq ($(shell uname -r | grep Microsoft),)
FASMGP     =windows\$(NAME).exe
ADDEXE     =&& mv $(NAME).exe $(NAME)
else
ADDEXE     =&& chmod +x $(NAME)
endif
endif

DEV ?=$(call NATIVEPATH,$(PREFIX)/CEdev)
BIN ?=$(call NATIVEPATH,$(DEV)/bin)
INC ?=$(call NATIVEPATH,$(DEV)/include/fasmg-ez80/)

INSTALLLOC :=$(call NATIVEPATH,$(DESTDIR)$(DEV))

INCDIR     :=$(call NATIVEPATH,../../src/include/)
INCLUDES   :=commands.alm ez80.alm ez80.inc ld.alm ti84pceg.inc tiformat.inc
FILES      :=$(addprefix $(INCDIR),$(INCLUDES))
INCFILES   :=$(addprefix $(INC),$(INCLUDES))

all: $(FILES)
	$(CP) $(call NATIVEPATH,$(FASMGP)) . $(ADDEXE)

$(FILES):
	$(CP) $(call NATIVEPATH,fasmg-ez80/$(@F)) $(INCDIR)$(@F)

clean:
	$(call RM,$(FILES) $(NAME))

install: $(INCFILES)
	$(CP) $(NAME) $(BIN)

$(INCFILES):
	$(CP) $(call NATIVEPATH,fasmg-ez80/$(@F)) $(INC)$(@F)

uninstall:

.PHONY: all clean install uninstall $(FILES)
