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

enum
{
    TI_HEADER_SIZE = 74,
    TI_SECTION_HEADER_SIZE = 19,
    TI_APPVAR_TYPE = 0x15,
    TI_ARCHIVED = 0x80,
    LIBLOAD_MAGIC_SIZE = 3,
    LIBLOAD_TRAILER_SIZE = 6
};

static void write_u16(uint8_t *data, uint16_t value)
{
    data[0] = value & 0xff;
    data[1] = value >> 8;
}

static void write_u24(uint8_t *data, uint32_t value)
{
    write_u16(data, value & 0xffff);
    data[2] = value >> 16;
}

/* Each assembler export record is a little-endian offset and a NUL-terminated name. */
static bool count_exports(const uint8_t *exports, size_t size, size_t code_size,
                          size_t *count)
{
    *count = 0;
    for (size_t offset = 0; offset < size;)
    {
        if (size - offset < 4)
            return false;
        uint16_t target = exports[offset] | ((uint16_t)exports[offset + 1] << 8);
        if (target >= code_size)
            return false;
        const uint8_t *name = exports + offset + 2;
        const uint8_t *end = memchr(name, 0, size - offset - 2);
        if (!end || end == name)
            return false;
        offset = end - exports + 1;
        ++*count;
    }
    return true;
}

static bool write_exports(const char *path, const uint8_t *header,
                          const uint8_t *exports, size_t size)
{
    FILE *file = fopen(path, "wb");
    if (!file)
        return false;

    fprintf(file, "\tlibrary\t%s, %u\n\n", (const char *)header + LIBLOAD_MAGIC_SIZE, (unsigned)header[2]);
    for (size_t offset = 0; offset < size;)
    {
        const char *name = (const char *)exports + offset + 2;
        fprintf(file, "\texport\t%s\n", name);
        offset += 2 + strlen(name) + 1;
    }
    bool ok = !ferror(file);
    return fclose(file) == 0 && ok;
}

static bool write_appvar(const char *path, const uint8_t *header,
                         const uint8_t *exports, size_t export_count,
                         const uint8_t *text, size_t text_size,
                         const uint16_t *relocations, size_t relocation_count,
                         size_t payload_size)
{
    size_t body_offset = LIBLOAD_MAGIC_SIZE + 2 * export_count;
    size_t file_size = TI_HEADER_SIZE + payload_size + 2;
    uint8_t *file_data = calloc(file_size, 1);
    if (!file_data)
        return false;

    memcpy(file_data, "**TI83F*\x1a\x0a", 10);
    write_u16(file_data + 53, payload_size + TI_SECTION_HEADER_SIZE);
    write_u16(file_data + 55, 13);
    write_u16(file_data + 57, payload_size + 2);
    file_data[59] = TI_APPVAR_TYPE;
    const char *name = (const char *)header + LIBLOAD_MAGIC_SIZE;
    memcpy(file_data + 60, name, strlen(name));
    file_data[69] = TI_ARCHIVED;
    write_u16(file_data + 70, payload_size + 2);
    write_u16(file_data + 72, payload_size);

    /* LibLoad layout: magic/version, export vector, body, relocations, trailer. */
    uint8_t *cursor = file_data + TI_HEADER_SIZE;
    memcpy(cursor, header, LIBLOAD_MAGIC_SIZE);
    cursor += LIBLOAD_MAGIC_SIZE;
    for (size_t i = 0; i < export_count; i++)
    {
        memcpy(cursor, exports, 2);
        cursor += 2;
        exports += 2 + strlen((const char *)exports + 2) + 1;
    }
    memcpy(cursor, text, text_size);
    cursor += text_size;
    for (size_t i = 0; i < relocation_count; i++)
    {
        write_u16(cursor, relocations[i]);
        cursor += 2;
    }
    write_u24(cursor, body_offset);
    write_u24(cursor + 3, text_size);

    uint16_t checksum = 0;
    for (size_t i = 55; i < file_size - 2; i++)
        checksum += file_data[i];
    write_u16(file_data + file_size - 2, checksum);

    FILE *file = fopen(path, "wb");
    bool ok = false;
    if (file)
    {
        ok = fwrite(file_data, 1, file_size, file) == file_size;
        ok = fclose(file) == 0 && ok;
    }
    free(file_data);
    return ok;
}

bool pack_libload(const char *input, const char *appvar, const char *descriptor)
{
    struct elf_file *elf = elf_open(input);
    if (!elf)
    {
        fprintf(stderr, "Error: Failed to open ELF file '%s'\n", input);
        return false;
    }

    uint8_t *header = NULL;
    uint8_t *exports = NULL;
    uint8_t *text = NULL;
    uint16_t *relocations = NULL;
    size_t header_size, exports_size, text_size, relocation_count, export_count;
    bool ok = elf_read_section(elf, ".libload.header", &header, &header_size) &&
              elf_read_section(elf, ".libload.exports", &exports, &exports_size) &&
              elf_read_section(elf, ".text", &text, &text_size) &&
              elf_relocate_library(elf, text, text_size, &relocations, &relocation_count);
    if (!ok)
    {
        fprintf(stderr, "Error: %s: %s\n", input, elf_get_error(elf));
    }
    else if (header_size < LIBLOAD_MAGIC_SIZE + 2 || header_size > LIBLOAD_MAGIC_SIZE + 9 ||
             memchr(header + LIBLOAD_MAGIC_SIZE, 0, header_size - LIBLOAD_MAGIC_SIZE) != header + header_size - 1 ||
             !text_size || !count_exports(exports, exports_size, text_size, &export_count))
    {
        fprintf(stderr, "Error: Invalid LibLoad metadata in '%s'\n", input);
        ok = false;
    }
    else
    {
        size_t payload_size = LIBLOAD_MAGIC_SIZE + 2 * export_count + text_size + 2 * relocation_count + LIBLOAD_TRAILER_SIZE;
        if (payload_size > UINT16_MAX - TI_SECTION_HEADER_SIZE)
        {
            fprintf(stderr, "Error: %s: Library is too large for an AppVar (%zu bytes, max %u)\n",
                    input, payload_size, (unsigned)(UINT16_MAX - TI_SECTION_HEADER_SIZE));
            ok = false;
        }
        else if (!write_appvar(appvar, header, exports, export_count, text, text_size, relocations, relocation_count, payload_size) ||
                 !write_exports(descriptor, header, exports, exports_size))
        {
            fprintf(stderr, "Error: Could not write '%s' and '%s'\n", appvar, descriptor);
            remove(appvar);
            remove(descriptor);
            ok = false;
        }
    }

    free(relocations);
    free(text);
    free(exports);
    free(header);
    elf_close(elf);
    return ok;
}
