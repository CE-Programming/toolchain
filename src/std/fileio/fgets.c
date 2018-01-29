#include <stdio.h>
#include <fileioc.h>

char *fgets(char *str, int num, FILE *stream) {
    int c;
    char *p = str;

    if (num == 1) {
        *p = 0;
        return str;
    }

    for (; num > 1; num--) {
        if ((c = fgetc(stream)) == EOF) {
            break;
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
    }

    if (p == str) {
        return NULL;
    }

    *p = 0;

    return str;
}
