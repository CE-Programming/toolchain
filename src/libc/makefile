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

include $(CURDIR)/../common.mk

EZCFLAGS += -DDEBUG_FOOBAR

OBJECTS =
OBJECTS += $(patsubst %.c,build/%.c.o,$(wildcard *.c))
OBJECTS += $(patsubst %.cpp,build/%.cpp.o,$(wildcard *.cpp))
OBJECTS += $(patsubst %.src,build/%.o,$(wildcard *.src))

OBJECTS_CE =
OBJECTS_CE += $(patsubst %.c,build/%.c.ce.o,$(wildcard *.c))
OBJECTS_CE += $(patsubst %.cpp,build/%.cpp.ce.o,$(wildcard *.cpp))
OBJECTS_CE += $(patsubst %.src,build/%.ce.o,$(wildcard *.src))

.SECONDARY:

all: build/libc.a build/libc_os.a
	$(MAKE) -C allocator
	$(MAKE) -C printf

build/libc.a: $(OBJECTS)
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $^

build/%.c.src: %.c
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCFLAGS) $< -o $@

build/%.cpp.src: %.cpp
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCXXFLAGS) $< -o $@

build/%.c.o: build/%.c.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

build/%.cpp.o: build/%.cpp.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

build/%.o: %.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

# -----

build/libc_os.a: $(OBJECTS_CE)
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $^

build/%.c.ce.src: %.c
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCFLAGS) -DPREFER_OS_LIBC=1 $< -o $@

build/%.cpp.ce.src: %.cpp
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCXXFLAGS) -DPREFER_OS_LIBC=1 $< -o $@

build/%.c.ce.o: build/%.c.ce.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) --defsym PREFER_OS_LIBC=1 $< -o $@

build/%.cpp.ce.o: build/%.cpp.ce.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) --defsym PREFER_OS_LIBC=1 $< -o $@

build/%.ce.o: %.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) --defsym PREFER_OS_LIBC=1 $< -o $@

clean:
	$(Q)$(call RMDIR,build)

install: all
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call MKDIR,$(INSTALL_LIBC))
	$(Q)$(call COPY,$(call NATIVEPATH,build/libc.a),$(INSTALL_LIBC))
	$(Q)$(call COPY,$(call NATIVEPATH,build/libc_os.a),$(INSTALL_LIBC))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(wildcard include/*.h)),$(call QUOTE_ARG,$(file))),$(INSTALL_H))
	$(MAKE) -C allocator install
	$(MAKE) -C printf install

.PHONY: all clean install
