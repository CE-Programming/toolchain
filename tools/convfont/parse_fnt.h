#pragma once

#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

uint8_t read_byte(FILE *input);

int16_t read_word(FILE *input);

int32_t read_dword(FILE *input);

/* Frees a malloc()ed font for you.
 * @param font Pointer to the font to free. */
void free_fnt(fontlib_font_t *font);

/* Unpacks an FNT into RAM.
 * @param input The already-opened file to read from.
 * @param offset The location of the FNT in the input file
 * @return A pointer to a malloc()ed font. */
fontlib_font_t *parse_fnt(FILE *input, int offset);

