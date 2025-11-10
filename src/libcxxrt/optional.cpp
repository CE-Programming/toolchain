//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <__availability>
#include <optional>

namespace std
{

bad_optional_access::~bad_optional_access() noexcept = default;

const char* bad_optional_access::what() const noexcept {
  return "bad_optional_access";
}

} // std
