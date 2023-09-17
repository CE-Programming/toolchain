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

include $(CURDIR)/common.mk

FASMG_FILES = $(subst $(space),$(comma) ,$(patsubst %,"%",$(subst ",\",$(subst \,\\,$(call NATIVEPATH,$1)))))#"
APPEND_FILES = $(foreach file,$(addprefix ../lib/$2/,$(notdir $3)),$(call APPEND,$1$(call FASMG_FILES,$(file)))$(newline))

CRT_FILES := $(filter-out crt/crt0.src,$(wildcard crt/*.src) $(patsubst crt/%,crt/build/%.src,$(wildcard crt/*.c crt/*.cpp)))
LIBC_FILES := $(wildcard libc/*.src) $(patsubst libc/%,libc/build/%.src,$(wildcard libc/*.c libc/*.cpp))
LIBCXX_FILES := $(wildcard libcxx/*.src) $(patsubst libcxx/%,libcxx/build/%.src,$(wildcard libcxx/*.c libcxx/*.cpp))
SOFTFLOAT_FILES := $(wildcard softfloat/*.src) $(patsubst softfloat/%,softfloat/build/%.src,$(wildcard softfloat/*.c softfloat/*.cpp))
# TODO: atomic
EASTL_FILES := $(filter-out EASTL/atomic.cpp.src,$(patsubst EASTL/source/%,EASTL/%.src,$(wildcard EASTL/source/*.c EASTL/source/*.cpp)))
CE_FILES := $(wildcard ce/*.src)

linker_script: $(STATIC_FILES) $(LINKED_FILES) $(SHARED_FILES)
	$(Q)$(call REMOVE,$(call QUOTE_ARG,$@))
	$(Q)$(call APPEND,if DEBUG)
	$(Q)$(call APPEND,	iterate sections$(comma) <.comment$(comma) .debug_abbrev$(comma) .debug_addr$(comma) .debug_aranges$(comma)     \)
	$(Q)$(call APPEND,	                   .debug_frame$(comma) .debug_info$(comma) .debug_line$(comma) .debug_line_str$(comma)  \)
	$(Q)$(call APPEND,	                   .debug_loc$(comma) .debug_loclists$(comma) .debug_macinfo$(comma)              \)
	$(Q)$(call APPEND,	                   .debug_macro$(comma) .debug_names$(comma) .debug_pubnames$(comma)              \)
	$(Q)$(call APPEND,	                   .debug_pubtypes$(comma) .debug_ranges$(comma) .debug_rnglists$(comma)          \)
	$(Q)$(call APPEND,	                   .debug_str$(comma) .debug_str_offsets$(comma) .debug_sup$(comma) .debug_types$(comma) \)
	$(Q)$(call APPEND,	                   .debug_abbrev.dwo$(comma) .debug_info.dwo$(comma) .debug_line.dwo$(comma)      \)
	$(Q)$(call APPEND,	                   .debug_loclists.dwo$(comma) .debug_macro.dwo$(comma)                    \)
	$(Q)$(call APPEND,	                   .debug_rnglists.dwo$(comma) .debug_str.dwo$(comma)                      \)
	$(Q)$(call APPEND,	                   .debug_str_offsets.dwo$(comma) .debug_cu_index$(comma) .debug_tu_index>)
	$(Q)$(call APPEND,		split debug: sections)
	$(Q)$(call APPEND,		precious sections)
	$(Q)$(call APPEND,	end iterate)
	$(Q)$(call APPEND,end if)
	$(Q)$(call APPEND)
	$(Q)$(call APPEND,order .header$(comma) .icon$(comma) .init.libs$(comma) .libs$(comma) .init.clock$(comma) .init.reruncheck$(comma) .init$(comma) .fini$(comma) .text$(comma) .data$(comma) .rodata)
	$(Q)$(call APPEND,split : .init_array$(comma) .ctors$(comma) .dtors$(comma) .fini_array)
	$(Q)$(call APPEND,precious .header$(comma) .icon$(comma) .init.libs if .libs.length$(comma) .libs$(comma) .init_array$(comma) .ctors$(comma) .dtors$(comma) .fini_array)
	$(Q)$(call APPEND,provide ___low_bss = .bss.base)
	$(Q)$(call APPEND,provide ___len_bss = .bss.length)
	$(Q)$(call APPEND,provide ___heaptop = .bss.high)
	$(Q)$(call APPEND,provide ___heapbot = .bss.top)
	$(Q)$(call APPEND,provide ___libs = .libs.base)
	$(Q)$(call APPEND,provide ___init_array_count = .init_array.length / 3)
	$(Q)$(call APPEND,provide ___ctors_count = .ctors.length / 3)
	$(Q)$(call APPEND,provide ___dtors_count = .dtors.length / 3)
	$(Q)$(call APPEND,provide ___fini_array_count = .fini_array.length / 3)
	$(Q)$(call APPEND,require __start)
	$(Q)$(call APPEND,library "../lib/libload/libload.lib" neveroptional)
	$(Q)$(call APPEND,require lib.LibLoad if .libs.length)
	$(Q)$(call APPEND)
	$(Q)$(call APPEND_FILES,source ,crt,$(sort $(CRT_FILES)))
	$(Q)$(call APPEND_FILES,source ,ce,$(sort $(CE_FILES)))
	$(Q)$(call APPEND,if HAS_LIBC)
	$(Q)$(call APPEND_FILES,	source ,libc,$(sort $(LIBC_FILES)))
	$(Q)$(call APPEND_FILES,	source ,softfloat,$(sort $(SOFTFLOAT_FILES)))
	$(Q)$(call APPEND,end if)
	$(Q)$(call APPEND,if HAS_LIBCXX)
	$(Q)$(call APPEND_FILES,	source ,libcxx,$(sort $(LIBCXX_FILES)))
	$(Q)$(call APPEND,end if)
	$(Q)$(call APPEND,if HAS_EASTL)
	$(Q)$(call APPEND_FILES,	source ,EASTL,$(sort $(EASTL_FILES)))
	$(Q)$(call APPEND,end if)
