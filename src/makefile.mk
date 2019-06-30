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

VERSION := 8.6

#----------------------------
# try not to edit anything below these lines unless you know what you are doing
#----------------------------

#----------------------------

# define some common makefile things
empty :=
space := $(empty) $(empty)
comma := ,

TARGET ?= $(NAME)
ICONPNG ?= $(ICON)
DEBUGMODE = NDEBUG
CCDEBUGFLAG = -nodebug

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
RM         = del /q /f 2>nul
CEDEV     ?= $(call NATIVEPATH,$(realpath ..\..))
BIN       ?= $(call NATIVEPATH,$(CEDEV)/bin)
LD         = $(call NATIVEPATH,$(BIN)/fasmg.exe)
CC         = $(call NATIVEPATH,$(BIN)/ez80cc.exe)
CV         = $(call NATIVEPATH,$(BIN)/convhex.exe)
PG         = $(call NATIVEPATH,$(BIN)/convpng.exe)
CD         = cd
CP         = copy /y
MV         = move /y >nul
NULL       = >nul 2>&1
RMDIR      = call && (if exist $1 rmdir /s /q $1)
MKDIR      = call && (if not exist $1 mkdir $1)
QUOTE_ARG  = "$(subst ",',$1)"#'
TO_LOWER   = $1
else
MAKEDIR   := $(CURDIR)
NATIVEPATH = $(subst \,/,$1)
WINPATH    = $(shell winepath -w $1)
WINRELPATH = $(subst /,\,$1)
RM         = rm -f
CEDEV     ?= $(call NATIVEPATH,$(realpath ..\..))
BIN       ?= $(call NATIVEPATH,$(CEDEV)/bin)
CC         = $(call NATIVEPATH,wine "$(BIN)/ez80cc.exe")
LD         = $(call NATIVEPATH,$(BIN)/fasmg)
CV         = $(call NATIVEPATH,$(BIN)/convhex)
PG         = $(call NATIVEPATH,$(BIN)/convpng)
CD         = cd
CP         = cp
MV         = mv
RMDIR      = rm -rf $1
MKDIR      = mkdir -p $1
QUOTE_ARG  = '$(subst ','\'',$1)'#'
TO_LOWER   = $(shell printf %s $(call QUOTE_ARG,$1) | tr [:upper:] [:lower:])
endif

