#ifndef _EZ80_BUILTIN_H
#define _EZ80_BUILTIN_H

#include <cdefs.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#if __has_builtin(__builtin_clzc)
#define __ez80_clzc __builtin_clzc
#else
static inline __attribute__((__always_inline__))
unsigned char __ez80_clzc(unsigned char __x) __NOEXCEPT_CONST {
    return (unsigned char)(__builtin_clzs(__x) - 8);
}
#define __ez80_clzc(x) ((int)__ez80_clzc(x))
#endif

#if __has_builtin(__builtin_clzi48)
#define __ez80_clzi48 __builtin_clzi48
#else
static inline __attribute__((__always_inline__))
unsigned char __ez80_clzi48(unsigned __int48 __x) __NOEXCEPT_CONST {
    return (unsigned char)(__builtin_clzll(__x) - 16);
}
#define __ez80_clzi48(x) ((int)__ez80_clzi48(x))
#endif

#if __has_builtin(__builtin_ctzc)
#define __ez80_ctzc __builtin_ctzc
#else
unsigned char __ez80_ctzc(unsigned char) __NOEXCEPT_CONST;
#define __ez80_ctzc(x) ((int)__ez80_ctzc(x))
#endif

#if __has_builtin(__builtin_ctzi48)
#define __ez80_ctzi48 __builtin_ctzi48
#else
unsigned char __ez80_ctzi48(unsigned __int48) __NOEXCEPT_CONST;
#define __ez80_ctzi48(x) ((int)__ez80_ctzi48(x))
#endif

#if __has_builtin(__builtin_ffsc)
#define __ez80_ffsc __builtin_ffsc
#else
unsigned char __ez80_ffsc(unsigned char) __NOEXCEPT_CONST;
#define __ez80_ffsc(x) ((int)__ez80_ffsc(x))
#endif

#if __has_builtin(__builtin_ffss)
#define __ez80_ffss __builtin_ffss
#else
unsigned char __ez80_ffss(unsigned short) __NOEXCEPT_CONST;
#define __ez80_ffss(x) ((int)__ez80_ffss(x))
#endif

#if __has_builtin(__builtin_ffsi48)
#define __ez80_ffsi48 __builtin_ffsi48
#else
unsigned char __ez80_ffsi48(unsigned __int48) __NOEXCEPT_CONST;
#define __ez80_ffsi48(x) ((int)__ez80_ffsi48(x))
#endif

#if __has_builtin(__builtin_clrsbc)
#define __ez80_clrsbc __builtin_clrsbc
#else
unsigned char __ez80_clrsbc(unsigned char) __NOEXCEPT_CONST;
#define __ez80_clrsbc(x) ((int)__ez80_clrsbc(x))
#endif

#if __has_builtin(__builtin_clrsbs)
#define __ez80_clrsbs __builtin_clrsbs
#else
unsigned char __ez80_clrsbs(unsigned short) __NOEXCEPT_CONST;
#define __ez80_clrsbs(x) ((int)__ez80_clrsbs(x))
#endif

#if __has_builtin(__builtin_clrsbi48)
#define __ez80_clrsbi48 __builtin_clrsbi48
#else
unsigned char __ez80_clrsbi48(unsigned __int48) __NOEXCEPT_CONST;
#define __ez80_clrsbi48(x) ((int)__ez80_clrsbi48(x))
#endif

#if __has_builtin(__builtin_parityc)
#define __ez80_parityc __builtin_parityc
#else
bool __ez80_parityc(unsigned char) __NOEXCEPT_CONST;
#define __ez80_parityc(x) ((int)__ez80_parityc(x))
#endif

#if __has_builtin(__builtin_paritys)
#define __ez80_paritys __builtin_paritys
#else
bool __ez80_paritys(unsigned short) __NOEXCEPT_CONST;
#define __ez80_paritys(x) ((int)__ez80_paritys(x))
#endif

#if __has_builtin(__builtin_parityi48)
#define __ez80_parityi48 __builtin_parityi48
#else
bool __ez80_parityi48(unsigned __int48) __NOEXCEPT_CONST;
#define __ez80_parityi48(x) ((int)__ez80_parityi48(x))
#endif

#if __has_builtin(__builtin_popcountc)
#define __ez80_popcountc __builtin_popcountc
#else
unsigned char __ez80_popcountc(unsigned char) __NOEXCEPT_CONST;
#define __ez80_popcountc(x) ((int)__ez80_popcountc(x))
#endif

#if __has_builtin(__builtin_popcounts)
#define __ez80_popcounts __builtin_popcounts
#else
unsigned char __ez80_popcounts(unsigned short) __NOEXCEPT_CONST;
#define __ez80_popcounts(x) ((int)__ez80_popcounts(x))
#endif

#if __has_builtin(__builtin_popcounti48)
#define __ez80_popcounti48 __builtin_popcounti48
#else
unsigned char __ez80_popcounti48(unsigned __int48) __NOEXCEPT_CONST;
#define __ez80_popcounti48(x) ((int)__ez80_popcounti48(x))
#endif

#if __has_builtin(__builtin_bswap24)
#define __ez80_bswap24 __builtin_bswap24
#else
unsigned int __ez80_bswap24(unsigned int) __NOEXCEPT_CONST;
#endif

#if __has_builtin(__builtin_bswap48)
#define __ez80_bswap48 __builtin_bswap48
#else
unsigned __int48 __ez80_bswap48(unsigned __int48) __NOEXCEPT_CONST;
#endif

#if __has_builtin(__builtin_bitreverse24)
#define __ez80_bitreverse24 __builtin_bitreverse24
#else
unsigned int __ez80_bitreverse24(unsigned int) __NOEXCEPT_CONST;
#endif

#if __has_builtin(__builtin_bitreverse48)
#define __ez80_bitreverse48 __builtin_bitreverse48
#else
unsigned __int48 __ez80_bitreverse48(unsigned __int48) __NOEXCEPT_CONST;
#endif

#if __has_builtin(__builtin_rotateleft24)
#define __ez80_rotateleft24 __builtin_rotateleft24
#else
unsigned int __ez80_rotateleft24(unsigned int, unsigned char) __NOEXCEPT_CONST;
#endif

#if __has_builtin(__builtin_rotateleft48)
#define __ez80_rotateleft48 __builtin_rotateleft48
#else
unsigned __int48 __ez80_rotateleft48(unsigned __int48, unsigned char) __NOEXCEPT_CONST;
#endif

#if __has_builtin(__builtin_rotateright24)
#define __ez80_rotateright24 __builtin_rotateright24
#else
unsigned int __ez80_rotateright24(unsigned int, unsigned char) __NOEXCEPT_CONST;
#endif

#if __has_builtin(__builtin_rotateright48)
#define __ez80_rotateright48 __builtin_rotateright48
#else
unsigned __int48 __ez80_rotateright48(unsigned __int48, unsigned char) __NOEXCEPT_CONST;
#endif

#ifdef __cplusplus
}
#endif

#endif /* _EZ80_BUILTIN_H */
