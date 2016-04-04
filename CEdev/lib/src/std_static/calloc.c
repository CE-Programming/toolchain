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
#include <string.h>
/*************************************************
*
* calloc - allocate and clear memory
*
* Inputs:
*	nmemb - number of bytes of an element
*	size - size of each element
*
* Returns:
*	a pointer to the allocated memory
*
*************************************************/
void *calloc(int nmemb,size_t size)
{
  void *p;

  if (p = malloc(nmemb*size))
    memset(p,0,nmemb*size);
  return(p);
}

