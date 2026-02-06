#ifndef _WCHAR_H
#define _WCHAR_H

#include <__wchar_def.h>
#include <__mbstate.h>
#include <stdio.h>
#include <time.h>

__BEGIN_DECLS

wchar_t *wmemcpy(wchar_t *__restrict dest, const wchar_t *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

wchar_t *wmemmove(wchar_t *dest, const wchar_t *src, size_t n)
    __attribute__((nonnull(1, 2)));

wchar_t *wmemset(wchar_t *s, wchar_t c, size_t n)
    __attribute__((nonnull(1)));

int wmemcmp(const wchar_t *s1, const wchar_t *s2, size_t n)
    __attribute__((nonnull(1, 2)));

wchar_t *wmemchr(const wchar_t *s, int c, size_t n)
    __attribute__((nonnull(1)));

wchar_t *wcscpy(wchar_t *__restrict dest, const wchar_t *__restrict src)
    __attribute__((nonnull(1, 2)));

wchar_t *wcsncpy(wchar_t *__restrict dest, const wchar_t *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

wchar_t *wcscat(wchar_t *__restrict dest, const wchar_t *__restrict src)
    __attribute__((nonnull(1, 2)));

wchar_t *wcsncat(wchar_t *__restrict dest, const wchar_t *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

wchar_t *wcschr(const wchar_t *s, int c)
    __attribute__((nonnull(1)));

wchar_t *wcsrchr(const wchar_t *s, int c)
    __attribute__((nonnull(1)));

wchar_t *wcspbrk(const wchar_t *s, const wchar_t *accept)
    __attribute__((nonnull(1, 2)));

wchar_t *wcsstr(const wchar_t *haystack, const wchar_t *needle)
    __attribute__((nonnull(1, 2)));

wchar_t *wcstok(wchar_t *__restrict s, const wchar_t *__restrict delim)
    __attribute__((nonnull(2)));

size_t wcscspn(const wchar_t *s, const wchar_t *reject)
    __attribute__((nonnull(1, 2)));

size_t wcsspn(const wchar_t *s, const wchar_t *accept)
    __attribute__((nonnull(1, 2)));

size_t wcslen(const wchar_t *s)
    __attribute__((nonnull(1)));

size_t wcsnlen(const wchar_t *s, size_t maxlen)
    __NOEXCEPT __attribute__((nonnull(1))) __attribute__((__pure__));

int wcscmp(const wchar_t *s1, const wchar_t *s2)
    __attribute__((nonnull(1, 2)));

int wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t n)
    __attribute__((nonnull(1, 2)));

int wprintf(const wchar_t *__restrict format, ...);

int vwprintf(const wchar_t *__restrict format, va_list va);

int swprintf(wchar_t *__restrict buffer, size_t count, const wchar_t *__restrict format, ...);

int vswprintf(wchar_t *__restrict buffer, size_t count, const wchar_t *__restrict format, va_list va);

int fwprintf(FILE *__restrict stream, const wchar_t *__restrict format, ...);

int vfwprintf(FILE *__restrict stream, const wchar_t *__restrict format, va_list va);

int wscanf(const wchar_t *__restrict format, ...);

int vwscanf(const wchar_t *__restrict format, va_list arg);

int swscanf(const wchar_t *__restrict s, const wchar_t *__restrict format, ...);

int vswscanf(const wchar_t *__restrict s, const wchar_t *__restrict format, va_list arg);

int fwscanf(FILE *__restrict stream, const wchar_t *__restrict format, ...);

int vfwscanf(FILE *__restrict stream, const wchar_t *__restrict format, va_list arg);

wint_t fgetwc(FILE *stream);

wchar_t *fgetws(wchar_t *__restrict s, int n, FILE *__restrict stream);

wint_t fputwc(wchar_t c, FILE *stream);

int fputws(const wchar_t *__restrict s, FILE *__restrict stream);

int fwide(FILE *stream, int mode);

wint_t getwc(FILE *stream);

wint_t getwchar(void);

wint_t putwc(wchar_t c, FILE *stream);

wint_t putwchar(wchar_t c);

wint_t ungetwc(wint_t c, FILE *stream);

float wcstof(const wchar_t *__restrict nptr, wchar_t **__restrict endptr);

double wcstod(const wchar_t *__restrict nptr, wchar_t **__restrict endptr);

long double wcstold(const wchar_t *__restrict nptr, wchar_t **__restrict endptr);

long wcstol(const wchar_t *__restrict nptr, wchar_t **__restrict endptr, int base);

long long wcstoll(const wchar_t *__restrict nptr, wchar_t **__restrict endptr, int base);

unsigned long wcstoul(const wchar_t *__restrict nptr, wchar_t **__restrict endptr, int base);

unsigned long long wcstoull(const wchar_t *__restrict nptr, wchar_t **__restrict endptr, int base);

size_t wcsftime(wchar_t *__restrict s, size_t maxsize, const wchar_t *__restrict format, const struct tm *__restrict timeptr);

int wcscoll(const wchar_t *s1, const wchar_t *s2);

size_t wcsxfrm(wchar_t *__restrict s1, const wchar_t *__restrict s2, size_t n);

wint_t btowc(int c);

int wctob(wint_t c);

int mbsinit(const mbstate_t *ps);

size_t mbrlen(const char *__restrict s, size_t n, mbstate_t *__restrict ps);

size_t mbrtowc(wchar_t *__restrict pwc, const char *__restrict s, size_t n, mbstate_t *__restrict ps);

size_t wcrtomb(char *__restrict s, wchar_t wc, mbstate_t *__restrict ps);

size_t mbsrtowcs(wchar_t *__restrict dst, const char **__restrict src, size_t len, mbstate_t *__restrict ps);

size_t wcsrtombs(char *__restrict dst, const wchar_t **__restrict src, size_t len, mbstate_t *__restrict ps);

size_t mbsnrtowcs(wchar_t *__restrict dest, const char **__restrict src, size_t nms, size_t size, mbstate_t *__restrict ps);

size_t wcsnrtombs(char *__restrict dest, const wchar_t **__restrict src, size_t nwc, size_t size, mbstate_t *__restrict ps);

__END_DECLS

#endif /* _WCHAR_H */
