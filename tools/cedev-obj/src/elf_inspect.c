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
#include <sys/stat.h>

/* ELF format definitions (from ELF specification) */
#define EI_NIDENT 16
#define EI_CLASS  4
#define EI_DATA   5
#define ELFCLASS32 1
#define ELFDATA2LSB 1

#define ET_REL 1
#define EM_Z80 220
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_REL 9
#define SHF_ALLOC 2
#define R_Z80_24 5

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

struct elf32_rela
{
    uint32_t r_offset;
    uint32_t r_info;
    int32_t r_addend;
};

/* Internal ELF file structure */
struct elf_file
{
    FILE *fp;
    char error[256];
    size_t file_size;

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
    uint16_t symtab_index;
};

static void set_error(struct elf_file *elf, const char *msg)
{
    snprintf(elf->error, sizeof(elf->error), "%s", msg);
}

static bool set_file_size(struct elf_file *elf)
{
    struct stat st;
    if (fstat(fileno(elf->fp), &st) != 0)
    {
        set_error(elf, "Failed to stat ELF file");
        return false;
    }
    if (st.st_size < 0)
    {
        set_error(elf, "Invalid ELF file size");
        return false;
    }
    elf->file_size = (size_t)st.st_size;
    return true;
}

static bool check_range(struct elf_file *elf, size_t offset, size_t size)
{
    if (offset > elf->file_size || size > elf->file_size - offset)
    {
        set_error(elf, "ELF file truncated or corrupt");
        return false;
    }
    return true;
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
    if (elf->file_size < sizeof(elf->ehdr))
    {
        set_error(elf, "ELF file too small");
        return false;
    }

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

    if (elf->ehdr.e_shentsize != sizeof(struct elf32_shdr))
    {
        set_error(elf, "Unexpected section header size");
        return false;
    }

    if (elf->ehdr.e_shnum == 0)
    {
        set_error(elf, "No section headers present");
        return false;
    }

    return true;
}

static bool load_section_headers(struct elf_file *elf)
{
    if (elf->ehdr.e_shnum > SIZE_MAX / elf->ehdr.e_shentsize)
    {
        set_error(elf, "Section header table size overflow");
        return false;
    }

    size_t shdr_table_size = elf->ehdr.e_shnum * elf->ehdr.e_shentsize;
    if (!check_range(elf, elf->ehdr.e_shoff, shdr_table_size))
    {
        return false;
    }

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
    if (shdr->sh_type != SHT_STRTAB)
    {
        set_error(elf, "Expected string table section");
        return false;
    }
    if (!check_range(elf, shdr->sh_offset, shdr->sh_size))
    {
        return false;
    }

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
            elf->symtab_index = i;
            break;
        }
    }

    if (!symtab_shdr)
    {
        set_error(elf, "No symbol table found");
        return false;
    }

    if (symtab_shdr->sh_entsize != sizeof(struct elf32_sym))
    {
        set_error(elf, "Unexpected symbol entry size");
        return false;
    }

    if (symtab_shdr->sh_size % sizeof(struct elf32_sym) != 0)
    {
        set_error(elf, "Invalid symbol table size");
        return false;
    }

    if (!check_range(elf, symtab_shdr->sh_offset, symtab_shdr->sh_size))
    {
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

static bool is_empty_string(const char *str)
{
    // test for a null string
    if (!str)
    {
        return true;
    }
    // test for an empty string
    if (*str == '\0')
    {
        return true;
    }
    // string contains at least one character
    return false;
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

    if (!set_file_size(elf))
    {
        elf_close(elf);
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
    if (!elf || is_empty_string(symbol_name))
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
    if (!elf || is_empty_string(symbol_name))
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
    if (!elf || is_empty_string(section_name))
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
                /* Section exists - check if it is non-empty */
                return elf->section_headers[i].sh_size > 0;
            }
        }
    }

    return false;
}

static bool matches_prefix(const char *name, const char *section_prefix, const size_t prefix_len)
{
    // match exactly "string" or a prefix of "string."
    if (strcmp(name, section_prefix) == 0)
    {
        // exact match
        return true;
    }

    if (strncmp(name, section_prefix, prefix_len) == 0)
    {
        if (name[prefix_len] == '.')
        {
            // "string."
            return true;
        }
        // not the same prefix (such as "string_word" or "string_word.")
        return false;
    }
    // no match
    return false;
}

