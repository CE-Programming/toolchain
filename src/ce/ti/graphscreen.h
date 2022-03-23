/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS graphscreen and small font text routines
 * 
 * The API here isn't really fleshed out so this is of limited usefulness outside of displaying text in TI's small font.
 */

#ifndef _TI_GRAPH_H
#define _TI_GRAPH_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * TIOS small font.
 * @see os_FontSelect
 */
#define os_SmallFont ((font_t *)0)

/**
 * TIOS large font.
 * @see os_FontSelect
 */
#define os_LargeFont ((font_t *)1)

/**
 * @brief Structure of font description
 * @see os_FontSelect
 */
typedef struct font {
    /**
     * Points to this font itself, yuck!
     */
    struct font *font;
    /**
     * Draws a character using this font.
     * @param c The character
     */
    void (*drawChar)(char c);
    /**
     * Gets the width of a character in this font.
     * @param c The character
     */
    uint24_t (*getWidth)(char c);
    /**
     * Gets the height of this font.
     */
    uint24_t (*getHeight)(void);
} font_t;

/**
 * Selects the (monospace) font to use when drawing on the graphscreen
 *
 * @param font font id/pointer to use
 * os_SmallFont                                       <br>
 * os_LargeFont
 */
void os_FontSelect(font_t *font);

/**
 * Gets the font to use when drawing on the graphscreen
 *
 * @returns
 * 0: small font                                      <br>
 * 1: large monospace font
 */
font_t *os_FontGetID(void);

/**
 * @param string String to get pixel width of
 * @returns The width of a string in the variable-width format
 */
uint24_t os_FontGetWidth(const char *string);

/**
 * @returns The height of the font characters
 */
uint24_t os_FontGetHeight(void);

/**
 * Draws text using the small font to the screen
 *
 * @param string String to draw
 * @param col Column to start drawing at
 * @param row Row to start drawing at
 * @returns The end column
 */
uint24_t os_FontDrawText(const char *string, uint16_t col, uint8_t row);

/**
 * Draws transparent text using the small font to the screen
 *
 * @param string String to draw
 * @param col Column to start drawing at
 * @param row Row to start drawing at
 * @returns The end column
 */
uint24_t os_FontDrawTransText(const char *string, uint16_t col, uint8_t row);

/**
 * Sets the foreground color used to draw text on the graphscreen
 * @param color 565 BGR color to set text foreground to
 */
void os_SetDrawFGColor(uint24_t color);

/**
 * Gets the foreground color used to draw text on the graphscreen
 * @returns 565 BGR color of text foreground
 */
uint24_t os_GetDrawFGColor(void);

/**
 * Sets the background color used to draw text on the graphscreen
 * @param color 565 BGR color to set text background to
 */
void os_SetDrawBGColor(uint24_t color);

/**
 * Gets the background color used to draw text on the graphscreen
 *
 * @returns 565 BGR color of text nackground
 * @warning Only useable in OS 5.2 and above; use at your own risk
 */
uint24_t os_GetDrawBGColor(void);

#define os_PenCol            (*(uint24_t*)0xD008D2) /**< Small font column location. */
#define os_PenRow            (*(uint8_t*)0xD008D5)  /**< Small font row location. */
#define os_DrawBGColor       (*(uint16_t*)0xD026AA)        /**< Small font background color */
#define os_DrawFGColor       (*(uint16_t*)0xD026AC)        /**< Small font foreground color */
#define os_DrawColorCode     (*(uint8_t*)0xD026AE)
#define os_GraphBGColor      (*(uint16_t*)0xD02A98)        /**< Graph background 565 color */
#define os_FillRectColor     (*(uint16_t*)0xD02AC0)

#ifdef __cplusplus
}
#endif

#endif
