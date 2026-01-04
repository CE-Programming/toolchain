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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORD_LEN 1024
#define MAX_FMT "1023"

typedef struct {
    char *elf_file;
    char *output_file;
    int optional_libs_start;
    int optional_libs_end;
    int lib_files_start;
    int lib_files_end;
} options_t;

static void print_usage(const char *prog)
{
    fprintf(stderr, "Usage: %s --elf <elf_file> -o|--output <output_file> "
                    "[--libs lib_file1 lib_file2 ...] [--optional-libs LIB1 LIB2 ...]\n", prog);
}

static bool is_flag(const char *arg)
{
    return arg[0] == '-';
}

static bool is_optional_lib(const char *lib_name, char **argv, int start, int end)
{
    if (start == -1 || end == -1)
        return false;
    
    for (int i = start; i < end; i++)
    {
        if (strcmp(lib_name, argv[i]) == 0)
            return true;
    }
    return false;
}

static bool parse_arguments(int argc, char **argv, options_t *opts)
{
    memset(opts, 0, sizeof(*opts));
    opts->optional_libs_start = -1;
    opts->optional_libs_end = -1;
    opts->lib_files_start = -1;
    opts->lib_files_end = -1;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--optional-libs") == 0)
        {
            opts->optional_libs_start = i + 1;
            for (i++; i < argc && !is_flag(argv[i]); i++)
                ;
            opts->optional_libs_end = i;
            i--;
        }
        else if (strcmp(argv[i], "--elf") == 0)
        {
            if (++i >= argc)
            {
                fprintf(stderr, "Error: --elf requires an argument\n");
                return false;
            }
            opts->elf_file = argv[i];
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
        {
            if (++i >= argc)
            {
                fprintf(stderr, "Error: %s requires an argument\n", argv[i-1]);
                return false;
            }
            opts->output_file = argv[i];
        }
        else if (strcmp(argv[i], "--libs") == 0)
        {
            opts->lib_files_start = i + 1;
            for (i++; i < argc && !is_flag(argv[i]); i++)
                ;
            opts->lib_files_end = i;
            i--;
        }
        else
        {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
            return false;
        }
    }

    if (!opts->elf_file || !opts->output_file)
    {
        fprintf(stderr, "Error: Missing required arguments\n");
        return false;
    }

    return true;
}

static void write_header_defines(FILE *out, const char *elf_file, struct elf_file *elf)
{
    fprintf(out, "/* generated from: %s */\n", elf_file);
    fprintf(out, "#define HAS_INIT_ARRAY %d\n", elf_has_section(elf, ".init_array") ? 1 : 0);
    fprintf(out, "#define HAS_FINI_ARRAY %d\n", elf_has_section(elf, ".fini_array") ? 1 : 0);
    fprintf(out, "#define HAS_CLOCK %d\n", elf_has_symbol(elf, "_clock") ? 1 : 0);
    fprintf(out, "#define HAS_ABORT %d\n", elf_has_symbol(elf, "_abort") ? 1 : 0);
    fprintf(out, "#define HAS_RUN_PRGM %d\n", elf_has_symbol(elf, "_os_RunPrgm") ? 1 : 0);
    fprintf(out, "#define HAS_MAIN_ARGC_ARGV %d\n", elf_has_defined_symbol(elf, "___main_argc_argv") ? 1 : 0);
    fprintf(out, "#define HAS_ATEXIT %d\n", elf_has_symbol(elf, "__atexit_functions") ? 1 : 0);
}

