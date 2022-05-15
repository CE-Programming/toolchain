#ifndef _CDEFS_H
#define _CDEFS_H

#define __JOIN2(x, y)     x ## y
#define __JOIN3(x, y, z)  x ## y ## z
#define __CONCAT(x, y)    __JOIN2(x, y)
#define __TOSTRING(x)     #x

#define __STDINT_C(C, T)  __CONCAT(C, __##T##_C_SUFFIX__)
#define __STDINT_WIDTH(T) (sizeof(__##T##_TYPE__)*__CHAR_BIT__)

#ifndef __cplusplus
# define __BEGIN_DECLS
# define __END_DECLS
# define __NOEXCEPT     __attribute__((__nothrow__, __leaf__))
# define __IGNORE(expr) ((void)(expr))
#else /* __cplusplus */
# define __BEGIN_DECLS  extern "C" {
# define __END_DECLS    }
# define __NOEXCEPT     noexcept
# define __IGNORE(expr) (static_cast<void>(expr))
#endif /* __cplusplus */

#ifndef NULL
# ifndef __cplusplus
#  define NULL ((void *)0)
# else /* __cplusplus */
#  define NULL 0
# endif /* __cplusplus */
#endif /* NULL */

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef __SIZE_TYPE__ size_t;
#endif /* SIZE_T_DEFINED */

#endif /* _CDEFS_H */
