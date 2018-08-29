#----------------------------
# Core C Makefile
#----------------------------
CLEANUP             ?= YES
BSSHEAP_LOW         ?= D031F6
BSSHEAP_HIGH        ?= D13FD6
STACK_HIGH          ?= D1A87E
INIT_LOC            ?= D1A87F
USE_FLASH_FUNCTIONS ?= YES
OUTPUT_MAP          ?= YES
ARCHIVED            ?= NO
OPT_MODE            ?= -optsize
#----------------------------
SRCDIR              ?= src
OBJDIR              ?= obj
BINDIR              ?= bin
GFXDIR              ?= src/gfx
#----------------------------

VERSION := 8.4

#----------------------------
# try not to edit anything below these lines unless you know what you are doing
#----------------------------

#----------------------------

# define some common makefile things
empty :=
space := $(empty) $(empty)
comma := $(empty),$(empty)

TARGET ?= $(NAME)
ICONPNG ?= $(ICON)
DEBUGMODE = NDEBUG
CCDEBUGFLAG = -nodebug

# get the os specific items
ifeq ($(OS),Windows_NT)
SHELL     := cmd.exe
MAKEDIR   := $(CURDIR)
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
WINRELPATH = $(subst /,\,$(1))
RM         = del /q /f 2>nul
CEDEV     ?= $(call NATIVEPATH,$(realpath ..\..))
BIN       ?= $(call NATIVEPATH,$(CEDEV)/bin)
LD         = $(call NATIVEPATH,$(BIN)/fasmg.exe)
CC         = $(call NATIVEPATH,$(BIN)/ez80cc.exe)
CV         = $(call NATIVEPATH,$(BIN)/convhex.exe)
PG         = $(call NATIVEPATH,$(BIN)/convpng.exe)
CD         = cd
CP         = copy /y
NULL       = >nul 2>&1
RMDIR      = call && (if exist $(1) rmdir /s /q $(1))
MKDIR      = call && (if not exist $(1) mkdir $(1))
else
MAKEDIR   := $(CURDIR)
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath -w $(1)))
WINRELPATH = $(subst /,\,$(1))
RM         = rm -f
CEDEV     ?= $(call NATIVEPATH,$(realpath ..\..))
BIN       ?= $(call NATIVEPATH,$(CEDEV)/bin)
CC         = $(call NATIVEPATH,wine "$(BIN)/ez80cc.exe")
LD         = $(call NATIVEPATH,$(BIN)/fasmg)
CV         = $(call NATIVEPATH,$(BIN)/convhex)
PG         = $(call NATIVEPATH,$(BIN)/convpng)
CD         = cd
CP         = cp
RMDIR      = rm -rf $(1)
MKDIR      = mkdir -p $(1)
endif

# ensure native paths
SRCDIR := $(call NATIVEPATH,$(SRCDIR))
OBJDIR := $(call NATIVEPATH,$(OBJDIR))
BINDIR := $(call NATIVEPATH,$(BINDIR))
GFXDIR := $(call NATIVEPATH,$(GFXDIR))

# generate default names
TARGETBIN     := $(TARGET).bin
TARGETMAP     := $(TARGET).map
TARGETTYPE    := $(TARGET).8xp
ICON_ASM      := iconc.src

# init conditionals
F_STARTUP     := $(call NATIVEPATH,$(CEDEV)/lib/cstartup.src)
F_LAUNCHER    := $(call NATIVEPATH,$(CEDEV)/lib/libheader.src)
F_CLEANUP     := $(call NATIVEPATH,$(CEDEV)/lib/ccleanup.src)
F_ICON        := $(OBJDIR)/$(ICON_ASM)

# set use cases
U_CLEANUP = 0
U_ICON    = 0

# source: http://blog.jgc.org/2011/07/gnu-make-recursive-wildcard-function.html
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)$(filter $(subst *,%,$2),$d))

# find all of the available C, H and ASM files (Remember, you can create C <-> assembly routines easily this way)
CSOURCES      := $(call NATIVEPATH,$(call rwildcard,$(SRCDIR),*.c))
CPPSOURCES    := $(call NATIVEPATH,$(call rwildcard,$(SRCDIR),*.cpp))
USERHEADERS   := $(call NATIVEPATH,$(call rwildcard,$(SRCDIR),*.h))
USERHEADERS   += $(call NATIVEPATH,$(call rwildcard,$(SRCDIR),*.hpp))
ASMSOURCES    := $(call NATIVEPATH,$(call rwildcard,$(SRCDIR),*.asm))

# create links for later
LINK_CSOURCES := $(filter %.src,$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.src,$(subst \,/,$(CSOURCES))))
LINK_CPPSOURCES := $(filter %.src,$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.src,$(subst \,/,$(CSPPOURCES))))
LINK_ASMSOURCES := $(ASMSOURCES)

