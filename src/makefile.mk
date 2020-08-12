#----------------------------
# Core C/C++ Makefile
#----------------------------
MAIN_ARGS           ?= NO
CLEANUP             ?= YES
BSSHEAP_LOW         ?= D031F6
BSSHEAP_HIGH        ?= D13FD6
STACK_HIGH          ?= D1A87E
INIT_LOC            ?= D1A87F
USE_FLASH_FUNCTIONS ?= YES
UPPERCASE_NAME      ?= YES
OUTPUT_MAP          ?= NO
ARCHIVED            ?= NO
OPT_MODE            ?= -O3
EXTRA_CFLAGS        ?=
EXTRA_CXXFLAGS      ?=
#----------------------------
SRCDIR              ?= src
OBJDIR              ?= obj
BINDIR              ?= bin
GFXDIR              ?= src/gfx
#----------------------------

VERSION := 9.0-devel

#----------------------------
# try not to edit anything below these lines unless you know what you are doing
#----------------------------

#----------------------------

# define some common makefile things
empty :=
space := $(empty) $(empty)
comma := ,

TARGET ?= $(NAME)
DEBUGMODE = NDEBUG
CCDEBUGFLAG = -g0

# verbosity
V ?= 0
ifeq ($(V),0)
Q = @
else
Q =
endif

# get the os specific items
ifeq ($(OS),Windows_NT)
SHELL     := cmd.exe
MAKEDIR   := $(CURDIR)
NATIVEPATH = $(subst /,\,$1)
WINPATH    = $(NATIVEPATH)
WINRELPATH = $(subst /,\,$1)
CEDEV     ?= $(call NATIVEPATH,$(realpath ..\..))
BIN       ?= $(call NATIVEPATH,$(CEDEV)/bin)
LD         = $(call NATIVEPATH,$(BIN)/fasmg.exe)
CONVBIN    = $(call NATIVEPATH,$(BIN)/convbin.exe)
CONVIMG    = $(call NATIVEPATH,$(BIN)/convimg.exe)
CD         = cd
RM         = ( del /q /f $1 2>nul || call )
RMDIR      = ( rmdir /s /q $1 2>nul || call )
NATIVEMKDR = ( mkdir $1 2>nul || call )
QUOTE_ARG  = "$(subst ",',$1)"#'
else
MAKEDIR   := $(CURDIR)
NATIVEPATH = $(subst \,/,$1)
WINPATH    = $(shell winepath -w $1)
WINRELPATH = $(subst /,\,$1)
CEDEV     ?= $(call NATIVEPATH,$(realpath ..\..))
BIN       ?= $(call NATIVEPATH,$(CEDEV)/bin)
LD         = $(call NATIVEPATH,$(BIN)/fasmg)
CONVBIN    = $(call NATIVEPATH,$(BIN)/convbin)
CONVIMG    = $(call NATIVEPATH,$(BIN)/convimg)
CD         = cd
RM         = rm -f $1
RMDIR      = rm -rf $1
NATIVEMKDR = mkdir -p $1
QUOTE_ARG  = '$(subst ','\'',$1)'#'
endif
EZCC = ez80-clang

MKDIR = $(call NATIVEMKDR,$(call QUOTE_ARG,$(call NATIVEPATH,$1)))

