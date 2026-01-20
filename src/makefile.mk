# Copyright (C) 2015-2026 CE Programming
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
ARCHIVED ?= YES
APPLICATION ?= NO
BSSHEAP_LOW ?= 0xD052C6
BSSHEAP_HIGH ?= 0xD13FD8
STACK_HIGH ?= 0xD1A87E
LOAD_ADDR ?= 0xD1A87F
OUTPUT_MAP ?= YES
CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz
ASFLAGS ?=
LTOFLAGS ?= $(CFLAGS)
LTO ?= YES
SRCDIR ?= src
OBJDIR ?= obj
BINDIR ?= bin
GFXDIR ?= src/gfx
CPP_EXTENSION ?= cpp
C_EXTENSION ?= c
ASM_EXTENSION ?= S
CUSTOM_FILE_FILE ?= stdio_file.h
DEPS ?=
HAS_UPPERCASE_NAME ?= YES
HAS_PRINTF ?= YES
HAS_CUSTOM_FILE ?= NO
HAS_LIBC ?= YES
HAS_LIBCXX ?= YES
ALLOCATOR ?= STANDARD
PREFER_OS_CRT ?= NO
PREFER_OS_LIBC ?= YES
SKIP_LIBRARY_LDFLAGS ?= NO
LIBLOAD_OPTIONAL ?=
COMPRESSED_MODE ?= zx7
COMMENT ?= $(shell cedev-config --comment)
#----------------------------
CEDEV_TOOLCHAIN ?= $(shell cedev-config --prefix)
#----------------------------

ifneq ($(words $(NAME)),1)
$(error NAME must not contain any spaces)
endif

# define some common makefile things
empty :=
space := $(empty) $(empty)
comma := ,

# verbosity
V ?= 0
ifeq ($(V),0)
Q = @
else
Q =
endif

# location of binaries
BIN ?= $(CEDEV_TOOLCHAIN)/bin
BINUTILS_BIN ?= $(CEDEV_TOOLCHAIN)/binutils/bin

# get the os specific operations
ifeq ($(OS),Windows_NT)
SHELL = cmd.exe
NATIVEPATH = $(subst /,\,$1)
EXE_SUFFIX = .exe
RM = ( del /q /f $1 2>nul || call )
RMDIR = ( rmdir /s /q $1 2>nul || call )
NATIVEMKDR = ( mkdir $1 2>nul || call )
QUOTE_ARG = "$(subst ",',$1)"#'
else
NATIVEPATH = $(subst \,/,$1)
EXE_SUFFIX =
RM = rm -f $1
RMDIR = rm -rf $1
NATIVEMKDR = mkdir -p $1
QUOTE_ARG = '$(subst ','\'',$1)'#'
endif

# toolchain binaries
CONVBIN = $(call NATIVEPATH,$(BIN)/convbin$(EXE_SUFFIX))
CONVIMG = $(call NATIVEPATH,$(BIN)/convimg$(EXE_SUFFIX))
CEMUTEST = $(call NATIVEPATH,$(BIN)/cemu-autotester$(EXE_SUFFIX))
CC = $(call NATIVEPATH,$(BIN)/ez80-clang$(EXE_SUFFIX))
LINK = $(call NATIVEPATH,$(BIN)/ez80-link$(EXE_SUFFIX))
AS = $(call NATIVEPATH,$(BINUTILS_BIN)/z80-none-elf-as$(EXE_SUFFIX))
LD = $(call NATIVEPATH,$(BINUTILS_BIN)/z80-none-elf-ld$(EXE_SUFFIX))
OBJCOPY = $(call NATIVEPATH,$(BINUTILS_BIN)/z80-none-elf-objcopy$(EXE_SUFFIX))
STRIP = $(call NATIVEPATH,$(BINUTILS_BIN)/z80-none-elf-strip$(EXE_SUFFIX))
CEDEV_OBJ = $(call NATIVEPATH,$(BIN)/cedev-obj$(EXE_SUFFIX))

# filepath operations
MKDIR = $(call NATIVEMKDR,$(call QUOTE_ARG,$(call NATIVEPATH,$1)))
FORWARD_PATH = $(subst \,/,$1)
UPDIR_ADD = $(subst ../,_../,$(subst \,/,$1))
UPDIR_RM = $(subst _../,../,$(subst \,/,$1))

# configure debug defaults
CC_DEBUG = -DNDEBUG=1
LD_DEBUG = --defsym NDEBUG=1

# linker script
LINKER_SCRIPT ?= $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/meta/linker_script.ld)

