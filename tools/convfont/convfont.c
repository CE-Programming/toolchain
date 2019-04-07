#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#ifdef _MSC_VER
#include "getopt.h"
#else
#include <getopt.h>
#endif
#include "convfont.h"
#include "parse_fnt.h"
#include "serialize_font.h"

/* http://benoit.papillault.free.fr/c/disc2/exefmt.txt */

bool unix_newline_style =
#ifdef _WIN32
false
#else
true
#endif
;


void throw_error(int code, char *string) {
    if (string != NULL)
        fprintf(stderr, "ERROR: %s\n", string);
    exit(code);
}

void output_format_byte(uint8_t byte, void *custom_data) {
    fputc(byte, custom_data);
}

typedef struct {
    FILE *file;
    int row_counter;
    bool first_line;
} format_c_array_data_t;

void print_newline(FILE *file) {
    if (!unix_newline_style)
        fputc('\r', file);
    fputc('\n', file);
}

void output_format_c_array(uint8_t byte, void *custom_data) {
    format_c_array_data_t *state = (format_c_array_data_t *)custom_data;
    if (!state->row_counter)
        if (state->first_line)
            state->first_line = false;
        else {
            fputc(',', state->file);
            print_newline(state->file);
        } else
            fprintf(state->file, ", ");
        fprintf(state->file, "0x%02X", byte);
        state->row_counter = (state->row_counter + 1) % 16;
}


void show_help(char *name) {
    printf("Syntax: %s -o <output format> -f <font FNT> [-metrics] [-f <font FNT 2> [-metrics]] <output file name>\n"
        "Specifying more than one input font is only valid for the font pack output format.\n"
        "Output formats:\n"
        "-o fontpack: A fontpack ready to be passed to convhex\n"
        "-o carray: A C-style array\n"
        "-o asmarray: An assembly-style array\n"
        "-o binary: A straight binary blob\n"
#ifdef _WIN32
        "-Z: Use CR+LF newlines (default for this platform)\n"
        "-z: Use LR newlines instead of CR+LF newlines\n"
#else
        "-z: Use LF newlines (default for this platform)\n"
        "-Z: Use CR+LF newlines instead of LF newlines\n"
#endif
        "Individual font properties:\n"
        "-f: <file name> input Font\n"
        "-a: <n> space Above\n"
        "-b: <n> space Below\n"
        "-i: <n> Italic space adjust\n"
        "-w: <n> Weight\n"
        "-s: <n> Style\n"
        "-c: <n> Cap height\n"
        "-x: <n> x height\n"
        "-l: <n> baseLine height\n"
        " Numbers may be prefixed with 0x to specify hexadecimal instead of decimal.\n"
        "Font pack properties:\n"
        "-N: \"<s>\" font pack Name\n"
        "-C: \"<s>\" pseudoCopyright\n"
        "-D: \"<s>\" Description\n"
        "-V: \"<s>\" Version\n"
        "-P: \"<s>\" codePage\n", name);
}



/*******************************************************************************
*                                    MAIN                                      *
*******************************************************************************/

#define MAX_FONTS 64

fontlib_font_t *fonts[MAX_FONTS] =
{
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};
int fonts_loaded = 0;

