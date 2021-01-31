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
# define __NOTHROW      __attribute__((__nothrow__, __leaf__))
# define __IGNORE(expr) ((void)(expr))
#else /* __cplusplus */
# define __BEGIN_DECLS  extern "C" {
# define __END_DECLS    }
# define __NOTHROW      throw()
# define __IGNORE(expr) (static_cast<void>(expr))
#endif /* __cplusplus */

#endif /* _CDEFS_H */
