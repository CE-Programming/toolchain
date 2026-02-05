// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <__verbose_abort>

namespace std {

exception_ptr::~exception_ptr() noexcept {
  __libcpp_verbose_abort("exception_ptr not yet implemented\n");
}

exception_ptr::exception_ptr(const exception_ptr& other) noexcept : __ptr_(other.__ptr_) {
  __libcpp_verbose_abort("exception_ptr not yet implemented\n");
}

exception_ptr& exception_ptr::operator=(__attribute__((__unused__)) const exception_ptr& other) noexcept {
  __libcpp_verbose_abort("exception_ptr not yet implemented\n");
}

exception_ptr exception_ptr::__from_native_exception_pointer(__attribute__((__unused__)) void *__e) noexcept {
  __libcpp_verbose_abort("exception_ptr not yet implemented\n");
}

nested_exception::nested_exception() noexcept : __ptr_(current_exception()) {}

#if !defined(__GLIBCXX__)

nested_exception::~nested_exception() noexcept {}

#endif

[[noreturn]] void nested_exception::rethrow_nested() const {
  __libcpp_verbose_abort("exception_ptr not yet implemented\n");
#if 0
  if (__ptr_ == nullptr)
      terminate();
  rethrow_exception(__ptr_);
#endif // FIXME
}

exception_ptr current_exception() noexcept {
  __libcpp_verbose_abort("exception_ptr not yet implemented\n");
}

[[noreturn]] void rethrow_exception(__attribute__((__unused__)) exception_ptr p) {
  __libcpp_verbose_abort("exception_ptr not yet implemented\n");
}

} // namespace std
