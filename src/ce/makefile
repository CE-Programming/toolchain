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

DEV        ?= $(call NATIVEPATH,$(PREFIX)/CEdev)
BIN        ?= $(call NATIVEPATH,$(DEV)/bin)

INSTALLLOC := $(call NATIVEPATH,$(DESTDIR)$(DEV))
LIB_LOC    := $(call NATIVEPATH,$(INSTALLLOC)/lib/shared)
LOC_H      := $(call NATIVEPATH,$(INSTALLLOC)/include)

LIB_H      := $(wildcard *.h)
SRC        := $(wildcard *.src)

ifeq ($(OS),Windows_NT)
COPY_HEADERS = (robocopy . $(LOC_H) $(LIB_H) /njh /njs /ndl /nc /ns) ^& exit 0
COPY_SRCS = (robocopy . $(LOC_H) $(SRC) /njh /njs /ndl /nc /ns) ^& exit 0
else
COPY_HEADERS = $(CP) $(LIB_H) $(LOC_H)
COPY_SRCS = $(CP) $(SRC) $(LIB_LOC)
endif

all:

install:
	$(COPY_HEADERS)
	$(COPY_SRCS)

.PHONY: all clean install
