#----------------------------
# Makefile
#----------------------------

RELEASE_NAME := CEdev
LIBRARIES := libload graphx fontlibc keypadc fileioc #usbdrvce fatdrvce srldrvce

# define some common makefile things
empty :=
space := $(empty) $(empty)
comma := ,
define newline

$(empty)
endef

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      = cmd.exe
NATIVEPATH = $(subst /,\,$1)
DIRNAME    = $(filter-out %:,$(patsubst %\,%,$(dir $1)))
RM         = del /f 2>nul
RMDIR      = call && (if exist $1 rmdir /s /q $1)
MKDIR      = call && (if not exist $1 mkdir $1)
PREFIX    ?= C:
INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(PREFIX))
CP         = copy /y
EXMPL_DIR  = $(call NATIVEPATH,$(INSTALLLOC)/CEdev/examples)
CPDIR      = xcopy /e /i /q /r /y /b
CP_EXMPLS  = $(call MKDIR,$(EXMPL_DIR)) && $(CPDIR) $(call NATIVEPATH,$(CURDIR)/examples) $(EXMPL_DIR)
ARCH       = $(call MKDIR,release) && cd tools\installer && ISCC.exe /DAPP_VERSION=8.4 /DDIST_PATH=$(call NATIVEPATH,$(DESTDIR)$(PREFIX)/CEdev) installer.iss && \
             cd ..\.. && move /y tools\installer\CEdev.exe release\\
QUOTE_ARG  = "$(subst ",',$1)"#'
APPEND     = @echo.$(subst ",^",$(subst \,^\,$(subst &,^&,$(subst |,^|,$(subst >,^>,$(subst <,^<,$(subst ^,^^,$1))))))) >>$@
else
NATIVEPATH = $(subst \,/,$1)
DIRNAME    = $(patsubst %/,%,$(dir $1))
RM         = rm -f
RMDIR      = rm -rf $1
MKDIR      = mkdir -p $1
PREFIX    ?= $(HOME)
INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(PREFIX))
CP         = cp
CPDIR      = cp -r
CP_EXMPLS  = $(CPDIR) $(call NATIVEPATH,$(CURDIR)/examples) $(call NATIVEPATH,$(INSTALLLOC)/CEdev)
ARCH       = cd $(INSTALLLOC) && tar -czf $(RELEASE_NAME).tar.gz $(RELEASE_NAME) ; \
             cd $(CURDIR) && $(call MKDIR,release) && mv -f $(INSTALLLOC)/$(RELEASE_NAME).tar.gz release