static bool process_library_file(FILE *out, struct elf_file *elf, const char *lib_file,
                                  char **argv, int optional_start, int optional_end)
{
    FILE *lib = fopen(lib_file, "r");
    if (!lib)
    {
        fprintf(stderr, "Error: Failed to open library file '%s'\n", lib_file);
        return false;
    }

    char word[MAX_WORD_LEN];
    char lib_name[MAX_WORD_LEN] = "";
    int lib_version = 0;
    int export_index = 0;
    bool lib_header_written = false;
    bool lib_needed = false;

    while (fscanf(lib, "%" MAX_FMT "s", word) == 1)
    {
        if (strcmp(word, "library") == 0)
        {
            if (fscanf(lib, " %" MAX_FMT "[^,], %d", lib_name, &lib_version) != 2)
            {
                fprintf(stderr, "Error: Failed to parse library line in '%s'\n", lib_file);
                fclose(lib);
                return false;
            }

            /* Check if library is explicitly requested via __libload_library_NAME */
            char libload_symbol[MAX_WORD_LEN + 20];
            snprintf(libload_symbol, sizeof(libload_symbol), "__libload_library_%s", lib_name);
            lib_needed = elf_has_symbol(elf, libload_symbol);
        }
        else if (strcmp(word, "export") == 0)
        {
            char export_name[MAX_WORD_LEN];
            if (fscanf(lib, "%" MAX_FMT "s", export_name) != 1)
            {
                fprintf(stderr, "Error: Failed to parse export line in '%s'\n", lib_file);
                fclose(lib);
                return false;
            }

            char symbol_name[MAX_WORD_LEN + 1];
            snprintf(symbol_name, sizeof(symbol_name), "_%s", export_name);
            bool symbol_referenced = elf_has_symbol(elf, symbol_name);

            if (symbol_referenced || lib_needed)
            {
                if (!lib_header_written)
                {
                    bool optional = is_optional_lib(lib_name, argv, optional_start, optional_end);
                    fprintf(out, "\t.global __libload_library_%s\n", lib_name);
                    fprintf(out, "\t.type __libload_library_%s, @object\n", lib_name);
                    fprintf(out, "__libload_library_%s:\n", lib_name);
                    fprintf(out, "\t.db 0x%s, \"%s\", 0, %d\n",
                            optional ? "C1" : "C0", lib_name, lib_version);
                    lib_header_written = true;
                }

                if (symbol_referenced)
                {
                    fprintf(out, "\t.global %s\n", symbol_name);
                    fprintf(out, "\t.type %s, @function\n", symbol_name);
                    fprintf(out, "%s:\n", symbol_name);
                    fprintf(out, "\tjp %d\n", export_index * 3);
                }
            }
            export_index++;
        }
    }

    fclose(lib);
    return lib_header_written;
}

static bool process_libraries(FILE *out, struct elf_file *elf, char **argv,
                               int lib_start, int lib_end, int opt_start, int opt_end)
{
    bool has_libload = false;

    fprintf(out, "#ifdef __ASSEMBLER__\n");
    fprintf(out, ".macro LIBLOAD_LIBS\n");

    if (lib_start != -1 && lib_end != -1)
    {
        for (int i = lib_start; i < lib_end; i++)
        {
            if (process_library_file(out, elf, argv[i], argv, opt_start, opt_end))
                has_libload = true;
        }
    }

    fprintf(out, ".endm\n");
    fprintf(out, "#endif\n");
    fprintf(out, "#define HAS_LIBLOAD %d\n", has_libload);

    return true;
}

int main(int argc, char **argv)
{
    options_t opts;

    if (!parse_arguments(argc, argv, &opts))
    {
        print_usage(argv[0]);
        return 1;
    }

    struct elf_file *elf = elf_open(opts.elf_file);
    if (!elf)
    {
        fprintf(stderr, "Error: Failed to open ELF file '%s'\n", opts.elf_file);
        return 1;
    }

    FILE *out = fopen(opts.output_file, "w");
    if (!out)
    {
        fprintf(stderr, "Error: Failed to open output file '%s'\n", opts.output_file);
        elf_close(elf);
        return 1;
    }

    write_header_defines(out, opts.elf_file, elf);

    bool success = process_libraries(out, elf, argv,
                                      opts.lib_files_start, opts.lib_files_end,
                                      opts.optional_libs_start, opts.optional_libs_end);

    fclose(out);
    elf_close(elf);
    return success ? 0 : 1;
}
