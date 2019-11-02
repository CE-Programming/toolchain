/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include <stddef.h>
#include <stdlib.h>

/*************************************************
*
* qsort - Quick sort
*
* Inputs:
*	base	- base of array to be sorted
*	nel	- number of elements
*	size	- size of each element
*	compar	- pointer to function for comparison
*
* Returns:
*	nothing
*
*************************************************/
static void swapmem(char *a,char *b,size_t size)
{
  register char t;
  register size_t i;

  for (i=0;i<size;++i,++b,++a) {
    t = *a;
    *a = *b;
    *b = t;
  }
}

struct stk {
  char *l;
  char *r;
};

void qsort(     void *ptr,
		size_t nel,
		size_t size,
                int (*compar)(void *,void *))
{
  char *base = ptr;
  char *i;
  char *j;
  char *x;
  char *r;
  struct stk *sp;
  struct stk stack[16];

  sp = stack;
  r = base + (nel-1)*size;
  for (;;) {
    do {
      x = base + (r-base)/size/2 * size;
      i = base;
      j = r;
      do {
	while ((*compar)(i,x) < 0)
	  i += size;
	while ((*compar)(x,j) < 0)
	  j -= size;
	if (i < j) {
	  swapmem(i, j, size);
	  if (i == x)
	    x = j;
	  else if (j == x)
	    x = i;
	}
	if (i <= j) {
	  i += size;
	  j -= size;
	}
      } while (i <= j);
      if (j-base < r-i) {
	if (i < r) {	/* stack request for right partition */
	  sp->l = i;
	  sp->r = r;
	  ++sp;
	}
	r = j;			/* continue sorting left partition */
      }
      else {
	if (base < j) { /* stack request for left partition */
	  sp->l = base;
	  sp->r = j;
	  ++sp;
	}
	base = i;		/* continue sorting right partition */
      }
    } while (base < r);

    if (sp <= stack)
      break;
    --sp;
    base = sp->l;
    r = sp->r;
  }
}
