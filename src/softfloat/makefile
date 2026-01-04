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

EZCFLAGS += -Iinclude

WILDCARD_H := $(wildcard include/*.h)

LIB_SOFTFLOAT := build/libsoftfloat.a

.SECONDARY:

all: $(LIB_SOFTFLOAT)

$(LIB_SOFTFLOAT): $(OBJECTS)
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

clean:
	$(Q)$(call RMDIR,build)

install: all
	$(Q)$(call MKDIR,$(INSTALL_SOFTFLOAT))
	$(Q)$(call COPY,$(call NATIVEPATH,$(LIB_SOFTFLOAT)),$(INSTALL_SOFTFLOAT))

.PHONY: all clean install
