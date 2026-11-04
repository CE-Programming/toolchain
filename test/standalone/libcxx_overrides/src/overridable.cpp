#include "../../../../src/libcxx/src/include/overridable_function.h"

static_assert(_LIBCPP_CAN_DETECT_OVERRIDDEN_FUNCTION,
              "exercise the assembler alias detector, not the fallback");

// Keep the weak definitions and their aliases in one translation unit. The
// strong replacement in main.cpp must change only the public symbol's address.
OVERRIDABLE_FUNCTION int default_hook() { return 11; }
OVERRIDABLE_FUNCTION int replaced_hook() { return 22; }

bool test_function_overrides() {
    return !std::__is_function_overridden<int(), default_hook>() &&
           std::__is_function_overridden<int(), replaced_hook>() && default_hook() == 11 &&
           replaced_hook() == 33;
}
