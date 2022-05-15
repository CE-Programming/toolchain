#ifndef _ASSERT_H
#define _ASSERT_H

#include <cdefs.h>

#ifdef NDEBUG

# define assert(expr) __IGNORE(0)

#else /* NDEBUG */

__BEGIN_DECLS

struct __assert_loc {
    const char *__file;
    __UINT32_TYPE__ __line;
    const char *__function;
    const char *__assertion;
};

extern void __assert_fail_loc(const struct __assert_loc *__loc)
    __NOEXCEPT __attribute__((__cold__, __noreturn__));

__END_DECLS

/* Avoid putting extra parens around expr because it can hide warnings. */
# define assert(expr) do if (expr) {} else {                            \
            static const struct __assert_loc __loc = {                  \
                .__file = __FILE__,                                     \
                .__line = __STDINT_C(__LINE__, UINT32),                 \
                .__function = __extension__ __PRETTY_FUNCTION__,        \
                .__assertion = #expr,                                   \
            };                                                          \
            __assert_fail_loc(&__loc);                                  \
        } while (0)

#endif /* NDEBUG */

#if __STDC_VERSION__ >= 201112L && !defined(__cplusplus)
# undef static_assert
# define static_assert _Static_assert
#endif

#endif /* _ASSERT_H */
