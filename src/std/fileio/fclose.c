#include <stdio.h>
#include <fileioc.h>

int fclose(FILE *stream) {
    ti_var_t slot = stream->slot;
    __stdio_files[slot].slot = 0;
    return ti_Close(slot);
}
