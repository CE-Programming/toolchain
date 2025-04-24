#ifndef _STRING_H
#define _STRING_H

#include <cdefs.h>

__BEGIN_DECLS

extern void *memcpy(void *__restrict dest, const void *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

void *memmove(void *dest, const void *src, size_t n)
    __attribute__((nonnull(1, 2)));

void *memset(void *s, int c, size_t n)
    __attribute__((nonnull(1)));

void bzero(void *s, size_t n)
    __attribute__((nonnull(1)));

int memcmp(const void *s1, const void *s2, size_t n)
    __attribute__((nonnull(1, 2)));

void *memchr(const void *s, int c, size_t n)
    __attribute__((nonnull(1)));

void *memrchr(const void *s, int c, size_t n)
    __NOEXCEPT __attribute__((nonnull(1))) __attribute((__pure__));

void *memmem(const void *haystack, size_t haystack_len, const void *needle, size_t needle_len)
    __NOEXCEPT __attribute__((nonnull(1, 3))) __attribute((__pure__));

void *memccpy(void *__restrict dest, const void *__restrict src, int c, size_t n)
    __NOEXCEPT __attribute__((nonnull(1, 2)));

void *mempcpy(void *__restrict dest, const void *__restrict src, size_t n)
    __NOEXCEPT __attribute__((nonnull(1, 2)));

char *strcpy(char *__restrict dest, const char *__restrict src)
    __attribute__((nonnull(1, 2)));

char *strncpy(char *__restrict dest, const char *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

char *stpcpy(char *__restrict dest, const char *__restrict src)
    __NOEXCEPT __attribute__((nonnull(1, 2)));

char *stpncpy(char *__restrict dest, const char *__restrict src, size_t n)
    __NOEXCEPT __attribute__((nonnull(1, 2)));

size_t strlcpy(char *__restrict dest, const char *__restrict src, size_t n)
    __NOEXCEPT __attribute__((nonnull(1, 2)));

char *strcat(char *__restrict dest, const char *__restrict src)
    __attribute__((nonnull(1, 2)));

char *strncat(char *__restrict dest, const char *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

size_t strlcat(char *__restrict dest, const char *__restrict src, size_t n)
    __NOEXCEPT __attribute__((nonnull(1, 2)));

char *strchr(const char *s, int c)
    __attribute__((nonnull(1)));

char *strrchr(const char *s, int c)
    __attribute__((nonnull(1)));

char *strpbrk(const char *s, const char *accept)
    __attribute__((nonnull(1, 2)));

char *strstr(const char *haystack, const char *needle)
    __attribute__((nonnull(1, 2)));

char *strcasestr(const char *haystack, const char *needle)
    __NOEXCEPT __attribute__((nonnull(1, 2))) __attribute__((__pure__));

char *strtok(char *__restrict s, const char *__restrict delim)
    __attribute__((nonnull(2)));

char *strdup(const char *s)
    __attribute__((__malloc__)) __attribute__((nonnull(1)));

char *strndup(const char *s, size_t n)
    __attribute__((__malloc__)) __attribute__((nonnull(1)));

size_t strcspn(const char *s, const char *reject)
    __attribute__((nonnull(1, 2)));

size_t strspn(const char *s, const char *accept)
    __attribute__((nonnull(1, 2)));

size_t strlen(const char *s)
    __attribute__((nonnull(1)));

size_t strnlen(const char *s, size_t maxlen)
    __attribute__((nonnull(1)));

int strcmp(const char *s1, const char *s2)
    __attribute__((nonnull(1, 2)));

int strncmp(const char *s1, const char *s2, size_t n)
    __attribute__((nonnull(1, 2)));

int strcasecmp(const char *s1, const char *s2)
    __NOEXCEPT __attribute__((nonnull(1, 2))) __attribute__((__pure__));

int strncasecmp(const char *s1, const char *s2, size_t n)
    __NOEXCEPT __attribute__((nonnull(1, 2))) __attribute__((__pure__));

char* strerror(int errnum);

__END_DECLS

#endif /* _STRING_H */
