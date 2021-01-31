#undef NDEBUG
#include <assert.h>
#include <debug.h>
#include <inttypes.h>
#include <stdlib.h>

void __assert_fail_loc(const struct __assert_loc *loc) {
    dbg_sprintf((char *)dbgerr, "assert: %s:%" PRIu32 ": %s: Assertion `%s' failed.\n",
                loc->__file, loc->__line, loc->__function, loc->__assertion);
    abort();
}
