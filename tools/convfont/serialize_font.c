#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "convfont.h"
#include "serialize_font.h"

/* Compute the total size, in bytes, a font will be.
 * @param font A pointer to the font to find the size of
 * @return The size of the font */
int compute_font_size(fontlib_font_t *font) {
	int size = 18;
	size += 3 * font->total_glyphs;
	for (int i = 0; i < font->total_glyphs; i++)
		size += byte_columns(font->bitmaps[i]->length) * font->height;
	return size;
}

/* The idea of this system with an output callback with custom_data is that you
 * can specify how exactly to output data.  For an output binary file, you can
 * pass a wrapper for fputc(); for a static C or assembly array, you can have it
 * produce hex bytes. */
void output_word(uint16_t data, void(*output)(uint8_t byte, void *custom_data), void *custom_data) {
	output((uint8_t)(data & 255), custom_data);
	output((uint8_t)(data >> 8), custom_data);
}

void output_ezword(uint32_t data, void(*output)(uint8_t byte, void *custom_data), void *custom_data) {
	output((uint8_t)(data & 255), custom_data);
	output((uint8_t)((data >> 8) & 255), custom_data);
	output((uint8_t)((data >> 16) & 255), custom_data);
}

/* Serializes a FontLib font into bytes.
 * @param font The font to serialize
 * @param output A function to use to serialize the bytes. custom_data can be
 * any data you like, such a FILE struct.
 */
void serialize_font(fontlib_font_t *font, void(*output)(uint8_t byte, void *custom_data), void *custom_data) {
	/* Write header */
	output(font->fontVersion, custom_data);
	output(font->height, custom_data);
	output(font->total_glyphs, custom_data);
	output(font->first_glyph, custom_data);
	/* These values come from the data format */
	output_ezword(18, output, custom_data);
	int next_bitmap_offset = 18 + font->total_glyphs;
	output_ezword(next_bitmap_offset, output, custom_data);
	/* More header */
	output(font->italic_space_adjust, custom_data);
	output(font->space_above, custom_data);
	output(font->space_below, custom_data);
	output(font->weight, custom_data);
	output(font->style, custom_data);
	output(font->cap_height, custom_data);
	output(font->x_height, custom_data);
	output(font->baseline_height, custom_data);
	/* Populate widths table */
	for (int i = 0; i < font->total_glyphs; i++)
		output(font->widths_table[i], custom_data);
	/* Populate bitmaps offsets table */
	next_bitmap_offset += font->total_glyphs * 2;
	for (int i = 0; i < font->total_glyphs; i++) {
		output_word((uint16_t)(next_bitmap_offset - 2 + (byte_columns(font->widths_table[i]) - 1)), output, custom_data);
		next_bitmap_offset += font->bitmaps[i]->length;
		if (next_bitmap_offset >= 0xFFF0)
			throw_error(invalid_fnt, "Output font too big to fit!");
	}
	/* Start writing glyph bitmaps */
	for (int i = 0; i < font->total_glyphs; i++)
		for (int j = 0; j < font->bitmaps[i]->length; j++)
			output(font->bitmaps[i]->bytes[j], custom_data);
}