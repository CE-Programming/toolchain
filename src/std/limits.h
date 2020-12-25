#ifndef _LIMITS_H
#define _LIMITS_H

#define    CHAR_BIT     __CHAR_BIT__
#define   SCHAR_MIN   ~__SCHAR_MAX__
#define   SCHAR_MAX    __SCHAR_MAX__
#define   UCHAR_MAX    __UCHAR_MAX__
#ifndef __CHAR_UNSIGNED__
# define   CHAR_MIN   ~__SCHAR_MAX__
# define   CHAR_MAX    __SCHAR_MAX__
#else /* __CHAR_UNSIGNED__ */
# define   CHAR_MIN          0
# define   CHAR_MAX    __UCHAR_MAX__
#endif /* __CHAR_UNSIGNED__ */

#define    SHRT_MIN    ~__SHRT_MAX__
#define    SHRT_MAX     __SHRT_MAX__
#define   USHRT_MAX    __USHRT_MAX__

#define     INT_MIN     ~__INT_MAX__
#define     INT_MAX      __INT_MAX__
#define    UINT_MAX     __UINT_MAX__

#define    LONG_MIN    ~__LONG_MAX__
#define    LONG_MAX     __LONG_MAX__
#define   ULONG_MAX    __ULONG_MAX__

#define   LLONG_MIN   ~__LLONG_MAX__
#define   LLONG_MAX    __LLONG_MAX__
#define  ULLONG_MAX   __ULLONG_MAX__

#endif /* _LIMITS_H */
