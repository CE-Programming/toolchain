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

include $(CURDIR)/../common.mk

TARGETS := sys ti

WILDCARD_SRC := $(wildcard *.src)
WILDCARD_H := $(wildcard *.h *.hpp)

all:

$(addprefix install-,$(TARGETS)):
	$(Q)$(MAKE) -C $(patsubst install-%,%,$@) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)

install: $(addprefix install-,$(TARGETS))
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call MKDIR,$(INSTALL_TI_H))
	$(Q)$(call MKDIR,$(INSTALL_HW_H))
	$(Q)$(call MKDIR,$(INSTALL_CE))
	$(Q)$(call COPY,$(WILDCARD_H),$(INSTALL_H))
	$(Q)$(call COPY,$(WILDCARD_SRC),$(INSTALL_CE))

.PHONY: all install $(addprefix install-,$(TARGETS))
