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

OBJECTS =
OBJECTS += $(patsubst %.c,build/%.c.o,$(wildcard *.c))
OBJECTS += $(patsubst %.cpp,build/%.cpp.o,$(wildcard *.cpp))
OBJECTS += $(patsubst %.src,build/%.o,$(wildcard *.src))

OBJECTS_CE =
OBJECTS_CE += $(patsubst %.c,build/%.c.ce.o,$(wildcard *.c))
OBJECTS_CE += $(patsubst %.cpp,build/%.cpp.ce.o,$(wildcard *.cpp))
OBJECTS_CE += $(patsubst %.src,build/%.ce.o,$(wildcard *.src))

.SECONDARY:

all: build/libcrt.a build/libcrt_os.a

build/libcrt.a: $(OBJECTS)
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

build/libcrt_os.a: $(OBJECTS_CE)
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $^

build/%.c.ce.src: %.c
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCFLAGS) $< -o $@

build/%.cpp.ce.src: %.cpp
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCXXFLAGS) $< -o $@

build/%.c.ce.o: build/%.c.ce.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) --defsym PREFER_OS_CRT=1 $< -o $@

build/%.cpp.ce.o: build/%.cpp.ce.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) --defsym PREFER_OS_CRT=1 $< -o $@

build/%.ce.o: %.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) --defsym PREFER_OS_CRT=1 $< -o $@

clean:
	$(Q)$(call RMDIR,build)

install: all
	$(Q)$(call MKDIR,$(INSTALL_CRT))
	$(Q)$(call COPY,$(call NATIVEPATH,build/libcrt.a),$(INSTALL_CRT))
	$(Q)$(call COPY,$(call NATIVEPATH,build/libcrt_os.a),$(INSTALL_CRT))
	$(Q)$(call COPY,$(call NATIVEPATH,crt0.S),$(INSTALL_CRT))

.PHONY: all clean install
