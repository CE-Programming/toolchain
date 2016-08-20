/**
 * @file    KEYPADC CE C Library
 * @version 1.1
 *
 * @section LICENSE
 *
 * Copyright (c) 2016
 * Matthew Waltz
 * Shaun "Methsoft" McFall
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @section DESCRIPTION
 *
 * This library implements some simple keyboard reading routines
 */

#ifndef H_KEYPADC
#define H_KEYPADC

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t kb_key_t;
typedef uint16_t kb_lkey_t;

/**
 * Scans the given keyboard row and returns the row value
 * Note: Disables interrupts during execution, and restores on completion
 */
uint8_t kb_ScanGroup(uint8_t row);

/**
 * Scans the keyboard quickly to tell if any key was pressed
 * Note: Disables interrupts during execution, and restores on completion
 */
uint8_t kb_AnyKey(void);

/**
 * Scans the keyboard to update data values
 * Note: Disables interrupts during execution, and restores on completion
 */
void kb_Scan(void);

/**
 * Resets the keyboard
 * Only use if you modify keyboard timers or number of rows
 */
void kb_Reset(void);

/**
 * Keyboard group 0 (Unused)
 */
#define kb_group_0      0

/**
 * Keyboard group 1
 */
#define kb_group_1    1
#define kb_Graph      1<<0
#define kb_Trace      1<<1
#define kb_Zoom       1<<2
#define kb_Window     1<<3
#define kb_Yequ       1<<4
#define kb_2nd        1<<5
#define kb_Mode       1<<6
#define kb_Del        1<<7

/**
 * Keyboard group 2
 */
#define kb_group_2    2
#define kb_Store      1<<1
#define kb_Ln         1<<2
#define kb_Log        1<<3
#define kb_Square     1<<4
#define kb_Recip      1<<5
#define kb_Math       1<<6
#define kb_Alpha      1<<7

/**
 * Keyboard group 3
 */
#define kb_group_3    3
#define kb_0          1<<0
#define kb_1          1<<1
#define kb_4          1<<2
#define kb_7          1<<3
#define kb_Comma      1<<4
#define kb_Sin        1<<5
#define kb_Apps       1<<6
#define kb_GraphVar   1<<7

/**
 * Keyboard group 4
 */
#define kb_group_4    4
#define kb_DecPnt     1<<0
#define kb_2          1<<1
#define kb_5          1<<2
#define kb_8          1<<3
#define kb_LParen     1<<4
#define kb_Cos        1<<5
#define kb_Pgrm       1<<6
#define kb_Stat       1<<7

/**
 * Keyboard group 5
 */
#define kb_group_5    5
#define kb_Chs        1<<0
#define kb_3          1<<1
#define kb_6          1<<2
#define kb_9          1<<3
#define kb_RParen     1<<4
#define kb_Tan        1<<5
#define kb_Vars       1<<6

/**
 * Keyboard group 6
 */
#define kb_group_6    6
#define kb_Enter      1<<0
#define kb_Add        1<<1
#define kb_Sub        1<<2
#define kb_Mul        1<<3
#define kb_Div        1<<4
#define kb_Power      1<<5
#define kb_Clear      1<<6

/**
 * Keyboard group 7
 */
#define kb_group_7    7
#define kb_Down       1<<0
#define kb_Left       1<<1
#define kb_Right      1<<2
#define kb_Up         1<<3

#define kb_dataArray ((uint16_t*)0xF50010)

/**
* Keyboard group 1
*/
#define kb_KeyGraph           (kb_lkey_t)(1 << 8 | 1<<0)
#define key_trace             (kb_lkey_t)(1 << 8 | 1<<1)
#define kb_KeyZoom            (kb_lkey_t)(1 << 8 | 1<<2)
#define kb_KeyWindow          (kb_lkey_t)(1 << 8 | 1<<3)
#define kb_KeyYequ            (kb_lkey_t)(1 << 8 | 1<<4)
#define kb_Key2nd             (kb_lkey_t)(1 << 8 | 1<<5)
#define kb_KeyMode            (kb_lkey_t)(1 << 8 | 1<<6)
#define kb_KeyDel             (kb_lkey_t)(1 << 8 | 1<<7)

