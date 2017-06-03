/**
 * @file
 * @authors Matt "MateoConLechuga" Waltz
 * @authors Jacob "jacobly" Young
 * @brief USB communication routines
 */

#ifndef H_USB
#define H_USB

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @returns True if the usb bus line is powered, i.e. connected to a another calc
 */
bool usb_BusPowered(void);

/**
 * @returns True if the usb is self powered
 */
bool usb_SelfPowered(void);

/**
 * Resets the usb controller chip
 */
void usb_ResetChip(void);

/**
 * Disables the usb timer interrupt (timer 3)
 */
void usb_DisableTimers(void);

/**
 * Enables the usb timer interrupt (timer 3)
 */
void usb_EnableTimers(void);

/**
 * Resets the usb timer interrupt (timer 3)
 */
void usb_ResetTimers(void);

#ifdef __cplusplus
}
#endif

#endif
