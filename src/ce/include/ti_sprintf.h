#ifndef TI_SPRINTF_H
#define TI_SPRINTF_H

#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief C89 `sprintf`. `long` arguments and width specifiers are unsupported.
 * @note `%s` will write up to 255 characters.
 */
int ti_sprintf(
    char *__restrict buffer, const char *__restrict format, ...
) __attribute__((format (__printf__, 2, 3)));

/**
 * @brief Returns an empty string if the output from sprintf does not fit.
 * @warning `__VA_ARGS__` is evaluated twice.
 * @note Undefined behaviour if the output is longer than ~258000 characters.
 */
#define ti_snprintf(buffer, count, ...)\
({\
    char * const __buffer = buffer;\
    const int __count = count;\
    int __ret = -1;\
    int __str_len = ti_sprintf((char*)0xFC1000, __VA_ARGS__);\
    if (__buffer == NULL || __count == 0) {\
        __ret = __str_len;\
    } else if ((size_t)__str_len > __count) {\
        *__buffer = '\0'; /* won't fit or invalid formatting */\
    } else {\
        __ret = ti_sprintf(__buffer, __VA_ARGS__);\
    }\
    __ret;\
})

/**
 * @brief Allocates a null terminated string containing the output of sprintf.
 * The returned pointer shall be deallocated with `free`.
 * @warning `__VA_ARGS__` is evaluated twice.
 * @note Undefined behaviour if the output is longer than ~258000 characters.
 */
#define ti_asprintf(p_buffer, ...)\
({\
    char** const __p_buffer = p_buffer;\
    int __ret = -1;\
    int __str_len = ti_sprintf((char*)0xFC1000, __VA_ARGS__);\
    if (__str_len >= 0) {\
        size_t __buffer_size = (size_t)__str_len + 1;\
        *__p_buffer = (char*)malloc(__buffer_size);\
        if (*__p_buffer != NULL) {\
            __ret = ti_sprintf(*__p_buffer, __VA_ARGS__);\
        }\
    }\
    __ret;\
})

#ifdef __cplusplus
}
#endif

#endif /* TI_SPRINTF_H */
