#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct __attribute__((packed)) block {
    struct block *next;
    size_t total_size;
    uint8_t data[];
} __attribute__((packed)) block_t;

extern uint8_t __heap_low[];
extern uint8_t __heap_high[];
static uintptr_t heap_ptr = (uintptr_t)__heap_low;
// heap_base is the only node where total_size = 0
static block_t heap_base = { .next = NULL, .total_size = 0 };

#define BLOCK_HEADER_SIZE offsetof(block_t, data)

// malloc(0) returns NULL
void *malloc(size_t alloc_size)
{
    const size_t block_size = alloc_size + BLOCK_HEADER_SIZE;
    if (block_size <= BLOCK_HEADER_SIZE) {
        // reject if alloc_size is 0 or size overflowed
        return NULL;
    }

    // search through the free-list for an open block (sorted by address)
    block_t *previous_block = &heap_base;
    while (previous_block->next != NULL) {
        block_t *current_block = previous_block->next;

        if (current_block->total_size >= block_size) {
            if (current_block->total_size - BLOCK_HEADER_SIZE <= block_size) {
                // region is too small to split into two parts, so just claim the whole region
                previous_block->next = current_block->next;
                return current_block->data;
            }
            // split from the high end so the original free-list node stays valid
            current_block->total_size -= block_size;
            current_block = (block_t*)(((uint8_t*)current_block) + current_block->total_size);
            current_block->total_size = block_size;
            return current_block->data;
        }

        previous_block = previous_block->next;
    }

    // no suitable free block exists, extend into fresh heap space
    size_t heap_available = (uintptr_t)__heap_high - (uintptr_t)heap_ptr;
    if (block_size > heap_available) {
        return NULL;
    }

    block_t *new_block = (block_t*)heap_ptr;
    new_block->total_size = block_size;
    heap_ptr = heap_ptr + block_size;

    return new_block->data;
}

void free(void *ptr)
{
    if (ptr == NULL) {
        return;
    }

    block_t *previous_block = &heap_base;
    block_t *current_block = (block_t*)((uint8_t*)ptr - BLOCK_HEADER_SIZE);
    while (
        previous_block->next != NULL &&
        (uintptr_t)previous_block->next < (uintptr_t)current_block
    ) {
        previous_block = previous_block->next;
    }

    // merge with the following free block if it is directly adjacent
    if (
        previous_block->next != NULL &&
        (uint8_t*)previous_block->next == ((uint8_t*)current_block) + current_block->total_size
    ) {
        current_block->total_size += previous_block->next->total_size;
        current_block->next = previous_block->next->next;
    } else {
        current_block->next = previous_block->next;
    }

    // merge with the preceding free block, unless that predecessor is heap_base
    if (
        previous_block->total_size != 0 &&
        ((uint8_t*)previous_block) + previous_block->total_size == (uint8_t*)current_block
    ) {
        previous_block->total_size += current_block->total_size;
        previous_block->next = current_block->next;
    } else {
        previous_block->next = current_block;
    }
}

// realloc(ptr, 0) returns ptr and does nothing
void *realloc(void *ptr, size_t alloc_size)
{
    if (ptr == NULL) {
        return malloc(alloc_size);
    }

    block_t *header = (block_t*)((uint8_t*)ptr - BLOCK_HEADER_SIZE);
    if (header->total_size - BLOCK_HEADER_SIZE >= alloc_size) {
        // realloc(ptr, 0) is undefined in C23 and returns here
        return ptr;
    }

    // increase allocation size
    void *new_ptr = malloc(alloc_size);
    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, header->total_size - BLOCK_HEADER_SIZE);
    free(ptr);

    return new_ptr;
}
