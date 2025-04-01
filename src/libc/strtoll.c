#define STRTOX_TYPE	long long
#define STRTOX_MAX	 LLONG_MAX
#define STRTOX_MIN	 LLONG_MIN

#define STRTOX_SIGNED  1
#define STRTOX_NAME	strtoll

#include "strtox.h"

#if __INTMAX_WIDTH__ == __LLONG_WIDTH__
__INTMAX_TYPE__ strtoimax(const char *, char **, int) __attribute__((alias("strtoll")));
#endif /* __INTMAX_WIDTH__ == __LLONG_WIDTH__ */
