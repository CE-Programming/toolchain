#ifndef _ASSERT_H
#define _ASSERT_H

#include <cdefs.h>

#ifdef NDEBUG

# define assert(expr) __IGNORE(0)

#else /* NDEBUG */

__BEGIN_DECLS

struct __assert_loc {
    const char *__file;
    unsigned __line;
    const char *__function;
    const char *__assertion;
};

extern void __assert_fail_loc(const struct __assert_loc *__loc)
    __NOTHROW __attribute__((__cold__, __noreturn__));

__END_DECLS

/* Avoid putting extra parens around expr because it can hide warnings. */
# define assert(expr) do if (expr) {} else {            \
            static const struct __assert_loc __loc = {  \
                .__file = __FILE__,                     \
                .__line = __LINE__,                     \
                .__function = __PRETTY_FUNCTION__,      \
                .__assertion = #expr,                   \
            };                                          \
            __assert_fail_loc(&__loc);                  \
        } while (0)

#endif /* NDEBUG */

#endif /* _ASSERT_H */
