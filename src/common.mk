# Copyright (C) 2015-2022
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

CEDEV_DIR := CEdev
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
DESTDIR ?=
PREFIX ?= C:
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
DESTDIR ?=
PREFIX ?= $(HOME)
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

INSTALL_PATH := $(call QUOTE_ARG,$(call NATIVEPATH,$(DESTDIR)$(PREFIX)))
INSTALL_DIR := $(DESTDIR)$(PREFIX)/$(CEDEV_DIR)
INSTALL_EXAMPLES := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/examples))
INSTALL_LIB := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/libload))
INSTALL_CRT := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/crt))
INSTALL_LIBC := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/libc))
INSTALL_LIBCXX := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/libcxx))
INSTALL_CE := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/lib/ce))
INSTALL_BIN := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/bin))
INSTALL_H := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include))
INSTALL_CXX_H := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/c++))
INSTALL_TI_H := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/ti))
INSTALL_HW_H := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/include/sys))
INSTALL_META := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)/meta))
INSTALL_DIR := $(call QUOTE_ARG,$(call NATIVEPATH,$(INSTALL_DIR)))
