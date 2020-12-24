/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by			*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <format.h>

/*************************************************
*
* realloc - change the size of an allocated block
*
* Inputs:
*	ptr - pointer to allocated memory
*	size - new size of memory
*
* Returns:
*	pointer to block - may have changed
*
*************************************************/
void *realloc(void *ptr,size_t size) {
	HEADER *h;
	void *p;

	if (ptr) {
		h = (HEADER *)((char *)ptr - sizeof(HEADER));
		if (h->s.size >= (size+sizeof(HEADER))) {
			return(ptr);
		}

		if ((p = malloc(size))) {
			memcpy(p,ptr,size);
			free(ptr);
		}
		return p;
	}
	return malloc(size);
}