int main(int argc, char *argv[]) {
    FILE *in_file;
    FILE *out_file;

    if (argc <= 1) {
        printf("No inputs supplied.\n\n");
        show_help(argv[0]);
        return 0;
    }

    /* Settings */
    char *font_pack_name = NULL;
    char *pseudocopyright = NULL;
    char *description = NULL;
    char *version = NULL;
    char *codepage = NULL;
    char *output_file_name = NULL;
    char *recent_input_file_name = NULL;
    fontlib_font_t *current_font = NULL;
    int temp_n;
    output_formats_t output_format = output_unspecified;

    int option;

    while ((option = getopt(argc, argv, "o:Zf:a:b:i:w:s:c:x:l:N:C:D:V:P:")) != -1) {
        switch (option) {
            case 'o':
                if (output_format != output_unspecified)
                    throw_error(bad_options, "-o: Cannot specify more than one output format.");
                switch (optarg[0]) {
                    case 'c':
                        output_format = output_c_array;
                        break;
                    case 'a':
                        output_format = output_asm_array;
                        break;
                    case 'f':
                    case 'p':
                        output_format = output_fontpack;
                        break;
                    case 'b':
                        output_format = output_binary_blob;
                        break;
                    default:
                        throw_error(bad_options, "-o: Unknown output format.");
                        break;
                }
                break;
            case 'Z':
                unix_newline_style = false;
                break;
            case 'z':
                unix_newline_style = true;
                break;
            case 'f':
                if (fonts_loaded > 0 && output_format != output_fontpack)
                    throw_error(bad_options, "-f: Cannot have multiple input fonts unless -o fontpack is specified first.");
                if (fonts_loaded >= MAX_FONTS - 1)
                    throw_error(bad_options, "-f: Too many fonts.  What on Earth makes you think your font pack needs so many fonts?");
                recent_input_file_name = optarg;
                in_file = fopen(recent_input_file_name, "rb");
                if (!in_file)
                    throw_error(bad_infile, "-f: Cannot open input file.");
                int ver = read_word(in_file);
                if (ver != 0x200 && ver != 0x300)
                    throw_error(bad_infile, "-f: Input file does not appear to be an FNT at all.");
                current_font = parse_fnt(in_file, 0);
                fclose(in_file);
                fonts[fonts_loaded++] = current_font;
                break;
            case 'a':
                if (current_font == NULL)
                    throw_error(bad_options, "-a: Must specify a font before specifying metrics.");
                temp_n = (int)strtol(optarg, NULL, 0);
                if (temp_n > 64 || temp_n < 0)
                    throw_error(bad_options, "-a: Number too large or small.");
                current_font->space_above = (uint8_t)temp_n;
                break;
            case 'b':
                if (current_font == NULL)
                    throw_error(bad_options, "-b: Must specify a font before specifying metrics.");
                temp_n = (int)strtol(optarg, NULL, 0);
                if (temp_n > 64 || temp_n < 0)
                    throw_error(bad_options, "-b: Number too large or small.");
                current_font->space_below = (uint8_t)temp_n;
                break;
            case 'i':
                if (current_font == NULL)
                    throw_error(bad_options, "-i: Must specify a font before specifying metrics.");
                temp_n = (int)strtol(optarg, NULL, 0);
                if (temp_n > 24 || temp_n < 0)
                    throw_error(bad_options, "-i: Number too large or small.");
                current_font->italic_space_adjust = (uint8_t)temp_n;
                break;
            case 'w':
                if (current_font == NULL)
                    throw_error(bad_options, "-w: Must specify a font before specifying metrics.");
                temp_n = (int)strtol(optarg, NULL, 0);
                if (temp_n > 255 || temp_n < 0)
                    throw_error(bad_options, "-w: Number too large or small.");
                current_font->weight = (uint8_t)temp_n;
                break;
            case 's':
                if (current_font == NULL)
                    throw_error(bad_options, "-s: Must specify a font before specifying metrics.");
                temp_n = (int)strtol(optarg, NULL, 0);
                if (temp_n > 255 || temp_n < 0)
                    throw_error(bad_options, "-s: Number too large or small.");
                current_font->style = (uint8_t)temp_n;
                break;
            case 'c':
                if (current_font == NULL)
                    throw_error(bad_options, "-c: Must specify a font before specifying metrics.");
                temp_n = (int)strtol(optarg, NULL, 0);
                if (temp_n > current_font->height || temp_n < 0)
                    throw_error(bad_options, "-c: Number too large or small.");
                current_font->cap_height = (uint8_t)temp_n;
                break;
            case 'x':
                if (current_font == NULL)
                    throw_error(bad_options, "-x: Must specify a font before specifying metrics.");
                temp_n = (int)strtol(optarg, NULL, 0);
                if (temp_n > current_font->height || temp_n < 0)
                    throw_error(bad_options, "-x: Number too large or small.");
                current_font->x_height = (uint8_t)temp_n;
                break;
            case 'l':
                if (current_font == NULL)
                    throw_error(bad_options, "-l: Must specify a font before specifying metrics.");
                temp_n = (int)strtol(optarg, NULL, 0);
                if (temp_n > current_font->height || temp_n < 0)
                    throw_error(bad_options, "-l: Number too large or small.");
                current_font->baseline_height = (uint8_t)temp_n;
                break;
            case 'N':
                if (output_format != output_fontpack)
                    throw_error(bad_options, "-N: Must specify font pack output format.");
                if (font_pack_name != NULL)
                    throw_error(bad_options, "-N: Duplicate.");
                font_pack_name = optarg;
                break;
            case 'C':
                if (output_format != output_fontpack)
                    throw_error(bad_options, "-C: Must specify font pack output format.");
                if (font_pack_name != NULL)
                    throw_error(bad_options, "-C: Duplicate.");
                pseudocopyright = optarg;
                break;
            case 'D':
                if (output_format != output_fontpack)
                    throw_error(bad_options, "-D: Must specify font pack output format.");
                if (font_pack_name != NULL)
                    throw_error(bad_options, "-D: Duplicate.");
                description = optarg;
                break;
            case 'V':
                if (output_format != output_fontpack)
                    throw_error(bad_options, "-V: Must specify font pack output format.");
                if (font_pack_name != NULL)
                    throw_error(bad_options, "-V: Duplicate.");
                version = optarg;
                break;
            case 'P':
                if (output_format != output_fontpack)
                    throw_error(bad_options, "-P: Must specify font pack output format.");
                if (font_pack_name != NULL)
                    throw_error(bad_options, "-P: Duplicate.");
                codepage = optarg;
                break;
            case '?':
                throw_error(bad_options, "Unknown option; check syntax.");
                break;
        }
    }

    if (optind == argc)
        throw_error(bad_options, "Last parameter must be output file name; none was given.");
    if (optind < argc - 1)
        throw_error(bad_options, "Too many trailing parameters.");

    /* Now write output */
    format_c_array_data_t c_array_data;
    out_file = fopen(argv[optind], "wb");
    if (!out_file)
        throw_error(bad_outfile, "Cannot open output file.");
    if (output_format == output_fontpack) {
        /* Write header */
        if (font_pack_name == NULL)
            throw_error(bad_options, "Must specify a font pack name (-N).");
        for (char* s = "FONTPACK"; *s != '\0'; s++)
            fputc(*s, out_file);
        /* Offset to metadata */
        int location = 12 + fonts_loaded * 3;
        output_ezword(location, output_format_byte, out_file);
        /* Font count */
        fputc(fonts_loaded, out_file);
        /* Fonts table */
        for (int i = 0; i < fonts_loaded; location += compute_font_size(fonts[i++]))
            output_ezword(location, output_format_byte, out_file);
        if (location >= 0xFFF0) {
            fclose(out_file);
            remove(argv[optind]);
            throw_error(bad_options, "Cannot form appvar; output appvar size would exceed 64 K appvar size limit.");
        }
        for (int i = 0; i < fonts_loaded; i++) {
            current_font = fonts[i];
            serialize_font(current_font, output_format_byte, out_file);
            fonts[i] = NULL;
            free_fnt(current_font);
        }
        current_font = NULL;
    } else {
        switch (output_format) {
            case output_c_array:
                c_array_data.file = out_file;
                c_array_data.row_counter = 0;
                c_array_data.first_line = true;
                serialize_font(current_font, output_format_c_array, &c_array_data);
                break;
            case output_asm_array:
                fprintf(out_file, ".header:"); print_newline(out_file);
                fprintf(out_file, "\tdb\t0 ; font format version"); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; height", current_font->height); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; glyph count", current_font->total_glyphs); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; first glyph", current_font->first_glyph); print_newline(out_file);
                fprintf(out_file, "\tdl\t.widthsTable - .header ; offset to widths table"); print_newline(out_file);
                fprintf(out_file, "\tdl\t.bitmapsTable - .header ; offset to bitmaps offsets table"); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; italics space adjust", current_font->italic_space_adjust); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; suggested blank space above", current_font->space_above); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; suggested blank space below", current_font->space_below); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; weight (boldness/thinness)", current_font->weight); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; style field", current_font->style); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; capital height", current_font->cap_height); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; lowercase x height", current_font->x_height); print_newline(out_file);
                fprintf(out_file, "\tdb\t%i ; baseline height", current_font->baseline_height); print_newline(out_file);
                fprintf(out_file, ".widthsTable: ; start of widths table"); print_newline(out_file);
                for (int i = 0; i < current_font->total_glyphs; i++) {
                    fprintf(out_file, "\tdb\t%i ; Code point $%02X %c", current_font->widths_table[i], i + current_font->first_glyph, i + current_font->first_glyph);
                    print_newline(out_file);
                }
                fprintf(out_file, ".bitmapsTable: ; start of table of offsets to bitmaps"); print_newline(out_file);
                for (int i = 0; i < current_font->total_glyphs; i++) {
                    int width = current_font->widths_table[i];
                    fprintf(out_file, "\tdw\t.glyph_%02X - .header", i + current_font->first_glyph);
                    if (width <= 16)
                        fprintf(out_file, " - %i", 3 - byte_columns(width));
                    fprintf(out_file, "; %c", i + current_font->first_glyph);
                    print_newline(out_file);
                }
                for (int i = 0; i < current_font->total_glyphs; i++) {
                    int width = current_font->widths_table[i];
                    int bwidth = byte_columns(width);
                    fprintf(out_file, ".glyph_%02X: ; %c", i + current_font->first_glyph, i + current_font->first_glyph); print_newline(out_file);
                    int byte = 0;
                    for (int row = 0; row < current_font->height; row++) {
                        switch (bwidth) {
                            case 1:
                                fprintf(out_file, "\tdb\t");
                                break;
                            case 2:
                                fprintf(out_file, "\tdw\t");
                                break;
                            case 3:
                                fprintf(out_file, "\tdl\t");
                                break;
                            default:
                                throw_error(internal_error, "byte_columns failed to give 1, 2, or 3.  That should not happen.");
                                break;
                        }
                        /* The format requires omitting the least-significant byte(s) if they're unused. */
                        for (int col = 0; col < bwidth; col++) {
                            int b = current_font->bitmaps[i]->bytes[byte++];
                            for (int bit = 0; bit < 8; bit++, b <<= 1)
                                if (b & 0x80)
                                    fprintf(out_file, "1");
                                else
                                    fprintf(out_file, "0");
                        }
                        fprintf(out_file, "b");
                        print_newline(out_file);
                    }
                }
                break;
            case output_binary_blob:
                serialize_font(current_font, output_format_byte, out_file);
                break;
            default:
                throw_error(internal_error, "-o: Someone attempted to add a new output format without actually coding it.");
                break;
        }
        free_fnt(current_font);
        current_font = NULL;
        fonts[0] = NULL;
    }
    fclose(out_file);

    return 0;
}
