# Copyright (C) 2015-2020
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

include $(CURDIR)/../../common.mk

WILDCARD_H := $(wildcard *.h *.hpp)
WILDCARD_C := $(wildcard *.c)
BUILD_SRC := $(addprefix build/,$(WILDCARD_C:%.c=%.src))

EZCFLAGS := -S -ffreestanding -Wall -Wextra -Oz
EZCFLAGS += -Dreentrant= -D_EZ80 -isystem ..

WILDCARD_SRC = $(wildcard *.src) $(patsubst %.c,build/%.src,$(wildcard *.c))

all: $(BUILD_SRC)

build/%.src: %.c
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCFLAGS) $< -o $@

clean:
	$(Q)$(call RMDIR,build)

install: all
	$(Q)$(call MKDIR,$(INSTALL_LINKED))
	$(Q)$(call COPY,$(WILDCARD_SRC),$(INSTALL_LINKED))

.PHONY: all clean

