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
EZCXXFLAGS += -Oz
EZCXXFLAGS += -D_LIBCPP_BUILDING_LIBRARY
EZCXXFLAGS += -D_LIBPCPP_DEFINE_NEW_HANDLER
EZCXXFLAGS += -DLIBCXX_BUILDING_LIBCXXABI
EZCXXFLAGS += -D_LIBCXXABI_HAS_NO_THREADS
EZCXXFLAGS += -fno-use-cxa-atexit
EZCXXFLAGS += -Iinclude
EZCXXFLAGS += -I./
EZCXXFLAGS += -I../src

OBJECTS =
OBJECTS += $(patsubst %.src,build/%.o,$(wildcard *.src))

# libcxxabi base

OBJECTS += build/cxa_aux_runtime.cpp.o
OBJECTS += build/cxa_default_handlers.cpp.o
OBJECTS += build/cxa_demangle.cpp.o
OBJECTS += build/cxa_exception_storage.cpp.o
OBJECTS += build/cxa_guard.cpp.o
OBJECTS += build/cxa_handlers.cpp.o
OBJECTS += build/cxa_vector.cpp.o
OBJECTS += build/cxa_virtual.cpp.o
OBJECTS += build/stdlib_exception.cpp.o
OBJECTS += build/stdlib_stdexcept.cpp.o
OBJECTS += build/stdlib_typeinfo.cpp.o
OBJECTS += build/abort_message.cpp.o
OBJECTS += build/fallback_malloc.cpp.o
# OBJECTS += build/private_typeinfo.cpp.o

# LIBCXXABI_ENABLE_NEW_DELETE_DEFINITIONS

OBJECTS += build/stdlib_new_delete.cpp.o

# enable exceptions

# OBJECTS += build/cxa_exception.cpp.o
# OBJECTS += build/cxa_personality.cpp

# disable exceptions

OBJECTS += build/cxa_noexception.cpp.o

.SECONDARY:

all: $(OBJECTS)

build/%.cpp.o: build/%.cpp.src
	$(Q)$(call MKDIR,$(call NATIVEPATH,$(@D)))
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

build/%.cpp.src: %.cpp
	$(Q)$(call MKDIR,$(call NATIVEPATH,$(@D)))
	$(Q)$(EZCC) $(EZCXXFLAGS) $< -o $@

clean:
	$(Q)$(call RMDIR,build)

install: all
	$(Q)$(NOOP)

print-objects:
	@printf '%s\n' $(OBJECTS)

.PHONY: all clean install print-objects
