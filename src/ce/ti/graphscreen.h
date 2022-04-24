/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS graphscreen and small font text routines.
 * The API here isn't really fleshed out so this is of limited usefulness outside of displaying text in TI's small font.
 */

#ifndef _TI_GRAPH_H
#define _TI_GRAPH_H

#include <stdint.h>
#include <ti/real.h>

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

/**
 * The following are variables that are always allocated.
 * 
 * Most of these are found under the [VARS] menu.
 * They are all `real_t`.
 */
#define os_uXMin             (*(real_t*)0xD01D61)
#define os_uXMax             (*(real_t*)0xD01D6A)
#define os_uXScl             (*(real_t*)0xD01D73)
#define os_uYMin             (*(real_t*)0xD01D7C)
#define os_uYMax             (*(real_t*)0xD01D85)
#define os_uYScl             (*(real_t*)0xD01D8E)
#define os_uThetaMin         (*(real_t*)0xD01D97)
#define os_uThetaMax         (*(real_t*)0xD01DA0)
#define os_uThetaStep        (*(real_t*)0xD01DA9)
#define os_uTmin             (*(real_t*)0xD01DB2)
#define os_uTmax             (*(real_t*)0xD01DBB)
#define os_uTStep            (*(real_t*)0xD01DC4)
#define os_uPlotStart        (*(real_t*)0xD01DCD)
#define os_unMax             (*(real_t*)0xD01DD6)
#define os_uu0               (*(real_t*)0xD01DDF)
#define os_uv0               (*(real_t*)0xD01DE8)
#define os_unMin             (*(real_t*)0xD01DF1)
#define os_uu02              (*(real_t*)0xD01DFA)
#define os_uv02              (*(real_t*)0xD01E03)
#define os_uw0               (*(real_t*)0xD01E0C)
#define os_uPlotStep         (*(real_t*)0xD01E15)
#define os_uXres             (*(real_t*)0xD01E1E)
#define os_uw02              (*(real_t*)0xD01E27)
#define os_XMin              (*(real_t*)0xD01E33)
#define os_XMax              (*(real_t*)0xD01E3C)
#define os_XScl              (*(real_t*)0xD01E45)
#define os_YMin              (*(real_t*)0xD01E4E)
#define os_YMax              (*(real_t*)0xD01E57)
#define os_YScl              (*(real_t*)0xD01E60)
#define os_ThetaMin          (*(real_t*)0xD01E69)
#define os_ThetaMax          (*(real_t*)0xD01E72)
#define os_ThetaStep         (*(real_t*)0xD01E7B)
#define os_TMinPar           (*(real_t*)0xD01E84)
#define os_TMaxPar           (*(real_t*)0xD01E8D)
#define os_TStep             (*(real_t*)0xD01E96)
#define os_PlotStart         (*(real_t*)0xD01E9F)
#define os_NMax              (*(real_t*)0xD01EA8)
#define os_u0                (*(real_t*)0xD01EB1)
#define os_V0                (*(real_t*)0xD01EBA)
#define os_NMin              (*(real_t*)0xD01EC3)
#define os_u02               (*(real_t*)0xD01ECC)
#define os_V02               (*(real_t*)0xD01ED5)
#define os_W0                (*(real_t*)0xD01EDE)
#define os_PlotStep          (*(real_t*)0xD01EE7)
#define os_XResO             (*(real_t*)0xD01EF0)
#define os_W02               (*(real_t*)0xD01EF9)
#define os_un1               (*(real_t*)0xD01F02)
#define os_un2               (*(real_t*)0xD01F0B)
#define os_Vn1               (*(real_t*)0xD01F14)
#define os_Vn2               (*(real_t*)0xD01F1D)
#define os_Wn1               (*(real_t*)0xD01F26)
#define os_Wn2               (*(real_t*)0xD01F2F)

/**
 * The following control the settings of the various graph equations.
 * 
 * Type: `uint8_t`
 */
#define os_Y1LineType        (*(uint8_t*)0xD024BF)
#define os_Y2LineType        (*(uint8_t*)0xD024C0)
#define os_Y3LineType        (*(uint8_t*)0xD024C1)
#define os_Y4LineType        (*(uint8_t*)0xD024C2)
#define os_Y5LineType        (*(uint8_t*)0xD024C3)
#define os_Y6LineType        (*(uint8_t*)0xD024C4)
#define os_Y7LineType        (*(uint8_t*)0xD024C5)
#define os_Y8LineType        (*(uint8_t*)0xD024C6)
#define os_Y9LineType        (*(uint8_t*)0xD024C7)
#define os_Y0LineType        (*(uint8_t*)0xD024C8)
#define os_Para1LineType     (*(uint8_t*)0xD024C9)
#define os_Para2LineType     (*(uint8_t*)0xD024CA)
#define os_Para3LineType     (*(uint8_t*)0xD024CB)
#define os_Para4LineType     (*(uint8_t*)0xD024CC)
#define os_Para5LineType     (*(uint8_t*)0xD024CD)
#define os_Para6LineType     (*(uint8_t*)0xD024CE)
#define os_Polar1LineType    (*(uint8_t*)0xD024CF)
#define os_Polar2LineType    (*(uint8_t*)0xD024D0)
#define os_Polar3LineType    (*(uint8_t*)0xD024D1)
#define os_Polar4LineType    (*(uint8_t*)0xD024D2)
#define os_Polar5LineType    (*(uint8_t*)0xD024D3)
#define os_Polar6LineType    (*(uint8_t*)0xD024D4)
#define os_SecULineType      (*(uint8_t*)0xD024D5)
#define os_SecVLineType      (*(uint8_t*)0xD024D6)
#define os_SecWLineType      (*(uint8_t*)0xD024D7)
#define os_Y1LineColor       (*(uint8_t*)0xD024D8)
#define os_Y2LineColor       (*(uint8_t*)0xD024D9)
#define os_Y3LineColor       (*(uint8_t*)0xD024DA)
#define os_Y4LineColor       (*(uint8_t*)0xD024DB)
#define os_Y5LineColor       (*(uint8_t*)0xD024DC)
#define os_Y6LineColor       (*(uint8_t*)0xD024DD)
#define os_Y7LineColor       (*(uint8_t*)0xD024DE)
#define os_Y8LineColor       (*(uint8_t*)0xD024DF)
#define os_Y9LineColor       (*(uint8_t*)0xD024E0)
#define os_Y0LineColor       (*(uint8_t*)0xD024E1)
#define os_Para1LineColor    (*(uint8_t*)0xD024E2)
#define os_Para2LineColor    (*(uint8_t*)0xD024E3)
#define os_Para3LineColor    (*(uint8_t*)0xD024E4)
#define os_Para4LineColor    (*(uint8_t*)0xD024E5)
#define os_Para5LineColor    (*(uint8_t*)0xD024E6)
#define os_Para6LineColor    (*(uint8_t*)0xD024E7)
#define os_Polar1LineColor   (*(uint8_t*)0xD024E8)
#define os_Polar2LineColor   (*(uint8_t*)0xD024E9)
#define os_Polar3LineColor   (*(uint8_t*)0xD024EA)
#define os_Polar4LineColor   (*(uint8_t*)0xD024EB)
#define os_Polar5LineColor   (*(uint8_t*)0xD024EC)
#define os_Polar6LineColor   (*(uint8_t*)0xD024ED)
#define os_SecULineColor     (*(uint8_t*)0xD024EE)
#define os_SecVLineColor     (*(uint8_t*)0xD024EF)
#define os_SecWLineColor     (*(uint8_t*)0xD024F0)

#ifdef __cplusplus
}
#endif

#endif
