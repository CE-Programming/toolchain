#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <format.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FILENAME_MAX     9
#define SYS_OPEN         5      /* max open files */
#define FOPEN_MAX        5

#define SEEK_CUR  1
#define SEEK_END  2
#define SEEK_SET  0

/* ANSI prototypes */
#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef __SIZE_TYPE__ size_t;
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef EOF
#define EOF (-1)             /* end of file */
#endif

typedef struct __stdio_file {
    unsigned char slot;
} FILE;

extern FILE __stdio_files[FOPEN_MAX];
extern FILE *stdin, *stdout, *stderr;

int printf(const char *format, ...);
int fprintf(FILE *f, const char *format, ...);
int sprintf(char *s, const char *format, ...);
int vprintf(const char *format, va_list arg);
int vsprintf(char *s, const char *format, va_list arg);

/* stdio.h functions implemented using FILEIOC */
int remove(const char *filename);
int fgetc(FILE *stream);
int fputc(int c, FILE *stream);
char *fgets(char *str, int num, FILE *stream);
int fputs(const char *str, FILE *stream);
size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
int fseek(FILE *stream, long int offset, int origin);
long int ftell(FILE *stream);
int fclose(FILE *stream);
FILE *fopen(const char *filename, const char *mode);
int feof(FILE *stream);
#define ferror(stream) (0)
#define fflush(ignore) ((void)0)
#define rewind(stream) ti_Rewind(stream->slot)
#define fcloseall() ti_CloseAll()

#ifdef __cplusplus
}
#endif

#endif
