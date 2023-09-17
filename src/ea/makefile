# Copyright (C) 2015-2023 CE Programming
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

BUILD := $(call NATIVEPATH,EASTL/build)
# TODO: atomic
BUILD_SRC := $(filter-out EASTL/build/atomic.cpp.src,$(patsubst EASTL/source/%,EASTL/build/%.src,$(wildcard EASTL/source/*.c EASTL/source/*.cpp)))

EZCFLAGS := -S -ffreestanding -Wall -Wextra -Oz
EZCFLAGS += -D_EZ80 -isystem ../ce/include -isystem ../libc/include -mllvm -profile-guided-section-prefix=false
EZCFLAGS += -DEASTL_USER_CONFIG_HEADER="<__EASTL_user_config.h>"
EZCXXFLAGS := $(EZCFLAGS) -fno-exceptions -fno-rtti -fno-use-cxa-atexit
EZCXXFLAGS += -isystem ../libcxx/include -isystem EABase/include/Common -isystem EASTL/include -isystem include

EZCFLAGS += -std=c17
EZCXXFLAGS += -std=c++20

CONFIG_H = include/__EASTL_user_config.h

WILDCARD_SRC = $(wildcard *.src) $(BUILD_SRC)
WILDCARD_EASTL_H := $(wildcard EASTL/include/EASTL/*.h)
WILDCARD_EASTL_BONUS_H := $(wildcard EASTL/include/EASTL/bonus/*.h)
WILDCARD_EASTL_INTERNAL_H := $(wildcard EASTL/include/EASTL/internal/*.h)
# WILDCARD_EASTL_INTERNAL_ATOMIC_H := $(wildcard EASTL/include/EASTL/internal/atomic/*.h)
WILDCARD_EABASE_H := $(wildcard EABase/include/Common/EABase/*.h)
WILDCARD_EABASE_CONFIG_H := $(wildcard EABase/include/Common/EABase/config/*.h)

all: $(BUILD_SRC)

EASTL/build/%.c.src: EASTL/source/%.c
	$(Q)$(call MKDIR,$(BUILD))
	$(Q)$(EZCC) $(EZCFLAGS) $< -o $@

EASTL/build/%.cpp.src: EASTL/source/%.cpp
	$(Q)$(call MKDIR,$(BUILD))
	$(Q)$(EZCC) $(EZCXXFLAGS) $< -o $@

clean:
	$(Q)$(call RMDIR,$(BUILD))

install: all
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call MKDIR,$(INSTALL_EABASE_H))
	$(Q)$(call MKDIR,$(INSTALL_EABASE_CONFIG_H))
	$(Q)$(call MKDIR,$(INSTALL_EASTL_H))
	$(Q)$(call MKDIR,$(INSTALL_EASTL_BONUS_H))
	$(Q)$(call MKDIR,$(INSTALL_EASTL_INTERNAL_H))
#	$(Q)$(call MKDIR,$(INSTALL_EASTL_INTERNAL_ATOMIC_H))
	$(Q)$(call MKDIR,$(INSTALL_EASTL))
	$(Q)$(call COPY,$(call NATIVEPATH,$(WILDCARD_SRC)),$(INSTALL_EASTL))
#	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_EASTL_INTERNAL_ATOMIC_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_EASTL_INTERNAL_ATOMIC_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_EASTL_INTERNAL_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_EASTL_INTERNAL_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_EASTL_BONUS_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_EASTL_BONUS_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_EASTL_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_EASTL_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_EABASE_CONFIG_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_EABASE_CONFIG_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_EABASE_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_EABASE_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(CONFIG_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_H))

.PHONY: all clean
