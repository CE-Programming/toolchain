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

include $(CURDIR)/common.mk

FASMG_FILES = $(subst $(space),$(comma) ,$(patsubst %,"%",$(subst ",\",$(subst \,\\,$(call NATIVEPATH,$1)))))#"
APPEND_FILES = $(foreach file,$(addprefix ../lib/$2/,$(notdir $3)),$(call APPEND,$1$(call FASMG_FILES,$(file)))$(newline))

STATIC_FILES := $(wildcard std/static/*.src) $(patsubst std/static/%.c,std/static/build/%.src,$(wildcard std/static/*.c))
LINKED_FILES := $(wildcard std/linked/*.src) $(patsubst std/linked/%.c,std/linked/build/%.src,$(wildcard std/linked/*.c))
SHARED_FILES := $(filter-out ce/crt0.src,$(wildcard ce/*.src)) $(wildcard std/shared/*.src) $(patsubst std/shared/%.c,std/shared/build/%.src,$(wildcard std/shared/*.c))

linker_script:
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
	$(Q)$(call APPEND,require __init$(comma) __start$(comma) _exit$(comma) __init_libload if .libs.length)
	$(Q)$(call APPEND,provide __low_bss = .bss.base)
	$(Q)$(call APPEND,provide __len_bss = .bss.length)
	$(Q)$(call APPEND,provide __heaptop = .bss.high)
	$(Q)$(call APPEND,provide __heapbot = .bss.top)
	$(Q)$(call APPEND,provide __relocationstart = .libs.base)
	$(Q)$(call APPEND,order $(subst $(space),$(comma) ,.header .icon .launcher .libs .start .cleanup .exit .text .data .rodata))
	$(Q)$(call APPEND,if STATIC)
	$(Q)$(call APPEND_FILES,	source ,static,$(STATIC_FILES))
	$(Q)$(call APPEND,else)
	$(Q)$(call APPEND_FILES,	source ,linked,$(LINKED_FILES))
	$(Q)$(call APPEND,end if)
	$(Q)$(call APPEND_FILES,source ,shared,$(SHARED_FILES))
