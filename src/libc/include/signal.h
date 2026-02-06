#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <cdefs.h>

__BEGIN_DECLS

void (*signal(int sig, void (*func)(int)))(int);

int raise(int sig);

__END_DECLS

#endif /* _SIGNAL_H */
