#include "cxxabi.h"

#include "abort_message.h"

namespace std {

type_info::~type_info() {}

} // namespace std

namespace __cxxabiv1 {

struct __dynamic_cast_info {
    const void *static_pointer;
    const __class_type_info *static_type;
    const __class_type_info *target_type;
    std::ptrdiff_t offset;
    const void *down_cast_target_pointer;
    const void *side_cast_target_pointer;
    bool public_target_to_static : 1;
    bool public_dynamic_to_static : 1;
    bool public_dynamic_to_target : 1;
    bool target_not_derived_from_static : 1;
    bool single_target_type : 1;
    bool found_static_pointer : 1;
    bool found_a_static_type : 1;
    bool done : 1;
};

__fundamental_type_info::~__fundamental_type_info() {}
__array_type_info::~__array_type_info() {}
__function_type_info::~__function_type_info() {}
__enum_type_info::~__enum_type_info() {}
__class_type_info::~__class_type_info() {}
__si_class_type_info::~__si_class_type_info() {}
__vmi_class_type_info::~__vmi_class_type_info() {}
__pbase_type_info::~__pbase_type_info() {}
__pointer_type_info::~__pointer_type_info() {}
__pointer_to_member_type_info::~__pointer_to_member_type_info() {}

void *__dynamic_cast(const void *static_pointer,
                     const __class_type_info *static_type,
                     const __class_type_info *target_type,
                     std::ptrdiff_t offset) {
    __dynamic_cast_info info = {
        .static_pointer = static_pointer,
        .static_type = static_type,
        .target_type = target_type,
        .offset = offset,
        .down_cast_target_pointer = nullptr,
        .side_cast_target_pointer = nullptr,
        .public_target_to_static = false,
        .public_dynamic_to_static = false,
        .public_dynamic_to_target = false,
        .target_not_derived_from_static = false,
        .single_target_type = false,
        .found_static_pointer = false,
        .found_a_static_type = false,
        .done = false,
    };
    const void *target_pointer = nullptr;
    const struct vtable_header {
        std::ptrdiff_t offset;
        const __class_type_info *type;
    } *vtable = *static_cast<const vtable_header *const *>(static_pointer) - 1;
    const void *dynamic_pointer = static_cast<const char *>(static_pointer) + vtable->offset;
    const __class_type_info *dynamic_type = vtable->type;
    if (*dynamic_type == *target_type) {
        info.single_target_type = true;
        dynamic_type->__search_above_target(&info, dynamic_pointer, dynamic_pointer, true);
        if (info.public_target_to_static)
            target_pointer = dynamic_pointer;
    } else {
        dynamic_type->__search_below_target(&info, dynamic_pointer, true);
        if (!info.down_cast_target_pointer) {
            if (info.side_cast_target_pointer != &info &&
                info.public_dynamic_to_static && info.public_dynamic_to_target)
                target_pointer = info.side_cast_target_pointer;
        } else if (info.down_cast_target_pointer != &info) {
            if (info.public_target_to_static)
                target_pointer = info.down_cast_target_pointer;
            else if (!info.side_cast_target_pointer &&
                     info.public_dynamic_to_static && info.public_dynamic_to_target)
                target_pointer = info.down_cast_target_pointer;
        }
    }
    return const_cast<void *>(target_pointer);
}

void __class_type_info::__search_above_target(
        __dynamic_cast_info *info,
        const void *target_pointer,
        const void *current_pointer,
        bool public_below) const noexcept {
    if (*this != *info->static_type)
        return;
    info->found_a_static_type = true;
    if (current_pointer != info->static_pointer)
        return;
    info->found_static_pointer = true;
    if (!info->down_cast_target_pointer) {
        info->down_cast_target_pointer = target_pointer;
        info->public_target_to_static = public_below;
    } else if (info->down_cast_target_pointer != target_pointer) {
        info->down_cast_target_pointer = info;
        info->done = true;
        return;
    }
    info->public_target_to_static |= public_below;
    info->done |= info->single_target_type && info->public_target_to_static;
}

void __class_type_info::__search_below_target(
        __dynamic_cast_info *info,
        const void *current_pointer,
        bool public_below) const noexcept {
    if (*this == *info->static_type) {
        if (current_pointer == info->static_pointer)
            info->public_dynamic_to_static |= public_below;
    } else if (*this == *info->target_type) {
        if (current_pointer == info->down_cast_target_pointer ||
            current_pointer == info->side_cast_target_pointer)
            info->public_dynamic_to_target |= public_below;
        else {
            info->public_dynamic_to_target = public_below;
            info->side_cast_target_pointer =
                info->side_cast_target_pointer ? info : current_pointer;
            info->done |= info->public_target_to_static && info->down_cast_target_pointer;
            info->target_not_derived_from_static = true;
        }
    }
}

void __si_class_type_info::__search_above_target(
        __dynamic_cast_info *info,
        const void *target_pointer,
        const void *current_pointer,
        bool public_below) const noexcept {
    if (*this == *info->static_type)
        return __class_type_info::__search_above_target(info, target_pointer, current_pointer, public_below);
    __base_type->__search_above_target(info, target_pointer, current_pointer, public_below);
}

void __si_class_type_info::__search_below_target(
        __dynamic_cast_info *info,
        const void *current_pointer,
        bool public_below) const noexcept {
    if (*this == *info->static_type)
        return __class_type_info::__search_below_target(info, current_pointer, public_below);
    if (*this != *info->target_type)
        return __base_type->__search_below_target(info, current_pointer, public_below);
    if (current_pointer == info->down_cast_target_pointer ||
        current_pointer == info->side_cast_target_pointer) {
        info->public_dynamic_to_target |= public_below;
        return;
    }
    info->public_dynamic_to_target = public_below;
    bool same_target_static_pointers = false;
    if (!info->target_not_derived_from_static) {
        info->found_static_pointer = false;
        info->found_a_static_type = false;
        __base_type->__search_above_target(info, current_pointer, current_pointer, true);
        info->target_not_derived_from_static = !info->found_a_static_type;
        same_target_static_pointers = info->found_static_pointer && info->found_a_static_type;
    }
    if (!same_target_static_pointers) {
        info->side_cast_target_pointer =
            info->side_cast_target_pointer ? info : current_pointer;
        info->done |= info->public_target_to_static && info->down_cast_target_pointer;
    }
}

void __vmi_class_type_info::__search_above_target(
        __dynamic_cast_info *info,
        const void *target_pointer,
        const void *current_pointer,
        bool public_below) const noexcept {
    if (*this == *info->static_type)
        return __class_type_info::__search_above_target(info, target_pointer, current_pointer, public_below);
    bool found_static_pointer = info->found_static_pointer;
    bool found_a_static_type = info->found_a_static_type;
    std::size_t count = __base_count;
    const __base_class_type_info *current_base = __base_info;
    while (true) {
        info->found_static_pointer = false;
        info->found_a_static_type = false;
        current_base++->__search_above_target(info, target_pointer, current_pointer, public_below);
        found_static_pointer |= info->found_static_pointer;
        found_a_static_type |= info->found_a_static_type;
        if (info->done || !--count)
            break;
        if (info->found_static_pointer) {
            if (info->public_target_to_static || !(__flags & __diamond_shaped_mask))
                break;
        } else if (info->found_a_static_type) {
            if (!(__flags & __non_diamond_repeat_mask))
                break;
        }
    }
    info->found_static_pointer = found_static_pointer;
    info->found_a_static_type = found_a_static_type;
}

void __vmi_class_type_info::__search_below_target(
        __dynamic_cast_info *info,
        const void *current_pointer,
        bool public_below) const noexcept {
    if (*this == *info->static_type)
        return __class_type_info::__search_below_target(info, current_pointer, public_below);
    std::size_t count = __base_count;
    const __base_class_type_info *current_base = __base_info;
    if (*this != *info->target_type) {
        if (__flags & __diamond_shaped_mask || info->down_cast_target_pointer)
            do
                current_base++->__search_below_target(info, current_pointer, public_below);
            while (!info->done && --count);
        else if (__flags & __non_diamond_repeat_mask)
            do
                current_base++->__search_below_target(info, current_pointer, public_below);
            while (!info->done && --count &&
                   !(info->public_target_to_static && info->down_cast_target_pointer));
        else
            do
                current_base++->__search_below_target(info, current_pointer, public_below);
            while (!info->done && --count && !info->down_cast_target_pointer);
        return;
    }
    if (current_pointer == info->down_cast_target_pointer ||
        current_pointer == info->side_cast_target_pointer) {
        info->public_dynamic_to_target |= public_below;
        return;
    }
    info->public_dynamic_to_target = public_below;
    bool same_target_static_pointers = false;
    if (!info->target_not_derived_from_static) {
        bool target_not_derived_from_static = true;
        do {
            info->found_static_pointer = false;
            info->found_a_static_type = false;
            current_base++->__search_above_target(info, current_pointer, current_pointer, true);
            if (info->done)
                break;
            if (info->found_a_static_type) {
                target_not_derived_from_static = false;
                if (info->found_static_pointer) {
                    same_target_static_pointers = true;
                    if (!(__flags & __diamond_shaped_mask))
                        break;
                } else if (!(__flags & __non_diamond_repeat_mask))
                    break;
            }
        } while (--count);
        info->target_not_derived_from_static = target_not_derived_from_static;
    }
    if (!same_target_static_pointers) {
        info->side_cast_target_pointer =
            info->side_cast_target_pointer ? info : current_pointer;
        info->done |= info->public_target_to_static && info->down_cast_target_pointer;
    }
}

const void *__base_class_type_info::__adjust_current_pointer(
        const void *current_pointer) const noexcept {
    return static_cast<const char *>(current_pointer) +
        (__offset_flags & __virtual_mask ? *reinterpret_cast<const std::ptrdiff_t *>(
                *static_cast<const char *const *>(current_pointer) + __offset()) : __offset());
}

void __base_class_type_info::__search_above_target(
        __dynamic_cast_info *info,
        const void *target_pointer,
        const void *current_pointer,
        bool public_below) const noexcept {
    __base_type->__search_above_target(info, target_pointer, __adjust_current_pointer(current_pointer),
                                     public_below && __offset_flags & __public_mask);
}

void __base_class_type_info::__search_below_target(
        __dynamic_cast_info *info,
        const void *current_pointer,
        bool public_below) const noexcept {
    __base_type->__search_below_target(info, __adjust_current_pointer(current_pointer),
                                     public_below && __offset_flags & __public_mask);
}

void __cxa_bad_cast() {
    _EZCXX_MAYBE_THROW(std::bad_cast);
}

void __cxa_bad_typeid() {
    _EZCXX_MAYBE_THROW(std::bad_typeid);
}

} // namespace __cxxabiv1
