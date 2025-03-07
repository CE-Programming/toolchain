#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/lcd.h>
#include <debug.h>

// This allocator uses the 2nd part of the VRAM as the heap. It gives you 76K of memory,
// but requires you to only use the first part of the VRAM for the LCD configured in 8bpp.

#define MALLOC_MINSIZE 6 // minimal size (avoid blocks that are too small)

static unsigned int freeslotpos(unsigned int n)
{
    unsigned int r = 1;
    if ((n << 8) == 0)
    {
        // bit15 to 0 are 0, position must be >=16
        // otherwise position is <16
        r += 16;
        n >>= 16;
    }
    if ((n << 16) == 0)
    {
        // bit7 to 0 are 0, position must be >=8
        // otherwise position is <8
        r += 8;
        n >>= 8;
    }
    if ((n << 20) == 0)
    {
        r += 4;
        n >>= 4;
    }
    if ((n << 22) == 0)
    {
        r += 2;
        n >>= 2;
    }
    r -= n & 1;
    // dbg_printf("freeslotpos n=%p r=%zu\n",n,r);
    return r;
}

typedef struct char2_ {
    char c1, c2, c3, c4;
} char2_t;

typedef struct char3_ {
    char c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;
} char3_t;

typedef struct char6_ {
    char c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16;
} char6_t;

typedef struct __attribute__((packed)) block
{
    struct block* ptr;
    size_t size;
} __attribute__((packed)) block_t;

extern uint8_t __heapbot[];
extern uint8_t __heaptop[];

// assumes that heap2_ptrend<=lcd_Ram
static uintptr_t heap2_ptr = (uintptr_t)__heapbot;
static uintptr_t heap2_ptrend = (uintptr_t)__heaptop;

#define ALLOC2 (12 * INT24_WIDTH)
static unsigned int freeslot2[ALLOC2 / INT24_WIDTH] = {
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
};
#define ALLOC3 (12 * INT24_WIDTH)
static unsigned int freeslot3[ALLOC3 / INT24_WIDTH] = {
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
};
#define ALLOC6 (12 * INT24_WIDTH)
static unsigned int freeslot6[ALLOC6 / INT24_WIDTH] = {
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
};

#define LCD_SIZE_8BPP (LCD_WIDTH * LCD_HEIGHT)
const char2_t* tab2 = lcd_Ram + LCD_SIZE_8BPP;
const char3_t* tab3 = lcd_Ram + LCD_SIZE_8BPP + ALLOC2 * sizeof(char2_t);
const char6_t* tab6 = lcd_Ram + LCD_SIZE_8BPP + ALLOC2 * sizeof(char2_t) + ALLOC3 * sizeof(char3_t);

static uintptr_t heap_ptr = (uintptr_t)(lcd_Ram + LCD_SIZE_8BPP + ALLOC2 * sizeof(char2_t) + ALLOC3 * sizeof(char3_t) + ALLOC6 * sizeof(char6_t));
static uintptr_t heap_ptrend = (uintptr_t)(lcd_Ram + LCD_SIZE);

static block_t _alloc_base, _alloc2_base;
// these are 0 initialized, pointing to a chained list of freed pointers

