#include <assert.h>

int check_disabled_assert(int value) {
    /* Disabled arguments must not even require valid identifiers. */
#ifdef __cplusplus
    static_assert(__is_same(decltype(assert(undeclared_identifier)), void),
                  "disabled assert must be void");
#else
    typedef char assert_must_be_void[
        __builtin_types_compatible_p(
            __typeof__(assert(undeclared_identifier)), void) ? 1 : -1
    ];
    (void)sizeof(assert_must_be_void);
#endif

    value ? assert(undeclared_identifier) : assert(undeclared_function());
    return (assert(undeclared_identifier), value);
}
