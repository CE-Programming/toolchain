#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <ti_sprintf.h>

static char const * const errno_strings[] = {
    "no error",
    "permission error",
    "invalid argument",
    "io error",
    "math domain error",
    "math range error",
};

static char * const unknown_errno_string = "unknown error -8388608";

#define unknown_errno_number_offset 14
#if 0
/* static_assert on a string is a Clang 16.0.0 extension */
static_assert(
    unknown_errno_string[unknown_errno_number_offset + 0] == '-' &&
    unknown_errno_string[unknown_errno_number_offset + 8] == '\0',
    "the string for unknown errno numbers has been changed"
);
#endif

#define errno_strings_count (sizeof(errno_strings) / sizeof(errno_strings[0]))

char* strerror(int errnum) {
    if ((unsigned int)errnum >= errno_strings_count) {
        ti_sprintf(&(unknown_errno_string[unknown_errno_number_offset]), "%d", errnum);
        return (char*)unknown_errno_string;
    }
    return (char*)errno_strings[errnum];
}

#if 0
/** disabled until the prototypes for this function are defined */
size_t strerrorlen_s(errno_t errnum) {
    return strlen(strerror(errnum));
}
#endif

void perror(const char *str) {
    if (str != NULL && *str != '\0') {
        fputs(str, stderr);
        fputs(": ", stderr);
    }
    fputs(strerror(errno), stderr);
    fputc('\n', stderr);
}