bool elf_has_section_prefix(struct elf_file *elf, const char *section_prefix)
{
    if (!elf || is_empty_string(section_prefix))
    {
        return false;
    }

    const size_t prefix_len = strlen(section_prefix);
    for (uint16_t i = 0; i < elf->ehdr.e_shnum; i++)
    {
        if (elf->section_headers[i].sh_name < elf->shstrtab_size)
        {
            const char *name = elf->shstrtab + elf->section_headers[i].sh_name;
            if (matches_prefix(name, section_prefix, prefix_len))
            {
                /* Section exists - check if it is non-empty */
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

static uint16_t find_section(struct elf_file *elf, const char *name)
{
    size_t length = strlen(name) + 1;
    for (uint16_t i = 1; i < elf->ehdr.e_shnum; i++)
    {
        size_t offset = elf->section_headers[i].sh_name;
        if (offset < elf->shstrtab_size && length <= elf->shstrtab_size - offset &&
            memcmp(elf->shstrtab + offset, name, length) == 0)
            return i;
    }
    return 0;
}

bool elf_read_section(struct elf_file *elf, const char *name,
                      uint8_t **data, size_t *size)
{
    uint16_t index = find_section(elf, name);
    *data = NULL;
    *size = 0;
    if (!index)
        return true;

    const struct elf32_shdr *section = &elf->section_headers[index];
    if (section->sh_type != SHT_PROGBITS ||
        !check_range(elf, section->sh_offset, section->sh_size))
    {
        snprintf(elf->error, sizeof(elf->error), "Invalid %s section", name);
        return false;
    }
    if (!section->sh_size)
        return true;

    uint8_t *buffer = malloc(section->sh_size);
    if (!buffer || !read_at(elf->fp, buffer, section->sh_size, section->sh_offset))
    {
        free(buffer);
        snprintf(elf->error, sizeof(elf->error), "Could not read %s section", name);
        return false;
    }
    *data = buffer;
    *size = section->sh_size;
    return true;
}

static int compare_offsets(const void *a, const void *b)
{
    uint16_t first = *(const uint16_t *)a;
    uint16_t second = *(const uint16_t *)b;
    return (first > second) - (first < second);
}

bool elf_relocate_library(struct elf_file *elf, uint8_t *text, size_t text_size,
                          uint16_t **offsets, size_t *count)
{
    *offsets = NULL;
    *count = 0;
    uint16_t text_index = find_section(elf, ".text");
    uint16_t header_index = find_section(elf, ".libload.header");
    uint16_t exports_index = find_section(elf, ".libload.exports");
    if (elf->ehdr.e_ident[EI_DATA] != ELFDATA2LSB || elf->ehdr.e_type != ET_REL ||
        elf->ehdr.e_machine != EM_Z80 || !text_index || text_size > UINT16_MAX)
    {
        set_error(elf, "Expected a relocatable eZ80 library object");
        return false;
    }

    const struct elf32_shdr *relocations = NULL;
    for (uint16_t i = 1; i < elf->ehdr.e_shnum; i++)
    {
        const struct elf32_shdr *section = &elf->section_headers[i];
        if (!section->sh_size)
            continue;
        if (section->sh_type == SHT_RELA || section->sh_type == SHT_REL)
        {
            if (section->sh_info == text_index && !relocations && section->sh_type == SHT_RELA)
            {
                relocations = section;
                continue;
            }
            if (section->sh_info != text_index && section->sh_info != header_index &&
                section->sh_info != exports_index && section->sh_info < elf->ehdr.e_shnum &&
                !(elf->section_headers[section->sh_info].sh_flags & SHF_ALLOC))
                continue;

            set_error(elf, "Unexpected relocation section in library object");
            return false;
        }
        if (i != text_index && (section->sh_flags & SHF_ALLOC))
        {
            set_error(elf, "Library code and data must be in .text");
            return false;
        }
    }
    if (!relocations)
        return true;

    size_t entries = relocations->sh_size / sizeof(struct elf32_rela);
    if (relocations->sh_link != elf->symtab_index ||
        relocations->sh_entsize != sizeof(struct elf32_rela) ||
        relocations->sh_size % sizeof(struct elf32_rela) != 0 ||
        entries > text_size / 3 ||
        !check_range(elf, relocations->sh_offset, relocations->sh_size) ||
        fseek(elf->fp, relocations->sh_offset, SEEK_SET) != 0)
    {
        set_error(elf, "Invalid .text relocation table");
        return false;
    }

    uint16_t *table = malloc(entries * sizeof(*table));
    if (!table)
    {
        set_error(elf, "Could not allocate library relocation table");
        return false;
    }
    for (size_t i = 0; i < entries; i++)
    {
        struct elf32_rela relocation;
        if (fread(&relocation, sizeof(relocation), 1, elf->fp) != 1)
        {
            set_error(elf, "Could not read library relocation");
            free(table);
            return false;
        }
        uint32_t offset = relocation.r_offset;
        uint32_t symbol_index = relocation.r_info >> 8;
        if ((relocation.r_info & 0xff) != R_Z80_24 || symbol_index >= elf->symtab_count ||
            offset > text_size || text_size - offset < 3)
        {
            snprintf(elf->error, sizeof(elf->error), "Unsupported .text relocation at 0x%x", offset);
            free(table);
            return false;
        }

        const struct elf32_sym *symbol = &elf->symtab[symbol_index];
        int64_t value = (int64_t)symbol->st_value + relocation.r_addend;
        if (symbol->st_shndx != text_index || value < 0 || value > 0xffffff)
        {
            snprintf(elf->error, sizeof(elf->error), "Invalid .text relocation target at 0x%x", offset);
            free(table);
            return false;
        }
        text[offset] = value & 0xff;
        text[offset + 1] = (value >> 8) & 0xff;
        text[offset + 2] = (value >> 16) & 0xff;
        table[i] = offset;
    }
    qsort(table, entries, sizeof(*table), compare_offsets);
    for (size_t i = 1; i < entries; i++)
    {
        if (table[i] < table[i - 1] + 3)
        {
            set_error(elf, "Overlapping library relocations");
            free(table);
            return false;
        }
    }
    *offsets = table;
    *count = entries;
    return true;
}
