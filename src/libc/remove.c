#include "__fileioc_stdio.h"

int __attribute__((weak)) remove(const char *filename)
{
    return !ti_Delete(filename);
}
