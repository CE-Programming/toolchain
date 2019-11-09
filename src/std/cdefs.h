#ifndef _CDEFS_H
#define _CDEFS_H

#define __CONCAT(x,y) x ## y
#define __TOSTRING(x) #x

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
