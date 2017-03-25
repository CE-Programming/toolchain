#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
CEDEV     ?= C:\CEdev
BIN       ?= $(CEDEV)/bin
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath --windows $(1)))
CEDEV     ?= $(HOME)/CEdev
BIN       ?= $(CEDEV)/bin
endif

STATICDIR := $(call NATIVEPATH,$(CURDIR)/static)
LINKEDDIR := $(call NATIVEPATH,$(CURDIR)/linked)
SHAREDDIR := $(call NATIVEPATH,$(CURDIR)/shared)

all: all-static all-linked all-shared
	
all-static:
	$(MAKE) -C $(STATICDIR) BIN=$(BIN)

all-linked:
	$(MAKE) -C $(LINKEDDIR) BIN=$(BIN)

all-shared:
	$(MAKE) -C $(SHAREDDIR) BIN=$(BIN)

clean:
	$(MAKE) -C $(SHAREDDIR) clean
	$(MAKE) -C $(LINKEDDIR) clean
	$(MAKE) -C $(STATICDIR) clean

.PHONY: all clean all-static all-shared all-linked

