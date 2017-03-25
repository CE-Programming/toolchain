#----------------------------
# Makefile
#----------------------------

# defult make type
MAKE ?= make

# common/os specific things
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH = $(NATIVEPATH)
RM = del /f 2>nul
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH = $(shell winepath --windows $(1))
RM = rm --force
endif

TOOLSDIR   := $(call NATIVEPATH,$(CURDIR)/tools)
SRCDIR     := $(call NATIVEPATH,$(CURDIR)/src)
SPASMDIR   := $(call NATIVEPATH,$(TOOLSDIR)/spasm-ng)
CONVHEXDIR := $(call NATIVEPATH,$(TOOLSDIR)/convhex)
CONVPNGDIR := $(call NATIVEPATH,$(TOOLSDIR)/convpng)

CEDIR      := $(call NATIVEPATH,$(SRCDIR)/ce)
STDDIR      := $(call NATIVEPATH,$(SRCDIR)/std)

SPASM      := $(call NATIVEPATH,$(SPASMDIR)/spasm)
CONVHEX    := $(call NATIVEPATH,$(CONVHEXDIR)/convhex)
CONVPNG    := $(call NATIVEPATH,$(CONVPNGDIR)/convpng)

BIN        := $(call NATIVEPATH,$(TOOLSDIR)/zds)

GRAPHXDIR  := $(call NATIVEPATH,$(SRCDIR)/graphx)
KEYPADCDIR := $(call NATIVEPATH,$(SRCDIR)/keypadc)
FILEIOCDIR := $(call NATIVEPATH,$(SRCDIR)/fileioc)

all: $(SPASM) $(CONVHEX) $(CONVPNG) all-graphx all-fileioc all-keypadc all-ce all-std

#----------------------------
# tool rules
#----------------------------
$(SPASM) $(CONVHEX) $(CONVPNG):
	$(MAKE) -C $(dir $@)
	
clean: clean-graphx clean-fileioc clean-keypadc clean-ce clean-std
	$(MAKE) -C $(SPASMDIR) clean
	$(MAKE) -C $(CONVHEXDIR) clean
	$(MAKE) -C $(CONVPNGDIR) clean
#----------------------------

#----------------------------
# ce rules
#----------------------------
all-ce:
	$(MAKE) -C $(CEDIR) BIN=$(BIN)
clean-ce:
	$(MAKE) -C $(CEDIR) clean
#----------------------------

#----------------------------
# std rules
#----------------------------
all-std:
	$(MAKE) -C $(STDDIR) BIN=$(BIN)
clean-std:
	$(MAKE) -C $(STDDIR) clean
#----------------------------

#----------------------------
# graphx rules
#----------------------------
all-graphx: $(SPASM)
	$(MAKE) -C $(GRAPHXDIR) SPASM=$(SPASM) BIN=$(BIN)

clean-graphx:
	$(MAKE) -C $(GRAPHXDIR) clean
#----------------------------

#----------------------------
# fileioc rules
#----------------------------
all-fileioc: $(SPASM)
	$(MAKE) -C $(FILEIOCDIR) SPASM=$(SPASM) BIN=$(BIN)

clean-fileioc:
	$(MAKE) -C $(FILEIOCDIR) clean
#----------------------------

#----------------------------
# keypadc rules
#----------------------------
all-keypadc: $(SPASM)
	$(MAKE) -C $(KEYPADCDIR) SPASM=$(SPASM) BIN=$(BIN)

clean-keypadc:
	$(MAKE) -C $(KEYPADCDIR) clean
#----------------------------

.PHONY: all clean all-graphx clean-graphx all-fileioc clean-fileioc all-keypadc clean-keypadc

