#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <ti/sprintf.h>

#define SINK (char *__restrict)0xE40000

int boot_vsnprintf(char *__restrict buffer, size_t count, const char *__restrict format, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    int str_len = boot_vsprintf(SINK, format, args_copy);
    va_end(args_copy);

    if (buffer == NULL || count == 0) {
        return str_len;
    }
    // str_len == 0 can take this fast path
    if ((size_t)str_len >= count || str_len < 0 || str_len == 0) {
        // won't fit, invalid formatting, or empty string
        *buffer = '\0';
        return str_len;
    }
    return boot_vsprintf(buffer, format, args);
}
__attribute__((weak, alias("boot_vsnprintf"))) int vsnprintf(char *__restrict buffer, size_t count, const char *__restrict format, va_list args);

int boot_snprintf(char *__restrict buffer, size_t count, const char *__restrict format, ...) {
    va_list args;
    va_start(args, format);
    const int ret = boot_vsnprintf(buffer, count, format, args);
    va_end(args);
    return ret;
}
__attribute__((weak, alias("boot_snprintf"))) int snprintf(char *__restrict buffer, size_t count, const char *__restrict format, ...);

int boot_vasprintf(char **__restrict p_buffer, const char *__restrict format, va_list args) {
    *p_buffer = NULL;
    va_list args_copy;
    va_copy(args_copy, args);
    int str_len = boot_vsprintf(SINK, format, args_copy);
    va_end(args_copy);

    if (str_len < 0) {
        // formatting error
        return str_len;
    }
    size_t buffer_size = (size_t)str_len + 1;
    char* buffer = malloc(buffer_size);
    if (buffer == NULL) {
        // malloc failure
        return -1;
    }
    va_copy(args_copy, args);
    int ret = boot_vsprintf(buffer, format, args_copy);
    va_end(args_copy);
    if (ret < 0) {
        free(buffer);
        return ret;
    }
    *p_buffer = buffer;
    return ret;
}
__attribute__((weak, alias("boot_vasprintf"))) int vasprintf(char **__restrict p_buffer, const char *__restrict format, va_list args);

int boot_asprintf(char **__restrict p_str, const char *__restrict format, ...) {
    va_list args;
    va_start(args, format);
    const int ret = boot_vasprintf(p_str, format, args);
    va_end(args);
    return ret;
}
__attribute__((weak, alias("boot_asprintf"))) int asprintf(char **__restrict p_str, const char *__restrict format, ...);
