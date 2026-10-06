#include <assert.h>

/* No NDEBUG: merely including the header does not expand the macro. */
void check_enabled_assert(int condition) {
    assert(condition);
}