void* _vram2_malloc(const size_t alloc_size)
{
    // dbg_printf("[malloc] %zu bytes\n", alloc_size);

    if (alloc_size == 0)
        return NULL;

    if (alloc_size == 0xFFFFFF)
        return (void*)((heap_ptrend - heap_ptr) + (heap2_ptrend - heap2_ptr));

    if (alloc_size <= sizeof(char6_t))
    {
        if (tab2 && alloc_size <= sizeof(char2_t))
        {
            for (unsigned int i = 0; i < ALLOC2 / INT24_WIDTH;)
            {
                if (!(freeslot2[i] || freeslot2[i + 1]))
                {
                    i += 2;
                    continue;
                }
                if (freeslot2[i])
                {
                end2: {
                        const unsigned int pos = freeslotpos(freeslot2[i]);
                        freeslot2[i] &= ~(1 << pos);
                        // dbg_printf("allocfast2 %p %p\n", tab2, tab2 + i * INT24_WIDTH + pos);
                        return (void*)(tab2 + i * INT24_WIDTH + pos);
                    }
                }
                ++i;
                goto end2;
            }
        }
        if (tab3 && alloc_size <= sizeof(char3_t))
        {
            for (unsigned int i = 0; i < ALLOC3 / INT24_WIDTH;)
            {
                if (!(freeslot3[i] || freeslot3[i + 1]))
                {
                    i += 2;
                    continue;
                }
                if (freeslot3[i])
                {
                end3: {
                        const unsigned int pos = freeslotpos(freeslot3[i]);
                        freeslot3[i] &= ~(1 << pos);
                        // dbg_printf("allocfast3 %p %p\n", tab3, tab3 + i * INT24_WIDTH + pos);
                        return (void*)(tab3 + i * INT24_WIDTH + pos);
                    }
                }
                i++;
                goto end3;
            }
        }
        if (tab6 && alloc_size <= sizeof(char6_t))
        {
            for (unsigned int i = 0; i < ALLOC6 / INT24_WIDTH;)
            {
                if (!(freeslot6[i] || freeslot6[i + 1]))
                {
                    i += 2;
                    continue;
                }
                if (freeslot6[i])
                {
                end6: {
                        const unsigned int pos = freeslotpos(freeslot6[i]);
                        freeslot6[i] &= ~(1 << pos);
                        // dbg_printf("allocfast6 %p %p\n", tab6, tab6 + i * INT24_WIDTH + pos);
                        return (void*)(tab6 + i * INT24_WIDTH + pos);
                    }
                }
                ++i;
                goto end6;
            }
        }
    }

    block_t* q;
    block_t* r;

    /* add size of block header to real size */
    size_t size = alloc_size + sizeof(block_t);
    if (size < alloc_size)
        return NULL;

    // dbg_printf("alloc heap %p ptr=%p size=%zu\n",&_alloc_base,_alloc_base.ptr,_alloc_base.size);

    for (block_t* p = &_alloc_base; (q = p->ptr); p = q)
    {
        if (q->size >= size)
        {
            if (q->size <= size + sizeof(block_t) + MALLOC_MINSIZE)
            {
                // dbg_printf("heap recycle full blocsize=%zu size=%zu\n", q->size, size);
                p->ptr = q->ptr;
            }
            else
            {
                // dbg_printf("heap recycle partial blocsize=%zu size=%zu\n", q->size, size);
                q->size -= size;
                q = (block_t*)(((uint8_t*)q) + q->size);
                q->size = size;
            }

            return q + 1;
        }
    }

    /* compute next heap pointer */
    if (heap_ptr + size < heap_ptr || heap_ptr + size >= (uintptr_t)heap_ptrend)
    {
        // dbg_printf("alloc heap2 %p ptr=%p size=%zu\n",&_alloc2_base,_alloc2_base.ptr,_alloc2_base.size);
        for (block_t* p = &_alloc2_base; (q = p->ptr); p = q)
        {
            if (q->size >= size)
            {
                if (q->size <= size + sizeof(block_t))
                {
                    // dbg_printf("heap2 recycle full blocsize=%zu size=%zu\n", q->size, size);
                    p->ptr = q->ptr;
                }
                else
                {
                    // dbg_printf("heap2 recycle partial blocsize=%zu size=%zu\n", q->size, size);
                    q->size -= size;
                    q = (block_t*)(((uint8_t*)q) + q->size);
                    q->size = size;
                }

                return q + 1;
            }
        }
        if (heap2_ptr + size < heap2_ptr ||
            heap2_ptr + size >= (uintptr_t)heap2_ptrend)
        {
            lcd_Control = 0b100100101101; // TI-OS default
            abort();
            return NULL;
        }
        r = (block_t*)heap2_ptr;
        if (size < MALLOC_MINSIZE)
            size = MALLOC_MINSIZE;
        r->size = size;
        heap2_ptr = heap2_ptr + size;
        return r + 1;
    }

    if (size < MALLOC_MINSIZE)
        size = MALLOC_MINSIZE;

    r = (block_t*)heap_ptr;
    r->size = size;
    heap_ptr = heap_ptr + size;
    return r + 1;
}

