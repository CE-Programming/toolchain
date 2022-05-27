/**
 * @file
 * @brief keypadc is a simple direct-input keypad library.
 *
 * @author Matt "MateoConLechuga" Waltz
 * @author Shaun "Merthsoft" McFall
 */

#ifndef _KEYPADC_H
#define _KEYPADC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t kb_key_t;   /**< Normal key type. */
typedef uint16_t kb_lkey_t; /**< Long key type.   */

/**
 * Scans the keyboard to update data values.
 * @note Disables interrupts.
 */
void kb_Scan(void);

/**
 * Scans the given keyboard row and returns the row value.
 * @param[in] row Row to scan.
 * @note Disables interrupts.
 */
kb_key_t kb_ScanGroup(uint8_t row);

/**
 * Scans the keyboard quickly to tell if any key was pressed.
 * @note Disables interrupts.
 */
uint8_t kb_AnyKey(void);

/**
 * Resets the keyboard before returning to the OS.
 * @note Only use if the keyboard timers or number of rows have been modified.
 */
void kb_Reset(void);

/**
 * @brief Sets the keypad scanning mode.
 * @see kb_scan_mode_t
 */
#define kb_SetMode(mode) \
(kb_Config = ((kb_Config & ~3)|(mode)))

/**
 * @brief Gets the keypad scanning mode.
 * @see kb_scan_mode_t
 */
#define kb_GetMode() \
(kb_Config & 3)

/**
 * Different available scanning modes.
 */
typedef enum {
    MODE_0_IDLE = 0,       /**< Keypad scanning is idle. */
    MODE_1_INDISCRIMINATE, /**< Indiscriminate key detection. Data registers are invalid, but when any key is pressed, interrupt KB_MODE_1_PRESS is set (and cannot be cleared until the key is released). */
    MODE_2_SINGLE,         /**< Single scan. The keypad is scanned once, and then the mode returns to MODE_0_IDLE. */
    MODE_3_CONTINUOUS      /**< Continuous scan. When scanning completes, it just starts over again after a delay. */
} kb_scan_mode_t;

#define kb_EnableInt \
(*(uint8_t*)0xF5000C)          /**< Enabled keypad interrupt signals. */
#define kb_IntAcknowledge \
(*(volatile uint8_t*)0xF50008) /**< Acknowledege keypad interrupt signals. */
#define kb_IntStatus \
(*(volatile uint8_t*)0xF50008) /**< Status of keypad interrupt signals. */
#define kb_Config \
(*(volatile uint8_t*)0xF50000) /**< Configuration of keypad controller. */

/**
 * Checks if a key is pressed. This uses the long key type (kb_lkey_t), which includes the group as well.
 * It can be used in place of reading directly from \c kb_Data.
 *
 * Long key types have the same name as the normal key types, but are prefixed with kb_Key* rather than kb_*.
 *
 * It does not call \c kb_Scan() internally, so you have to do so before calling this if you want the keyboard data to get updated.
 */
#define kb_IsDown(lkey) \
(kb_Data[(lkey) >> 8] & (lkey))

/**
 * Keypad Data registers
 *
 * \rst
 *
 * +--------+------------+------------+------------+------------+------------+------------+------------+------------+
 * | Offset | Bit 0      | Bit 1      | Bit 2      | Bit 3      |  Bit 4     |  Bit 5     |  Bit 6     | Bit 7      |
 * +========+============+============+============+============+============+============+============+============+
 * | 1      | kb_Graph   | kb_Trace   | kb_Zoom    | kb_Window  | kb_Yequ    | kb_2nd     | kb_Mode    | kb_Del     |
 * |        |            |            |            |            |            |            |            |            |
 * |        |            |            |            | kb_Fenetre | kb_Fx      |            |            | kb_Suppr   |
 * +--------+------------+------------+------------+------------+------------+------------+------------+------------+
 * | 2      |            | kb_Sto     | kb_Ln      | kb_Log     | kb_Square  | kb_Recip   | kb_Math    | kb_Alpha   |
 * |        |            |            |            |            |            |            |            |            |
 * |        |            |            |            |            |            | kb_TglExact|            |            |
 * +--------+------------+------------+------------+------------+------------+------------+------------+------------+
 * | 3      | kb_0       | kb_1       | kb_4       | kb_7       | kb_Comma   | kb_Sin     | kb_Apps    | kb_GraphVar|
 * |        |            |            |            |            |            |            |            |            |
 * |        |            |            |            |            |            | kb_Trig    | kb_Matrice |            |
 * +--------+------------+------------+------------+------------+------------+------------+------------+------------+
 * | 4      | kb_DecPnt  | kb_2       | kb_5       | kb_8       | kb_LParen  | kb_Cos     | kb_Prgm    | kb_Stat    |
 * |        |            |            |            |            |            |            |            |            |
 * |        |            |            |            |            |            | kb_Resol   |            |            |
 * +--------+------------+------------+------------+------------+------------+------------+------------+------------+
 * | 5      | kb_Chs     | kb_3       | kb_6       | kb_9       | kb_RParen  | kb_Tan     | kb_Vars    |            |
 * |        |            |            |            |            |            |            |            |            |
 * |        |            |            |            |            |            | kb_Frac    |            |            |
 * +--------+------------+------------+------------+------------+------------+------------+------------+------------+
 * | 6      | kb_Enter   | kb_Add     | kb_Sub     | kb_Mul     | kb_Div     | kb_Power   | kb_Clear   |            |
 * |        |            |            |            |            |            |            |            |            |
 * |        |            |            |            |            |            |            | kb_Annul   |            |
 * +--------+------------+------------+------------+------------+------------+------------+------------+------------+
 * | 7      | kb_Down    | kb_Left    | kb_Right   | kb_Up      |            |            |            |            |
 * +--------+------------+------------+------------+------------+------------+------------+------------+------------+
 *
 * \endrst
 *
 * These data registers can be indexed as a normal array. For example, to check the status of the '2nd' key:
 * @code{.cpp}
 *  if (kb_Data[1] & kb_2nd) {
 *      ...
 *  }
 * @endcode
 *
 * Likewise, you can test keys with the following general format:
 * @code{.cpp}
 *  if (kb_Data[group] & kb_Name){
 *      ...
 *  }
 * @endcode
 *
 * @see kb_On
 */
