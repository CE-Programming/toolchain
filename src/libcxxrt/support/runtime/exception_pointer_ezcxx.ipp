// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <stdio.h>
#include <stdlib.h>
#include "../libcxx/abort_message.h"

namespace std {

exception_ptr::~exception_ptr() noexcept
{
  __abort_message("exception_ptr not yet implemented");
}

exception_ptr::exception_ptr(const exception_ptr& other) noexcept
    : __ptr_(other.__ptr_)
{
  __abort_message("exception_ptr not yet implemented");
}

exception_ptr& exception_ptr::operator=(__attribute__((__unused__)) const exception_ptr& other) noexcept
{
  __abort_message("exception_ptr not yet implemented");
}

nested_exception::nested_exception() noexcept
    : __ptr_(current_exception())
{
}

#if !defined(__GLIBCXX__)

nested_exception::~nested_exception() noexcept
{
}

#endif

_LIBCPP_NORETURN
void
nested_exception::rethrow_nested() const
{
  __abort_message("exception_ptr not yet implemented");
#if 0
  if (__ptr_ == nullptr)
      terminate();
  rethrow_exception(__ptr_);
#endif // FIXME
}

exception_ptr current_exception() noexcept
{
  __abort_message("exception_ptr not yet implemented");
}

_LIBCPP_NORETURN
void rethrow_exception(__attribute__((__unused__)) exception_ptr p)
{
  __abort_message("exception_ptr not yet implemented");
}

} // namespace std
