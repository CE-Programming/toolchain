#include "__fileioc_stdio.h"
#include <unistd.h>
#include <errno.h>

int __attribute__((weak)) isatty(int fd)
{
    if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO)
    {
        return 1;
    }
    if (is_fd_a_fileioc_slot(fd))
    {
        // not a terminal
        errno = ENOTTY;
        return 0;
    }
    // invalid fd
    errno = EBADF;
    return 0;
}
