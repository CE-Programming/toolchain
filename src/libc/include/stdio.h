#ifndef _STDIO_H
#define _STDIO_H

#include <cdefs.h>
#include <stdarg.h>

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

__BEGIN_DECLS

/* weak user-defined functions */
int inchar(void);

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

int printf(const char *__restrict format, ...)
    __attribute__((format(__printf__, 1, 2)));

int vprintf(const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 1, 0)));

int sprintf(char *__restrict buffer, const char *__restrict format, ...)
    __attribute__((format (__printf__, 2, 3)));

int vsprintf(char *__restrict buffer, const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 2, 0)));

int snprintf(char *__restrict buffer, size_t count, const char *__restrict format, ...)
    __attribute__((format(__printf__, 3, 4)));

int vsnprintf(char *__restrict buffer, size_t count, const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 3, 0)));

int fprintf(FILE *__restrict stream, const char *__restrict format, ...)
    __attribute__((format (__printf__, 2, 3)));

int vfprintf(FILE *__restrict stream, const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 2, 0)));

int asprintf(char **__restrict p_buffer, const char *__restrict format, ...)
    __attribute__((format (__printf__, 2, 3))) __attribute__((nonnull(1)));

int vasprintf(char **__restrict p_buffer, const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 2, 0))) __attribute__((nonnull(1)));

int sscanf(const char *__restrict buffer, const char *__restrict format, ...)
    __attribute__((format(__scanf__, 2, 3)));

int vsscanf(const char *__restrict buffer, const char *__restrict format, va_list va)
    __attribute__((format(__scanf__, 2, 0)));

void perror(const char *str);

__END_DECLS

#ifdef __cplusplus
namespace std {
    using ::size_t;
    using ::FILE;

    using ::fopen;
    using ::fclose;
    using ::fflush;
    using ::ferror;
    using ::feof;
    using ::clearerr;
    using ::fputs;
    using ::fread;
    using ::fwrite;
    using ::ftell;
    using ::fseek;
    using ::fgetc;
    using ::fputc;
    using ::fgets;
    using ::remove;
    using ::rewind;
    using ::getchar;
    using ::putchar;
    using ::puts;
    using ::printf;
    using ::vprintf;
    using ::sprintf;
    using ::vsprintf;
    using ::snprintf;
    using ::vsnprintf;
    using ::fprintf;
    using ::vfprintf;
    using ::asprintf;
    using ::vasprintf;
    using ::sscanf;
    using ::vsscanf;
    using ::perror;
} /* namespace std */
#endif /* __cplusplus */

#endif /* _STDIO_H */
