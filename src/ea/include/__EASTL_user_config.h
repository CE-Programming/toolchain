#ifndef _EASTL_USER_CONFIG_H
#define _EASTL_USER_CONFIG_H


#define EASTL_THREAD_SUPPORT_AVAILABLE 0
#define EASTL_EASTDC_VSNPRINTF 0


#if !defined(_SSIZE_T_) && !defined(_SSIZE_T_DEFINED) && !defined(SSIZE_T_DEFINED)
#define _SSIZE_T_
#define _SSIZE_T_DEFINED
#define SSIZE_T_DEFINED

#include <cstddef>

typedef ptrdiff_t ssize_t;
#define SSIZE_MAX INT_MAX
#endif


#include <__config>
#include <cstdint>

_EZCXX_INLINE void* operator new[](size_t size,
                                   const char* name,
                                   int flags,
                                   unsigned debugFlags,
                                   const char* file,
                                   int line)
{
    (void)name;
    (void)flags;
    (void)debugFlags;
    (void)file;
    (void)line;
    return new uint8_t[size];
}

_EZCXX_INLINE void* operator new[](size_t size,
                                   size_t alignment,
                                   size_t alignmentOffset,
                                   const char* name,
                                   int flags,
                                   unsigned debugFlags,
                                   const char* file,
                                   int line)
{
    (void)alignment;
    (void)alignmentOffset;
    (void)name;
    (void)flags;
    (void)debugFlags;
    (void)file;
    (void)line;
    return new uint8_t[size];
}

#endif // _EASTL_USER_CONFIG_H
