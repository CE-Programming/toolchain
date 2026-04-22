#ifndef __FILEIOC_STDIO_H
#define __FILEIOC_STDIO_H

#include <cdefs.h>
#include <fileioc.h>
#include <stdio.h>
#include <stdbool.h>

/*
 * fd mapping:
 * STDIN_FILENO = 0
 * STDOUT_FILENO = 1
 * STDERR_FILENO = 2
 * fileioc slot 1 = 3
 * fileioc slot 2 = 4
 * fileioc slot 3 = 5
 * fileioc slot 4 = 6
 * fileioc slot 5 = 7
 */

__BEGIN_DECLS

extern FILE _file_streams[FOPEN_MAX];

#define FILEIOC_MIN_FD_SLOT 3
#define FILEIOC_MAX_FD_SLOT (FILEIOC_MIN_FD_SLOT + (FOPEN_MAX - 1))

static inline int fileioc_slot_to_fd(ti_var_t slot)
{
    return (int)(slot + (FILEIOC_MIN_FD_SLOT - 1));
}

static inline ti_var_t fd_to_fileioc_slot(int fd)
{
    return (ti_var_t)(fd - (FILEIOC_MIN_FD_SLOT - 1));
}

static inline bool is_fd_a_fileioc_slot(int fd)
{
    return (fd >= FILEIOC_MIN_FD_SLOT && fd <= FILEIOC_MAX_FD_SLOT);
}

__END_DECLS

#endif /* __FILEIOC_STDIO_H */