/**
* Keyboard group 2
*/
#define kb_KeyStore           (kb_lkey_t)(2 << 8 | 1<<1)
#define kb_KeyLn              (kb_lkey_t)(2 << 8 | 1<<2)
#define kb_KeyLog             (kb_lkey_t)(2 << 8 | 1<<3)
#define kb_KeySquare          (kb_lkey_t)(2 << 8 | 1<<4)
#define kb_KeyRecip           (kb_lkey_t)(2 << 8 | 1<<5)
#define kb_KeyMath            (kb_lkey_t)(2 << 8 | 1<<6)
#define kb_KeyAlpha           (kb_lkey_t)(2 << 8 | 1<<7)

/**
* Keyboard group 3
*/
#define kb_Key0               (kb_lkey_t)(3 << 8 | 1<<0)
#define kb_Key1               (kb_lkey_t)(3 << 8 | 1<<1)
#define kb_Key4               (kb_lkey_t)(3 << 8 | 1<<2)
#define kb_Key7               (kb_lkey_t)(3 << 8 | 1<<3)
#define kb_KeyComma           (kb_lkey_t)(3 << 8 | 1<<4)
#define kb_KeySin             (kb_lkey_t)(3 << 8 | 1<<5)
#define kb_KeyApps            (kb_lkey_t)(3 << 8 | 1<<6)
#define kb_KeyGraphVar        (kb_lkey_t)(3 << 8 | 1<<7)

/**
* Keyboard group 4
*/
#define kb_KeyDecPnt          (kb_lkey_t)(4 << 8 | 1<<0)
#define kb_Key2               (kb_lkey_t)(4 << 8 | 1<<1)
#define kb_Key5               (kb_lkey_t)(4 << 8 | 1<<2)
#define kb_Key8               (kb_lkey_t)(4 << 8 | 1<<3)
#define kb_KeyLParen          (kb_lkey_t)(4 << 8 | 1<<4)
#define kb_KeyCos             (kb_lkey_t)(4 << 8 | 1<<5)
#define kb_KeyPgrm            (kb_lkey_t)(4 << 8 | 1<<6)
#define kb_KeyStat            (kb_lkey_t)(4 << 8 | 1<<7)

/**
* Keyboard group 5
*/
#define kb_KeyChs            (kb_lkey_t)(5 << 8 | 1<<0)
#define kb_Key3              (kb_lkey_t)(5 << 8 | 1<<1)
#define kb_Key6              (kb_lkey_t)(5 << 8 | 1<<2)
#define kb_Key9              (kb_lkey_t)(5 << 8 | 1<<3)
#define kb_KeyRParen         (kb_lkey_t)(5 << 8 | 1<<4)
#define key_tan              (kb_lkey_t)(5 << 8 | 1<<5)
#define kb_KeyVars           (kb_lkey_t)(5 << 8 | 1<<6)

/**
* Keyboard group 6
*/
#define kb_KeyEnter          (kb_lkey_t)(6 << 8 | 1<<0)
#define kb_KeyAdd            (kb_lkey_t)(6 << 8 | 1<<1)
#define kb_KeySub            (kb_lkey_t)(6 << 8 | 1<<2)
#define kb_KeyMul            (kb_lkey_t)(6 << 8 | 1<<3)
#define kb_KeyDiv            (kb_lkey_t)(6 << 8 | 1<<4)
#define kb_KeyPower          (kb_lkey_t)(6 << 8 | 1<<5)
#define kb_KeyClear          (kb_lkey_t)(6 << 8 | 1<<6)

/**
* Keyboard group 7
*/
#define kb_KeyDown           (kb_lkey_t)(7 << 8 | 1<<0)
#define kb_KeyLeft           (kb_lkey_t)(7 << 8 | 1<<1)
#define kb_KeyRight          (kb_lkey_t)(7 << 8 | 1<<2)
#define kb_KeyUp             (kb_lkey_t)(7 << 8 | 1<<3)

#endif
