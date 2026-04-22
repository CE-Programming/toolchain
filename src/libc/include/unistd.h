#ifndef _UNISTD_H
#define _UNISTD_H

#include <cdefs.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

__BEGIN_DECLS

int isatty(int fd);

__END_DECLS

#endif /* _UNISTD_H */
