#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

// custom version of sprintf where %s is all uppercase
int sprintf(char *buffer, const char *__restrict format, ...) {
    va_list args;
    va_start(args, format);

    int count = 0;
    const char *ptr = format;
    while (*ptr != '\0') {
        if (*ptr == '%' && *(ptr + 1) == 's') {
            const char *str = va_arg(args, const char*);
            while (*str != '\0') {
                *buffer = toupper(*str);
                buffer++;
                str++;
                count++;
            }
            // consume %s
            ptr += 2;
            continue;
        }
        *buffer = *ptr;
        buffer++;
        ptr++;
        count++;
    }
    *buffer++ = '\0';

    va_end(args);
    return count;
}
