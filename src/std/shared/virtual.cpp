#include <cxxabi.h>

#include "abort_message.h"

namespace __cxxabiv1 {

void __cxa_pure_virtual() {
    std::__terminate_message("pure virtual method called");
}

void __cxa_deleted_virtual() {
    std::__terminate_message("deleted virtual method called");
}

} // namespace __cxxabiv1
