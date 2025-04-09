#ifndef _EZ80_BUILTIN_H
#define _EZ80_BUILTIN_H

#include <cdefs.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned char __ez80_clzc(unsigned char) __NOEXCEPT_CONST;
unsigned char __ez80_clzi48(unsigned __int48) __NOEXCEPT_CONST;

unsigned char __ez80_ctzc(unsigned char) __NOEXCEPT_CONST;
unsigned char __ez80_ctzi48(unsigned __int48) __NOEXCEPT_CONST;

unsigned char __ez80_ffsc(unsigned char) __NOEXCEPT_CONST;
unsigned char __ez80_ffss(unsigned short) __NOEXCEPT_CONST;
unsigned char __ez80_ffsi48(unsigned __int48) __NOEXCEPT_CONST;

unsigned char __ez80_clrsbc(unsigned char) __NOEXCEPT_CONST;
unsigned char __ez80_clrsbs(unsigned short) __NOEXCEPT_CONST;
unsigned char __ez80_clrsbi48(unsigned __int48) __NOEXCEPT_CONST;

bool __ez80_parityc(unsigned char) __NOEXCEPT_CONST;
bool __ez80_paritys(unsigned short) __NOEXCEPT_CONST;
bool __ez80_parityi48(unsigned __int48) __NOEXCEPT_CONST;

unsigned char __ez80_popcountc(unsigned char) __NOEXCEPT_CONST;
unsigned char __ez80_popcounts(unsigned short) __NOEXCEPT_CONST;
unsigned char __ez80_popcounti48(unsigned __int48) __NOEXCEPT_CONST;

unsigned int __ez80_bswap24(unsigned int) __NOEXCEPT_CONST;
unsigned __int48 __ez80_bswap48(unsigned __int48) __NOEXCEPT_CONST;

unsigned int __ez80_bitreverse24(unsigned int) __NOEXCEPT_CONST;
unsigned __int48 __ez80_bitreverse48(unsigned __int48) __NOEXCEPT_CONST;

unsigned int __ez80_rotateleft24(unsigned int, unsigned char) __NOEXCEPT_CONST;
unsigned __int48 __ez80_rotateleft48(unsigned __int48, unsigned char) __NOEXCEPT_CONST;

unsigned int __ez80_rotateright24(unsigned int, unsigned char) __NOEXCEPT_CONST;
unsigned __int48 __ez80_rotateright48(unsigned __int48, unsigned char) __NOEXCEPT_CONST;

#ifdef __cplusplus
}
#endif

#endif /* _EZ80_BUILTIN_H */