#define kb_Data \
(uint8_t)((volatile uint16_t*)0xF50010)

/**
 * ON key signal.
 * @note Scanning mode does not matter.
 * @note The ON key is not wired as part of the normal key matrix. The ON key must be checked separately from the
 * other keys with kb_On:
 * @code{.cpp}
 *  int main(void) {
 *      kb_DisableOnLatch();
 *      ...
 *      if (kb_On) {
 *          ...
 *      }
 *  }
 * @endcode
 * @see kb_DisableOnLatch kb_EnableOnLatch kb_ClearOnLatch
 */
#define kb_On \
(*(volatile uint8_t*)0xF00020 & 1)

/**
 * Causes kb_On to latch when the ON is key pressed: once the ON key is pressed, kb_On will remain true until
 * reset with kb_ClearOnLatch(). This may be useful if you want to check the ON key occasionally, for example
 * as a break signal.
 * @warning This defaults to whatever the last program set this to, so be sure to set it explicitly.
 * @see kb_DisableOnLatch kb_ClearOnLatch
 */
#define kb_EnableOnLatch() \
((*(volatile uint8_t*)0xF0002C) |= 1)

/**
 * Disables ON key latching behavior.
 * @warning This defaults to whatever the last program set this to, so be sure to set it explicitly.
 * @see kb_EnableOnLatch
 */
#define kb_DisableOnLatch() \
((*(volatile uint8_t*)0xF0002C) &= ~1)

/**
 * When ON key latching has been enabled with kb_EnableOnLatch(), this will reset kb_On back to false
 * (assuming the user is no longer pressing ON).
 * @note This may persist between program runs, so be to sure to disable as needed.
 * @see kb_EnableOnLatch
 */
#define kb_ClearOnLatch() \
((*(volatile uint8_t*)0xF00028) = 1)

/**
 * Different available interrupt signals
 */
typedef enum {
    KB_SCAN_COMPLETE = 1, /**< Interrupt set when keypad is done scanning */
    KB_DATA_CHANGED = 2,  /**< Interrupt set when data is changed on a press or a release */
    KB_MODE_1_PRESS = 4   /**< Interrupt set when a key is pressed in MODE_1_INDISCRIMINATE */
} kb_int_signal_t;

/* Keyboard group 1 */
/* @cond */
#define kb_Graph    (1<<0)
#define kb_Trace    (1<<1)
#define kb_Zoom     (1<<2)
#define kb_Window   (1<<3)
#define kb_Yequ     (1<<4)
#define kb_2nd      (1<<5)
#define kb_Mode     (1<<6)
#define kb_Del      (1<<7)

/* Keyboard group 1 - 83 Premium CE key names */
#define kb_Fenetre  kb_Window
#define kb_Fx       kb_Yequ
#define kb_Suppr    kb_Del


/* Keyboard group 2 */
#define kb_Sto      (1<<1)
#define kb_Ln       (1<<2)
#define kb_Log      (1<<3)
#define kb_Square   (1<<4)
#define kb_Recip    (1<<5)
#define kb_Math     (1<<6)
#define kb_Alpha    (1<<7)

