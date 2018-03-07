#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      = cmd.exe
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

FILEIODIR := $(call NATIVEPATH,$(CURDIR)/fileio)
STATICDIR := $(call NATIVEPATH,$(CURDIR)/static)
LINKEDDIR := $(call NATIVEPATH,$(CURDIR)/linked)
SHAREDDIR := $(call NATIVEPATH,$(CURDIR)/shared)

DEV        ?= $(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?= $(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(DEV))
LIB_LOC    := $(call NATIVEPATH,$(INSTALLLOC)/lib)
LOC_H      := $(call NATIVEPATH,$(INSTALLLOC)/include)

LIBFILEIO   = $(call NATIVEPATH,$(wildcard $(FILEIODIR)/*.src))
LIBSTATIC   = $(call NATIVEPATH,$(wildcard $(STATICDIR)/*.src))
LIBSHARED   = $(call NATIVEPATH,$(wildcard $(SHAREDDIR)/*.src))
LIBLINKED   = $(call NATIVEPATH,$(wildcard $(LINKEDDIR)/*.src))
LIB_H       = $(call NATIVEPATH,$(wildcard *.h))

ifeq ($(OS),Windows_NT)
COPY_HEADERS = (robocopy . $(LOC_H) $(LIB_H) /njh /njs /ndl /nc /ns) ^& exit 0
COPY_LIBFILEIO = (robocopy $(FILEIODIR) $(call NATIVEPATH,$(LIB_LOC)/fileio) $(notdir $(LIBFILEIO)) /njh /njs /ndl /nc /ns) ^& exit 0
COPY_LIBSTATIC = (robocopy $(STATICDIR) $(call NATIVEPATH,$(LIB_LOC)/static) $(notdir $(LIBSTATIC)) /njh /njs /ndl /nc /ns) ^& exit 0
COPY_LIBSHARED = (robocopy $(SHAREDDIR) $(call NATIVEPATH,$(LIB_LOC)/shared) $(notdir $(LIBSHARED)) /njh /njs /ndl /nc /ns) ^& exit 0
COPY_LIBLINKED = (robocopy $(LINKEDDIR) $(call NATIVEPATH,$(LIB_LOC)/linked) $(notdir $(LIBLINKED)) /njh /njs /ndl /nc /ns) ^& exit 0
else
COPY_HEADERS = $(CP) $(LIB_H) $(LOC_H)
COPY_LIBFILEIO = $(CP) $(LIBFILEIO) $(call NATIVEPATH,$(LIB_LOC)/fileio)
COPY_LIBSTATIC = $(CP) $(LIBSTATIC) $(call NATIVEPATH,$(LIB_LOC)/static)
COPY_LIBSHARED = $(CP) $(LIBSHARED) $(call NATIVEPATH,$(LIB_LOC)/shared)
COPY_LIBLINKED = $(CP) $(LIBLINKED) $(call NATIVEPATH,$(LIB_LOC)/linked)
endif

all:
	$(MAKE) -C $(FILEIODIR) BIN=$(BIN)
	$(MAKE) -C $(STATICDIR) BIN=$(BIN)
#	$(MAKE) -C $(LINKEDDIR) BIN=$(BIN) # nothing to do
	$(MAKE) -C $(SHAREDDIR) BIN=$(BIN)

clean:
	$(MAKE) -C $(FILEIODIR) $(MAKECMDGOALS)
	$(MAKE) -C $(SHAREDDIR) $(MAKECMDGOALS)
#	$(MAKE) -C $(LINKEDDIR) $(MAKECMDGOALS) # nothing to do
	$(MAKE) -C $(STATICDIR) $(MAKECMDGOALS)

install:
	$(COPY_HEADERS)
	$(COPY_LIBFILEIO)
	$(COPY_LIBSTATIC)
	$(COPY_LIBSHARED)
	$(COPY_LIBLINKED)

.PHONY: all clean install
