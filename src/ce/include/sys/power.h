/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief CE power control functions define file (APD/on/off/battery/charging)
 */

#ifndef SYS_POWER_H
#define SYS_POWER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* @cond */
#define tiflags __attribute__((__tiflags__))
/* @endcond */

/**
 * Routine to turn off APD
 */
tiflags void os_DisableAPD(void);

/**
 * Routine to turn on APD
 */
tiflags void os_EnableAPD(void);

/**
 * Turns on the calculator
 */
void boot_TurnOn(void);

/**
 * Turns off the calculator (probably not a good idea to use, is likely to leak memory)
 */
void boot_TurnOff(void);

/* On the one hand, these don't make too much sense here.  On the other hand, why would you use them? */
/**
 * Runs the calulator at 6 MHz
 */
void boot_Set6MHzMode(void);

/**
 * Runs the calulator at 48 MHz
 */
void boot_Set48MHzMode(void);

/**
 * Runs the calulator at 6 MHz (saves interrupt status)
 */
void boot_Set6MHzModeI(void);

/**
 * Runs the calulator at 48 MHz (saves interrupt status)
 */
void boot_Set48MHzModeI(void);

/**
 * @returns Current battery status
 */
tiflags uint8_t boot_GetBatteryStatus(void);

/**
 * @returns A non-zero value if the battery is charging.
 */
uint8_t boot_BatteryCharging(void);


#define os_ApdFlags          (*(uint8_t*)0xD00088)
#define os_ApdSubTimer       (*(uint8_t*)0xD00590)
#define os_ApdTimer          (*(uint8_t*)0xD00591)

#define os_BatteryStatus     (*(uint8_t*)0xD02A86)

#undef tiflags

#ifdef __cplusplus
}
#endif

#endif
