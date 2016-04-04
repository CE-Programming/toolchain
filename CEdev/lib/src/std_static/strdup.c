#include <string.h>
#include <stdlib.h>

char *strdup(const char *s) {
    char *d = malloc(strlen(s)+1);
    if (d != NULL) {
        strcpy(d, s);
    }
    return d;
}