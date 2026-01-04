# Copyright (C) 2015-2025 CE Programming
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

.SECONDARY:

all: build/allocator_standard.a build/allocator_simple.a

# --- allocator_simple

build/allocator_simple.a: build/allocator_simple.o
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $^

build/allocator_simple.o: allocator_simple.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

# --- allocator_standard

build/allocator_standard.a: build/allocator_standard.o
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $^

build/allocator_standard.o: build/allocator_standard.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

build/allocator_standard.src: allocator_standard.c
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCFLAGS) $< -o $@

clean:
	$(Q)$(call RMDIR,build)

install: all
	$(Q)$(call MKDIR,$(INSTALL_LIBC))
	$(Q)$(call COPY,$(call NATIVEPATH,build/allocator_simple.a),$(INSTALL_LIBC))
	$(Q)$(call COPY,$(call NATIVEPATH,build/allocator_standard.a),$(INSTALL_LIBC))

.PHONY: all clean install
