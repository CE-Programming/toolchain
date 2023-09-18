#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct __attribute__((packed)) block
{
    struct block *ptr;
    size_t size;
} __attribute__((packed)) block_t;

extern uint8_t __heapbot[];
extern uint8_t __heaptop[];
static uintptr_t heap_ptr = (uintptr_t)__heapbot;
static block_t _alloc_base;

void *_standard_malloc(size_t alloc_size)
{
    block_t *q;
    block_t *r;

    /* add size of block header to real size */
    const size_t size = alloc_size + sizeof(block_t);
    if (size < alloc_size)
    {
        return NULL;
    }

    for (block_t *p = &_alloc_base; (q = p->ptr); p = q)
    {
        if (q->size >= size)
        {
            if (q->size <= size + sizeof(block_t))
            {
                p->ptr = q->ptr;
            }
            else
            {
                q->size -= size;
                q = (block_t*)(((uint8_t*)q) + q->size);
                q->size = size;
            }

            return q + 1;
        }
    }

    /* compute next heap pointer */
    if (heap_ptr + size < heap_ptr || heap_ptr + size >= (uintptr_t)__heaptop)
    {
        return NULL;
    }

    r = (block_t*)heap_ptr;
    r->size = size;

    heap_ptr = heap_ptr + size;

    return r + 1;
}

void _standard_free(void *ptr)
{
    if (ptr != NULL)
    {
        block_t *p;
        block_t *q;

        q = (block_t*)ptr - 1;

        for (p = &_alloc_base; p->ptr && p->ptr < q; p = p->ptr);

        if ((uint8_t*)p->ptr == ((uint8_t*)q) + q->size)
        {
            q->size += p->ptr->size;
            q->ptr = p->ptr->ptr;
        }
        else
        {
            q->ptr = p->ptr;
        }

        if (((uint8_t*)p) + p->size == (uint8_t*)q)
        {
            p->size += q->size;
            p->ptr = q->ptr;
        }
        else
        {
            p->ptr = q;
        }
    }
}

void *_standard_realloc(void *ptr, size_t size)
{
    block_t *h;
    void *p;

    if (ptr == NULL)
    {
        return malloc(size);
    }

    h = (block_t*)((uint8_t*)ptr - sizeof(block_t));

    if (h->size >= (size + sizeof(block_t)))
    {
        return ptr;
    }

    if ((p = malloc(size)))
    {
        memcpy(p, ptr, size);
        free(ptr);
    }

    return p;
}
