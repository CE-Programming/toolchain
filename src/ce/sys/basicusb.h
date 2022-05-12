/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS USB routines
 */

#ifndef SYS_BASIC_USB_H
#define SYS_BASIC_USB_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @returns True if the USB bus is powered by a host.
 */
bool boot_USBBusPowered(void);

/**
 * @returns True if the USB bus is self-powered.
 */
bool boot_USBSelfPowered(void);

/**
 * Resets the USB controller.
 */
void boot_USBResetChip(void);

/**
 * Disables the USB Timers.
 */
void boot_USBDisableTimers(void);

/**
 * Enables the USB Timers.
 */
void boot_USBEnableTimers(void);

/**
 * Resets the USB Timers.
 */
void boot_USBResetTimers(void);

/**
 * Gets some status after a control request.
 * @return Some status in the range [0, 3].
 */
int8_t os_USBGetRequestStatus(void);

#ifdef __cplusplus
}
#endif

#endif
