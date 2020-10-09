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

int printf(const char *__restrict format, ...);

int sprintf(char *__restrict str,
            const char *__restrict format, ...);

int vprintf(const char *__restrict format, va_list __arg);

int vsprintf(char *__restrict str, const char *__restrict format,
             va_list __arg);

__END_DECLS

#endif
