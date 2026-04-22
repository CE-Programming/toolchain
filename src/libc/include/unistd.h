#ifndef _UNISTD_H
#define _UNISTD_H

#include <cdefs.h>

/*
 * unsigned int sleep(unsigned int seconds);
 * typedef unsigned int useconds_t;
 * int usleep(useconds_t usec);
 */
#include <sys/timers.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#ifndef _SSIZE_T_DEFINED
#define _SSIZE_T_DEFINED
typedef __PTRDIFF_TYPE__ ssize_t;
#endif /* _SSIZE_T_DEFINED */

__BEGIN_DECLS

int isatty(int fd);

void swab(const void *__restrict src, void *__restrict dst, ssize_t count);

__END_DECLS

#endif /* _UNISTD_H */
