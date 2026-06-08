#include "__fileioc_stdio.h"

size_t __attribute__((weak)) fwrite(const void *__restrict ptr, size_t size, size_t count, FILE *__restrict stream)
{
    if (stream == NULL || stream == stdin)
    {
        return 0;
    }
    // If size or count is zero, fwrite returns zero and performs no other action.
    if (size == 0 || count == 0)
    {
        return 0;
    }

    if (stream == stdout || stream == stderr)
    {
        char *p = (char *)ptr;
        size_t len = size * count;
        size_t bytes_written = 0;

        for (; len > 0; len--)
        {
            if (putchar(*p++) == EOF)
            {
                break;
            }
            bytes_written++;
        }

        return bytes_written / size;
    }

    size_t ncount = ti_Write(ptr, size, count, stream->slot);
    if (ncount != count)
    {
        stream->err = 1;
    }

    return ncount;
}
