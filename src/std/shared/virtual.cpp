#include <cxxabi.h>

#include "abort_message.h"

namespace __cxxabiv1 {

void __cxa_pure_virtual() {
    abort_message("pure virtual method called");
}

void __cxa_deleted_virtual() {
    abort_message("deleted virtual method called");
}

} // namespace __cxxabiv1
