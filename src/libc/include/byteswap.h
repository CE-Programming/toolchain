#ifndef _BYTESWAP_H
#define _BYTESWAP_H

#include <cdefs.h>
#include <stdint.h>
#include <ez80_builtin.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline uint16_t bswap_16(uint16_t x) { return __builtin_bswap16(x); }
static inline uint24_t bswap_24(uint24_t x) { return __ez80_bswap24(x); }
static inline uint32_t bswap_32(uint32_t x) { return __builtin_bswap32(x); }
static inline uint48_t bswap_48(uint48_t x) { return __ez80_bswap48(x); }
static inline uint64_t bswap_64(uint64_t x) { return __builtin_bswap64(x); }

#ifdef __cplusplus
}
#endif

#endif /* _BYTESWAP_H */
