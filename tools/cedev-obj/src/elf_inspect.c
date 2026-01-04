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

#include "elf_inspect.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* ELF format definitions (from ELF specification) */
#define EI_NIDENT 16
#define EI_CLASS  4
#define ELFCLASS32 1

#define SHT_SYMTAB 2
#define SHT_STRTAB 3

/* ELF32 structures */
struct elf32_ehdr
{
    uint8_t  e_ident[EI_NIDENT];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
};

struct elf32_shdr
{
    uint32_t sh_name;
    uint32_t sh_type;
    uint32_t sh_flags;
    uint32_t sh_addr;
    uint32_t sh_offset;
    uint32_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint32_t sh_addralign;
    uint32_t sh_entsize;
};

struct elf32_sym
{
    uint32_t st_name;
    uint32_t st_value;
    uint32_t st_size;
    uint8_t  st_info;
    uint8_t  st_other;
    uint16_t st_shndx;
};

/* Internal ELF file structure */
struct elf_file
{
    FILE *fp;
    char error[256];
    
    /* ELF header */
    struct elf32_ehdr ehdr;
    
    /* Section headers */
    struct elf32_shdr *section_headers;
    
    /* String tables */
    char *shstrtab;
    size_t shstrtab_size;
    char *strtab;
    size_t strtab_size;
    
    /* Symbol table */
    struct elf32_sym *symtab;
    size_t symtab_count;
};

static void set_error(struct elf_file *elf, const char *msg)
{
    snprintf(elf->error, sizeof(elf->error), "%s", msg);
}

static bool read_at(FILE *fp, void *buf, size_t size, long offset)
{
    if (fseek(fp, offset, SEEK_SET) != 0)
    {
        return false;
    }
    
    return fread(buf, 1, size, fp) == size;
}

static bool parse_elf_header(struct elf_file *elf)
{
    if (!read_at(elf->fp, &elf->ehdr, sizeof(elf->ehdr), 0))
    {
        set_error(elf, "Failed to read ELF header");
        return false;
    }
    
    /* Check ELF magic number */
    if (memcmp(elf->ehdr.e_ident, "\177ELF", 4) != 0)
    {
        set_error(elf, "Not an ELF file");
        return false;
    }
    
    /* Check for 32-bit */
    if (elf->ehdr.e_ident[EI_CLASS] != ELFCLASS32)
    {
        set_error(elf, "Only 32-bit ELF supported");
        return false;
    }
    
    return true;
}

static bool load_section_headers(struct elf_file *elf)
{
    size_t shdr_table_size = elf->ehdr.e_shnum * elf->ehdr.e_shentsize;
    
    elf->section_headers = malloc(shdr_table_size);
    if (!elf->section_headers)
    {
        set_error(elf, "Failed to allocate section headers");
        return false;
    }
    
    if (!read_at(elf->fp, elf->section_headers, shdr_table_size, elf->ehdr.e_shoff))
    {
        set_error(elf, "Failed to read section headers");
        return false;
    }
    
    return true;
}

static bool load_string_table(struct elf_file *elf, uint32_t shdr_idx, char **strtab, size_t *size)
{
    if (shdr_idx >= elf->ehdr.e_shnum)
    {
        set_error(elf, "Invalid section index");
        return false;
    }
    
    struct elf32_shdr *shdr = &elf->section_headers[shdr_idx];
    
    *strtab = malloc(shdr->sh_size);
    if (!*strtab)
    {
        set_error(elf, "Failed to allocate string table");
        return false;
    }
    
    if (!read_at(elf->fp, *strtab, shdr->sh_size, shdr->sh_offset))
    {
        set_error(elf, "Failed to read string table");
        free(*strtab);
        *strtab = NULL;
        return false;
    }
    
    *size = shdr->sh_size;
    return true;
}

