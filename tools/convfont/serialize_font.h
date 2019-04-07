#pragma once

#include "convfont.h"

/* Compute the total size, in bytes, a font will be.
 * @param font A pointer to the font to find the size of
 * @return The size of the font */
int compute_font_size(fontlib_font_t *font);

/* The idea of this system with an output callback with custom_data is that you
 * can specify how exactly to output data.  For an output binary file, you can
 * pass a wrapper for fputc(); for a static C or assembly array, you can have it
 * produce hex bytes. */
void output_word(uint16_t data, void(*output)(uint8_t byte, void *custom_data), void *custom_data);

void output_ezword(uint32_t data, void(*output)(uint8_t byte, void *custom_data), void *custom_data);

/* Serializes a FontLib font into bytes.
 * @param font The font to serialize
 * @param output A function to use to serialize the bytes. custom_data can be
 * any data you like, such a FILE struct.
 */
void serialize_font(fontlib_font_t *font, void(*output)(uint8_t byte, void *custom_data), void *custom_data);
