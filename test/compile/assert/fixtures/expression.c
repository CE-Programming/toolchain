#include <assert.h>

// expected-no-diagnostics

int check_assert_expression(int value) {
#ifdef __cplusplus
    static_assert(__is_same(decltype(assert(value)), void), "assert must be void");
#else
    typedef char assert_must_be_void[
        __builtin_types_compatible_p(__typeof__(assert(value)), void) ? 1 : -1
    ];
    (void)sizeof(assert_must_be_void);
#endif

    value ? assert(value > 0) : assert(value == 0);
    return (assert(value >= 0), value);
}
