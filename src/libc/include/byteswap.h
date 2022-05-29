#ifndef _BYTESWAP_H
#define _BYTESWAP_H

#include <stdint.h>

static inline uint16_t bswap_16(uint16_t x) { return __builtin_bswap16(x); }
static inline uint32_t bswap_32(uint32_t x) { return __builtin_bswap32(x); }
static inline uint64_t bswap_64(uint64_t x) { return __builtin_bswap64(x); }

#endif /* _BYTESWAP_H */
