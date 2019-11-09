#ifndef _CDEFS_H
#define _CDEFS_H

#ifndef __cplusplus
# define __BEGIN_DECLS
# define __END_DECLS
# define __NOTHROW     __attribute__((__nothrow__, __leaf__))
#else
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS   }
# define __NOTHROW     throw()
#endif

#endif /* _CDEFS_H */
