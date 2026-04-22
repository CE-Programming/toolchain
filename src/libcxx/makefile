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

EZCXXFLAGS += -std=gnu++23
EZCXXFLAGS += -Oz
EZCXXFLAGS += -D_LIBCPP_BUILDING_LIBRARY
EZCXXFLAGS += -DLIBCXX_BUILDING_LIBCXXABI
EZCXXFLAGS += -D_LIBPCPP_DEFINE_NEW_HANDLER
EZCXXFLAGS += -fno-use-cxa-atexit

OBJECTS =
OBJECTS += $(patsubst %.c,build/%.c.o,$(wildcard *.c))
OBJECTS += $(patsubst %.cpp,build/%.cpp.o,$(wildcard *.cpp))
OBJECTS += $(patsubst %.src,build/%.o,$(wildcard *.src))

SRC_OBJECTS := $(addprefix src/,$(shell $(MAKE) -s -C src print-objects))
ABI_OBJECTS := $(addprefix abi/,$(shell $(MAKE) -s -C abi print-objects))

CXX_LIB := build/libcxx.a

.SECONDARY:

all: $(CXX_LIB)

$(CXX_LIB): src-build abi-build $(OBJECTS)
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $(OBJECTS) $(SRC_OBJECTS) $(ABI_OBJECTS)

src-build:
	$(Q)$(MAKE) -C src all

abi-build:
	$(Q)$(MAKE) -C abi all

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
	$(MAKE) -C src clean
	$(MAKE) -C abi clean

install: all
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call MKDIR,$(INSTALL_CXX_H))
	$(Q)$(call MKDIR,$(INSTALL_LIBCXX))
	$(Q)$(call COPY,$(call NATIVEPATH,$(CXX_LIB)),$(INSTALL_LIBCXX))
	$(Q)$(call COPYDIR,$(call NATIVEPATH,include),$(INSTALL_CXX_H))

.PHONY: all clean install src-build abi-build
