#include <debug.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef assert
#undef assert
#endif

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(e) \
	do { \
		if (!(e)) { \
			dbg_sprintf(dbgout, "Assertion failure: %s, file: %s, line %d\n", #e, __FILE__, __LINE__); \
			abort(); \
		} \
	} while (0)
#endif
