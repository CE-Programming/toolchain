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

include $(CURDIR)/../common.mk

TARGETS := static shared linked

WILDCARD_H := $(wildcard *.h c++/*[^~\#])

all: $(TARGETS)

$(TARGETS):
	$(Q)$(MAKE) -C $@ V=$(V)

install: $(addprefix install-,$(TARGETS))
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call COPY,$(WILDCARD_H),$(INSTALL_H))

$(addprefix install-,$(TARGETS)):
	$(Q)$(MAKE) -C $(patsubst install-%,%,$@) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR) V=$(V)

clean: $(addprefix clean-,$(TARGETS))

$(addprefix clean-,$(TARGETS)):
	$(Q)$(MAKE) -C $(patsubst clean-%,%,$@) clean V=$(V)

.PHONY: all clean install
.PHONY: $(TARGETS) $(addprefix install-,$(TARGETS)) $(addprefix clean-,$(TARGETS))