FASMG_FILES    = $(subst $(space),$(comma) ,$(patsubst %,"%",$(subst ",\",$(subst \,\\,$(call NATIVEPATH,$1)))))#"
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
ICON_ASM      := iconc.src

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
LINK_CSOURCES := $(CSOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.src)
LINK_CPPSOURCES := $(CPPSOURCES:$(SRCDIR)/%=$(OBJDIR)/%.src)
LINK_ASMSOURCES := $(ASMSOURCES)

# files created to be used for linking
LINK_FILES   := $(LINK_CSOURCES) $(LINK_CPPSOURCES) $(LINK_ASMSOURCES)
LINK_LIBS    := $(wildcard $(CEDEV)/lib/libload/*.lib)
LINK_LIBLOAD := $(CEDEV)/lib/libload.lib

# check if there is an icon present that we can convert; if so, generate a recipe to build it properly
ifneq ("$(wildcard $(ICONPNG))","")
F_ICON     := $(OBJDIR)/$(ICON_ASM)
ICON_CONV  := $(PG) -c $(ICONPNG)$(comma)$(call NATIVEPATH,$(F_ICON))$(comma)$(DESCRIPTION)
LINK_ICON   = , $(call FASMG_FILES,$(F_ICON)) used
endif

# determine if output should be archived or compressed
ifeq ($(ARCHIVED),YES)
CVFLAGS += -a
endif
ifeq ($(COMPRESSED),YES)
CVFLAGS += -x
endif
ifeq ($(CLEANUP),YES)
LINK_CLEANUP = , $(call FASMG_FILES,$(F_CLEANUP)) used
endif
ifeq ($(OUTPUT_MAP),YES)
LDMAPFLAG = -i map
endif

# choose static or linked flash functions
ifeq ($(USE_FLASH_FUNCTIONS),YES)
STATIC := 0
else
STATIC := 1
endif

ifneq ("$(EXTRA_CFLAGS)","")
EXTRA_COMPILER_FLAGS := $(addprefix -define:,$(EXTRA_CFLAGS))
endif

# define the C flags used by the Zilog compiler
CFLAGS ?= \
    -noasm $(CCDEBUGFLAG) -nogenprint -keepasm -quiet $(OPT_MODE) -cpu:EZ80F91 -noreduceopt -nolistinc -nomodsect -define:_EZ80F91 -define:_EZ80 -define:$(DEBUGMODE) $(EXTRA_COMPILER_FLAGS)

# these are the linker flags, basically organized to properly set up the environment
LDFLAGS ?= \
	$(call QUOTE_ARG,$(call NATIVEPATH,$(CEDEV)/include/fasmg-ez80/ld.fasmg)) \
	-i $(call QUOTE_ARG,include $(call FASMG_FILES,$(LINKER_SCRIPT))) \
	$(LDDEBUGFLAG) \
	$(LDMAPFLAG) \
	-i $(call QUOTE_ARG,range bss $$$(BSSHEAP_LOW) : $$$(BSSHEAP_HIGH)) \
	-i $(call QUOTE_ARG,symbol __stack = $$$(STACK_HIGH)) \
	-i $(call QUOTE_ARG,locate header at $$$(INIT_LOC)) \
	-i $(call QUOTE_ARG,STATIC := $(STATIC)) \
	-i $(call QUOTE_ARG,srcs $(call FASMG_FILES,$(F_LAUNCHER)) used if libs.length$(LINK_ICON)$(LINK_CLEANUP)$(comma) $(call FASMG_FILES,$(F_STARTUP)) used$(comma) $(call FASMG_FILES,$(LINK_FILES))) \
	-i $(call QUOTE_ARG,libs $(call FASMG_FILES,$(LINK_LIBLOAD)) used if libs.length$(comma) $(call FASMG_FILES,$(LINK_LIBS)))

# this rule is trigged to build everything
all: dirs $(BINDIR)/$(TARGET8XP) ;

# this rule is trigged to build debug everything
debug: LDDEBUGFLAG = -i dbg
debug: DEBUGMODE = DEBUG
debug: CCDEBUGFLAG = -debug
debug: dirs $(BINDIR)/$(TARGET8XP) ;

dirs:
	@echo C CE SDK Version $(VERSION) && \
	$(call MKDIR,$(BINDIR)) && \
	$(call MKDIR,$(OBJDIR))

$(BINDIR)/$(TARGET8XP): $(BINDIR)/$(TARGETBIN)
	$(Q)$(CD) $(BINDIR) && \
	$(CV) $(CVFLAGS) $(notdir $<) $(notdir $@)

$(BINDIR)/$(TARGETBIN): $(LINK_FILES) $(F_ICON)
	$(Q)$(LD) $(LDFLAGS) $@

# this rule handles conversion of the icon, if it is ever updated
$(OBJDIR)/$(ICON_ASM): $(ICONPNG)
	$(Q)$(ICON_CONV)

# these rules compile the source files into object files
$(OBJDIR)/%.src: $(SRCDIR)/%.c $(USERHEADERS)
	$(Q)$(call MKDIR,$(call NATIVEPATH,$(@D))) && \
	$(CC) $(CFLAGS) $(call QUOTE_ARG,$(call WINPATH,$(addprefix $(MAKEDIR)/,$<))) && \
	$(MV) $(call QUOTE_ARG,$(call TO_LOWER,$(@F))) $(call QUOTE_ARG,$@)

clean:
	$(Q)$(call RMDIR,$(OBJDIR))
	$(Q)$(call RMDIR,$(BINDIR))
	@echo Cleaned build files.

gfx:
	$(Q)$(CD) $(GFXDIR) && convpng

version:
	@echo C SDK Version $(VERSION)

.PHONY: all clean version gfx dirs debug
