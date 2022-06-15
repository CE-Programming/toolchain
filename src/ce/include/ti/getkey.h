/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI's keyboard interface defines
 */

#ifndef TI_GETKEY_H
#define TI_GETKEY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets a key from the OS
 *
 * This is only really useful when interacting with the OS.
 * Otherwise, it is recommended to use os_GetCSC instead.
 *
 * @returns Key code
 * @returns Extended key code in high byte
 */
uint16_t os_GetKey(void);

#ifdef __cplusplus
}
#endif

#endif
