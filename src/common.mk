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

GIT_SHA = $(shell git describe --abbrev=8 --dirty --always --tags)

CEDEV_VERSION := $(GIT_SHA)

LINUX := 0
MACOS := 0
WINDOWS := 0

empty :=
space := $(empty) $(empty)
comma := ,
define newline

$(empty)
endef

V ?= 0
ifeq ($(V),0)
Q = @
else
Q =
endif

ifeq ($(OS),Windows_NT)
WINDOWS := 1
SHELL := cmd.exe
FASMG ?= fasmg.exe
EZCC ?= ez80-clang.exe
NULL ?= nul
NATIVEPATH ?= $(subst /,\,$1)
NATIVEEXE ?= $(NATIVEPATH).exe
MKDIR ?= ( mkdir $1 2>nul || call )
REMOVE ?= ( del /f /q $1 2>nul || call )
RMDIR ?= ( rmdir /s /q $1 2>nul || call )
COPY ?= ( for %%a in ($(subst $(space),$(comma) ,$1)) do xcopy %%a $2 /Q /Y /I /K 1>nul 2>nul || call )
COPYDIR ?= ( xcopy $1 $2 /S /Q /Y /I /K 1>nul 2>nul || call )
QUOTE_ARG  ?= "$(subst ",',$1)"#'
APPEND ?= $(Q)echo.$(subst ",^",$(subst \,^\,$(subst &,^&,$(subst |,^|,$(subst >,^>,$(subst <,^<,$(subst ^,^^,$1))))))) >>$@
RELEASE_NAME = windows
else
FASMG ?= fasmg
EZCC ?= ez80-clang
NULL ?= /dev/null
NATIVEPATH ?= $(subst \,/,$1)
NATIVEEXE ?= $(NATIVEPATH)
MKDIR ?= mkdir -p $1
REMOVE ?= rm -f $1
RMDIR ?= rm -rf $1
COPY ?= cp $1 $2
COPYDIR ?= cp -r $1 $2
QUOTE_ARG ?= '$(subst ','\'',$1)'#'
APPEND ?= $(Q)echo $(call QUOTE_ARG,$1) >>$@
ifeq ($(shell uname -s),Darwin)
MACOS := 1
RELEASE_NAME = macos
else
LINUX := 1
RELEASE_NAME = linux
endif
endif

INSTALL_DIR := $(patsubst %/,%,$(subst \,/,$(DESTDIR)))/$(PREFIX)
INSTALL_PATH := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)))
INSTALL_EXAMPLES := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/examples))
INSTALL_LIB := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/libload))
INSTALL_CRT := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/crt))
INSTALL_LIBC := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/libc))
INSTALL_LIBCXX := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/libcxx))
INSTALL_LIBCXXRT := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/libcxxrt))
INSTALL_SOFTFLOAT := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/softfloat))
INSTALL_CE := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/ce))
INSTALL_BIN := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/bin))
INSTALL_H := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include))
INSTALL_TI_H := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/ti))
INSTALL_HW_H := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/sys))
INSTALL_CXX_H := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++))
INSTALL_CXX_TI_H := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/ti))
INSTALL_CXX_HW_H := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/sys))
INSTALL_META := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/meta))

INSTALL_ALGORITHM := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__algorithm))
INSTALL_ALGORITHM_PSTL := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__algorithm/pstl_backends))
INSTALL_ALGORITHM_PSTL_CPU := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__algorithm/pstl_backends/cpu_backends))
INSTALL_ATOMIC := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__atomic))
INSTALL_BIT := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__bit))
INSTALL_CHARCONV := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__charconv))
INSTALL_CHRONO := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__chrono))
INSTALL_COMPARE := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__compare))
INSTALL_CONCEPTS := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__concepts))
INSTALL_CONDITION_VARIABLE := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__condition_variable))
INSTALL_CONFIGURATION := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__configuration))
INSTALL_COROUTINE := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__coroutine))
INSTALL_CSTDDEF := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__cstddef))
INSTALL_DEBUG_UTILS := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__debug_utils))
INSTALL_EXCEPTION := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__exception))
INSTALL_EXPECTED := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__expected))
INSTALL_FILESYSTEM := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__filesystem))
INSTALL_FLAT_MAP := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__flat_map))
INSTALL_FLAT_SET := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__flat_set))
INSTALL_FORMAT := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__format))
INSTALL_FUNCTIONAL := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__functional))
INSTALL_FWD := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__fwd))
INSTALL_IOS := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__ios))
INSTALL_ITERATOR := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__iterator))
INSTALL_LOCALE_DIR := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__locale_dir))
INSTALL_LOCALE_BASE_API := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__locale_dir/locale_base_api))
INSTALL_MATH := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__math))
INSTALL_MDSPAN := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__mdspan))
INSTALL_MEMORY := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__memory))
INSTALL_MEMORY_RESOURCE := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__memory_resource))
INSTALL_MUTEX := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__mutex))
INSTALL_NEW := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__new))
INSTALL_NUMERIC := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__numeric))
INSTALL_OSTREAM := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__ostream))
INSTALL_RANDOM := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__random))
INSTALL_RANGES := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__ranges))
INSTALL_STOP_TOKEN := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__stop_token))
INSTALL_STRING := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__string))
INSTALL_SUPPORT_DIR := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__support))
INSTALL_SUPPORT_XLOCALE := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__support/xlocale))
INSTALL_SYSTEM_ERROR := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__system_error))
INSTALL_THREAD := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__thread))
INSTALL_TUPLE := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__tuple))
INSTALL_TYPE_TRAITS := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__type_traits))
INSTALL_UTILITY := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__utility))
INSTALL_VARIANT := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__variant))
INSTALL_VECTOR := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++/__vector))
INSTALL_DIR := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)))
