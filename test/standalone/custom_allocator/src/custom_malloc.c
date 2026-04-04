#include <string.h>
#include <stdlib.h>

static unsigned char arr[4096];

static unsigned char *arr_ptr = &arr[0];

int malloc_calls = 0;

void *malloc(size_t size) {
    if (size >= sizeof(arr)) {
        return NULL;
    }
    unsigned char *ret = arr_ptr;
    arr_ptr += size;
    memset(ret, 0xAA, size);
    malloc_calls++;
    return ret;
}
