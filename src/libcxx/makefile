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
EZCXXFLAGS += -D_EZ80 -isystem ../libcxx/include
EZCXXFLAGS += -isystem ../libc/include -isystem ../ce/include -isystem ../fileioc -mllvm -profile-guided-section-prefix=false
EZCXXFLAGS += -fno-exceptions -fno-rtti -std=c++20 -D_LIBCPP_BUILDING_LIBRARY -DLIBCXX_BUILDING_LIBCXXABI
EZCXXFLAGS += -fno-use-cxa-atexit

WILDCARD_SRC = $(wildcard *.src) $(BUILD_SRC)
LIBCXX_H := include/.

ALGORITHM_H := include/__algorithm
ALGORITHM_PSTL_H := include/__algorithm/pstl_backends
ALGORITHM_PSTL_CPU_H := include/__algorithm/pstl_backends/cpu_backends
ATOMIC_H := include/__atomic
BIT_H := include/__bit
CHARCONV_H := include/__charconv
CHRONO_H := include/__chrono
COMPARE_H := include/__compare
CONCEPTS_H := include/__concepts
CONDITION_VARIABLE_H := include/__condition_variable
CONFIGURATION_H := include/__configuration
COROUTINE_H := include/__coroutine
CSTDDEF_H := include/__cstddef
DEBUG_UTILS_H := include/__debug_utils
EXCEPTION_H := include/__exception
EXPECTED_H := include/__expected
FILESYSTEM_H := include/__filesystem
FLAT_MAP_H := include/__flat_map
FLAT_SET_H := include/__flat_set
FORMAT_H := include/__format
FUNCTIONAL_H := include/__functional
FWD_H := include/__fwd
IOS_H := include/__ios
ITERATOR_H := include/__iterator
LOCALE_DIR_H := include/__locale_dir
LOCALE_BASE_API_H := include/__locale_dir/locale_base_api
MATH_H := include/__math
MDSPAN_H := include/__mdspan
MEMORY_H := include/__memory
MEMORY_RESOURCE_H := include/__memory_resource
MUTEX_H := include/__mutex
NEW_H := include/__new
NUMERIC_H := include/__numeric
OSTREAM_H := include/__ostream
RANDOM_H := include/__random
RANGES_H := include/__ranges
STOP_TOKEN_H := include/__stop_token
STRING_H := include/__string
SUPPORT_DIR_H := include/__support
SUPPORT_XLOCALE_H := include/__support/xlocale
SYSTEM_ERROR_H := include/__system_error
THREAD_H := include/__thread
TUPLE_H := include/__tuple
TYPE_TRAITS_H := include/__type_traits
UTILITY_H := include/__utility
VARIANT_H := include/__variant
VECTOR_H := include/__vector

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
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call MKDIR,$(INSTALL_CXX_H))
	$(Q)$(call MKDIR,$(INSTALL_LIBCXX))
	$(Q)$(call MKDIR,$(INSTALL_ALGORITHM))
	$(Q)$(call MKDIR,$(INSTALL_ALGORITHM_PSTL))
	$(Q)$(call MKDIR,$(INSTALL_ALGORITHM_PSTL_CPU))
	$(Q)$(call MKDIR,$(INSTALL_ATOMIC))
	$(Q)$(call MKDIR,$(INSTALL_BIT))
	$(Q)$(call MKDIR,$(INSTALL_CHARCONV))
	$(Q)$(call MKDIR,$(INSTALL_CHRONO))
	$(Q)$(call MKDIR,$(INSTALL_COMPARE))
	$(Q)$(call MKDIR,$(INSTALL_CONCEPTS))
	$(Q)$(call MKDIR,$(INSTALL_CONDITION_VARIABLE))
	$(Q)$(call MKDIR,$(INSTALL_CONFIGURATION))
	$(Q)$(call MKDIR,$(INSTALL_COROUTINE))
	$(Q)$(call MKDIR,$(INSTALL_CSTDDEF))
	$(Q)$(call MKDIR,$(INSTALL_DEBUG_UTILS))
	$(Q)$(call MKDIR,$(INSTALL_EXCEPTION))
	$(Q)$(call MKDIR,$(INSTALL_EXPECTED))
	$(Q)$(call MKDIR,$(INSTALL_FILESYSTEM))
	$(Q)$(call MKDIR,$(INSTALL_FLAT_MAP))
	$(Q)$(call MKDIR,$(INSTALL_FLAT_SET))
	$(Q)$(call MKDIR,$(INSTALL_FORMAT))
	$(Q)$(call MKDIR,$(INSTALL_FUNCTIONAL))
	$(Q)$(call MKDIR,$(INSTALL_FWD))
	$(Q)$(call MKDIR,$(INSTALL_IOS))
	$(Q)$(call MKDIR,$(INSTALL_ITERATOR))
	$(Q)$(call MKDIR,$(INSTALL_LOCALE_DIR))
	$(Q)$(call MKDIR,$(INSTALL_LOCALE_BASE_API))
	$(Q)$(call MKDIR,$(INSTALL_MATH))
	$(Q)$(call MKDIR,$(INSTALL_MDSPAN))
	$(Q)$(call MKDIR,$(INSTALL_MEMORY))
	$(Q)$(call MKDIR,$(INSTALL_MEMORY_RESOURCE))
	$(Q)$(call MKDIR,$(INSTALL_MUTEX))
	$(Q)$(call MKDIR,$(INSTALL_NEW))
	$(Q)$(call MKDIR,$(INSTALL_NUMERIC))
	$(Q)$(call MKDIR,$(INSTALL_OSTREAM))
	$(Q)$(call MKDIR,$(INSTALL_RANDOM))
	$(Q)$(call MKDIR,$(INSTALL_RANGES))
	$(Q)$(call MKDIR,$(INSTALL_STOP_TOKEN))
	$(Q)$(call MKDIR,$(INSTALL_STRING))
	$(Q)$(call MKDIR,$(INSTALL_SUPPORT_DIR))
	$(Q)$(call MKDIR,$(INSTALL_SUPPORT_XLOCALE))
	$(Q)$(call MKDIR,$(INSTALL_SYSTEM_ERROR))
	$(Q)$(call MKDIR,$(INSTALL_THREAD))
	$(Q)$(call MKDIR,$(INSTALL_TUPLE))
	$(Q)$(call MKDIR,$(INSTALL_TYPE_TRAITS))
	$(Q)$(call MKDIR,$(INSTALL_UTILITY))
	$(Q)$(call MKDIR,$(INSTALL_VARIANT))
	$(Q)$(call MKDIR,$(INSTALL_VECTOR))
	$(Q)$(call COPY,$(call NATIVEPATH,$(WILDCARD_SRC)),$(INSTALL_LIBCXX))
	$(Q)$(call COPY,$(call NATIVEPATH,$(LIBCXX_H)),$(INSTALL_CXX_H))
	$(Q)$(call COPY,$(call NATIVEPATH,$(ALGORITHM_H)),$(INSTALL_ALGORITHM))
	$(Q)$(call COPY,$(call NATIVEPATH,$(ALGORITHM_PSTL_H)),$(INSTALL_ALGORITHM_PSTL))
	$(Q)$(call COPY,$(call NATIVEPATH,$(ALGORITHM_PSTL_CPU_H)),$(INSTALL_ALGORITHM_PSTL_CPU))
	$(Q)$(call COPY,$(call NATIVEPATH,$(ATOMIC_H)),$(INSTALL_ATOMIC))
	$(Q)$(call COPY,$(call NATIVEPATH,$(BIT_H)),$(INSTALL_BIT))
	$(Q)$(call COPY,$(call NATIVEPATH,$(CHARCONV_H)),$(INSTALL_CHARCONV))
	$(Q)$(call COPY,$(call NATIVEPATH,$(CHRONO_H)),$(INSTALL_CHRONO))
	$(Q)$(call COPY,$(call NATIVEPATH,$(COMPARE_H)),$(INSTALL_COMPARE))
	$(Q)$(call COPY,$(call NATIVEPATH,$(CONCEPTS_H)),$(INSTALL_CONCEPTS))
	$(Q)$(call COPY,$(call NATIVEPATH,$(CONDITION_VARIABLE_H)),$(INSTALL_CONDITION_VARIABLE))
	$(Q)$(call COPY,$(call NATIVEPATH,$(CONFIGURATION_H)),$(INSTALL_CONFIGURATION))
	$(Q)$(call COPY,$(call NATIVEPATH,$(COROUTINE_H)),$(INSTALL_COROUTINE))
	$(Q)$(call COPY,$(call NATIVEPATH,$(CSTDDEF_H)),$(INSTALL_CSTDDEF))
	$(Q)$(call COPY,$(call NATIVEPATH,$(DEBUG_UTILS_H)),$(INSTALL_DEBUG_UTILS))
	$(Q)$(call COPY,$(call NATIVEPATH,$(EXCEPTION_H)),$(INSTALL_EXCEPTION))
	$(Q)$(call COPY,$(call NATIVEPATH,$(EXPECTED_H)),$(INSTALL_EXPECTED))
	$(Q)$(call COPY,$(call NATIVEPATH,$(FILESYSTEM_H)),$(INSTALL_FILESYSTEM))
	$(Q)$(call COPY,$(call NATIVEPATH,$(FLAT_MAP_H)),$(INSTALL_FLAT_MAP))
	$(Q)$(call COPY,$(call NATIVEPATH,$(FLAT_SET_H)),$(INSTALL_FLAT_SET))
	$(Q)$(call COPY,$(call NATIVEPATH,$(FORMAT_H)),$(INSTALL_FORMAT))
	$(Q)$(call COPY,$(call NATIVEPATH,$(FUNCTIONAL_H)),$(INSTALL_FUNCTIONAL))
	$(Q)$(call COPY,$(call NATIVEPATH,$(FWD_H)),$(INSTALL_FWD))
	$(Q)$(call COPY,$(call NATIVEPATH,$(IOS_H)),$(INSTALL_IOS))
	$(Q)$(call COPY,$(call NATIVEPATH,$(ITERATOR_H)),$(INSTALL_ITERATOR))
	$(Q)$(call COPY,$(call NATIVEPATH,$(LOCALE_DIR_H)),$(INSTALL_LOCALE_DIR))
	$(Q)$(call COPY,$(call NATIVEPATH,$(LOCALE_BASE_API_H)),$(INSTALL_LOCALE_BASE_API))
	$(Q)$(call COPY,$(call NATIVEPATH,$(MATH_H)),$(INSTALL_MATH))
	$(Q)$(call COPY,$(call NATIVEPATH,$(MDSPAN_H)),$(INSTALL_MDSPAN))
	$(Q)$(call COPY,$(call NATIVEPATH,$(MEMORY_H)),$(INSTALL_MEMORY))
	$(Q)$(call COPY,$(call NATIVEPATH,$(MEMORY_RESOURCE_H)),$(INSTALL_MEMORY_RESOURCE))
	$(Q)$(call COPY,$(call NATIVEPATH,$(MUTEX_H)),$(INSTALL_MUTEX))
	$(Q)$(call COPY,$(call NATIVEPATH,$(NEW_H)),$(INSTALL_NEW))
	$(Q)$(call COPY,$(call NATIVEPATH,$(NUMERIC_H)),$(INSTALL_NUMERIC))
	$(Q)$(call COPY,$(call NATIVEPATH,$(OSTREAM_H)),$(INSTALL_OSTREAM))
	$(Q)$(call COPY,$(call NATIVEPATH,$(RANDOM_H)),$(INSTALL_RANDOM))
	$(Q)$(call COPY,$(call NATIVEPATH,$(RANGES_H)),$(INSTALL_RANGES))
	$(Q)$(call COPY,$(call NATIVEPATH,$(STOP_TOKEN_H)),$(INSTALL_STOP_TOKEN))
	$(Q)$(call COPY,$(call NATIVEPATH,$(STRING_H)),$(INSTALL_STRING))
	$(Q)$(call COPY,$(call NATIVEPATH,$(SUPPORT_DIR_H)),$(INSTALL_SUPPORT_DIR))
	$(Q)$(call COPY,$(call NATIVEPATH,$(SUPPORT_XLOCALE_H)),$(INSTALL_SUPPORT_XLOCALE))
	$(Q)$(call COPY,$(call NATIVEPATH,$(SYSTEM_ERROR_H)),$(INSTALL_SYSTEM_ERROR))
	$(Q)$(call COPY,$(call NATIVEPATH,$(THREAD_H)),$(INSTALL_THREAD))
	$(Q)$(call COPY,$(call NATIVEPATH,$(TUPLE_H)),$(INSTALL_TUPLE))
	$(Q)$(call COPY,$(call NATIVEPATH,$(TYPE_TRAITS_H)),$(INSTALL_TYPE_TRAITS))
	$(Q)$(call COPY,$(call NATIVEPATH,$(UTILITY_H)),$(INSTALL_UTILITY))
	$(Q)$(call COPY,$(call NATIVEPATH,$(VARIANT_H)),$(INSTALL_VARIANT))
	$(Q)$(call COPY,$(call NATIVEPATH,$(VECTOR_H)),$(INSTALL_VECTOR))

.PHONY: all clean
