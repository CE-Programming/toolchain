#include "__fileioc_stdio.h"

__attribute__((__weak__))
int rename(const char *old_filename, const char *new_filename) {
    return (int)ti_Rename(old_filename, new_filename);
}
