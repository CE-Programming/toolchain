# Copyright (C) 2015-2024 CE Programming
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

include $(CURDIR)/../common.mk

LIB_SRC := graphy.asm
LIB_LIB := graphy.lib
LIB_8XV := graphy.8xv
LIB_H := graphy.h

EZCFLAGS := -Wall -Wextra -Wshadow -Oz
EZCFLAGS += -D_EZ80 -isystem ../libc/include

all: $(LIB_8XV)

build/graphy.c.asm: graphy.c
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCFLAGS) graphy.c

$(LIB_8XV): $(LIB_SRC)
	$(Q)$(FASMG) $< $@

clean:
	$(Q)$(call REMOVE,$(LIB_LIB) $(LIB_8XV))
	$(Q)$(call RMDIR,build)

install: all
	$(Q)$(call MKDIR,$(INSTALL_LIB))
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call COPY,$(LIB_LIB),$(INSTALL_LIB))
	$(Q)$(call COPY,$(LIB_H),$(INSTALL_H))

.PHONY: all clean install

