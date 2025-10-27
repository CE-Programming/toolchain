#ifndef _STDDEF_H
#define _STDDEF_H

#include <cdefs.h>

#define offsetof(type, member) __builtin_offsetof(type, member)

typedef __PTRDIFF_TYPE__ ptrdiff_t;

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif /* __cplusplus */
#endif /* _WCHAR_T_DEFINED */

#if __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L
typedef struct {
    long long    __max_align_ll __attribute__((__aligned__(__alignof__(  long long))));
    long double  __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
#ifdef __FLOAT128__
    __float128 __max_align_f128 __attribute__((__aligned__(__alignof__( __float128))));
#endif
} max_align_t;
#endif /* __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L */

#endif /* _STDDEF_H */
