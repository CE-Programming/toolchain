#include "__fileioc_stdio.h"
#include <errno.h>
#include <unistd.h>

int __attribute__((weak)) fileno(FILE *stream)
{
    if (stream == NULL)
    {
        // invalid stream
        errno = EBADF;
        return -1;
    }

    if (stream == stdin)
    {
        return STDIN_FILENO;
    }
    if (stream == stdout)
    {
        return STDOUT_FILENO;
    }
    if (stream == stderr)
    {
        return STDERR_FILENO;
    }

    return fileioc_slot_to_fd(stream->slot);
}
