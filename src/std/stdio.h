#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <format.h>

#ifdef __cplusplus
extern "C" {
#endif

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

int printf(const char *format, ...);
int sprintf(char *s, const char *format, ...);
int vprintf(const char *format, va_list arg);
int vsprintf(char *s, const char *format, va_list arg);

#ifdef __cplusplus
}
#endif

#endif
