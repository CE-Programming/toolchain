#----------------------------
# Makefile
#----------------------------

# common/os specific things
ifeq ($(OS),Windows_NT)
SHELL      = cmd.exe
NATIVEPATH = $(subst /,\,$(1))
PREFIX    ?= C:
else
NATIVEPATH = $(subst \,/,$(1))
PREFIX    ?= $(HOME)
endif

FILEIODIR := $(CURDIR)/fileio
STATICDIR := $(CURDIR)/static
LINKEDDIR := $(CURDIR)/linked
SHAREDDIR := $(CURDIR)/shared

DEV        ?= $(PREFIX)/CEdev
BIN        ?= $(PREFIX)/CEdev/bin

LIB_LOC    := $(DESTDIR)$(DEV)/lib
LOC_H      := $(DESTDIR)$(DEV)/include
LIB_H       = $(wildcard *.h *.hpp)

# windows is trash at copying files, so just do it manually
ifeq ($(OS),Windows_NT)
COPY_HEADERS   = xcopy /y *.h* $(call NATIVEPATH,$(LOC_H))
COPY_LIBFILEIO = cd $(call NATIVEPATH,$(FILEIODIR)/build) && xcopy /y *.src $(call NATIVEPATH,$(LIB_LOC)/fileio)
COPY_LIBSTATIC = cd $(call NATIVEPATH,$(STATICDIR)) && xcopy /y *.src $(call NATIVEPATH,$(LIB_LOC)/static) && \
                 cd build && xcopy /y *.src $(call NATIVEPATH,$(LIB_LOC)/static)
COPY_LIBSHARED = cd $(call NATIVEPATH,$(SHAREDDIR)) && xcopy /y *.src $(call NATIVEPATH,$(LIB_LOC)/shared) && \
                 cd build && xcopy /y *.src $(call NATIVEPATH,$(LIB_LOC)/shared)
COPY_LIBLINKED = cd $(call NATIVEPATH,$(LINKEDDIR)) && xcopy /y *.src $(call NATIVEPATH,$(LIB_LOC)/linked)
else
LIBFILEIO_C = $(wildcard $(FILEIODIR)/*.c)
LIBSTATIC_C = $(wildcard $(STATICDIR)/*.c)
LIBSHARED_C = $(wildcard $(SHAREDDIR)/*.c)
LIBLINKED_C = $(wildcard $(LINKEDDIR)/*.c)
LIBFILEIO   = $(wildcard $(FILEIODIR)/*.src) $(LIBFILEIO_C:$(FILEIODIR)/%.c=$(FILEIODIR)/build/%.src)
LIBSTATIC   = $(wildcard $(STATICDIR)/*.src) $(LIBSTATIC_C:$(STATICDIR)/%.c=$(STATICDIR)/build/%.src)
LIBSHARED   = $(wildcard $(SHAREDDIR)/*.src) $(LIBSHARED_C:$(SHAREDDIR)/%.c=$(SHAREDDIR)/build/%.src)
LIBLINKED   = $(wildcard $(LINKEDDIR)/*.src) $(LIBLINKED_C:$(LINKEDDIR)/%.c=$(LINKEDDIR)/build/%.src)

COPY_HEADERS = cp $(call NATIVEPATH,$(LIB_H)) $(call NATIVEPATH,$(LOC_H))
COPY_LIBFILEIO = cp $(call NATIVEPATH,$(LIBFILEIO)) $(call NATIVEPATH,$(LIB_LOC)/fileio)
COPY_LIBSTATIC = cp $(call NATIVEPATH,$(LIBSTATIC)) $(call NATIVEPATH,$(LIB_LOC)/static)
COPY_LIBSHARED = cp $(call NATIVEPATH,$(LIBSHARED)) $(call NATIVEPATH,$(LIB_LOC)/shared)
COPY_LIBLINKED = cp $(call NATIVEPATH,$(LIBLINKED)) $(call NATIVEPATH,$(LIB_LOC)/linked)
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

install: all
	$(COPY_HEADERS)
	$(COPY_LIBFILEIO)
	$(COPY_LIBSTATIC)
	$(COPY_LIBSHARED)
	$(COPY_LIBLINKED)

.PHONY: all clean install