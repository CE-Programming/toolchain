# Copyright (C) 2015-2021
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#----------------------------
MAKEFLAGS += -rR
#----------------------------
NAME ?= DEMO
ICON ?=
DESCRIPTION ?=
COMPRESSED ?= NO
ARCHIVED ?= NO
BSSHEAP_LOW ?= D052C6
BSSHEAP_HIGH ?= D13FD8
STACK_HIGH ?= D1A87E
INIT_LOC ?= D1A87F
OUTPUT_MAP ?= YES
CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz
SRCDIR ?= src
OBJDIR ?= obj
BINDIR ?= bin
GFXDIR ?= src/gfx
CPP_EXTENSION = cpp
C_EXTENSION = c
CUSTOM_FILE_FILE ?= stdio_file.h
DEPS ?=
#----------------------------
HAS_UPPERCASE_NAME ?= YES
HAS_FLASH_FUNCTIONS ?= YES
HAS_PRINTF ?= YES
HAS_CUSTOM_FILE ?= NO
#----------------------------
CEDEV_TOOLCHAIN ?= $(shell cedev-config --prefix)
#----------------------------

# define some common makefile things
empty :=
space := $(empty) $(empty)
comma := ,

# configure defaults
DEBUGMODE := NDEBUG
CCDEBUG := -g0
LDDEBUG := 0
LDSTATIC := 0

# verbosity
V ?= 0
ifeq ($(V),0)
Q = @
else
Q =
endif

BIN ?= $(CEDEV_TOOLCHAIN)/bin
# get the os specific items
ifeq ($(OS),Windows_NT)
SHELL = cmd.exe
NATIVEPATH = $(subst /,\,$1)
FASMGLD = $(call NATIVEPATH,$(BIN)/fasmg.exe)
CONVBIN = $(call NATIVEPATH,$(BIN)/convbin.exe)
CONVIMG = $(call NATIVEPATH,$(BIN)/convimg.exe)
CC = $(call NATIVEPATH,$(BIN)/ez80-clang.exe)
RM = ( del /q /f $1 2>nul || call )
RMDIR = ( rmdir /s /q $1 2>nul || call )
NATIVEMKDR = ( mkdir $1 2>nul || call )
QUOTE_ARG = "$(subst ",',$1)"#'
else
NATIVEPATH = $(subst \,/,$1)
FASMGLD = $(call NATIVEPATH,$(BIN)/fasmg)
CONVBIN = $(call NATIVEPATH,$(BIN)/convbin)
CONVIMG = $(call NATIVEPATH,$(BIN)/convimg)
CC = $(call NATIVEPATH,$(BIN)/ez80-clang)
RM = rm -f $1
RMDIR = rm -rf $1
NATIVEMKDR = mkdir -p $1
QUOTE_ARG = '$(subst ','\'',$1)'#'
endif

MKDIR = $(call NATIVEMKDR,$(call QUOTE_ARG,$(call NATIVEPATH,$1)))
UPDIR_ADD = $(subst ../,_../,$(subst \,/,$1))
UPDIR_RM = $(subst _../,../,$(subst \,/,$1))

