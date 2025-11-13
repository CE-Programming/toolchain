#ifndef _SETJMP_H
#define _SETJMP_H

#include <cdefs.h>

__BEGIN_DECLS

void (*signal(int sig, void (*func)(int)))(int);

int raise(int sig);

__END_DECLS

#endif /* _SETJMP_H */
