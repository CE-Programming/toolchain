#ifndef _STDLIB_H
#define _STDLIB_H

#include <cdefs.h>

__BEGIN_DECLS

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif
#endif

typedef struct {
  int quot;
  int rem;
} div_t;

typedef struct {
  long quot;
  long rem;
} ldiv_t;

typedef char __align;
union header {
  struct {
    union header *ptr;
    unsigned int size;
  } s;
  __align x;
};
typedef union header _HEADER;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define RAND_MAX 8388607

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned int size_t;
#endif
#define HEADER _HEADER
#define allocp _allocp
#define NALLOC 50

#ifndef NULL
#define NULL ((void *)0)
#endif

void *calloc(size_t nmemb, size_t size) __attribute__((malloc));

void *malloc(size_t size) __attribute__((malloc));

void *realloc(void *ptr, size_t size) __attribute__((warn_unused_result));

void free (void *ptr);

double atof(const char *nptr) __attribute__((nonnull(1)));

int atoi(const char *nptr) __attribute__((nonnull(1)));

long atol(const char *nptr) __attribute__((nonnull(1)));

float strtof(const char *__restrict nptr,
             char **__restrict endptr) __attribute__((nonnull(1)));

double strtod(const char *__restrict nptr,
              char **__restrict endptr) __attribute__((nonnull(1)));

float strtof(const char *__restrict nptr,
             char **__restrict endptr) __attribute__((nonnull(1)));

long strtol(const char *__restrict nptr,
            char **__restrict endptr, int base) __attribute__((nonnull(1)));

unsigned long strtoul(const char *__restrict nptr,
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

void abort(void) __attribute__((noreturn));

void exit(int status) __attribute__((noreturn));

int abs(int j);

long labs(long j);

div_t div(int numer, int denom);

ldiv_t ldiv(long numer, long denom);

__END_DECLS

#endif
