#include "__fileioc_stdio.h"

int __attribute__((weak)) ungetc(int ch, FILE *stream)
{
    // unimplemented
    (void)ch;
    (void)stream;
    return EOF;
}
