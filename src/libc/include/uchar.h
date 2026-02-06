#ifndef _UCHAR_H
#define _UCHAR_H

#include <cdefs.h>
#include <__mbstate.h>

#ifndef __cplusplus

#if __STDC_VERSION__ >= 202311L
typedef unsigned char char8_t;
#endif
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;

#endif /* __cplusplus */

__BEGIN_DECLS

#if (__STDC_VERSION__ >= 202311L) || (defined(__cplusplus) && __cplusplus >= 202002L)
size_t mbrtoc8(char8_t *__restrict pc8, const char *__restrict s, size_t n, mbstate_t *__restrict ps);

size_t c8rtomb(char *__restrict s, char8_t c8, mbstate_t *__restrict ps);
#endif

size_t mbrtoc16(char16_t *__restrict pc16, const char *__restrict s, size_t n, mbstate_t *__restrict ps);

size_t c16rtomb(char *__restrict s, char16_t c16, mbstate_t *__restrict ps);

size_t mbrtoc32(char32_t *__restrict pc32, const char *__restrict s, size_t n, mbstate_t *__restrict ps);

size_t c32rtomb(char *__restrict s, char32_t c32, mbstate_t *__restrict ps);

__END_DECLS

#endif /* _UCHAR_H */
