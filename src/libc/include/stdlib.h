#ifndef _STDLIB_H
#define _STDLIB_H

#include <cdefs.h>

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

#ifdef __SIZEOF_INT48__
typedef struct {
    signed __int48 quot;
    signed __int48 rem;
} i48div_t;
#endif /* __SIZEOF_INT48__ */

typedef struct {
    long long rem;
    long long quot;
} lldiv_t;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define RAND_MAX 8388607

#define allocp _allocp

__BEGIN_DECLS

void *calloc(size_t nmemb, size_t size) __attribute__((malloc));

void *malloc(size_t size) __attribute__((malloc));

void *realloc(void *ptr, size_t size) __attribute__((warn_unused_result));

void free(void *ptr) __NOEXCEPT;

double atof(const char *nptr) __attribute__((nonnull(1)));

int atoi(const char *nptr) __attribute__((nonnull(1)));

long atol(const char *nptr) __attribute__((nonnull(1)));

long long atoll(const char *nptr) __attribute__((nonnull(1)));

float strtof(const char *__restrict nptr,
             char **__restrict endptr) __attribute__((nonnull(1)));

double strtod(const char *__restrict nptr,
              char **__restrict endptr) __attribute__((nonnull(1)));

long double strtold(const char *__restrict nptr,
                    char **__restrict endptr) __attribute__((nonnull(1)));

long strtol(const char *__restrict nptr,
            char **__restrict endptr, int base) __attribute__((nonnull(1)));

long long strtoll(const char *__restrict nptr,
                  char **__restrict endptr,
                  int base) __attribute__((nonnull(1)));

unsigned long strtoul(const char *__restrict nptr,
                      char **__restrict endptr, int base)
                      __attribute__((nonnull(1)));

unsigned long long strtoull(const char *__restrict nptr,
                            char **__restrict endptr, int base)
                            __attribute__((nonnull(1)));

void srand(unsigned int seed);

int rand(void);

void *bsearch(void *key, void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *))
              __attribute__((nonnull(1, 2, 5)));

void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *))
           __attribute__((nonnull(1, 4)));

void abort(void) __NOEXCEPT __attribute__((noreturn));

int atexit(void (*)(void)) __NOEXCEPT;

int on_exit(void (*)(int, void *), void *) __NOEXCEPT;

void exit(int) __NOEXCEPT __attribute__((noreturn));

int at_quick_exit(void (*)(void)) __NOEXCEPT;

void quick_exit(int) __NOEXCEPT __attribute__((noreturn));

void _Exit(int) __NOEXCEPT __attribute__((noreturn));

#ifndef _ABS_INT_DEFINED
#define _ABS_INT_DEFINED

int abs(int n);
long labs(long n);
long long llabs(long long n);

#ifdef __SIZEOF_INT48__
signed __int48 i48abs(signed __int48 n) __NOEXCEPT_CONST;
#endif /* __SIZEOF_INT48__ */

#endif /* _ABS_INT_DEFINED */

div_t div(int numer, int denom);

ldiv_t ldiv(long numer, long denom);

lldiv_t lldiv(long long numer, long long denom);

#ifdef __SIZEOF_INT48__
i48div_t i48div(signed __int48 numer, signed __int48 denom) __NOEXCEPT_CONST;
#endif /* __SIZEOF_INT48__ */

__END_DECLS

#endif /* _STDLIB_H */
