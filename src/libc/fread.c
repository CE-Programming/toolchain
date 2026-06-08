#include "__fileioc_stdio.h"

size_t __attribute__((weak)) fread(void *ptr, size_t size, size_t count, FILE *__restrict stream)
{
    if (stream == NULL || stream == stdout || stream == stderr)
    {
        return 0;
    }
    // If size or count is zero, fread returns zero and performs no other action.
    if (size == 0 || count == 0)
    {
        return 0;
    }

    if (stream == stdin)
    {
        int c;
        char *p = ptr;
        size_t len = size * count;
        size_t bytes_read = 0;

        for (; len > 0; len--)
        {
            if ((c = fgetc(stream)) == EOF)
            {
                break;
            }
            *p++ = (char)c;
            bytes_read++;
        }

        return bytes_read / size;
    }

    size_t ncount = ti_Read(ptr, size, count, stream->slot);
    if (ncount != count)
    {
        stream->err = 1;
    }

    return ncount;
}
