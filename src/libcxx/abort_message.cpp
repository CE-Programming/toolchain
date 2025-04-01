#undef NDEBUG
#include "abort_message.h"

#include <debug.h>
#include <cstdlib>
#include <exception>

namespace std {

void __terminate_message(const char *message) {
	dbg_sprintf(dbgerr, "libezc++: %s\n", message);
	std::terminate();
}

void __abort_message(const char *message) {
	dbg_sprintf(dbgerr, "libezc++: %s\n", message);
	abort();
}

}
