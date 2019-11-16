/*
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *  Modified by Matt "MateoConLechuga" Waltz for TI84+CE platform
 */
#ifndef STDLIB_H
#define STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef int onexit_t;

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif /* __cplusplus */
#endif /* _WCHAR_T_DEFINED */

typedef struct {
  int quot;
  int rem;
} div_t;

typedef struct {
  long quot;
  long rem;
} ldiv_t;

/* Heap packet header for malloc */

typedef char __align;           /* alignment type */
union header {
  struct {
    union header *ptr;          /* next free block */
    unsigned int size;          /* size of block   */
  } s;
  __align x;
};
typedef union header _HEADER;

#define EDOM    4               /* domain error */
#define ERANGE  5               /* range error */
extern double _huge_val;
#define HUGE_VAL _huge_val      /* overflow error */

#define RAND_MAX 8388607        /* maximum value returned by rand() */

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned int size_t;
#endif
#define HEADER _HEADER
#define allocp _allocp
#define NALLOC 50

#ifndef NULL
#define NULL    ((void *)0)
#endif

/* Dynamic memory functions */
void *calloc(size_t, size_t);
void *malloc(size_t);
void *realloc(void *, size_t);
void free(void *);

/* Character and string functions */
double atof(char * nptr);
int atoi(char * nptr);
long atol(char * nptr);
double strtod(char * nptr,char ** endptr);
long strtol(char *nptr,char ** endptr,int base);
unsigned long strtoul(char *nptr,char ** endptr,int base);

/* Random routines */
void srand(unsigned int seed);
int rand(void);

/* Binary search and quicksort */
void *bsearch(void * key,void * base, size_t nmemb, size_t size, int (*compar)(void * ,void * ));
void qsort(void * base,size_t nmemb,size_t size, int (*compar)(void * ,void * ));

/* Exit and abort */
void abort(void) __attribute__((noreturn));
void exit(int status) __attribute__((noreturn));

/* Absolutes and division */
int abs(int j);
long labs(long j);
div_t div(int numer,int denom);
ldiv_t ldiv(long numer, long denom);

#ifdef __cplusplus
}
#endif

#endif