void _vram2_free(void* ptr)
{
    // dbg_printf("[free] %p\n", ptr);
    if (ptr != NULL)
    {
        if (((size_t)ptr >= (size_t)&tab2[0]) &&
            ((size_t)ptr < (size_t)&tab2[ALLOC2]))
        {
            const unsigned int pos = ((size_t)ptr - ((size_t)&tab2[0])) / sizeof(char2_t);
            // dbg_printf("deletefast2 %p pos=%i\n", ptr, pos);
            freeslot2[pos / INT24_WIDTH] |= (1 << (pos % INT24_WIDTH));
            return;
        }
        if (((size_t)ptr >= (size_t)&tab3[0]) &&
            ((size_t)ptr < (size_t)&tab3[ALLOC3]))
        {
            const unsigned int pos = ((size_t)ptr - ((size_t)&tab3[0])) / sizeof(char3_t);
            // dbg_printf("deletefast3 %p pos=%i\n", ptr, pos);
            freeslot3[pos / INT24_WIDTH] |= (1 << (pos % INT24_WIDTH));
            return;
        }
        if (((size_t)ptr >= (size_t)&tab6[0]) &&
            ((size_t)ptr < (size_t)&tab6[ALLOC6]))
        {
            const unsigned int pos = ((size_t)ptr - ((size_t)&tab6[0])) / sizeof(char6_t);
            // dbg_printf("deletefast6 %p pos=%i\n", ptr, pos);
            freeslot6[pos / INT24_WIDTH] |= (1 << (pos % INT24_WIDTH));
            return;
        }

        block_t* q = (block_t*)ptr - 1;

        block_t* p = ((uintptr_t)ptr <= heap2_ptrend) ? &_alloc2_base : &_alloc_base;
        // dbg_printf("free ptr=%p heap_end=%p p=%p pptr=%p psize=%zu\n",ptr,heap_ptrend,p,p->ptr,p->size);

        for (; p->ptr && p->ptr < q; p = p->ptr) {}
        // p next pointer in the free-ed chaine list, p->ptr,
        // is 0 or is the first pointer >= q
        // (this means that p is before q)
        if ((uint8_t*)p->ptr == ((uint8_t*)q) + q->size)
        {
            // concatenate q and p next pointer
            q->size += p->ptr->size;
            q->ptr = p->ptr->ptr;
            // dbg_printf("free concatenate blocsize=%zu\n", q->size);
        }
        else
        {
            // insert in chained list: get q next cell from p next cell
            q->ptr = p->ptr;
            // dbg_printf("free add block blocsize=%zu\n", q->size);
        }
        // check if we can concatenate p and q
        if (((uint8_t*)p) + p->size == (uint8_t*)q)
        {
            // yes
            p->size += q->size;
            p->ptr = q->ptr;
        }
        else
        {
            // no, update next pointer for p
            p->ptr = q;
        }
    }
}

void* _vram2_realloc(void* ptr, const size_t size)
{
    // dbg_printf("[realloc] %p for %zu bytes\n", ptr, size);

    if (ptr == NULL)
    {
        return malloc(size);
    }

    if ((((size_t)ptr >= (size_t)&tab2[0]) && ((size_t)ptr < (size_t)&tab2[ALLOC2])) ||
        (((size_t)ptr >= (size_t)&tab3[0]) && ((size_t)ptr < (size_t)&tab3[ALLOC2])) ||
        (((size_t)ptr >= (size_t)&tab6[0]) && ((size_t)ptr < (size_t)&tab6[ALLOC2])))
    {
        // ok
    }
    else
    {
        const block_t* h = (block_t*)((uint8_t*)ptr - sizeof(block_t));
        if (h->size >= (size + sizeof(block_t)))
        {
            return ptr;
        }
    }

    void* p = malloc(size);
    if (p)
    {
        memcpy(p, ptr, size);
        free(ptr);
    }

    return p;
}
