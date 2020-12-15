#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <format.h>
#include <cdefs.h>

__BEGIN_DECLS

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef __SIZE_TYPE__ size_t;
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef EOF
#define EOF (-1)
#endif

#ifndef SEEK_CUR
#define SEEK_CUR  1
#endif
#ifndef SEEK_END
#define SEEK_END  2
#endif
#ifndef SEEK_SET
#define SEEK_SET  0
#endif

/* weak user-defined function */
char inchar(void);

int getchar(void);

/* weak user-defined function */
void outchar(char character);

int putchar(int character);

int puts(const char *str);

int printf_(const char *__restrict format, ...)
    __attribute__ ((format (__printf__, 1, 2)));

int vprintf_(const char *__restrict format, va_list __arg)
    __attribute__ ((format (__printf__, 1, 0)));

int sprintf_(char *__restrict buffer,
    const char *__restrict format, ...)
    __attribute__ ((format (__printf__, 2, 3)));

int vsprintf_(char *__restrict buffer, const char *__restrict format,
    va_list __arg)
    __attribute__ ((format (__printf__, 1, 0)));

int snprintf_(char* buffer, size_t count, const char *__restrict format, ...)
    __attribute__ ((format (__printf__, 3, 4)));

int vsnprintf_(char* buffer, size_t count, const char *__restrict format,
    va_list va)
    __attribute__ ((format (__printf__, 3, 0)));

#ifdef HAS_PRINTF
#define printf printf_
#define vprintf vprintf_
#define sprintf sprintf_
#define vsprintf vsprintf_
#define snprintf snprintf_
#define vsnprintf vsnprintf_
#else
/* This function is embedded in the OS, but only supports a subset of printf */
int sprintf(char *__restrict buffer,
    const char *__restrict format, ...)
    __attribute__ ((format (__printf__, 2, 3)));
#endif

__END_DECLS

#endif
