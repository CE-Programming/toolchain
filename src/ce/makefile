# Copyright (C) 2015-2024 CE Programming
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

WILDCARD_SRC = $(wildcard *.src)
WILDCARD_H = $(wildcard include/*.h)
WILDCARD_HW_H = $(wildcard include/sys/*.h)
WILDCARD_TI_H = $(wildcard include/ti/*.h)

WILDCARD_CXX_H = $(wildcard include/c++/*)
WILDCARD_CXX_TI_H = $(wildcard include/ti/c++/*)

all:

install: $(addprefix install-,$(TARGETS))
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call MKDIR,$(INSTALL_TI_H))
	$(Q)$(call MKDIR,$(INSTALL_HW_H))
	$(Q)$(call MKDIR,$(INSTALL_CE))
	$(Q)$(call MKDIR,$(INSTALL_CXX_H))
	$(Q)$(call MKDIR,$(INSTALL_CXX_TI_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_HW_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_HW_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_TI_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_TI_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_CXX_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_CXX_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_CXX_TI_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_CXX_TI_H))
	$(Q)$(call COPY,$(WILDCARD_SRC),$(INSTALL_CE))

clean:
	$(Q)$(call RMDIR,build)

.PHONY: all install clean
