// -*- C++ -*-
#ifndef _EZCXX_ABORT_MESSAGE_H
#define _EZCXX_ABORT_MESSAGE_H

#include <cdefs.h>

#ifdef __cplusplus
# if __has_feature(cxx_exceptions)
#  define _EZCXX_MAYBE_THROW(exception, ...) throw exception(__VA_ARGS__)
# else // __has_feature(cxx_exceptions)
#  define _EZCXX_MAYBE_THROW(exception, ...) std::__terminate_message(#exception)
# endif // __has_feature(cxx_exceptions)

namespace std {
[[noreturn]] void __terminate_message(const char *);
#endif // __cplusplus

__BEGIN_DECLS

void __abort_message(const char *) __attribute__((noreturn));

__END_DECLS

} // namespace std

#endif // _EZCXX_ABORT_MESSAGE_H
