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

include $(CURDIR)/../../common.mk

OBJECTS_DEFAULT = build/nanoprintf_default.c.o
OBJECTS_NOFLOAT = build/nanoprintf_nofloat.c.o
OBJECTS_LONGDOUBLE = build/nanoprintf_longdouble.c.o

LIB_NANOPRINTF_DEFAULT := libnanoprintf_default.a
LIB_NANOPRINTF_NOFLOAT := libnanoprintf_nofloat.a
LIB_NANOPRINTF_LONGDOUBLE := libnanoprintf_longdouble.a

.SECONDARY:

all: build/$(LIB_NANOPRINTF_DEFAULT) build/$(LIB_NANOPRINTF_NOFLOAT) build/$(LIB_NANOPRINTF_LONGDOUBLE)

build/$(LIB_NANOPRINTF_DEFAULT): $(OBJECTS_DEFAULT)
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $^

build/$(LIB_NANOPRINTF_NOFLOAT): $(OBJECTS_NOFLOAT)
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $^

build/$(LIB_NANOPRINTF_LONGDOUBLE): $(OBJECTS_LONGDOUBLE)
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $^

build/%.c.o: build/%.c.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

build/%.c.src: %.c
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCFLAGS) $< -o $@

clean:
	$(Q)$(call RMDIR,build)

install: all
	$(Q)$(call MKDIR,$(INSTALL_LIBC))
	$(Q)$(call COPY,$(call NATIVEPATH,build/$(LIB_NANOPRINTF_DEFAULT)),$(INSTALL_LIBC))
	$(Q)$(call COPY,$(call NATIVEPATH,build/$(LIB_NANOPRINTF_NOFLOAT)),$(INSTALL_LIBC))
	$(Q)$(call COPY,$(call NATIVEPATH,build/$(LIB_NANOPRINTF_LONGDOUBLE)),$(INSTALL_LIBC))

.PHONY: all clean install
