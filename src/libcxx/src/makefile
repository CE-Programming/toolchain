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

EZCXXFLAGS += -std=gnu++23
EZCXXFLAGS += -O1
EZCXXFLAGS += -D_LIBCPP_BUILDING_LIBRARY -DLIBCXX_BUILDING_LIBCXXABI
EZCXXFLAGS += -fno-use-cxa-atexit
EZCXXFLAGS += -D_LIBPCPP_DEFINE_NEW_HANDLER
EZCXXFLAGS += -Iinclude
EZCXXFLAGS += -I./

OBJECTS =
OBJECTS += $(patsubst %.src,build/%.o,$(wildcard *.src))

# libcxxrt base

OBJECTS += build/algorithm.cpp.o
OBJECTS += build/any.cpp.o
OBJECTS += build/bind.cpp.o
OBJECTS += build/call_once.cpp.o
OBJECTS += build/charconv.cpp.o
OBJECTS += build/chrono.cpp.o
OBJECTS += build/error_category.cpp.o
OBJECTS += build/exception.cpp.o
OBJECTS += build/expected.cpp.o
OBJECTS += build/functional.cpp.o
OBJECTS += build/hash.cpp.o
OBJECTS += build/legacy_pointer_safety.cpp.o
OBJECTS += build/memory.cpp.o
OBJECTS += build/memory_resource.cpp.o
OBJECTS += build/new_handler.cpp.o
OBJECTS += build/new_helpers.cpp.o
OBJECTS += build/optional.cpp.o
OBJECTS += build/print.cpp.o
OBJECTS += build/random_shuffle.cpp.o
OBJECTS += build/stdexcept.cpp.o
OBJECTS += build/string.cpp.o
OBJECTS += build/system_error.cpp.o
OBJECTS += build/typeinfo.cpp.o
OBJECTS += build/valarray.cpp.o
OBJECTS += build/variant.cpp.o
OBJECTS += build/vector.cpp.o
OBJECTS += build/verbose_abort.cpp.o

# LIBCXX_ENABLE_NEW_DELETE_DEFINITIONS

OBJECTS += build/new.cpp.o

# LIBCXX_ENABLE_LOCALIZATION

OBJECTS += build/fstream.cpp.o
OBJECTS += build/ios.cpp.o
OBJECTS += build/ios.instantiations.cpp.o
OBJECTS += build/iostream.cpp.o
OBJECTS += build/locale.cpp.o
OBJECTS += build/ostream.cpp.o
OBJECTS += build/regex.cpp.o
OBJECTS += build/strstream.cpp.o

CXXRT_LIB := build/libcxxrt.a

.SECONDARY:

all: $(CXXRT_LIB)

$(CXXRT_LIB): $(OBJECTS)
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $^

build/%.cpp.o: build/%.cpp.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

build/%.cpp.src: %.cpp
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCXXFLAGS) $< -o $@

clean:
	$(Q)$(call RMDIR,build)

install: all
	$(Q)$(call MKDIR,$(INSTALL_LIBCXX))
	$(Q)$(call COPY,$(call NATIVEPATH,$(CXXRT_LIB)),$(INSTALL_LIBCXX))

.PHONY: all clean install
