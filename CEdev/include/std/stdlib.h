/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#ifndef STDLIB_H
#define STDLIB_H

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef int onexit_t;

#ifndef WCHAR_T_DEFINED
#define WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#endif

typedef struct {
  int quot;
  int rem;
} div_t;

typedef struct {
  long quot;
  long rem;
} ldiv_t;

	/* Heap packet header for malloc */

typedef char __align;	/* alignment type */
union header {
  struct {
    union header *ptr;	/* next free block */
    unsigned int size; 		/* size of block   */
  } s;
  __align x;
};
typedef union header _HEADER;

#define EDOM	4		/* domain error */
#define ERANGE	5		/* range error	*/
extern double _huge_val;
#define HUGE_VAL _huge_val	/* overflow error */

#define RAND_MAX 32767		/* maximum value returned by rand() */


#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned int size_t;
#endif
#define HEADER _HEADER
#define allocp _allocp
#define NALLOC 50

#ifndef NULL
#define NULL	(void *)0
#endif

void * calloc(int nmemb,size_t size);
void free(void * ptr);
void * malloc(size_t size);
void * realloc(void * ptr,size_t size);
double atof(char * nptr);
int atoi(char * nptr);
long atol(char * nptr);
double strtod(char * nptr,char ** endptr);
long strtol(char *nptr,char ** endptr,int base);
unsigned long strtoul(char *nptr,char ** endptr,int base);
int rand(void);
void srand(unsigned int seed);
void abort(void);
void exit(int status);
onexit_t onexit(onexit_t (*func)(void));
void * bsearch(void * key,void * base,
	size_t nmemb, size_t size,
	int (*compar)(void * ,void * ));
void  qsort(void * base,size_t nmemb,size_t size,
	int (*compar)(void * ,void * ));
int abs(int j);
div_t div(int numer,int denom);
long labs(long j);
ldiv_t ldiv(long numer, long denom);

#endif
