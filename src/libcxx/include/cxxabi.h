// -*- C++ -*-
#ifndef _EZCXX_CXXABI_H
#define _EZCXX_CXXABI_H

#include <cstddef>
#include <typeinfo>

#pragma clang system_header

namespace __cxxabiv1 {
struct __dynamic_cast_info;

class __fundamental_type_info : public std::type_info {
public:
    ~__fundamental_type_info();
};

class __array_type_info : public std::type_info {
public:
    ~__array_type_info();
};

class __function_type_info : public std::type_info {
public:
    ~__function_type_info();
};

class __enum_type_info : public std::type_info {
public:
    ~__enum_type_info();
};

class __class_type_info : public std::type_info {
public:
    ~__class_type_info();
    virtual void __search_above_target(__dynamic_cast_info *, const void *, const void *, bool) const noexcept;
    virtual void __search_below_target(__dynamic_cast_info *, const void *, bool) const noexcept;
};

class __si_class_type_info : public __class_type_info {
public:
    const __class_type_info *__base_type;

    ~__si_class_type_info();
    void __search_above_target(__dynamic_cast_info *, const void *, const void *, bool) const noexcept;
    void __search_below_target(__dynamic_cast_info *, const void *, bool) const noexcept;
};

struct __base_class_type_info {
public:
    const __class_type_info *__base_type;
    enum __offset_flags_masks : long {
        __virtual_mask = 0x1,
        __public_mask  = 0x2,
    } __offset_flags;

    std::ptrdiff_t __offset() const noexcept { return __offset_flags >> 8; }
    const void *__adjust_current_pointer(const void *) const noexcept;
    void __search_above_target(__dynamic_cast_info *, const void *, const void *, bool) const noexcept;
    void __search_below_target(__dynamic_cast_info *, const void *, bool) const noexcept;
};

class __vmi_class_type_info : public __class_type_info {
public:
    enum __flags_masks : unsigned {
        __non_diamond_repeat_mask = 1 << 0,
        __diamond_shaped_mask     = 1 << 1,
    } __flags;
    std::size_t __base_count;
    __base_class_type_info __base_info[];

    ~__vmi_class_type_info();
    void __search_above_target(__dynamic_cast_info *, const void *, const void *, bool) const noexcept;
    void __search_below_target(__dynamic_cast_info *, const void *, bool) const noexcept;
};

class __pbase_type_info : public std::type_info {
public:
    enum __masks : unsigned {
        __const_mask            = 1 << 0,
        __volatile_mask         = 1 << 1,
        __restrict_mask         = 1 << 2,
        __incomplete_mask       = 1 << 3,
        __incomplete_class_mask = 1 << 4,
        __transaction_safe_mask = 1 << 5,
        __noexcept_mask         = 1 << 6,
    } __flags;
    const std::type_info *__pointee;

    ~__pbase_type_info();
};

class __pointer_type_info : public __pbase_type_info {
public:
    ~__pointer_type_info();
};

class __pointer_to_member_type_info : public __pbase_type_info {
public:
    const __class_type_info *__context;

    ~__pointer_to_member_type_info();
};

extern "C" {

void *__dynamic_cast(const void *sub,
                     const __class_type_info *src,
                     const __class_type_info *dst,
                     std::ptrdiff_t src2dst_offset);

[[noreturn]] void __cxa_bad_cast();
[[noreturn]] void __cxa_bad_typeid();
[[noreturn]] void __cxa_pure_virtual();
[[noreturn]] void __cxa_deleted_virtual();

} // extern "C"

} // namespace __cxxabiv1

namespace abi = __cxxabiv1;

#endif // _EZCXX_CXXABI_H
