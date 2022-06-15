/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS standard TI user interface stuff.
 * Has run indicator, status bar, TI colors, and user-specified brightness.
 */

#ifndef TI_UI_H
#define TI_UI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* @cond */
#define tiflags __attribute__((__tiflags__))
/* @endcond */

/*
 * Bootcode functions
 */

/* I'm just throwing this in here since there isn't really a better-matching place.
   It doesn't really seem like a homescreen routine. */
/**
 * Turns all of VRAM into 0xFF (white)
 */
void boot_ClearVRAM(void);

/*
 * OS Routines
 */

/**
 * Routine to turn on the Run Indicator
 */
tiflags void os_RunIndicOn(void);

/**
 * Routine to turn off the Run Indicator
 */
tiflags void os_RunIndicOff(void);

/**
 * Routine to redraw the status bar
 */
tiflags void os_DrawStatusBar(void);

/**
 * Executes the assembly routine _ForceCmdNoChar
 * 
 * Probably not a good idea to use in a program.
 */
void os_ForceCmdNoChar(void);

/**
 * Colors used by the OS
 */
typedef enum {
    OS_COLOR_BLUE = 10,
    OS_COLOR_RED,
    OS_COLOR_BLACK,
    OS_COLOR_MAGENTA,
    OS_COLOR_GREEN,
    OS_COLOR_ORANGE,
    OS_COLOR_BROWN,
    OS_COLOR_NAVY,
    OS_COLOR_LTBLUE,
    OS_COLOR_YELLOW,
    OS_COLOR_WHITE,
    OS_COLOR_LTGRAY,
    OS_COLOR_MEDGRAY,
    OS_COLOR_GRAY,
    OS_COLOR_DARKGRAY
} os_colors_t;

/** `uint8_t`: User's configured screen brightness */
#define os_Brightness        (*(uint8_t*)0xD0058F)
/** `uint16_t`: Status bar 565 color */
#define os_StatusBarBGColor  (*(uint16_t*)0xD02ACC)

#undef tiflags

#ifdef __cplusplus
}
#endif

#endif
