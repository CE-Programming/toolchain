/**
 * @file
 * @brief Interrupt configuring and setting.
 * @author Matt "MateoConLechuga" Waltz
 * @author Jacob "jacobly" Young
 *
 * This file provides routines for setting custom interrupt vectors
 * for your program. Note that TI broke interrupt support in hardware
 * revisions >= I, and they will not work. Use at your own risk.
 */

#ifndef _INTCE_H
#define _INTCE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enable global interrupts
 */
#define int_Enable() \
asm("ei")

/**
 * @brief Diasble global interrupts
 */
#define int_Disable() \
asm("di")

/**
 * @brief Blocking wait for an interrupt to trigger
 */
#define int_Wait() \
asm("halt")

#define ON_IVECT        0  /**< [on] key interrupt source        */
#define TIMER1_IVECT    1  /**< Timer 1 interrupt source         */
#define TIMER2_IVECT    2  /**< Timer 2 interrupt source         */
#define TIMER3_IVECT    3  /**< Timer 3 interrupt source         */
#define TIMEROS_IVECT   4  /**< Timer OS interrupt source        */
#define KEYBOARD_IVECT  10 /**< Keyboard interrupt source        */
#define LCD_IVECT       11 /**< LCD interrupt source             */
#define RTC_IVECT       12 /**< Real Time Clock interrupt source */
#define USB_IVECT       13 /**< USB interrupt source             */

#define INT_ON          (1<<ON_IVECT)       /**< [on] key interrupt source mask        */
#define INT_TIMER1      (1<<TIMER1_IVECT)   /**< Timer 1 interrupt source mask         */
#define INT_TIMER2      (1<<TIMER2_IVECT)   /**< Timer 2 interrupt source mask         */
#define INT_TIMER3      (1<<TIMER3_IVECT)   /**< Timer 3 interrupt source mask         */
#define INT_TIMEROS     (1<<TIMEROS_IVECT)  /**< Timer OS interrupt source mask        */
#define INT_KEYBOARD    (1<<KEYBOARD_IVECT) /**< Keyboard interrupt source mask        */
#define INT_LCD         (1<<LCD_IVECT)      /**< LCD interrupt source mask             */
#define INT_RTC         (1<<RTC_IVECT)      /**< Real Time Clock interrupt source mask */
#define INT_USB         (1<<USB_IVECT)      /**< USB interrupt source mask             */

#define int_RawStatus       (*(volatile uint24_t*)0x0F00000) /**< State of interrupt signals        */
#define int_MaskedStatus    (*(volatile uint24_t*)0x0F00014) /**< Masked state of interrupt signals */
#define int_EnableConfig    (*(volatile uint24_t*)0x0F00004) /**< Enabled interrupt signals         */
#define int_LatchConfig     (*(volatile uint24_t*)0x0F0000C) /**< Latchable interrupt signals       */
#define int_InvertConfig    (*(volatile uint24_t*)0x0F00010) /**< Invertable interrupt signals      */
#define int_Acknowledge     (*(volatile uint24_t*)0x0F00008) /**< Acknowledge interrupt signals     */

#ifdef FORCE_INTERRUPTS
#warning TI broke interrupt support on CE models with hardware revision >= I. Use at your own risk.

/**
 * Initizalize to use custom interrupts.
 *
 * @note Saves status of current interrupt state.
 * @warning TI broke interrupt support on CE models with hardware revision >= I.
 */
void int_Initialize(void);

/**
 * Resets interrupts back to the OS expected values.
 *
 * @warning Must have called int_Initialize before using.
 * @warning TI broke interrupt support on CE models with hardware revision >= I.
 */
void int_Reset(void);

/**
 * Sets up an interrupt vector given an ISR.
 *
 * @param[in] ivect Interrupt vector to set.
 * @param[in] handler Handler to interrupt service routine.
 * @warning TI broke interrupt support on CE models with hardware revision >= I.
 */
void int_SetVector(uint8_t ivect, void (*handler)(void));

#endif

#ifdef __cplusplus
}
#endif

#endif
