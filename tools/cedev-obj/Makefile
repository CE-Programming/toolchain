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

include $(CURDIR)/../../src/common.mk

CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -O3 -std=c99 -Isrc -DNDEBUG -DCEDEV_VERSION="\"$(CEDEV_VERSION)\"" -flto
LDFLAGS = -flto
LIBRARIES :=

ifeq ($(OS),Windows_NT)
  TARGET ?= cedev-obj.exe
  STRIP = strip --strip-all "$1"
else
  TARGET ?= cedev-obj
  ifeq ($(shell uname -s),Darwin)
    STRIP = strip "$1"
    CFLAGS += -D_DARWIN_C_SOURCE -mmacosx-version-min=10.13
    LDFLAGS += -mmacosx-version-min=10.13
  else
    STRIP = strip --strip-all "$1"
    CFLAGS += -D_XOPEN_SOURCE=500 -static
    LDFLAGS += -static
    LIBRARIES += dl
  endif
endif

BINDIR = ./bin
OBJDIR = ./obj
SRCDIR = ./src
DEPDIR = ./src/deps
SOURCES = \
	$(SRCDIR)/main.c \
	$(SRCDIR)/elf_inspect.c

OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(BINDIR)/$(TARGET)

release: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(Q)$(call MKDIR,$(call NATIVEPATH,$(@D)))
	$(Q)$(CC) $(LDFLAGS) $(call NATIVEPATH,$^) -o $(call NATIVEPATH,$@) $(addprefix -l, $(LIBRARIES))
	$(Q)$(call STRIP,$@)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(Q)$(call MKDIR,$(call NATIVEPATH,$(@D)))
	$(Q)$(CC) -c $(call NATIVEPATH,$<) $(CFLAGS) -o $(call NATIVEPATH,$@)

clean:
	$(Q)$(call RMDIR,$(call NATIVEPATH,$(BINDIR)))
	$(Q)$(call RMDIR,$(call NATIVEPATH,$(OBJDIR)))

.PHONY: all release test clean
