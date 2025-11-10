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

include $(CURDIR)/../common.mk

BUILD_SRC := $(patsubst %,build/%.src,$(wildcard *.c *.cpp))

EZCFLAGS := -S -ffreestanding -Wall -Wextra -Wimplicit-float-conversion -Wimplicit-int-float-conversion -Oz
EZCFLAGS += -D_EZ80 -isystem ../libc/include -isystem ../ce/include -isystem ../fileioc -mllvm -profile-guided-section-prefix=false
EZCXXFLAGS := -S -ffreestanding -Wall -Wextra -Wimplicit-float-conversion -Wimplicit-int-float-conversion -Oz
EZCXXFLAGS += -D_EZ80 -isystem ../libcxxrt/include -isystem ../libcxx/include
EZCXXFLAGS += -isystem ../libc/include -isystem ../ce/include -isystem ../fileioc -mllvm -profile-guided-section-prefix=false
EZCXXFLAGS += -fno-exceptions -fno-rtti -std=c++20 -D_LIBCPP_BUILDING_LIBRARY -DLIBCXX_BUILDING_LIBCXXABI
EZCXXFLAGS += -fno-use-cxa-atexit
EZCXXFLAGS += -D_LIBPCPP_DEFINE_NEW_HANDLER

WILDCARD_SRC = $(wildcard *.src) $(BUILD_SRC)

all: $(BUILD_SRC)

build/%.c.src: %.c
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCFLAGS) $< -o $@

build/%.cpp.src: %.cpp
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCXXFLAGS) $< -o $@

clean:
	$(Q)$(call RMDIR,build)

install: all
	$(Q)$(call MKDIR,$(INSTALL_LIBCXXRT))
	$(Q)$(call COPY,$(call NATIVEPATH,$(WILDCARD_SRC)),$(INSTALL_LIBCXXRT))

.PHONY: all clean
