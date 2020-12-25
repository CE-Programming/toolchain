/************************************************************************/
/*									*/
/*			Copyright (C)1987-2011 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*                                                                      */
/*   This implements a straight forward version of malloc, allocating   */
/*   memory between the first unused address in RAM (__heapbot) and     */
/*   the current stack pointer; the stack pointer being initialized to  */
/*   the top of RAM (__heaptop).                                        */
/*   The Zilog real time kernel, RZK, implements an entirely  */
/*   different version of malloc.                                       */
/*                                                                      */
/*   ZDS arranges that this malloc does not get linked into  RZK        */
/*   applications by placing the C runtime library, crt.lib or          */
/*   crtD.lib, after the RZK libraries in the linker command file.      */
/*									*/
/************************************************************************/
#include <stddef.h>
#include <stdlib.h>

HEADER _alloc_base;                /* empty list to get started    */
extern void *_s_sbrk(size_t);

/*************************************************
*
* morecore - get more memory for heap
*
* Inputs:
*	nu - number of units
*
* Returns:
*	the address of the new memory
*
*************************************************/

static void* morecore(size_t nbytes)
{
    register void *cp;
    if ((cp = _s_sbrk(nbytes)))
    {
        ((HEADER*)cp)->s.size=nbytes;
        cp = ((HEADER*)cp) + 1;
    }
    return cp;
}

/*************************************************
*
* malloc - allocate heap storage
*
* Inputs:
*	nbytes - number of bytes to allocate
*
* Returns:
*	the address of the memory or NULL
*
*************************************************/

void *malloc(size_t nbytes)
{
    HEADER *p,*q;
    size_t size = nbytes + sizeof(HEADER);

    if (size < nbytes)
        return NULL;  /* Happens on malloc(-1) or like stupidity */

    for(p=&_alloc_base; (q=p->s.ptr); p=q)
    {
        if (q->s.size >= size)
        {
            /* big enough */
            if (q->s.size <= size+sizeof(HEADER))
            {
                /* exactly enough */
                p->s.ptr = q->s.ptr;
            }
            else
            {
                q->s.size -= size;
                q = (HEADER*)(((char*)q) + q->s.size);
                q->s.size = size;
            }
            return((void*)(q+1));
        }
    }
    return(morecore(size));
}