# allocator (malloc/realloc/free)
ifeq ($(ALLOCATOR),STANDARD)
LIB_ALLOCATOR = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/libc/allocator_standard.a)
endif
ifeq ($(ALLOCATOR),SIMPLE)
LIB_ALLOCATOR = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/libc/allocator_simple.a)
endif

# ensure always a hexadecimal value
BSSHEAP_LOW := 0x$(patsubst 0x%,%,$(BSSHEAP_LOW))
BSSHEAP_HIGH := 0x$(patsubst 0x%,%,$(BSSHEAP_HIGH))
STACK_HIGH := 0x$(patsubst 0x%,%,$(STACK_HIGH))
LOAD_ADDR := 0x$(patsubst 0x%,%,$(LOAD_ADDR))

# ensure native paths
SRCDIR := $(call FORWARD_PATH,$(SRCDIR))
OBJDIR := $(call FORWARD_PATH,$(OBJDIR))
BINDIR := $(call FORWARD_PATH,$(BINDIR))
GFXDIR := $(call FORWARD_PATH,$(GFXDIR))

# generate default names
TARGETOBJ ?= $(NAME).obj
TARGETTMP ?= $(NAME).o
TARGETMAP ?= $(NAME).map
TARGET ?= $(NAME).8xp
ICON_IMG := $(call FORWARD_PATH,$(wildcard $(call NATIVEPATH,$(ICON))))

# startup routines
CRT0_SRC = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/crt/crt0.S)
CRT0_TMP = $(OBJDIR)/crt0.s
CRT0_OBJ = $(OBJDIR)/crt0.o
LTO_BC = $(OBJDIR)/lto.bc
LTO_SRC = $(OBJDIR)/lto.s
LTO_OBJ = $(OBJDIR)/lto.o

