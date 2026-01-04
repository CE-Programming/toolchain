// Copyright (C) 2015-2026 CE Programming
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef ELF_INSPECT_H
#define ELF_INSPECT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque handle for ELF file */
struct elf_file;

/* Open an ELF file for inspection */
struct elf_file *elf_open(const char *filename);

/* Close and free resources */
void elf_close(struct elf_file *elf);

/* Check if a symbol exists by name */
bool elf_has_symbol(struct elf_file *elf, const char *symbol_name);

/* Check if a symbol exists by name and is defined */
bool elf_has_defined_symbol(struct elf_file *elf, const char *symbol_name);

/* Check if a section exists and is non-empty */
bool elf_has_section(struct elf_file *elf, const char *section_name);

/* Get last error message (valid until next call or elf_close) */
const char *elf_get_error(struct elf_file *elf);

#ifdef __cplusplus
}
#endif

#endif
