#include <stdio.h>
#include <fileioc.h>

FILE *fopen(const char *filename, const char *mode) {
    ti_var_t f = ti_Open(filename, mode);
    if (!f) {
        return NULL;
    }
    __stdio_files[(unsigned char)f].slot = f;

    return &__stdio_files[f];
}