FASMG_FILES = $(subst $(space),$(comma) ,$(patsubst %,"%",$(subst ",\",$(subst \,\\,$(call NATIVEPATH,$1)))))#"
LINKER_SCRIPT ?= $(CEDEV)/include/.linker_script

# ensure native paths
SRCDIR := $(call NATIVEPATH,$(SRCDIR))
OBJDIR := $(call NATIVEPATH,$(OBJDIR))
BINDIR := $(call NATIVEPATH,$(BINDIR))
GFXDIR := $(call NATIVEPATH,$(GFXDIR))

# generate default names
TARGETBIN     := $(TARGET).bin
TARGETMAP     := $(TARGET).map
TARGET8XP     := $(TARGET).8xp
ICONIMG       := $(wildcard $(call NATIVEPATH,$(ICON)))
ICONSRC       := $(call NATIVEPATH,$(OBJDIR)/icon.src)

# init conditionals
F_STARTUP     := $(call NATIVEPATH,$(CEDEV)/lib/cstartup.src)
F_LAUNCHER    := $(call NATIVEPATH,$(CEDEV)/lib/libheader.src)
F_CLEANUP     := $(call NATIVEPATH,$(CEDEV)/lib/ccleanup.src)

# source: http://blog.jgc.org/2011/07/gnu-make-recursive-wildcard-function.html
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)$(filter $(subst *,%,$2),$d))

# find all of the available C, H and ASM files (Remember, you can create C <-> assembly routines easily this way)
CSOURCES      := $(call rwildcard,$(SRCDIR),*.c)
CPPSOURCES    := $(call rwildcard,$(SRCDIR),*.cpp)
USERHEADERS   := $(call rwildcard,$(SRCDIR),*.h *.hpp)
ASMSOURCES    := $(call rwildcard,$(SRCDIR),*.asm)

# create links for later
LINK_CSOURCES := $(CSOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.c.src)
LINK_CPPSOURCES := $(CPPSOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.cpp.src)
LINK_ASMSOURCES := $(ASMSOURCES)

# files created to be used for linking
LINK_FILES   := $(LINK_CSOURCES) $(LINK_CPPSOURCES) $(LINK_ASMSOURCES)
LINK_LIBS    := $(wildcard $(CEDEV)/lib/libload/*.lib)
LINK_LIBLOAD := $(CEDEV)/lib/libload.lib

# check if there is an icon present that we can convert
# if so, generate a recipe to build it
ifneq ($(ICONIMG),)
ICON_CONV := @echo [convimg] $(ICONIMG) && $(CONVIMG) --icon $(call QUOTE_ARG,$(ICONIMG)) --icon-output $(call QUOTE_ARG,$(ICONSRC)) --icon-format asm --icon-description $(DESCRIPTION)
LINK_REQUIRE += -i $(call QUOTE_ARG,require ___icon)
LINK_ICON = , $(call FASMG_FILES,$(ICONSRC))
else
ifneq ($(DESCRIPTION),)
ICON_CONV := @echo [convimg] description && $(CONVIMG) --icon-output $(call QUOTE_ARG,$(ICONSRC)) --icon-format asm --icon-description $(DESCRIPTION)
LINK_REQUIRE += -i $(call QUOTE_ARG,require ___description)
LINK_ICON = , $(call FASMG_FILES,$(ICONSRC))
ICONIMG :=
else
ICONSRC :=
endif
endif

# check if gfx directory exists
ifneq ($(wildcard $(GFXDIR)/.),)
GFXCMD := $(CD) $(GFXDIR) && $(CONVIMG)
else
GFXCMD :=
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
ifeq ($(UPPERCASE_NAME),YES)
CONVBINFLAGS += --uppercase
endif
CONVBINFLAGS += --name $(TARGET)

# support main args?
ifeq ($(MAIN_ARGS),YES)
LINK_DEFINITIONS += -i __MAIN_ARGS=1
endif

# link cleanup source
ifeq ($(CLEANUP),YES)
LINK_REQUIRE += -i $(call QUOTE_ARG,require __ccleanup)
LINK_CLEANUP  = , $(call FASMG_FILES,$(F_CLEANUP))
endif

# output debug map file
ifeq ($(OUTPUT_MAP),YES)
LDMAPFLAG = -i map
endif

# choose static or linked flash functions
ifeq ($(USE_FLASH_FUNCTIONS),YES)
STATIC := 0
else
STATIC := 1
endif

# define the C/C++ flags used by Clang
CFLAGS ?= -S -nostdinc -isystem $(CEDEV)/include $(CCDEBUGFLAG) $(OPT_MODE) -Dinterrupt="__attribute__((__interrupt__))" -Dreentrant= -D_EZ80 -D$(DEBUGMODE) $(EXTRA_CFLAGS)
CFLAGS := $(CFLAGS) -Wno-main-return-type
CXXFLAGS := $(CFLAGS) -fno-exceptions $(EXTRA_CXXFLAGS)

# these are the linker flags, basically organized to properly set up the environment
LDFLAGS ?= \
	-n \
	$(call QUOTE_ARG,$(call NATIVEPATH,$(CEDEV)/include/fasmg-ez80/ld.alm)) \
	-i $(call QUOTE_ARG,include $(call FASMG_FILES,$(LINKER_SCRIPT))) \
	$(LDDEBUGFLAG) \
	$(LDMAPFLAG) \
	-i $(call QUOTE_ARG,range .bss $$$(BSSHEAP_LOW) : $$$(BSSHEAP_HIGH)) \
	-i $(call QUOTE_ARG,provide __stack = $$$(STACK_HIGH)) \
	-i $(call QUOTE_ARG,locate .header at $$$(INIT_LOC)) \
	-i $(call QUOTE_ARG,STATIC := $(STATIC)) \
	$(LINK_DEFINITIONS) \
	$(LINK_REQUIRE) \
	-i $(call QUOTE_ARG,source $(call FASMG_FILES,$(F_LAUNCHER))$(LINK_ICON)$(LINK_CLEANUP)$(comma) $(call FASMG_FILES,$(F_STARTUP))$(comma) $(call FASMG_FILES,$(LINK_FILES))) \
	-i $(call QUOTE_ARG,library $(call FASMG_FILES,$(LINK_LIBLOAD))$(comma) $(call FASMG_FILES,$(LINK_LIBS)))

# this rule is trigged to build everything
all: $(BINDIR)/$(TARGET8XP) ;

# this rule is trigged to build debug everything
debug: LDDEBUGFLAG = -i dbg
debug: DEBUGMODE = DEBUG
#debug: CCDEBUGFLAG = -g
debug: $(BINDIR)/$(TARGET8XP) ;

$(BINDIR)/$(TARGET8XP): $(BINDIR)/$(TARGETBIN)
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(CONVBIN) $(CONVBINFLAGS) --input $(call QUOTE_ARG,$(call NATIVEPATH,$<)) --output $(call QUOTE_ARG,$(call NATIVEPATH,$@))

$(BINDIR)/$(TARGETBIN): $(ICONSRC) $(LINK_FILES)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [linking] $(call NATIVEPATH,$@)
	$(Q)$(LD) $(LDFLAGS) $(call NATIVEPATH,$@)

# this rule handles conversion of the icon, if it is ever updated
$(ICONSRC): $(ICONIMG)
	$(Q)$(call MKDIR,$(@D))
	$(Q)$(ICON_CONV)

# these rules compile the source files into assembly files
$(OBJDIR)/%.c.src: $(SRCDIR)/%.c $(USERHEADERS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [compiling] $(call NATIVEPATH,$<)
	$(Q)$(EZCC) $(CFLAGS) $(call QUOTE_ARG,$(addprefix $(MAKEDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(MAKEDIR)/,$@))

$(OBJDIR)/%.cpp.src: $(SRCDIR)/%.cpp $(USERHEADERS)
	$(Q)$(call MKDIR,$(@D))
	$(Q)echo [compiling] $(call NATIVEPATH,$<)
	$(Q)$(EZCC) $(CXXFLAGS) $(call QUOTE_ARG,$(addprefix $(MAKEDIR)/,$<)) -o $(call QUOTE_ARG,$(addprefix $(MAKEDIR)/,$@))

clean:
	$(Q)$(call RMDIR,$(OBJDIR) $(BINDIR))
	@echo Removed build objects and binaries.

gfx:
	$(Q)$(GFXCMD)

version:
	$(Q)echo CE C SDK Version $(VERSION)

.PHONY: all clean version gfx debug
