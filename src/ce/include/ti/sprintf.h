#ifndef TI_SPRINTF_H
#define TI_SPRINTF_H

#include <stddef.h>
#include <stdlib.h>

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief C89 `sprintf`. `long` arguments and width specifiers are unsupported.
 * @note `%s` will write up to 255 characters.
 */
int boot_sprintf(char *__restrict buffer, const char *__restrict format, ...)
    __attribute__((format (__printf__, 2, 3)));

/**
 * @note calls va_copy to wrap boot_sprintf
 */
int boot_vsprintf(char *__restrict buffer, const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 2, 0)));

/**
 * @brief Returns an empty string if the output from sprintf does not fit.
 */
int boot_snprintf(char *__restrict buffer, size_t count, const char *__restrict format, ...)
    __attribute__((format(__printf__, 3, 4)));

/**
 * @brief Returns an empty string if the output from sprintf does not fit.
 */
int boot_vsnprintf(char *__restrict buffer, size_t count, const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 3, 0)));

/**
 * @brief Allocates a null terminated string containing the output of sprintf.
 * The returned pointer shall be deallocated with `free`.
 */
int boot_asprintf(char **__restrict p_buffer, const char *__restrict format, ...)
    __attribute__((format (__printf__, 2, 3))) __attribute__((nonnull(1)));

/**
 * @brief Allocates a null terminated string containing the output of sprintf.
 * The returned pointer shall be deallocated with `free`.
 */
int boot_vasprintf(char **__restrict p_buffer, const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 2, 0))) __attribute__((nonnull(1)));

#ifdef __cplusplus
}
#endif

#endif /* TI_SPRINTF_H */
