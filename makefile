#----------------------------
# Makefile
#----------------------------

RELEASE_NAME := CEdev

# common/os specific things
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
WINCHKDIR  = if exist $(1)
RM         = del /f 2>nul
RMDIR      = rmdir /s /q
MKDIR      = mkdir
PREFIX    ?= C:
INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(PREFIX))
CP         = copy /y
SPASMFLG   = NO_APPSIGN=1 MINGW_COMPILE=YES
EXMPL_DIR  = $(call NATIVEPATH,$(INSTALLLOC)/CEdev/examples)
CP_EXMPLS  = (if not exist "$(EXMPL_DIR)" mkdir $(EXMPL_DIR)) && xcopy /y /s /e $(call NATIVEPATH,$(CURDIR)/examples) $(EXMPL_DIR)
ARCH       = makensis.exe /DDIST_PATH=$(call NATIVEPATH,$(DESTDIR)$(PREFIX)/CEdev) $(call NATIVEPATH,$(CURDIR)\installer\installer.nsi) && \
             (if not exist "release" mkdir "release") && move /y installer\CEdev.exe release\\
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(shell winepath --windows $(1))
RM         = rm -f
MKDIR      = mkdir -p
RMDIR      = rm -rf
PREFIX    ?= $(HOME)
INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(PREFIX))
SPASMFLG   = NO_APPSIGN=1
CP         = cp
CP_EXMPLS  = cp -r $(call NATIVEPATH,$(CURDIR)/examples) $(call NATIVEPATH,$(INSTALLLOC)/CEdev)
ARCH       = cd $(INSTALLLOC) ; tar -czf $(RELEASE_NAME).tar.gz $(RELEASE_NAME) ; \
             cd $(CURDIR) ; mkdir -p release ; mv -f $(INSTALLLOC)/$(RELEASE_NAME).tar.gz release
chain     := ;
endif

TOOLSDIR   := $(call NATIVEPATH,$(CURDIR)/tools)
SRCDIR     := $(call NATIVEPATH,$(CURDIR)/src)
SPASMDIR   := $(call NATIVEPATH,$(TOOLSDIR)/spasm-ng)
CONVHEXDIR := $(call NATIVEPATH,$(TOOLSDIR)/convhex)
CONVPNGDIR := $(call NATIVEPATH,$(TOOLSDIR)/convpng)

CEDIR      := $(call NATIVEPATH,$(SRCDIR)/ce)
STDDIR     := $(call NATIVEPATH,$(SRCDIR)/std)

SPASM      := $(call NATIVEPATH,$(SPASMDIR)/spasm)
CONVHEX    := $(call NATIVEPATH,$(CONVHEXDIR)/convhex)
CONVPNG    := $(call NATIVEPATH,$(CONVPNGDIR)/convpng)


ifeq ($(OS),Windows_NT)
SPASM      := $(call NATIVEPATH,$(SPASMDIR)/spasm.exe)
CONVHEX    := $(call NATIVEPATH,$(CONVHEXDIR)/convhex.exe)
CONVPNG    := $(call NATIVEPATH,$(CONVPNGDIR)/convpng.exe)
endif

BIN        := $(call NATIVEPATH,$(TOOLSDIR)/zds)

GRAPHXDIR  := $(call NATIVEPATH,$(SRCDIR)/graphx)
KEYPADCDIR := $(call NATIVEPATH,$(SRCDIR)/keypadc)
FILEIOCDIR := $(call NATIVEPATH,$(SRCDIR)/fileioc)

CEDEVDIR   := $(call NATIVEPATH,$(INSTALLLOC)/$(RELEASE_NAME))
INSTALLBIN := $(call NATIVEPATH,$(INSTALLLOC)/$(RELEASE_NAME)/bin)
INSTALLINC := $(call NATIVEPATH,$(INSTALLLOC)/$(RELEASE_NAME)/include)
INSTALLLIB := $(call NATIVEPATH,$(INSTALLLOC)/$(RELEASE_NAME)/lib)
DIRS       := $(INSTALLINC) $(INSTALLINC)/ce $(INSTALLINC)/ce/libs $(INSTALLINC)/std $(INSTALLBIN) $(INSTALLLIB)
DIRS       := $(call NATIVEPATH,$(DIRS))

