/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI's keyboard interface defines
 */

#ifndef TI_GETCSC_H
#define TI_GETCSC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/** `uint8_t`: Cached GetCSC code. */
#define os_KbdScanCode       (*(uint8_t*)0xD00587)
/* @cond */
#define os_KbdLGSC           (*(uint8_t*)0xD00588)
#define os_KbdPSC            (*(uint8_t*)0xD00589)
#define os_KbdWUR            (*(uint8_t*)0xD0058A)
#define os_KbdDebncCnt       (*(uint8_t*)0xD0058B)
/* @endcond */

/**
 * Checks if the [on] key was pressed
 *
 * @returns True is returned if [on] key was pressed
 */
bool boot_CheckOnPressed(void);

/**
 * Performs an OS call to get the keypad scan code. This function does NOT block, use os_GetKey() if you need blocking.
 *
 * This function does NOT account for 2nd/alpha modifiers. Use os_getKey() if you need to account for those
 *
 * You can also use this function to get input from the user as a string like this:
 * @code{.cpp}
 * const char *chars = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
 * uint8_t key, i = 0;
 * char buffer[50];
 *
 * while((key = os_GetCSC()) != sk_Enter) {
 *     if(chars[key]) {
 *         buffer[i++] = chars[key];
 *     }
 * }
 * @endcode
 * Feel free to modify the string to suit your needs.
 * @returns Keypad scan code or 0 if no key is pressed
 */
uint8_t os_GetCSC(void);

#define sk_Down             0x01
#define sk_Left             0x02
#define sk_Right            0x03
#define sk_Up               0x04
#define sk_Enter            0x09
#define sk_2nd              0x36
/** TI-84 Plus CE name */
#define sk_Clear            0x0F
#define sk_Alpha            0x30
#define sk_Add              0x0A
/** Subtract, not negate */
#define sk_Sub              0x0B
#define sk_Mul              0x0C
#define sk_Div              0x0D
#define sk_Graph            0x31
#define sk_Trace            0x32
#define sk_Zoom             0x33
/** TI-84 Plus CE name */
#define sk_Window           0x34
/** TI-84 Plus CE name */
#define sk_Yequ             0x35
#define sk_Mode             0x37
 /** TI-84 Plus CE name */
#define sk_Del              0x38
#define sk_Store            0x2A
#define sk_Ln               0x2B
#define sk_Log              0x2C
#define sk_Square           0x2D
 /** TI-84 Plus CE [x^-1]; on the TI-83 Premium CE, this is [<>] */
#define sk_Recip            0x2E
#define sk_Math             0x2F
#define sk_0                0x21
#define sk_1                0x22
#define sk_4                0x23
#define sk_7                0x24
#define sk_2                0x1A
#define sk_5                0x1B
#define sk_8                0x1C
#define sk_3                0x12
#define sk_6                0x13
#define sk_9                0x14
#define sk_Comma            0x25
/** TI-84 Plus CE; on the TI-83 Premium CE, this is [TRIG]  */
#define sk_Sin              0x26
/** TI-84 Plus CE; on the TI-83 Premium CE, this is [MATRICE] */
#define sk_Apps             0x27
/** X, T, theta, n */
#define sk_GraphVar         0x28
#define sk_DecPnt           0x19
#define sk_LParen           0x1D
/** TI-84 Plus CE; on the TI-83 Premium CE, this is [RESOL] */
#define sk_Cos              0x1E
#define sk_Prgm             0x1F
#define sk_Stat             0x20
 /** Unary negation, not subtraction */
#define sk_Chs              0x11
#define sk_RParen           0x15
/** TI-84 Plus CE; on; the TI-83 Premium CE, this is the fraction template */
#define sk_Tan              0x16
#define sk_Vars             0x17
/** [^] */
#define sk_Power            0x0E

/* For the TI-83 Premium CE */
/** TI-83 Premium CE name */
#define sk_Fenetre          sk_Window
/** TI-83 Premium CE name */
#define sk_Fx               sk_Yequ
/** TI-83 Premium CE name */
#define sk_Suppr            sk_Del
/** TI-83 Premium CE [<>]; it's [x^-1] on the TI-84 Plus CE */
#define sk_TglExact         sk_Recip
/** TI-83 Premium CE; on the TI-84 Plus CE, this is [SIN] */
#define sk_Trig             sk_Sin
/** TI-83 Premium CE; on the TI-84 Plus CE, this is [APPS] */
#define sk_Matrice          sk_Apps
/** TI-83 Premium CE; on the TI-84 Plus CE, this is [COS] */
#define sk_Resol            sk_Cos
/** TI-83 Premium CE; on the TI-84 Plus CE, this is [TAN] */
#define sk_Frac             sk_Tan
/** TI-83 Premium CE name */
#define sk_Annul            sk_Clear

/* compatibility defines */
/* @cond */
typedef uint8_t sk_key_t;
/* @endcond */

#ifdef __cplusplus
}
#endif

#endif