/* Keyboard group 2 - 83 Premium CE key names */
#define kb_TglExact kb_Recip


/* Keyboard group 3 */
#define kb_0        (1<<0)
#define kb_1        (1<<1)
#define kb_4        (1<<2)
#define kb_7        (1<<3)
#define kb_Comma    (1<<4)
#define kb_Sin      (1<<5)
#define kb_Apps     (1<<6)
#define kb_GraphVar (1<<7)

/* Keyboard group 3 - 83 Premium CE key names */
#define kb_Trig     kb_Sin
#define kb_Matrice  kb_Apps


/* Keyboard group 4 */
#define kb_DecPnt   (1<<0)
#define kb_2        (1<<1)
#define kb_5        (1<<2)
#define kb_8        (1<<3)
#define kb_LParen   (1<<4)
#define kb_Cos      (1<<5)
#define kb_Prgm     (1<<6)
#define kb_Stat     (1<<7)

/* Keyboard group 4 - 83 Premium CE key names */
#define kb_Resol    kb_Cos


/* Keyboard group 5 */
#define kb_Chs      (1<<0)
#define kb_3        (1<<1)
#define kb_6        (1<<2)
#define kb_9        (1<<3)
#define kb_RParen   (1<<4)
#define kb_Tan      (1<<5)
#define kb_Vars     (1<<6)

/* Keyboard group 5 - 83 Premium CE key names */
#define kb_Frac     kb_Tan


/* Keyboard group 6 */
#define kb_Enter    (1<<0)
#define kb_Add      (1<<1)
#define kb_Sub      (1<<2)
#define kb_Mul      (1<<3)
#define kb_Div      (1<<4)
#define kb_Power    (1<<5)
#define kb_Clear    (1<<6)

/* Keyboard group 5 - 83 Premium CE key names */
#define kb_Annul    kb_Clear


/* Keyboard group 7 */
#define kb_Down     (1<<0)
#define kb_Left     (1<<1)
#define kb_Right    (1<<2)
#define kb_Up       (1<<3)


/* Keyboard group 1 */
#define kb_KeyGraph     ((kb_lkey_t)(1 << 8 | 1<<0))
#define kb_KeyTrace     ((kb_lkey_t)(1 << 8 | 1<<1))
#define kb_KeyZoom      ((kb_lkey_t)(1 << 8 | 1<<2))
#define kb_KeyWindow    ((kb_lkey_t)(1 << 8 | 1<<3))
#define kb_KeyYequ      ((kb_lkey_t)(1 << 8 | 1<<4))
#define kb_Key2nd       ((kb_lkey_t)(1 << 8 | 1<<5))
#define kb_KeyMode      ((kb_lkey_t)(1 << 8 | 1<<6))
#define kb_KeyDel       ((kb_lkey_t)(1 << 8 | 1<<7))

/* Keyboard group 1 - 83 Premium CE key names */
#define kb_KeyFenetre   kb_KeyWindow
#define kb_KeyFx        kb_KeyYequ
#define kb_KeySuppr     kb_KeyDel


/* Keyboard group 2 */
#define kb_KeySto       ((kb_lkey_t)(2 << 8 | 1<<1))
#define kb_KeyLn        ((kb_lkey_t)(2 << 8 | 1<<2))
#define kb_KeyLog       ((kb_lkey_t)(2 << 8 | 1<<3))
#define kb_KeySquare    ((kb_lkey_t)(2 << 8 | 1<<4))
#define kb_KeyRecip     ((kb_lkey_t)(2 << 8 | 1<<5))
#define kb_KeyMath      ((kb_lkey_t)(2 << 8 | 1<<6))
#define kb_KeyAlpha     ((kb_lkey_t)(2 << 8 | 1<<7))

/* Keyboard group 2 - 83 Premium CE key names */
#define kb_KeyTglExact  kb_KeyRecip


/* Keyboard group 3 */
#define kb_Key0         ((kb_lkey_t)(3 << 8 | 1<<0))
#define kb_Key1         ((kb_lkey_t)(3 << 8 | 1<<1))
#define kb_Key4         ((kb_lkey_t)(3 << 8 | 1<<2))
#define kb_Key7         ((kb_lkey_t)(3 << 8 | 1<<3))
#define kb_KeyComma     ((kb_lkey_t)(3 << 8 | 1<<4))
#define kb_KeySin       ((kb_lkey_t)(3 << 8 | 1<<5))
#define kb_KeyApps      ((kb_lkey_t)(3 << 8 | 1<<6))
#define kb_KeyGraphVar  ((kb_lkey_t)(3 << 8 | 1<<7))

/* Keyboard group 3 - 83 Premium CE key names */
#define kb_KeyTrig      kb_KeySin
#define kb_KeyMatrice   kb_KeyApps


