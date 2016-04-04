/************************************************************************/
/*									*/
/*			Copyright (C) 2000-2008 Zilog, Inc.		*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include <stdlib.h>

/*************************************************
*
* free - free up allocated memory
*
* Inputs:
*	ap - pointer to allocated memory
*
* Returns:
*	nothing
*
*************************************************/
extern HEADER _alloc_base;

void free(void *ap)
{
	HEADER *p,*q=(HEADER*)ap - 1;
	for(p=&_alloc_base; p->s.ptr && p->s.ptr < q; p=p->s.ptr);
	if((char*)p->s.ptr == ((char*)q) + q->s.size) {		/* join upper */
		q->s.size += p->s.ptr->s.size;
		q->s.ptr = p->s.ptr->s.ptr;
	}
	else
		q->s.ptr = p->s.ptr;
	if(((char*)p) + p->s.size == (char*)q) {		/* join lower */
		p->s.size += q->s.size;
		p->s.ptr = q->s.ptr;
	}
	else
		p->s.ptr = q;
}

