#include <assert.h>

/* Clang verifies that this warning is present and rejects unrelated errors. */
void check_assignment_warning(int value) {
    // expected-warning@+1 {{using the result of an assignment as a condition without parentheses}}
    assert(value = 1);
}