/* Keyboard group 4 */
#define kb_KeyDecPnt    ((kb_lkey_t)(4 << 8 | 1<<0))
#define kb_Key2         ((kb_lkey_t)(4 << 8 | 1<<1))
#define kb_Key5         ((kb_lkey_t)(4 << 8 | 1<<2))
#define kb_Key8         ((kb_lkey_t)(4 << 8 | 1<<3))
#define kb_KeyLParen    ((kb_lkey_t)(4 << 8 | 1<<4))
#define kb_KeyCos       ((kb_lkey_t)(4 << 8 | 1<<5))
#define kb_KeyPrgm      ((kb_lkey_t)(4 << 8 | 1<<6))
#define kb_KeyStat      ((kb_lkey_t)(4 << 8 | 1<<7))

/* Keyboard group 4 - 83 Premium CE key names */
#define kb_KeyResol     kb_KeyCos


/* Keyboard group 5 */
#define kb_KeyChs      ((kb_lkey_t)(5 << 8 | 1<<0))
#define kb_Key3        ((kb_lkey_t)(5 << 8 | 1<<1))
#define kb_Key6        ((kb_lkey_t)(5 << 8 | 1<<2))
#define kb_Key9        ((kb_lkey_t)(5 << 8 | 1<<3))
#define kb_KeyRParen   ((kb_lkey_t)(5 << 8 | 1<<4))
#define kb_KeyTan      ((kb_lkey_t)(5 << 8 | 1<<5))
#define kb_KeyVars     ((kb_lkey_t)(5 << 8 | 1<<6))

/* Keyboard group 5 - 83 Premium CE key names */
#define kb_KeyFrac     kb_KeyTan


/* Keyboard group 6 */
#define kb_KeyEnter    ((kb_lkey_t)(6 << 8 | 1<<0))
#define kb_KeyAdd      ((kb_lkey_t)(6 << 8 | 1<<1))
#define kb_KeySub      ((kb_lkey_t)(6 << 8 | 1<<2))
#define kb_KeyMul      ((kb_lkey_t)(6 << 8 | 1<<3))
#define kb_KeyDiv      ((kb_lkey_t)(6 << 8 | 1<<4))
#define kb_KeyPower    ((kb_lkey_t)(6 << 8 | 1<<5))
#define kb_KeyClear    ((kb_lkey_t)(6 << 8 | 1<<6))

/* Keyboard group 6 - 83 Premium CE key names */
#define kb_KeyAnnul    kb_KeyClear

/* Keyboard group 7 */
#define kb_KeyDown     ((kb_lkey_t)(7 << 8 | 1<<0))
#define kb_KeyLeft     ((kb_lkey_t)(7 << 8 | 1<<1))
#define kb_KeyRight    ((kb_lkey_t)(7 << 8 | 1<<2))
#define kb_KeyUp       ((kb_lkey_t)(7 << 8 | 1<<3))


/* Compatibility defines */
#define kb_DataArray    _Pragma("GCC warning \"'kb_DataArray' is deprecated, check if you can use 'kb_Data' instead\"") ((volatile uint16_t*)0xF50010)
#define kb_dataArray    kb_DataArray
#define kb_Store        _Pragma("GCC warning \"'kb_Store' is deprecated, use 'kb_Sto' instead\"") kb_Sto
#define kb_KeyStore     _Pragma("GCC warning \"'kb_KeyStore' is deprecated, use 'kb_KeySto' instead\"") kb_KeySto
#define kb_KeyPgrm      _Pragma("GCC warning \"'kb_KeyPgrm' is deprecated, use 'kb_KeyPrgm' instead\"") kb_KeyPrgm
#define kb_group_0      _Pragma("GCC warning \"'kb_group_0' is deprecated, use '0' instead\"") 0
#define kb_group_1      _Pragma("GCC warning \"'kb_group_1' is deprecated, use '1' instead\"") 1
#define kb_group_2      _Pragma("GCC warning \"'kb_group_2' is deprecated, use '2' instead\"") 2
#define kb_group_3      _Pragma("GCC warning \"'kb_group_3' is deprecated, use '3' instead\"") 3
#define kb_group_4      _Pragma("GCC warning \"'kb_group_4' is deprecated, use '4' instead\"") 4
#define kb_group_5      _Pragma("GCC warning \"'kb_group_5' is deprecated, use '5' instead\"") 5
#define kb_group_6      _Pragma("GCC warning \"'kb_group_6' is deprecated, use '6' instead\"") 6
#define kb_group_7      _Pragma("GCC warning \"'kb_group_7' is deprecated, use '7' instead\"") 7
/* @endcond */

#ifdef __cplusplus
}
#endif

#endif
