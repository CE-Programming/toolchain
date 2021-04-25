#undef NDEBUG
#include "abort_message.h"

#include <debug.h>
#include <stdlib.h>

void abort_message(const char *message) {
    dbg_sprintf(dbgerr, "libezc++: %s\n", message);
    abort();
}
