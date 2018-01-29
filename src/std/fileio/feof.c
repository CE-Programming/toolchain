#include <stdio.h>
#include <fileioc.h>

int feof(FILE *stream) {
    char a;
    int sz;

    sz = fread(&a, 1, 1, stream);
    fseek(stream, -sz, SEEK_CUR);
    return !sz;
}
