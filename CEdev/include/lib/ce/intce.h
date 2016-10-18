/**
 * @file    INTERRUPT CE C Library
 * @version 1.0
 *
 * @section LICENSE
 *
 * Copyright (c) 2016
 * Matthew "MateoConLechuga" Waltz
 * Jacob "jacobly" Young
 * calc84maniac
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

#ifndef H_INTCE
#define H_INTCE

#include <stdint.h>

/**
 * Initizalize to use custom interrupts
 */
void int_Initialize(void);

/**
 * Resets interrupts back to the OS expected values
 */
void int_Reset(void);

/**
 * Sets up an interrupt vector given an ISR
 */
void int_SetVector(uint8_t ivect, void (*handler)(void));

/**
 * Enable/Disable global interrupts
 */
#define int_Enable()    asm("ei")
#define int_Disable()   asm("di")

/**
 * Interrupt sources
 */
#define ON_IVECT        0
#define TIMER1_IVECT    1
#define TIMER2_IVECT    2
#define TIMER3_IVECT    3
#define TIMEROS_IVECT   4
#define KEYBOARD_IVECT  10
#define LCD_IVECT       11
#define RTC_IVECT       12
#define USB_IVECT       13

/**
 * Interrupt config bitmasks
 */
#define INT_ON          1<<ON_IVECT
#define INT_TIMER1      1<<TIMER1_IVECT
#define INT_TIMER2      1<<TIMER2_IVECT
#define INT_TIMER3      1<<TIMER3_IVECT
#define INT_TIMEROS     1<<TIMEROS_IVECT
#define INT_KEYBOARD	1<<KEYBOARD_IVECT
#define INT_LCD         1<<LCD_IVECT
#define INT_RTC         1<<RTC_IVECT
#define INT_USB         1<<USB_IVECT

/**
 * Interrupt controller registers
 */
#define int_RawStatus       (*(volatile uint24_t*)0x0F00000)
#define int_MaskedStatus    (*(volatile uint24_t*)0x0F00014)
#define int_EnableConfig    (*(uint24_t*)0x0F00004)
#define int_LatchConfig     (*(uint24_t*)0x0F0000C)
#define int_InvertConfig    (*(uint24_t*)0x0F00010)
#define int_Acknowledge     (*(uint24_t*)0x0F00008)

#endif
