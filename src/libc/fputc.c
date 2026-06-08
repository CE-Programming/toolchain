#include "__fileioc_stdio.h"

int __attribute__((weak)) fputc(int c, FILE *stream)
{
    if (stream == NULL || stream == stdin)
    {
        return EOF;
    }
    if (stream == stdout || stream == stderr)
    {
        return putchar(c);
    }

    int ret = ti_PutC((char)c, stream->slot);
    /*
     * `ti_PutC` returns `(unsigned char)c` or `EOF` so we can skip testing for
     * the case of `ret != (unsigned char)c`
     */
    if (ret == EOF)
    {
        stream->err = 1;
    }

    return ret;
}

int putc(int c, FILE *stream) __attribute__((weak, alias("fputc")));
