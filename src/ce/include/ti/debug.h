/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief This file is pretty much pointless.
 */

#ifndef TI_DEBUG_H
#define TI_DEBUG_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Basically a reimplemented form of printf that prints to some debugging device
 *
 * @param[in] string String to send to debug device
 */
void boot_DebugPrintf(const char *string);

#ifdef __cplusplus
}
#endif

#endif
