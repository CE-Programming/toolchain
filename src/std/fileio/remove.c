#include <stdio.h>
#include <fileioc.h>

int remove(const char *filename) {
    return !ti_Delete(filename);
}