FASMG_FILES = $(subst $(space),$(comma) ,$(patsubst %,"%",$(subst ",\",$(subst \,\\,$(call NATIVEPATH,$1)))))#"
LINKER_SCRIPT ?= $(CEDEV_TOOLCHAIN)/meta/linker_script

# ensure native paths
SRCDIR := $(call NATIVEPATH,$(SRCDIR))
OBJDIR := $(call NATIVEPATH,$(OBJDIR))
BINDIR := $(call NATIVEPATH,$(BINDIR))
GFXDIR := $(call NATIVEPATH,$(GFXDIR))

# generate default names
TARGETBIN ?= $(NAME).bin
TARGETMAP ?= $(NAME).map
TARGET8XP ?= $(NAME).8xp
ICONIMG := $(wildcard $(call NATIVEPATH,$(ICON)))

# startup routines
LDCRT0 ?= $(call NATIVEPATH,$(CEDEV_TOOLCHAIN)/lib/shared/crt0.src)

# source: http://blog.jgc.org/2011/07/gnu-make-recursive-wildcard-function.html
rwildcard = $(strip $(foreach d,$(wildcard $1/*),$(call rwildcard,$d,$2) $(filter $(subst %%,%,%$(subst *,%,$2)),$d)))

# find source files
CSOURCES ?= $(sort $(call rwildcard,$(SRCDIR),*.$(C_EXTENSION)) $(EXTRA_CSOURCES))
CPPSOURCES ?= $(sort $(call rwildcard,$(SRCDIR),*.$(CPP_EXTENSION)) $(EXTRA_CPPSOURCES))
USERHEADERS ?= $(sort $(call rwildcard,$(SRCDIR),*.h *.hpp) $(EXTRA_USERHEADERS))
ASMSOURCES ?= $(sort $(call rwildcard,$(SRCDIR),*.asm) $(EXTRA_ASMSOURCES))

# create links for later
LINK_CSOURCES ?= $(call UPDIR_ADD,$(CSOURCES:%.$(C_EXTENSION)=$(OBJDIR)/%.$(C_EXTENSION).src))
LINK_CPPSOURCES ?= $(call UPDIR_ADD,$(CPPSOURCES:%.$(CPP_EXTENSION)=$(OBJDIR)/%.$(CPP_EXTENSION).src))
LINK_ASMSOURCES ?= $(call UPDIR_ADD,$(ASMSOURCES))

# files created to be used for linking
LDFILES ?= $(LDCRT0) $(LINK_CSOURCES) $(LINK_CPPSOURCES) $(LINK_ASMSOURCES)
LDLIBS ?= $(wildcard $(CEDEV_TOOLCHAIN)/lib/libload/*.lib)

# check if there is an icon present that to convert
ifneq ($(ICONIMG),)
ICONSRC ?= $(call NATIVEPATH,$(OBJDIR)/icon.src)
ifneq ($(DESCRIPTION),)
ICON_CONV ?= $(CONVIMG) --icon $(call QUOTE_ARG,$(ICONIMG)) --icon-output $(call QUOTE_ARG,$(ICONSRC)) --icon-format asm --icon-description $(DESCRIPTION)
else
ICON_CONV ?= $(CONVIMG) --icon $(call QUOTE_ARG,$(ICONIMG)) --icon-output $(call QUOTE_ARG,$(ICONSRC)) --icon-format asm
endif
LDICON ?= $(call FASMG_FILES,$(ICONSRC))$(comma)$(space)
else
ifneq ($(DESCRIPTION),)
ICONSRC ?= $(call NATIVEPATH,$(OBJDIR)/icon.src)
ICON_CONV ?= $(CONVIMG) --icon-output $(call QUOTE_ARG,$(ICONSRC)) --icon-format asm --icon-description $(DESCRIPTION)
LDICON ?= $(call FASMG_FILES,$(ICONSRC))$(comma)$(space)
endif
endif

# check if gfx directory exists
ifneq ($(wildcard $(GFXDIR)/.),)
GFXCMD ?= cd $(GFXDIR) && $(CONVIMG)
endif

# determine output target flags
ifeq ($(ARCHIVED),YES)
CONVBINFLAGS += --archive
endif
ifeq ($(COMPRESSED),YES)
CONVBINFLAGS += --oformat 8xp-auto-decompress
else
CONVBINFLAGS += --oformat 8xp
endif
ifeq ($(HAS_UPPERCASE_NAME),YES)
CONVBINFLAGS += --uppercase
endif
CONVBINFLAGS += --name $(NAME)

# output debug map file
ifeq ($(OUTPUT_MAP),YES)
LDMAPFLAG := -i map
endif

# selectively include embedded printf functionality
ifeq ($(HAS_PRINTF),YES)
DEFPRINTF := -DHAS_PRINTF=1
endif

# support custom file io configuration
ifeq ($(HAS_CUSTOM_FILE),YES)
DEFCUSTOMFILE := -DHAS_CUSTOM_FILE=1 -DCUSTOM_FILE_FILE=\"$(CUSTOM_FILE_FILE)\"
endif

# choose static or linked flash functions
ifeq ($(HAS_FLASH_FUNCTIONS),YES)
LDSTATIC := 1
endif

# define the c/c++ flags used by clang
EZCFLAGS = -nostdinc -isystem $(call NATIVEPATH,$(CEDEV_TOOLCHAIN)/include) -I$(SRCDIR) -Dinterrupt="__attribute__((__interrupt__))"
EZCFLAGS += -fno-threadsafe-statics -Xclang -fforce-mangle-main-argc-argv -mllvm -profile-guided-section-prefix=false -D_EZ80 -D$(DEBUGMODE) $(DEFPRINTF) $(DEFCUSTOMFILE) $(CCDEBUG)
EZCXXFLAGS = $(EZCFLAGS) -fno-exceptions -fno-use-cxa-atexit $(CXXFLAGS)
EZCFLAGS += $(CFLAGS)

# these are the fasmg linker flags
FASMGFLAGS = \
	-n \
	$(call QUOTE_ARG,$(call NATIVEPATH,$(CEDEV_TOOLCHAIN)/meta/ld.alm)) \
	-i $(call QUOTE_ARG,DEBUG := $(LDDEBUG)) \
	-i $(call QUOTE_ARG,STATIC := $(LDSTATIC)) \
	-i $(call QUOTE_ARG,include $(call FASMG_FILES,$(LINKER_SCRIPT))) \
	-i $(call QUOTE_ARG,range .bss $$$(BSSHEAP_LOW) : $$$(BSSHEAP_HIGH)) \
	-i $(call QUOTE_ARG,provide __stack = $$$(STACK_HIGH)) \
	-i $(call QUOTE_ARG,locate .header at $$$(INIT_LOC)) \
	$(LDMAPFLAG) \
	-i $(call QUOTE_ARG,source $(LDICON)$(call FASMG_FILES,$(LDFILES))) \
	-i $(call QUOTE_ARG,library $(call FASMG_FILES,$(LDLIBS))) \
	$(EXTRA_LDFLAGS)

.PHONY: all clean version gfx debug

# this rule is trigged to build everything
all: $(BINDIR)/$(TARGET8XP)

# this rule is trigged to build debug everything
debug: DEBUGMODE = DEBUG
debug: LDDEBUG = 1
debug: CCDEBUG = -gdwarf-5 -g3
debug: $(BINDIR)/$(TARGET8XP)

$(BINDIR)/$(TARGET8XP): $(BINDIR)/$(TARGETBIN) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(CONVBIN) $(CONVBINFLAGS) --input $(call QUOTE_ARG,$(call NATIVEPATH,$<)) --output $(call QUOTE_ARG,$(call NATIVEPATH,$@))

$(BINDIR)/$(TARGETBIN): $(LDFILES) $(ICONSRC) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [linking] $(call NATIVEPATH,$@)
	$(Q)$(FASMGLD) $(FASMGFLAGS) $(call NATIVEPATH,$@)

ifneq ($(ICONSRC),)
$(ICONSRC): $(ICONIMG) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [convimg] $(or $(ICONIMG),description)
	$(Q)$(ICON_CONV)
endif

clean:
	$(Q)$(call RM,$(EXTRA_CLEAN))
	$(Q)$(call RMDIR,$(OBJDIR) $(BINDIR))
	$(Q)echo Removed built binaries and objects.

gfx:
	$(Q)$(GFXCMD)

version:
	$(Q)echo CE C Toolchain v$(shell cedev-config --version)

.SECONDEXPANSION:
$(OBJDIR)/%.$(C_EXTENSION).src: $$(call UPDIR_RM,$$*).$(C_EXTENSION) $(USERHEADERS) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [compiling] $(call NATIVEPATH,$<)
	$(Q)$(CC) -S $(EZCFLAGS) $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$@))

$(OBJDIR)/%.$(CPP_EXTENSION).src: $$(call UPDIR_RM,$$*).$(CPP_EXTENSION) $(USERHEADERS) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [compiling] $(call NATIVEPATH,$<)
	$(Q)$(CC) -S $(EZCXXFLAGS) $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$@))
