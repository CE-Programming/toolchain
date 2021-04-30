// -*- C++ -*-
#ifndef _EZCXX_TYPEINFO_H
#define _EZCXX_TYPEINFO_H

#include <typeinfo>

#pragma GCC system_header

namespace __cxxabiv1 {

struct __dynamic_cast_info;

struct __fundamental_type_info : std::type_info {
    ~__fundamental_type_info();
};
struct __array_type_info : std::type_info {
    ~__array_type_info();
};
struct __function_type_info : std::type_info {
    ~__function_type_info();
};
struct __enum_type_info : std::type_info {
    ~__enum_type_info();
};
struct __class_type_info : std::type_info {
    ~__class_type_info();
    virtual void search_above_target(__dynamic_cast_info *, const void *, const void *, bool) const;
    virtual void search_below_target(__dynamic_cast_info *, const void *, bool) const;
};
struct __si_class_type_info : __class_type_info {
    const __class_type_info *__base_type;
    ~__si_class_type_info();
    void search_above_target(__dynamic_cast_info *, const void *, const void *, bool) const;
    void search_below_target(__dynamic_cast_info *, const void *, bool) const;
};
struct __base_class_type_info {
    const __class_type_info *__base_type;
    enum __offset_flags_masks : unsigned char {
        __virtual_mask = 0x1,
        __public_mask  = 0x2,
    } __offset_flags;
    std::ptrdiff_t __offset;
    const void *adjust_current_pointer(const void *) const;
    void search_above_target(__dynamic_cast_info *, const void *, const void *, bool) const;
    void search_below_target(__dynamic_cast_info *, const void *, bool) const;
};
struct __vmi_class_type_info : __class_type_info {
    enum __flags_masks : unsigned {
        __non_diamond_repeat_mask = 1 << 0,
        __diamond_shaped_mask     = 1 << 1,
    } __flags;
    std::size_t __base_count;
    __base_class_type_info __base_info[];
    ~__vmi_class_type_info();
    void search_above_target(__dynamic_cast_info *, const void *, const void *, bool) const;
    void search_below_target(__dynamic_cast_info *, const void *, bool) const;
};
struct __pointer_type_info : std::type_info {
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
    ~__pointer_type_info();
};
struct __pointer_to_member_type_info : __pointer_type_info {
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
} // extern "C"

} // namespace __cxxabiv1

#endif // _EZCXX_TYPEINFO_H