static bool load_symbol_table(struct elf_file *elf)
{
    /* Find .symtab section */
    struct elf32_shdr *symtab_shdr = NULL;
    
    for (uint16_t i = 0; i < elf->ehdr.e_shnum; i++)
    {
        if (elf->section_headers[i].sh_type == SHT_SYMTAB)
        {
            symtab_shdr = &elf->section_headers[i];
            break;
        }
    }
    
    if (!symtab_shdr)
    {
        set_error(elf, "No symbol table found");
        return false;
    }
    
    /* Load symbol table */
    elf->symtab_count = symtab_shdr->sh_size / sizeof(struct elf32_sym);
    elf->symtab = malloc(symtab_shdr->sh_size);
    if (!elf->symtab)
    {
        set_error(elf, "Failed to allocate symbol table");
        return false;
    }
    
    if (!read_at(elf->fp, elf->symtab, symtab_shdr->sh_size, symtab_shdr->sh_offset))
    {
        set_error(elf, "Failed to read symbol table");
        return false;
    }
    
    /* Load associated string table */
    if (!load_string_table(elf, symtab_shdr->sh_link, &elf->strtab, &elf->strtab_size))
    {
        return false;
    }
    
    return true;
}

struct elf_file *elf_open(const char *filename)
{
    struct elf_file *elf = calloc(1, sizeof(struct elf_file));
    if (!elf)
    {
        return NULL;
    }
    
    elf->fp = fopen(filename, "rb");
    if (!elf->fp)
    {
        set_error(elf, "Failed to open file");
        free(elf);
        return NULL;
    }
    
    if (!parse_elf_header(elf))
    {
        elf_close(elf);
        return NULL;
    }
    
    if (!load_section_headers(elf))
    {
        elf_close(elf);
        return NULL;
    }
    
    /* Load section header string table */
    if (!load_string_table(elf, elf->ehdr.e_shstrndx, &elf->shstrtab, &elf->shstrtab_size))
    {
        elf_close(elf);
        return NULL;
    }
    
    if (!load_symbol_table(elf))
    {
        elf_close(elf);
        return NULL;
    }
    
    return elf;
}

void elf_close(struct elf_file *elf)
{
    if (!elf)
    {
        return;
    }
    
    if (elf->fp)
    {
        fclose(elf->fp);
    }
    
    if (elf->section_headers)
    {
        free(elf->section_headers);
    }
    
    if (elf->shstrtab)
    {
        free(elf->shstrtab);
    }
    
    if (elf->strtab)
    {
        free(elf->strtab);
    }
    
    if (elf->symtab)
    {
        free(elf->symtab);
    }
    
    free(elf);
}

bool elf_has_symbol(struct elf_file *elf, const char *symbol_name)
{
    if (!elf || !symbol_name)
    {
        return false;
    }

    for (size_t i = 0; i < elf->symtab_count; i++)
    {
        if (elf->symtab[i].st_name < elf->strtab_size)
        {
            const char *name = elf->strtab + elf->symtab[i].st_name;
            if (strcmp(name, symbol_name) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool elf_has_defined_symbol(struct elf_file *elf, const char *symbol_name)
{
    if (!elf || !symbol_name)
    {
        return false;
    }
    
    for (size_t i = 0; i < elf->symtab_count; i++)
    {
        if (elf->symtab[i].st_name < elf->strtab_size)
        {
            const char *name = elf->strtab + elf->symtab[i].st_name;
            if (strcmp(name, symbol_name) == 0)
            {
                return elf->symtab[i].st_shndx != 0;
            }
        }
    }
    
    return false;
}

bool elf_has_section(struct elf_file *elf, const char *section_name)
{
    if (!elf || !section_name)
    {
        return false;
    }
    
    for (uint16_t i = 0; i < elf->ehdr.e_shnum; i++)
    {
        if (elf->section_headers[i].sh_name < elf->shstrtab_size)
        {
            const char *name = elf->shstrtab + elf->section_headers[i].sh_name;
            if (strcmp(name, section_name) == 0)
            {
                /* Section exists - check if it's non-empty */
                return elf->section_headers[i].sh_size > 0;
            }
        }
    }
    
    return false;
}

const char *elf_get_error(struct elf_file *elf)
{
    return elf ? elf->error : "Invalid ELF handle";
}
