#include <stdio.h>
#include <fileioc.h>

int fputs(const char *str, FILE *stream) {
    unsigned char slot = stream->slot;
    unsigned int i = 0;
    char c;
    
    while((c = str[i])) {
        if(ti_PutC(c, slot) == EOF) { 
            return EOF;
        }
        i++;
    }
    if(ti_PutC('\n', slot) == EOF) {
        return EOF;
    }
    return 1;
}
