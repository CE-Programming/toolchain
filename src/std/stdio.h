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

#ifdef HAS_CUSTOM_FILE
#include CUSTOM_FILE_FILE
#else
typedef struct
{
    unsigned char slot;
    unsigned char eof;
    unsigned char err;
} FILE;
#define FOPEN_MAX  5
#define stdin      ((FILE*)1)
#define stdout     ((FILE*)2)
#define stderr     ((FILE*)2)
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

/* weak user-defined functions */
char inchar(void);

void outchar(char character);

FILE *fopen(const char *__restrict filename,
    const char *__restrict mode);

int fclose(FILE *stream);

int fflush(FILE *stream);

int ferror(FILE *stream);

int feof(FILE *stream);

void clearerr(FILE *stream);

int fputs(const char *__restrict str, FILE *__restrict stream);

size_t fread(void *ptr, size_t size, size_t count, FILE *__restrict stream);

size_t fwrite(const void *__restrict ptr, size_t size, size_t count,
    FILE *__restrict stream);

long int ftell(FILE *stream) __attribute__((__warn_unused_result__));

int fseek(FILE *stream, long int offset, int origin);

int fgetc(FILE *stream);
#define getc(...) fgetc(__VA_ARGS__)

int fputc(int c, FILE *stream);
#define putc(...) fputc(__VA_ARGS__)

char *fgets(char *__restrict str, int num, FILE *__restrict stream);

int remove(const char *filename);

void rewind(FILE *stream);

/* standard impls */
int getchar(void);

int putchar(int character);

int puts(const char *str);

int printf_(const char *__restrict format, ...)
    __attribute__((format(__printf__, 1, 2)));

int vprintf_(const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 1, 0)));

int sprintf_(char *__restrict buffer,
    const char *__restrict format, ...)
    __attribute__((format(__printf__, 2, 3)));

int vsprintf_(char *__restrict buffer, const char *__restrict format,
    va_list va)
    __attribute__((format(__printf__, 1, 0)));

int snprintf_(char* buffer, size_t count, const char *__restrict format, ...)
    __attribute__((format(__printf__, 3, 4)));

int vsnprintf_(char* buffer, size_t count, const char *__restrict format,
    va_list va)
    __attribute__((format(__printf__, 3, 0)));

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
