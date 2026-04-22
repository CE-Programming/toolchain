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

__BEGIN_DECLS

int isatty(int fd);

__END_DECLS

#endif /* _UNISTD_H */
