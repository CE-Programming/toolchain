# libc++ 23 for the CE toolchain

This port imports LLVM **23.1.5**, tag `llvmorg-23.1.5`, commit
`392dfff97d29b59d77e5cac6d4b6ef2585fe7117`. The imported files and their
licenses are mapped in [UPSTREAM.json](UPSTREAM.json).

The branch starts from toolchain master at `283292dd` and carries forward
the CE adaptations from `libcxx_22` at `1f960e0d`, originally based on
ZERICO2005's port at `63b8cce1`. Its four commits separate removal of the
old STL, the pristine upstream import, CE customization, and metadata/tests.
All 1,851 files in the raw import commit match the upstream Git blobs exactly;
the following commit contains the target changes.

## Building and using the library

Use eZ80 Clang 22 and GNU binutils with `make libcxx`. The CE build includes
libc++ and libc++abi; only headers are imported from libunwind. Recursive
installation includes libc++'s internal header directories. The installed
headers report `_LIBCPP_VERSION == 230105`.

Library and application builds default to GNU C++23. A project's explicit
`-std=` option in `CXXFLAGS` takes precedence, for example
`CXXFLAGS = -Wall -Wextra -Oz -std=c++20` before including the toolchain
makefile.

The library is built without exceptions or RTTI. Threads, filesystem,
random-device support, Unicode, and the time-zone database are disabled.
Localization and wide-character support retain the incomplete CE runtime
interfaces from the previous port. Integer-width conversion warnings also
remain. The 24/48-bit byteswap and 48-bit `<bit>` checks are enabled.
The full regression suite requires the eZ80 Clang 22.1.8 nightly from compiler
revision [`c1c359f0f2ea`](https://github.com/CE-Programming/llvm-project/commit/c1c359f0f2ea33df6fe0a8a0e11676db1ff7507a)
or a descendant. It includes the 48-bit signedness fix from
[`b3f9795fb32c`](https://github.com/CE-Programming/llvm-project/commit/b3f9795fb32c)
and conversion legalization in both directions between 48-bit integers and
floating point. Older 22.1.8 binaries can build the library but fail these new
regressions.

## Target adaptations

The existing 24-bit integer, 32-bit double, locale, allocation, hash, and
formatting adaptations are preserved. The signed/unsigned `__int48`
conversion, math-promotion, random-distribution, and string-conversion extensions
are adapted from Zerico's earlier [`libcxx_stl` patch](https://github.com/CE-Programming/toolchain/commit/c5e39332614ec9c0ae7c55c33daf729539f8e84e)
and [`libcxx_22_locale` port](https://github.com/ZERICO2005/toolchain/commit/5c3317788edabe8bd1a40cfe753a57b9e2f77525).
`to_string` and `to_wstring` include runtime definitions and widen to 64 bits
before formatting, since upstream charconv helpers do not handle six-byte
integer storage. The v23 upstream traits and bit algorithms remain in use.
Floating-point classification uses
the CE routines at runtime and compiler builtins for constant folding;
`<numbers>` retains long-double precision.

The runtime classification fallbacks remain necessary: the Z80 backend maps
`FCMP_UNO` to constant false and `FCMP_ORD` to true, even with fast-math
disabled. Remove those fallbacks when compiler-side NaN handling is fixed
and the existing classification tests pass with direct builtins. No global
fast-math or finite-only default is introduced here.

The obsolete `__ishru_1_fast`/`__ishrs_1_fast` compatibility aliases are removed;
the compiler uses the existing `__ishru_1`/`__ishrs_1` entry points.

LLVM 23 needs these additional target adjustments:

- 24-bit byteswap uses a 32-bit builtin followed by an eight-bit shift.
  Clang 22's generic builtin emits `llvm.bswap.i24`, which its LLVM verifier
  rejects during LTO. The generic 48-bit builtin works directly.
- `_BitInt` overloads are excluded because eZ80 Clang advertises
  `__BITINT_MAXWIDTH__` while rejecting `_BitInt` for this target.
- `chrono::years` and `chrono::months` use exact integer periods. The upstream
  floating-point expression both exceeds 24-bit `int` and loses precision
  with the CE's 32-bit `double`.
- The function-override diagnostic uses libc++'s portable fallback because
  the eZ80 backend cannot lower the new inline-assembly constraints. Weak
  `operator new`/`delete` definitions remain overridable.

## Validation

The archive builds with eZ80 Clang 22.1.8. All 83 toolchain test projects
and the installed examples build against a fresh SDK in compressed and
uncompressed modes. All 129 CEmu autotest suites pass in each mode on the
TI-83 Premium CE Edition Python 5.3.6 ROM. Public-header syntax checks pass
in C++17, C++20, and C++23, and project standard overrides are verified.

The autotests cover the CE math predicates, STL allocations and
containers, optional/expected values, integer character conversion, exact
chrono periods, and first-equivalent-element extraction.

The `libcxx_stl` test includes both scalar and array nothrow allocation and
zero-size allocation. Its 48-bit regressions exercise signed/unsigned algorithm
counts, narrow/wide string conversion at integer limits, and random generation
over full-width and bounded intervals, including intervals crossing zero.
Compile-time checks verify mixed-integer math promotion, signed/unsigned 48-bit
type transformations (including cv-qualified types and enums), and the exact
year/month periods. Runtime checks exercise integer/floating-point casts in both
directions, fractional truncation, signed/unsigned boundaries, mixed 48-bit
`hypot`, duration conversion, and leap-year dates.
Validation uses the published Clang 22.1.8 nightly at `c1c359f0f2ea` in both
compression modes. Physical-calculator validation has not been performed.

The `stdbit` suite also exercises signed/unsigned 24- and 48-bit byteswap,
48-bit leading/trailing counts, bit width, floor/ceil, popcount, and randomized
rotations. Its constexpr checks cover 48-bit traits and both byteswap widths.
Target-specific compatibility blocks use compiler/width guards; the raw
upstream import commit provides the baseline for auditing every CE change.