all: $(SPASM) $(CONVHEX) $(CONVPNG) graphx fileioc keypadc ce std

#----------------------------
# tool rules
#----------------------------
$(SPASM) $(CONVHEX) $(CONVPNG):
	$(MAKE) -C $(SPASMDIR) $(SPASMFLG)
	$(MAKE) -C $(CONVHEXDIR)
	$(MAKE) -C $(CONVPNGDIR)

clean: clean-graphx clean-fileioc clean-keypadc clean-ce clean-std
	$(MAKE) -C $(SPASMDIR) clean
	$(MAKE) -C $(CONVHEXDIR) clean
	$(MAKE) -C $(CONVPNGDIR) clean
	$(WINCHKDIR) $(RMDIR) release
#----------------------------

#----------------------------
# ce rules
#----------------------------
ce:
	$(MAKE) -C $(CEDIR) BIN=$(BIN)

clean-ce:
	$(MAKE) -C $(CEDIR) clean
#----------------------------

#----------------------------
# std rules
#----------------------------
std:
	$(MAKE) -C $(STDDIR) BIN=$(BIN)
clean-std:
	$(MAKE) -C $(STDDIR) clean
#----------------------------

#----------------------------
# graphx rules
#----------------------------
graphx: $(SPASM)
	$(MAKE) -C $(GRAPHXDIR) SPASM=$(SPASM) BIN=$(BIN)
clean-graphx:
	$(MAKE) -C $(GRAPHXDIR) clean
#----------------------------

#----------------------------
# fileioc rules
#----------------------------
fileioc: $(SPASM)
	$(MAKE) -C $(FILEIOCDIR) SPASM=$(SPASM) BIN=$(BIN)
clean-fileioc:
	$(MAKE) -C $(FILEIOCDIR) clean
#----------------------------

#----------------------------
# keypadc rules
#----------------------------
keypadc: $(SPASM)
	$(MAKE) -C $(KEYPADCDIR) SPASM=$(SPASM) BIN=$(BIN)
clean-keypadc:
	$(MAKE) -C $(KEYPADCDIR) clean
#----------------------------

uninstall:
	$(WINCHKDIR) $(RMDIR) $(call NATIVEPATH,$(INSTALLLOC)/CEdev)

install: $(DIRS)
	$(CP_EXMPLS)
	$(CP) $(call NATIVEPATH,$(SRCDIR)/asm/*) $(call NATIVEPATH,$(INSTALLLIB)/asm)
	$(CP) $(call NATIVEPATH,$(SRCDIR)/example_makefile) $(call NATIVEPATH,$(INSTALLINC)/.makefile)
	$(CP) $(SPASM) $(INSTALLBIN)
	$(CP) $(CONVHEX) $(INSTALLBIN)
	$(CP) $(CONVPNG) $(INSTALLBIN)
	$(CP) $(call NATIVEPATH,$(BIN)/*) $(INSTALLBIN)
	$(MAKE) -C $(GRAPHXDIR) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)
	$(MAKE) -C $(KEYPADCDIR) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)
	$(MAKE) -C $(FILEIOCDIR) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)
	$(MAKE) -C $(CEDIR) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)
	$(MAKE) -C $(STDDIR) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)

$(DIRS):
	$(MKDIR) $(INSTALLBIN)
	$(MKDIR) $(INSTALLLIB)
	$(MKDIR) $(INSTALLINC)
	$(MKDIR) $(call NATIVEPATH,$(INSTALLLIB)/asm)
	$(MKDIR) $(call NATIVEPATH,$(INSTALLINC)/ce)
	$(MKDIR) $(call NATIVEPATH,$(INSTALLINC)/std)

dist: install
	$(ARCH)

help:
	@echo Available targets:
	@echo all
	@echo ce
	@echo std
	@echo graphx
	@echo fileioc
	@echo keypadc
	@echo clean
	@echo clean-ce
	@echo clean-std
	@echo clean-graphx
	@echo clean-fileioc
	@echo clean-keypadc
	@echo install
	@echo uninstall
	@echo dist
	@echo help

.PHONY: all clean graphx clean-graphx fileioc clean-fileioc keypadc clean-keypadc install uninstall help dist

