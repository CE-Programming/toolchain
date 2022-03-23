/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS flags
 * 
 * None of the flag bits are in this API, so it's not very useful. . . .
 */

#ifndef _TI_OS_FLAGS_H
#define _TI_OS_FLAGS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set a particular OS flag
 *
 * @param offset Offset to particular flag in list
 * @param set Bitmask of flag to set
 */
void os_SetFlagByte(int offset, uint8_t set);

/**
 * Get a particular OS flag
 *
 * @param offset Offset to particular flag in list
 * @returns Bitmask of flag
 */
uint8_t os_GetFlagByte(int offset);

/**
 * High 8 is unsigned offset, low 8 is bits to test
 */
int os_TestFlagBits(uint16_t offset_pattern);
bool os_TestFlagBitsFast(uint16_t offset_pattern); /* Warning: has a bug if bits and flags are all set! */
void os_SetFlagBits(int16_t offset_pattern);
void os_ResetFlagBits(int16_t offset_pattern);

#define os_Flags             ((uint8_t*)0xD00080)

#ifdef __cplusplus
}
#endif

#endif
