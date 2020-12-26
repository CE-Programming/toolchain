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

include $(CURDIR)/../../src/common.mk

INCLUDE_DIR := $(call NATIVEPATH,../../src/include)
INCLUDE_SRC := $(addprefix $(call NATIVEPATH,fasmg-ez80/), commands.alm ez80.alm ez80.inc tiformat.inc)
INSTALL_SRC := $(addprefix $(call NATIVEPATH,fasmg-ez80/), commands.alm ez80.alm ld.alm)

all:
	$(Q)$(call COPY,$(INCLUDE_SRC),$(INCLUDE_DIR))

install:
	$(Q)$(call MKDIR,$(INSTALL_META))
	$(Q)$(call MKDIR,$(INSTALL_BIN))
	$(Q)$(call COPY,$(INSTALL_SRC),$(INSTALL_META))

.PHONY: all install
