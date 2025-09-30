#ifndef _WCHAR_H
#define _WCHAR_H

#include <__wchar_def.h>

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

__END_DECLS

#endif /* _WCHAR_H */
