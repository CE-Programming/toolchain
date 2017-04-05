#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
NATIVEPATH = $(subst /,\,$(1))
WINPATH    = $(NATIVEPATH)
CP         = xcopy /y
PREFIX    ?= C:
else
NATIVEPATH = $(subst \,/,$(1))
WINPATH    = $(subst \,\\,$(shell winepath --windows $(1)))
CP         = cp
PREFIX    ?= $(HOME)
endif

STATICDIR := $(call NATIVEPATH,$(CURDIR)/static)
LINKEDDIR := $(call NATIVEPATH,$(CURDIR)/linked)
SHAREDDIR := $(call NATIVEPATH,$(CURDIR)/shared)

DEV        ?= $(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?= $(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(DEV))
LIB_LOC    := $(call NATIVEPATH,$(INSTALLLOC)/lib)
LOC_H      := $(call NATIVEPATH,$(INSTALLLOC)/include/std)

LIBSTATIC   = $(call NATIVEPATH,$(wildcard $(STATICDIR)/*.lib))
LIBSHARED   = $(call NATIVEPATH,$(wildcard $(SHAREDDIR)/*.lib))
LIBLINKED   = $(call NATIVEPATH,$(wildcard $(LINKEDDIR)/*.lib))
LIB_H       = $(call NATIVEPATH,$(wildcard *.h))

RMLIBSTATIC = $(call NATIVEPATH,$(LIB_LOC)/$(notdir $(LIBSTATIC)))
RMLIBSHARED = $(call NATIVEPATH,$(LIB_LOC)/$(notdir $(LIBSHARED)))
RMLIBLINKED = $(call NATIVEPATH,$(LIB_LOC)/$(notdir $(LIBLINKED)))
RMLIBH      = $(call NATIVEPATH,$(LIB_LOC)/$(notdir $(LIB_H)))

ifeq ($(OS),Windows_NT)
COPY_HEADERS = (robocopy . $(LOC_H) $(LIB_H) /njh /njs /ndl /nc /ns) ^& exit 0
else
COPY_HEADERS = $(CP) $(LIB_H) $(LOC_H)
endif

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

install:
	$(COPY_HEADERS)
	$(CP) $(LIBSTATIC) $(LIB_LOC)
	$(CP) $(LIBSHARED) $(LIB_LOC)
	$(CP) $(LIBLINKED) $(LIB_LOC)

uninstall:
	$(RM) $(RMLIBH)
	$(RM) $(RMLIBSTATIC)
	$(RM) $(RMLIBSHARED)
	$(RM) $(RMLIBLINKED)

.PHONY: all clean all-static all-shared all-linked install uninstall

