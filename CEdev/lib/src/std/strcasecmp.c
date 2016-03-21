#include <string.h>
#include <ctype.h>

int strcasecmp(const char* s1, const char* s2) {
    const unsigned char* us1 = (const unsigned char*)s1;
    const unsigned char* us2 = (const unsigned char*)s2;

    while (tolower(*us1) == tolower(*us2)) {
        if (*us1++ == '\0')
            return (0);
        us2++;
    }
    
    return (tolower(*us1) - tolower(*us2));
}