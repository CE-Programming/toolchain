# Copyright (C) 2015-2020
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

CEDEV_DIR := CEdev
CEDEV_VERSION := 9.0-devel

LINUX := 0
MACOS := 0
WINDOWS := 0

ifeq ($(OS),Windows_NT)
WINDOWS := 1
SHELL := cmd.exe
FASMG ?= fasmg.exe
EZCC ?= ez80-clang.exe
NATIVEPATH ?= $(subst /,\,$(1))
NATIVEEXE ?= $(subst /,\,$(1)).exe
MKDIR ?= ( mkdir $1 2>nul || call )
REMOVE ?= ( del /f /q $1 2>nul || call )
RMDIR ?= ( rmdir /s /q $1 2>nul || call )
COPY ?= (robocopy . $(2) $(1) /njh /njs /ndl /nc /ns) ^& exit 0
COPYDIR ?= (robocopy . $(2) $(1) /njh /njs /ndl /nc /ns) ^& exit 0
DESTDIR ?=
PREFIX ?= C:
QUOTE_ARG  ?= "$(subst ",',$1)"#'
APPEND ?= @echo.$(subst ",^",$(subst \,^\,$(subst &,^&,$(subst |,^|,$(subst >,^>,$(subst <,^<,$(subst ^,^^,$1))))))) >>$@
RELEASE_NAME = windows
else
FASMG ?= fasmg
EZCC ?= ez80-clang
NATIVEPATH ?= $(subst \,/,$(1))
NATIVEEXE ?= $(subst \,/,$(1))
MKDIR ?= mkdir -p $1
REMOVE ?= rm -f $1
RMDIR ?= rm -rf $1
COPY ?= cp $1 $2
COPYDIR ?= cp -r $1 $2
DESTDIR ?=
PREFIX ?= $(HOME)
QUOTE_ARG ?= '$(subst ','\'',$1)'#'
APPEND ?= @echo $(call QUOTE_ARG,$1) >>$@
ifeq ($(shell uname -s),Darwin)
MACOS := 1
RELEASE_NAME = macos
else
LINUX := 1
RELEASE_NAME = linux
endif
endif

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

INSTALL_PATH := $(call QUOTE_ARG,$(call NATIVEPATH,$(DESTDIR)$(PREFIX)))
INSTALL_DIR := $(call QUOTE_ARG,$(call NATIVEPATH,$(DESTDIR)$(PREFIX)/$(CEDEV_DIR)))
INSTALL_LIB := $(call NATIVEPATH,$(INSTALL_DIR)/lib/libload)
INSTALL_SHARED := $(call NATIVEPATH,$(INSTALL_DIR)/lib/shared)
INSTALL_STATIC := $(call NATIVEPATH,$(INSTALL_DIR)/lib/static)
INSTALL_LINKED := $(call NATIVEPATH,$(INSTALL_DIR)/lib/linked)
INSTALL_BIN := $(call NATIVEPATH,$(INSTALL_DIR)/bin)
INSTALL_H := $(call NATIVEPATH,$(INSTALL_DIR)/include)
INSTALL_META := $(call NATIVEPATH,$(INSTALL_DIR)/meta)