# source: http://blog.jgc.org/2011/07/gnu-make-recursive-wildcard-function.html
rwildcard = $(strip $(foreach d,$(wildcard $1/*),$(call rwildcard,$d,$2) $(filter $(subst %%,%,%$(subst *,%,$2)),$d)))

# compatibility with older makefiles
EXTRA_HEADERS += $(EXTRA_USERHEADERS)
EXTRA_C_SOURCES += $(EXTRA_CSOURCES)
EXTRA_CXX_SOURCES += $(EXTRA_CPPSOURCES)
EXTRA_ASM_SOURCES += $(EXTRA_ASMSOURCES)

# find source files
CSOURCES = $(sort $(call rwildcard,$(SRCDIR),*.$(C_EXTENSION)) $(EXTRA_C_SOURCES))
CPPSOURCES = $(sort $(call rwildcard,$(SRCDIR),*.$(CPP_EXTENSION)) $(EXTRA_CXX_SOURCES))
ASMSOURCES = $(sort $(call rwildcard,$(SRCDIR),*.s) $(EXTRA_ASM_SOURCES))
PREASMSOURCES = $(sort $(call rwildcard,$(SRCDIR),*.S) $(EXTRA_PREASM_SOURCES))

# link time optimization
ifneq ($(filter debug,$(MAKECMDGOALS)),)
LTO := NO
endif
ifeq ($(LTO),YES)
LINK_CSOURCES = $(call UPDIR_ADD,$(CSOURCES:%.$(C_EXTENSION)=$(OBJDIR)/%.$(C_EXTENSION).bc))
LINK_CPPSOURCES = $(call UPDIR_ADD,$(CPPSOURCES:%.$(CPP_EXTENSION)=$(OBJDIR)/%.$(CPP_EXTENSION).bc))
LINK_ASMSOURCES = $(call UPDIR_ADD,$(ASMSOURCES:%.s=$(OBJDIR)/%.s.o))
LINK_PREASMSOURCES = $(call UPDIR_ADD,$(PREASMSOURCES:%.S=$(OBJDIR)/%.S.o))
LTO_FILES = $(LINK_CSOURCES) $(LINK_CPPSOURCES)
OBJECTS = $(LTO_OBJ) $(LINK_ASMSOURCES) $(LINK_PREASMSOURCES)
DEPFILES = $(wildcard $(LINK_CSOURCES:%.bc=%.d) $(LINK_CPPSOURCES:%.bc=%.d))
else
LINK_CSOURCES = $(call UPDIR_ADD,$(CSOURCES:%.$(C_EXTENSION)=$(OBJDIR)/%.$(C_EXTENSION).o))
LINK_CPPSOURCES = $(call UPDIR_ADD,$(CPPSOURCES:%.$(CPP_EXTENSION)=$(OBJDIR)/%.$(CPP_EXTENSION).o))
LINK_ASMSOURCES = $(call UPDIR_ADD,$(ASMSOURCES:%.s=$(OBJDIR)/%.s.o))
LINK_PREASMSOURCES = $(call UPDIR_ADD,$(PREASMSOURCES:%.S=$(OBJDIR)/%.S.o))
OBJECTS = $(LINK_CSOURCES) $(LINK_CPPSOURCES) $(LINK_ASMSOURCES) $(LINK_PREASMSOURCES)
DEPFILES = $(wildcard $(LINK_CSOURCES:%.o=%.d) $(LINK_CPPSOURCES:%.o=%.d))
endif

ifneq ($(SKIP_LIBRARY_LDFLAGS),YES)
# find all required/optional libload libraries
LIBLOAD_LIBS ?= $(wildcard $(CEDEV_TOOLCHAIN)/lib/libload/*.lib) $(EXTRA_LIBLOAD_LIBS)
LIBLOAD_LIBS := $(foreach l,$(filter-out %libload.lib,$(LIBLOAD_LIBS)),$(call QUOTE_ARG,$(call FORWARD_PATH,$l)))
endif

# check if there is an icon present that to convert
ifneq ($(ICON_IMG),)
ICON_SRC = $(OBJDIR)/icon.s
ifneq ($(DESCRIPTION),)
ICON_CONV ?= $(CONVIMG) --icon $(call QUOTE_ARG,$(ICON_IMG)) --icon-output $(call QUOTE_ARG,$(ICON_SRC)) --icon-format gas --icon-description $(DESCRIPTION)
else
ICON_CONV ?= $(CONVIMG) --icon $(call QUOTE_ARG,$(ICON_IMG)) --icon-output $(call QUOTE_ARG,$(ICON_SRC)) --icon-format gas
endif
ICON_OBJ = $(OBJDIR)/icon.obj
else
ifneq ($(DESCRIPTION),)
ICON_SRC ?= $(OBJDIR)/icon.s
ICON_CONV ?= $(CONVIMG) --icon-output $(call QUOTE_ARG,$(ICON_SRC)) --icon-format gas --icon-description $(DESCRIPTION)
ICON_OBJ = $(OBJDIR)/icon.obj
endif
endif

# set default 'make gfx' target
ifneq ($(wildcard $(GFXDIR)/.),)
MAKE_GFX ?= cd $(GFXDIR) && $(CONVIMG)
endif

# determine output target flags
ifeq ($(APPLICATION),YES)
LD_EMIT_RELOCS = --emit-relocs
LOAD_ADDR = 0x000000
CONVBINFLAGS += -k 8ek
TARGET = $(NAME).8ek
CRT0_APPLICATION = -DHAS_APPLICATION=1
LINKER_SCRIPT = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/meta/linker_script_app.ld)
else
LD_EMIT_RELOCS =
ifeq ($(ARCHIVED),YES)
CONVBINFLAGS += -r
endif
ifeq ($(COMPRESSED),YES)
CONVBINFLAGS += -e $(COMPRESSED_MODE)
CONVBINFLAGS += -k 8xp-compressed
else
CONVBINFLAGS += -k 8xp
endif
endif

# common output targer flags
ifeq ($(HAS_UPPERCASE_NAME),YES)
CONVBINFLAGS += -u
endif
ifneq ($(COMMENT),)
CONVBINFLAGS += -b $(call QUOTE_ARG,$(COMMENT))
endif
CONVBINFLAGS += -n $(NAME)

# output debug map file
ifeq ($(OUTPUT_MAP),YES)
LD_MAP = -Map=$(BINDIR)/$(TARGETMAP)
else
LD_MAP =
endif
ifeq ($(HAS_CUSTOM_FILE),YES)
CC_CUSTOMFILE := -DHAS_CUSTOM_FILE=1 -DCUSTOM_FILE_FILE=\"$(CUSTOM_FILE_FILE)\"
endif

# choose crt
ifeq ($(PREFER_OS_CRT),YES)
LIB_CRT = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/crt/libcrt_os.a)
else
LIB_CRT = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/crt/libcrt.a)
endif

# choose libc
ifeq ($(HAS_LIBC),YES)
ifeq ($(PREFER_OS_LIBC),YES)
LIB_C = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/libc/libc_os.a)
else
LIB_C = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/libc/libc.a)
endif
else
LIB_C =
endif

# choose libcxx
ifeq ($(HAS_LIBCXX),YES)
LIB_CXX = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/libcxx/libcxx.a)
else
LIB_CXX =
endif

# add other libs
LIB_CE = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/ce/libce.a)
LIB_SOFTFLOAT = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/softfloat/libsoftfloat.a)

# include printf
ifeq ($(HAS_PRINTF),YES)
LIB_PRINTF = $(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/lib/libc/libnanoprintf.a)
else
LIB_PRINTF =
endif

# enable/disable errno checks
ifeq ($(HAS_MATH_ERRNO),YES)
MATH_ERRNO =
else
MATH_ERRNO = -fno-math-errno
endif

# define the compiler/assembler flags
EZLLVMFLAGS = -mllvm -profile-guided-section-prefix=false -mllvm -z80-gas-style -ffunction-sections -fdata-sections -fno-addrsig -fno-autolink -fno-threadsafe-statics $(MATH_ERRNO)
EZCOMMONFLAGS = -nostdinc -isystem $(call QUOTE_ARG,$(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/include)) -I$(SRCDIR) -Xclang -fforce-mangle-main-argc-argv $(EZLLVMFLAGS) -D__TICE__=1 $(CC_DEBUG) $(CC_CUSTOMFILE)
EZCFLAGS = $(EZCOMMONFLAGS) $(CFLAGS)
EZCXXFLAGS = $(EZCOMMONFLAGS) -isystem $(call QUOTE_ARG,$(call FORWARD_PATH,$(CEDEV_TOOLCHAIN)/include/c++)) -fno-exceptions -fno-use-cxa-atexit $(CXXFLAGS)
EZLTOFLAGS = $(EZLLVMFLAGS) $(LTOFLAGS)
EZASFLAGS = -march=ez80+full $(ASFLAGS)

.PHONY: all clean version gfx debug

# this rule is trigged to build everything
all: $(BINDIR)/$(TARGET)

# this rule is trigged to build debug everything
debug: CC_DEBUG = -DDEBUG=1
debug: LD_DEBUG = --defsym DEBUG=1
debug: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(BINDIR)/$(TARGETOBJ) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(CONVBIN) $(CONVBINFLAGS) -j elf -i $(call QUOTE_ARG,$<) -o $(call QUOTE_ARG,$@)

$(BINDIR)/$(TARGETOBJ): $(CRT0_OBJ) $(OBJDIR)/$(TARGETTMP) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [linking] $@
	$(Q)$(LD) \
		-static \
		--entry=__start \
		--no-warn-rwx-segments \
		--gc-sections \
		--omagic \
		--defsym=LOAD_ADDR=$(LOAD_ADDR) \
		--defsym=BSSHEAP_LOW=$(BSSHEAP_LOW) \
		--defsym=BSSHEAP_HIGH=$(BSSHEAP_HIGH) \
		--defsym=STACK_HIGH=$(STACK_HIGH) \
		--defsym __TICE__=1 \
		-T$(LINKER_SCRIPT) \
		$(LD_MAP) \
		$(LD_EMIT_RELOCS) \
		$(EXTRA_LDFLAGS) \
		$(OBJDIR)/$(TARGETTMP) \
		$(CRT0_OBJ) \
		$(LIB_ALLOCATOR) \
		--start-group \
		$(LIB_SOFTFLOAT) \
		$(LIB_CRT) \
		--end-group \
		$(LIB_C) \
		$(LIB_CXX) \
		$(LIB_CE) \
		-o $(call QUOTE_ARG,$@)

ifneq ($(ICON_SRC),)
$(ICON_OBJ): $(ICON_IMG) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [convimg] $(or $(ICON_IMG),description)
	$(Q)$(ICON_CONV)
	$(Q)$(AS) -march=ez80+full $(call QUOTE_ARG,$(ICON_SRC)) -o $(call QUOTE_ARG,$@)
endif

clean:
	$(Q)$(EXTRA_CLEAN)
	$(Q)$(call RMDIR,$(OBJDIR) $(BINDIR))
	$(Q)echo Removed built binaries and objects.

gfx:
	$(Q)$(MAKE_GFX)

test:
	$(Q)$(CEMUTEST) $(call QUOTE_ARG,$(call FORWARD_PATH,$(CURDIR)/autotest.json))

version:
	$(Q)echo CE C/C++ Toolchain $(shell cedev-config --version)

.SECONDEXPANSION:
.SECONDARY:

# no lto
$(OBJDIR)/%.$(C_EXTENSION).s: $$(call UPDIR_RM,$$*).$(C_EXTENSION) $(EXTRA_HEADERS) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [cc] $<
	$(Q)$(CC) -S -MD $(EZCFLAGS) $(call QUOTE_ARG,$<) -o $(call QUOTE_ARG,$@)

$(OBJDIR)/%.$(CPP_EXTENSION).s: $$(call UPDIR_RM,$$*).$(CPP_EXTENSION) $(EXTRA_HEADERS) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [cc] $<
	$(Q)$(CC) -S -MD $(EZCXXFLAGS) $(call QUOTE_ARG,$<) -o $(call QUOTE_ARG,$@)

$(OBJDIR)/%.$(C_EXTENSION).o: $(OBJDIR)/%.$(C_EXTENSION).s
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(AS) $(EZASFLAGS) $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$@))

$(OBJDIR)/%.$(CPP_EXTENSION).o: $(OBJDIR)/%.$(CPP_EXTENSION).s
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(AS) $(EZASFLAGS) $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$@))

$(OBJDIR)/%.s.o: $$(call UPDIR_RM,$$*).s 
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [as] $<
	$(Q)$(AS) $(EZASFLAGS) $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$@))

$(OBJDIR)/%.s: $$(call UPDIR_RM,$$*).S
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [as] $<
	$(Q)$(CC) -MD $(EZCFLAGS) -E $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$@))

$(OBJDIR)/%.S.o: $(OBJDIR)/%.s
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(AS) $(EZASFLAGS) $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$@))

# lto
$(LTO_OBJ): $(LTO_SRC)
	$(Q)$(AS) $(EZASFLAGS) $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$@))

$(LTO_SRC): $(LTO_BC)
	$(Q)$(CC) -S $(EZLTOFLAGS) $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$@))

$(LTO_BC): $(LTO_FILES)
	$(Q)echo [lto] $@
	$(Q)$(LINK) $(foreach d,$^,$(call QUOTE_ARG,$(addprefix $(CURDIR)/,$d))) -o $(call QUOTE_ARG,$(addprefix $(CURDIR)/,$@))

$(OBJDIR)/%.$(C_EXTENSION).bc: $$(call UPDIR_RM,$$*).$(C_EXTENSION) $(EXTRA_HEADERS) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [cc] $<
	$(Q)$(CC) -MD -c -emit-llvm $(EZCFLAGS) $(call QUOTE_ARG,$<) -o $(call QUOTE_ARG,$@)

$(OBJDIR)/%.$(CPP_EXTENSION).bc: $$(call UPDIR_RM,$$*).$(CPP_EXTENSION) $(EXTRA_HEADERS) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [cc] $<
	$(Q)$(CC) -MD -c -emit-llvm $(EZCXXFLAGS) $(call QUOTE_ARG,$<) -o $(call QUOTE_ARG,$@)

# crt
$(OBJDIR)/$(TARGETTMP): $(OBJECTS) $(LIB_ALLOCATOR) $(LIB_PRINTF) $(LIB_CXX) $(LIB_CE) $(LIB_SOFTFLOAT) $(LIB_CRT) $(LIB_C) $(ICON_OBJ) $(EXTRA_LIBS) $(MAKEFILE_LIST) $(DEPS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(LD) \
		-i \
		-static \
		--entry=__start \
		--build-id=none \
		--gc-sections \
		--omagic \
		--defsym __TICE__=1 \
		$(LD_DEBUG) \
		$(EXTRA_PRE_LDFLAGS) \
		$(OBJECTS) \
		$(ICON_OBJ) \
		$(LIB_ALLOCATOR) \
		$(LIB_PRINTF) \
		$(LIB_CXX) \
		$(LIB_CE) \
		$(LIB_CRT) \
		$(LIB_C) \
		$(LIB_SOFTFLOAT) \
		$(EXTRA_LIBS) \
		-o $(call QUOTE_ARG,$@)
	$(Q)$(STRIP) --strip-unneeded $(call QUOTE_ARG,$@)

$(OBJDIR)/crt.h: $(OBJDIR)/$(TARGETTMP)
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(CEDEV_OBJ) --elf $(call QUOTE_ARG,$<) --output $(call QUOTE_ARG,$@) --libs $(LIBLOAD_LIBS) --optional-libs $(LIBLOAD_OPTIONAL)

$(CRT0_OBJ): $(CRT0_TMP)
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(AS) -I$(OBJDIR) -march=ez80+full $(call QUOTE_ARG,$<) -o $(call QUOTE_ARG,$@)

$(CRT0_TMP): $(CRT0_SRC) $(OBJDIR)/crt.h
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(CC) -I$(OBJDIR) $(CRT0_APPLICATION) -E -P $(call QUOTE_ARG,$<) -o $(call QUOTE_ARG,$@)

ifeq ($(filter clean gfx test version,$(MAKECMDGOALS)),)
-include $(DEPFILES)
endif