CHMOD      = find $(BIN) -name "*.exe" -exec chmod +x {} \;
QUOTE_ARG  = '$(subst ','\'',$1)'#'
APPEND     = @echo $(call QUOTE_ARG,$1) >>$@
endif
FASMG_FILES  = $(subst $(space),$(comma) ,$(patsubst %,"%",$(subst ",\",$(subst \,\\,$(call NATIVEPATH,$1)))))#"
APPEND_FILES = $(foreach file,$(addprefix ../../lib/$2/,$(notdir $3)),$(call APPEND,$1$(call FASMG_FILES,$(file)))$(newline))

TOOLSDIR   := $(call NATIVEPATH,$(CURDIR)/tools)
SRCDIR     := $(call NATIVEPATH,$(CURDIR)/src)
FASMGDIR   := $(call NATIVEPATH,$(TOOLSDIR)/fasmg)
CONVBINDIR := $(call NATIVEPATH,$(TOOLSDIR)/convbin)
CONVPNGDIR := $(call NATIVEPATH,$(TOOLSDIR)/convpng)
CONVFNTDIR := $(call NATIVEPATH,$(TOOLSDIR)/convfont)
CEDIR      := $(call NATIVEPATH,$(SRCDIR)/ce)
STDDIR     := $(call NATIVEPATH,$(SRCDIR)/std)
STARTDIR   := $(call NATIVEPATH,$(SRCDIR)/startup)
DEVLIBDIR  := $(call NATIVEPATH,$(SRCDIR)/devlib)

FASMG      := $(call NATIVEPATH,$(FASMGDIR)/fasmg)
CONVPNG    := $(call NATIVEPATH,$(CONVPNGDIR)/convpng)
CONVFONT   := $(call NATIVEPATH,$(CONVFNTDIR)/convfont)
FASMG_EZ80 := $(call NATIVEPATH,$(SRCDIR)/include/ez80.inc)

BIN        := $(call NATIVEPATH,$(TOOLSDIR)/zds)

LIBRARYDIR  = $(call NATIVEPATH,$(SRCDIR)/$1)

CEDEVDIR   := $(call NATIVEPATH,$(INSTALLLOC)/$(RELEASE_NAME))
INSTALLBIN := $(call NATIVEPATH,$(CEDEVDIR)/bin)
INSTALLBF  := $(call NATIVEPATH,$(CEDEVDIR)/include/fasmg-ez80)
INSTALLINC := $(call NATIVEPATH,$(CEDEVDIR)/include)
INSTALLLIB := $(call NATIVEPATH,$(CEDEVDIR)/lib)
INSTALLLL  := $(call NATIVEPATH,$(CEDEVDIR)/lib/libload)
INSTALLIO  := $(call NATIVEPATH,$(CEDEVDIR)/lib/fileio)
INSTALLSH  := $(call NATIVEPATH,$(CEDEVDIR)/lib/shared)
INSTALLST  := $(call NATIVEPATH,$(CEDEVDIR)/lib/static)
INSTALLLI  := $(call NATIVEPATH,$(CEDEVDIR)/lib/linked)
DIRS       := $(CEDEVDIR) $(INSTALLBIN) $(INSTALLLIB) $(INSTALLINC) $(INSTALLBF) $(INSTALLLL) $(INSTALLIO) $(INSTALLSH) $(INSTALLST) $(INSTALLLI)

ifeq ($(OS),Windows_NT)
FASMG      := $(call NATIVEPATH,$(FASMGDIR)/fasmg.exe)
CONVBIN    := $(call NATIVEPATH,$(CONVBINDIR)/bin/convbin.exe)
CONVPNG    := $(call NATIVEPATH,$(CONVPNGDIR)/convpng.exe)
CONVFONT   := $(call NATIVEPATH,$(CONVFNTDIR)/convfont.exe)
MAKEBIN    := $(call NATIVEPATH,$(TOOLSDIR)/make/make.exe)
CPMAKE     := $(CP) $(MAKEBIN) $(INSTALLBIN)
else
FASMG      := $(call NATIVEPATH,$(FASMGDIR)/fasmg)
CONVBIN    := $(call NATIVEPATH,$(CONVBINDIR)/bin/convbin)
CONVPNG    := $(call NATIVEPATH,$(CONVPNGDIR)/convpng)
CONVFONT   := $(call NATIVEPATH,$(CONVFNTDIR)/convfont)
MAKEBIN    :=
CPMAKE     :=
endif

STATIC_FILES := $(wildcard src/std/static/*.src) $(patsubst src/std/static/%.c,src/std/static/build/%.src,$(wildcard src/std/static/*.c))
LINKED_FILES := $(wildcard src/std/linked/*.src) $(patsubst src/std/linked/%.c,src/std/linked/build/%.src,$(wildcard src/std/linked/*.c))
SHARED_FILES := $(wildcard src/ce/*.src src/std/shared/*.src) $(patsubst src/std/shared/%.c,src/std/shared/build/%.src,$(wildcard src/std/shared/*.c))
FILEIO_FILES := $(wildcard src/std/fileio/*.src) $(patsubst src/std/fileio/%.c,src/std/fileio/build/%.src,$(wildcard src/std/fileio/*.c))

all: $(CONVBIN) $(CONVPNG) $(CONVFONT) $(LIBRARIES) ce std startup
	@echo Toolchain built.

clean: $(addprefix clean-,$(LIBRARIES)) clean-devlib clean-ce clean-std clean-startup
	$(MAKE) -C $(FASMGDIR) clean
	$(MAKE) -C $(CONVBINDIR) clean
	$(MAKE) -C $(CONVPNGDIR) clean
	$(MAKE) -C $(CONVFNTDIR) clean
	$(RM) linker_script
	$(call RMDIR,release)
	$(call RMDIR,clibraries)
	$(call RMDIR,doxygen)

#----------------------------
# tool rules
#----------------------------
$(FASMG_EZ80): $(FASMG)
$(FASMG):
	$(MAKE) -C $(FASMGDIR)
$(CONVBIN):
	$(MAKE) -C $(CONVBINDIR) release
$(CONVPNG):
	$(MAKE) -C $(CONVPNGDIR)
$(CONVFONT):
	$(MAKE) -C $(CONVFNTDIR)
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
# template rules
#----------------------------
template: $(FASMG)
	$(MAKE) -C $(TEMPLATEDIR) FASMG=$(FASMG) BIN=$(BIN)
clean-template:
	$(MAKE) -C $(TEMPLATEDIR) clean
#----------------------------


#----------------------------
# library rules
#----------------------------
$(LIBRARIES): $(FASMG)
	$(MAKE) -C $(call LIBRARYDIR,$@) FASMG=$(call QUOTE_ARG,$(FASMG)) BIN=$(call QUOTE_ARG,$(BIN))

$(addprefix clean-,$(LIBRARIES)):
	$(MAKE) -C $(call LIBRARYDIR,$(patsubst clean-%,%,$@)) clean

#----------------------------
# development library rules
#----------------------------
devlib: $(LIBRARIES)
	$(MAKE) -C $(DEVLIBDIR) all

clean-devlib:
	$(MAKE) -C $(DEVLIBDIR) clean

#----------------------------
# startup rules
#----------------------------
startup:
	$(MAKE) -C $(STARTDIR) BIN=$(BIN)
clean-startup:
	$(MAKE) -C $(STARTDIR) clean
#----------------------------

#----------------------------
# uninstall rule
#----------------------------
uninstall:
	$(call RMDIR,$(CEDEVDIR))
#----------------------------

#----------------------------
# install rule
#----------------------------
install: $(DIRS) chmod all linker_script
	$(CP_EXMPLS)
	$(CP) $(call NATIVEPATH,$(SRCDIR)/startup/*.src) $(call NATIVEPATH,$(INSTALLLIB))
	$(CP) $(call NATIVEPATH,$(SRCDIR)/makefile.mk) $(call NATIVEPATH,$(INSTALLINC)/.makefile)
	$(CP) $(call NATIVEPATH,linker_script) $(call NATIVEPATH,$(INSTALLINC)/.linker_script)
	$(CP) $(FASMG) $(INSTALLBIN)
	$(CP) $(CONVBIN) $(INSTALLBIN)
	$(CP) $(CONVPNG) $(INSTALLBIN)
	$(CP) $(CONVFONT) $(INSTALLBIN)
	$(CP) $(call NATIVEPATH,$(BIN)/*) $(INSTALLBIN)
	$(MAKE) -C $(FASMGDIR) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)
	$(foreach library,$(LIBRARIES),$(MAKE) -C $(call LIBRARYDIR,$(library)) install PREFIX=$(call QUOTE_ARG,$(PREFIX)) DESTDIR=$(call QUOTE_ARG,$(DESTDIR))$(newline))
	$(MAKE) -C $(CEDIR) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)
	$(MAKE) -C $(STDDIR) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)
	$(CPDIR) $(call NATIVEPATH,$(SRCDIR)/compatibility/*) $(call NATIVEPATH,$(INSTALLINC))

chmod:
	$(CHMOD)
#----------------------------

#----------------------------
# release rule
#----------------------------
dist release: install
	$(ARCH)
#----------------------------

#----------------------------
# libraries release rules
#----------------------------
dist-libs release-libs: clibraries $(CONVBIN) $(LIBRARIES)
	$(foreach library,$(LIBRARIES),$(CP) $(call NATIVEPATH,$(call LIBRARYDIR,$(library))/$(library).8xv) $(call NATIVEPATH,clibraries/$(library).8xv)$(newline))
	$(CONVBIN) --oformat 8xg-auto-extract $(foreach library,$(LIBRARIES),$(addprefix --input ,$(call LIBRARYDIR,$(library))/$(library).8xv)) --output $(call NATIVEPATH,clibraries/clibs.8xg)
clibraries:
	$(call MKDIR,clibraries)

#----------------------------

#----------------------------
# doxygen rule
#----------------------------
doxygen:
	cd $(call NATIVEPATH,tools/doxygen) && doxygen config
#----------------------------

#----------------------------
# linker script rule
#----------------------------
linker_script: std
	$(RM) $(call QUOTE_ARG,$@)
	@echo Generating linker script...
	$(call APPEND,symbol __low_bss = bss.base)
	$(call APPEND,symbol __len_bss = bss.length)
	$(call APPEND,symbol __heaptop = bss.high)
	$(call APPEND,symbol __heapbot = bss.top)
	$(call APPEND,order $(subst $(space),$(comma) ,header icon launcher libs startup cleanup exit code data strsect text))
	$(call APPEND,if STATIC)
	$(call APPEND_FILES,	srcs ,static,$(STATIC_FILES))
	$(call APPEND,else)
	$(call APPEND_FILES,	srcs ,linked,$(LINKED_FILES))
	$(call APPEND,end if)
	$(call APPEND_FILES,srcs ,shared,$(SHARED_FILES))
	$(call APPEND_FILES,srcs ,fileio,$(FILEIO_FILES))

#----------------------------
# makefile help rule
#----------------------------
help:
	@echo Available targets:
	@echo all
	@echo ce
	@echo asm
	@echo std
	@echo fasmg
	$(foreach library,$(LIBRARIES),@echo $(library)$(newline))
	@echo clean
	@echo clean-ce
	@echo clean-asm
	@echo clean-std
	$(foreach library,$(LIBRARIES),@echo clean-$(library)$(newline))
	@echo doxygen
	@echo install
	@echo uninstall
	@echo release
	@echo release-libs
	@echo help

.PHONY: release-libs clibraries doxygen chmod all clean $(LIBRARIES) $(addprefix clean-,$(LIBRARIES)) install uninstall help release

.SECONDEXPANSION:
$(DIRS): $$(call DIRNAME,$$@)
	$(call MKDIR,$@)
