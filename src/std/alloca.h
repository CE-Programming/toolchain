#ifndef _ALLOCA_H
#define _ALLOCA_H

#include <cdefs.h>

__BEGIN_DECLS

void *alloca(size_t __size) __NOEXCEPT;
#define alloca(size) __builtin_alloca(size)

__END_DECLS

#endif /* _ALLOCA_H */
