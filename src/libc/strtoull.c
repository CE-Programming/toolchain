#define STRTOX_TYPE    long long
#define STRTOX_MAX     ULLONG_MAX
#define STRTOX_MIN     0

#define STRTOX_SIGNED  0
#define STRTOX_NAME    strtoull

#include "strtox.h"

/* not sure why __ULLONG_WIDTH__ isn't defined */
#if __UINTMAX_WIDTH__ == __LLONG_WIDTH__
__UINTMAX_TYPE__ strtoumax(const char *, char **, int) __attribute__((alias("strtoull")));
#endif /* __UINTMAX_WIDTH__ == __LLONG_WIDTH__ */
