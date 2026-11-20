# Copyright (C) 2015-2026 CE Programming
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

LIB_OBJ := $(LIB_NAME).o
LIB_LIB := $(LIB_NAME).lib
LIB_8XV := $(LIB_NAME).8xv
LIB_H := $(LIB_NAME).h
LIB_INCLUDES := ../include . $(LIB_DEPENDENCY_DIR)
LIB_PACKER_DIR := ../../tools/cedev-obj
LIB_PACKER := $(LIB_PACKER_DIR)/bin/cedev-obj$(if $(filter 1,$(WINDOWS)),.exe)

all: $(LIB_8XV) $(LIB_LIB)

$(LIB_OBJ): $(LIB_NAME).s ../library.mk ../common.mk ../include/library.inc ../include/ti84pce.inc $(LIB_ASM_DEPS)
	$(Q)$(EZAS) $(EZASFLAGS) $(foreach dir,$(LIB_INCLUDES),-I $(call QUOTE_NATIVE,$(dir))) -o $(call QUOTE_NATIVE,$@) $(call QUOTE_NATIVE,$<)

# A multi-target pattern rule lets older versions of GNU make track both outputs
# from one invocation and regenerate the pair if either output is missing.
%.8xv %.lib: %.o $(LIB_PACKER)
	$(Q)$(call QUOTE_NATIVE,$(LIB_PACKER)) --pack-libload $(call QUOTE_NATIVE,$<) $(call QUOTE_NATIVE,$*.8xv) $(call QUOTE_NATIVE,$*.lib)

$(LIB_PACKER): $(LIB_PACKER_DIR)/Makefile $(wildcard $(LIB_PACKER_DIR)/src/*.c $(LIB_PACKER_DIR)/src/*.h)
	$(Q)$(MAKE) -C $(call QUOTE_NATIVE,$(LIB_PACKER_DIR))

clean:
	$(Q)$(call REMOVE,$(LIB_OBJ) $(LIB_LIB) $(LIB_8XV))

install: all
	$(Q)$(call MKDIR,$(INSTALL_LIB))
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call COPY,$(LIB_LIB),$(INSTALL_LIB))
	$(Q)$(call COPY,$(LIB_H),$(INSTALL_H))

.DELETE_ON_ERROR:
.PHONY: all clean install
