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

DESTDIR = $(CURDIR)/
PREFIX = CEdev

include $(CURDIR)/src/common.mk

LIBS := libload graphx fontlibc keypadc fileioc usbdrvce srldrvce msddrvce fatdrvce lcddrvce
SRCS := ce crt ea libc libcxx softfloat
TOOLS := fasmg convbin convimg convfont cedev-config

ifeq ($(OS),Windows_NT)
WINDOWS_COPY := $(call COPY,resources\windows\make.exe,$(INSTALL_BIN)) && $(call COPY,resources\windows\cedev.bat,$(INSTALL_DIR))
else
WINDOWS_COPY :=
endif

SRCDIR = $(call NATIVEPATH,src/$1)
TOOLSDIR = $(call NATIVEPATH,tools/$1)

all: $(TOOLS) $(SRCS) $(LIBS)

$(TOOLS): check
	$(Q)$(MAKE) -C $(call TOOLSDIR,$@)

$(SRCS):
	$(Q)$(MAKE) -C $(call SRCDIR,$@)

$(LIBS): fasmg
	$(Q)$(MAKE) -C $(call SRCDIR,$@)

install: all $(addprefix install-,$(SRCS)) $(addprefix install-,$(LIBS))
	$(Q)$(MAKE) -f linker.mk -C src -B
	$(Q)$(call MKDIR,$(INSTALL_DIR))
	$(Q)$(call MKDIR,$(INSTALL_BIN))
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call MKDIR,$(INSTALL_TI_H))
	$(Q)$(call MKDIR,$(INSTALL_HW_H))
	$(Q)$(call MKDIR,$(INSTALL_LIB))
	$(Q)$(call MKDIR,$(INSTALL_META))
	$(Q)$(call MKDIR,$(INSTALL_EXAMPLES))
	$(Q)$(call COPYDIR,$(call NATIVEPATH,examples/*),$(INSTALL_EXAMPLES))
	$(Q)$(call COPY,$(call NATIVEPATH,src/makefile.mk),$(INSTALL_META))
	$(Q)$(call COPY,$(call NATIVEPATH,src/linker_script),$(INSTALL_META))
	$(Q)$(call COPY,$(call NATIVEPATH,tools/fasmg/fasmg-ez80/commands.alm),$(INSTALL_META))
	$(Q)$(call COPY,$(call NATIVEPATH,tools/fasmg/fasmg-ez80/ez80.alm),$(INSTALL_META))
	$(Q)$(call COPY,$(call NATIVEPATH,tools/fasmg/fasmg-ez80/ld.alm),$(INSTALL_META))
	$(Q)$(call COPY,$(call NATIVEEXE,tools/convfont/convfont),$(INSTALL_BIN))
	$(Q)$(call COPY,$(call NATIVEEXE,tools/convimg/bin/convimg),$(INSTALL_BIN))
	$(Q)$(call COPY,$(call NATIVEEXE,tools/convbin/bin/convbin),$(INSTALL_BIN))
	$(Q)$(call COPY,$(call NATIVEEXE,tools/cedev-config/bin/cedev-config),$(INSTALL_BIN))
	$(Q)$(WINDOWS_COPY)

$(addprefix install-,$(SRCS)): $(TOOLS)
	$(Q)$(MAKE) -C $(call SRCDIR,$(patsubst install-%,%,$@)) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)

$(addprefix install-,$(LIBS)): $(TOOLS)
	$(Q)$(MAKE) -C $(call SRCDIR,$(patsubst install-%,%,$@)) install PREFIX=$(PREFIX) DESTDIR=$(DESTDIR)

libs: $(LIBS) $(TOOLS)
	$(Q)$(call NATIVEEXE,tools/convbin/bin/convbin) --oformat 8xg-auto-extract \
		$(foreach library,$(LIBS),$(addprefix --input ,$(call SRCDIR,$(library))/$(library).8xv)) --output $(call NATIVEPATH,clibs.8xg)

libs-zip:
	$(Q)$(call MKDIR,clibs)
	$(Q)$(foreach library,$(LIBS),$(call COPY,$(call NATIVEPATH,$(call SRCDIR,$(library))/$(library).8xv),clibs) &&) $(call NATIVEEXE,7z) a clibs_separately_in_zip.zip clibs

clean: $(addprefix clean-,$(TOOLS)) $(addprefix clean-,$(SRCS)) $(addprefix clean-,$(LIBS))
	$(Q)$(call REMOVE,src/linker_script)
	$(Q)$(call REMOVE,clibs.8xg)
	$(Q)$(call RMDIR,docs/build)
	$(Q)$(call RMDIR,docs/doxygen)

$(addprefix clean-,$(LIBS)):
	$(Q)$(MAKE) -C $(call SRCDIR,$(patsubst clean-%,%,$@)) clean

$(addprefix clean-,$(SRCS)):
	$(Q)$(MAKE) -C $(call SRCDIR,$(patsubst clean-%,%,$@)) clean

$(addprefix clean-,$(TOOLS)):
	$(Q)$(MAKE) -C $(call TOOLSDIR,$(patsubst clean-%,%,$@)) clean

check:
	$(Q)$(EZCC) --version || ( echo Please install ez80-clang && exit 1 )
	$(Q)$(FASMG) $(NULL) $(NULL) || ( echo Please install fasmg && exit 1 )

docs:
	$(Q)$(MAKE) -C docs html

local-docs:
	$(Q)$(MAKE) -C docs local-html

.PHONY: $(LIBS) $(SRCS)
.PHONY: $(addprefix install-,$(SRCS)) $(addprefix install-,$(LIBS))
.PHONY: $(addprefix clean-,$(SRCS)) $(addprefix clean-,$(LIBS))
.PHONY: all check clean install libs docs local-docs