# files created to be used for linking
LINK_FILES    += $(LINK_CSOURCES)
LINK_FILES    += $(LINK_CPPSOURCES)
LINK_FILES    += $(LINK_ASMSOURCES)
LINK_FILES    += $(call NATIVEPATH,$(wildcard $(CEDEV)/lib/shared/*.src))
LINK_FILES    += $(call NATIVEPATH,$(wildcard $(CEDEV)/lib/fileio/*.src))
LINK_LIBLOAD  := $(call NATIVEPATH,$(wildcard $(CEDEV)/lib/libload/*.lib))

# check if there is an icon present that we can convert; if so, generate a recipe to build it properly
ifneq ("$(wildcard $(ICONPNG))","")
LINK_ICON  := $(F_ICON)
ICON_CONV  := $(PG) -c $(ICONPNG)$(comma)$(call NATIVEPATH,$(LINK_ICON))$(comma)$(DESCRIPTION)
U_ICON     = 1
endif

# determine if output should be archived or compressed
ifeq ($(ARCHIVED),YES)
CVFLAGS += -a
endif
ifeq ($(COMPRESSED),YES)
CVFLAGS += -x
endif
ifeq ($(CLEANUP),YES)
U_CLEANUP = 1
endif
ifeq ($(OUTPUT_MAP),YES)
LDMAPFLAG = -i 'map'
endif

# choose static or linked flash functions
ifeq ($(USE_FLASH_FUNCTIONS),YES)
LINK_FILES += $(wildcard $(CEDEV)/lib/linked/*.src)
else
LINK_FILES += $(wildcard $(CEDEV)/lib/static/*.src)
endif

# define the nesassary headers, along with any the user may have defined, where modification should just trigger a build
HEADERS :=$(strip $(subst $(space),;,$(call WINPATH,$(sort $(dir $(USERHEADERS))))))
ifeq ($(words $(HEADERS)),0)
HEADERS :=$(call WINPATH,$(CEDEV)/include);$(call WINPATH,$(CEDEV)/include/compat)
else
HEADERS +=$(strip ;$(call WINPATH,$(CEDEV)/include);$(call WINPATH,$(CEDEV)/include/compat))
endif
HEADERS :=$(subst \;,;,$(HEADERS))
HEADERS :=$(subst \;,;,$(HEADERS))
HEADERS :=$(subst /;,;,$(HEADERS))

# define the C flags used by the Zilog compiler
CFLAGS ?= \
    -noasm $(CCDEBUGFLAG) -nogenprint -keepasm -quiet $(OPT_MODE) -cpu:EZ80F91 -noreduceopt -nolistinc -nomodsect \
    -stdinc:"$(HEADERS)" -define:_EZ80F91 -define:_EZ80 -define:$(DEBUGMODE)

# these are the linker flags, basically organized to properly set up the environment
LDFLAGS ?= \
	$(CEDEV)/include/fasmg-ez80/ld.fasmg \
	$(LDDEBUGFLAG) \
	$(LDMAPFLAG) \
	-i 'range bss $$$(BSSHEAP_LOW) : $$$(BSSHEAP_HIGH)' \
	-i 'symbol __low_bss = bss.base' \
	-i 'symbol __len_bss = bss.length' \
	-i 'symbol __heaptop = bss.high' \
	-i 'symbol __heapbot = bss.top' \
	-i 'symbol __stack = $$$(STACK_HIGH)' \
	-i 'locate header at $$$(INIT_LOC)' \
	-i 'libs $(LINK_LIBLOAD)' \
	-i 'order header,icon,launcher,libs,startup,cleanup,exit,code,data,strsect,text' \
	-i 'sources '$(F_LAUNCHER)' if libs.length, '$(F_ICON)' if $(U_ICON), '$(F_CLEANUP)' if $(U_CLEANUP)' \
	-i 'sources '$(F_STARTUP)'' \
	-i 'deps $(call NATIVEPATH,$(LINK_FILES))'

# this rule is trigged to build everything
all: dirs $(BINDIR)/$(TARGET8XP)

# this rule is trigged to build debug everything
debug: LDDEBUGFLAG = -i 'dbg'
debug: DEBUGMODE = DEBUG
debug: CCDEBUGFLAG = -debug
debug: dirs $(BINDIR)/$(TARGET8XP)

dirs:
	@echo C CE SDK Version $(VERSION) && \
	$(call MKDIR,$(BINDIR)) && \
	$(call MKDIR,$(OBJDIR))

$(BINDIR)/$(TARGET8XP): $(BINDIR)/$(TARGETBIN)
	@$(CD) $(BINDIR) && \
	$(CV) $(CVFLAGS) $(notdir $<)

$(BINDIR)/$(TARGETBIN): $(LINK_FILES) $(LINK_ICON)
	@$(LD) $(LDFLAGS) $@

# this rule handles conversion of the icon, if it is ever updated
$(OBJDIR)/$(ICON_ASM): $(ICONPNG)
	@$(ICON_CONV)

# these rules compile the source files into object files
$(OBJDIR)/%.src: */%.c $(USERHEADERS)
	@$(call MKDIR,$(call NATIVEPATH,$(@D))) && \
	$(CD) $(call NATIVEPATH,$(@D)) && \
	$(CC) $(CFLAGS) "$(call WINPATH,$(addprefix $(MAKEDIR)/,$<))"

# these rules compile the source files into object files
$(OBJDIR)/%.src: **/*/%.c $(USERHEADERS)
	@$(call MKDIR,$(call NATIVEPATH,$(@D))) && \
	$(CD) $(call NATIVEPATH,$(@D)) && \
	$(CC) $(CFLAGS) "$(call WINPATH,$(addprefix $(MAKEDIR)/,$<))"

clean:
	@$(call RMDIR,$(OBJDIR)) && \
	$(call RMDIR,$(BINDIR)) && \
	echo Cleaned build files.

gfx:
	@$(CD) $(GFXDIR) && convpng

version:
	@echo C SDK Version $(VERSION)

.PHONY: all clean version gfx dirs
