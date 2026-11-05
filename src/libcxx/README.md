# libc++ 23 for the CE toolchain

This port imports LLVM **23.1.5**, tag `llvmorg-23.1.5`, commit
`392dfff97d29b59d77e5cac6d4b6ef2585fe7117`. The imported files and their
licenses are mapped in [UPSTREAM.json](UPSTREAM.json).

The branch starts from toolchain master at `283292dd` and carries forward
the CE adaptations from `libcxx_22` at `1f960e0d`, originally based on
ZERICO2005's port at `63b8cce1`. Its first four commits separate removal of the
old STL, the pristine upstream import, CE customization, and metadata/tests.
Follow-up commits remove workarounds covered by the compiler audit below.
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
The full regression suite now requires the **unpublished compiler fixes** listed
in `UPSTREAM.json`, on top of the Clang 22.1.8 nightly at `c1c359f0f2ea`.
They fix generic 24-bit byteswap, NaN and signed-zero comparisons, partial-width
overflow arithmetic, and inline-assembly symbol operands. The published nightly
already contains the 48-bit signedness and bidirectional floating-point
conversion fixes, but does not yet contain these new audit fixes.

## Target adaptations

The existing 24-bit integer, 32-bit double, locale, allocation, hash, and
formatting adaptations are preserved. The signed/unsigned `__int48`
conversion, math-promotion, random-distribution, and string-conversion extensions
are adapted from Zerico's earlier [`libcxx_stl` patch](https://github.com/CE-Programming/toolchain/commit/c5e39332614ec9c0ae7c55c33daf729539f8e84e)
and [`libcxx_22_locale` port](https://github.com/ZERICO2005/toolchain/commit/5c3317788edabe8bd1a40cfe753a57b9e2f77525).
`to_string` and `to_wstring` include runtime definitions and widen to 64 bits
before formatting, since upstream charconv helpers do not handle six-byte
integer storage. The v23 upstream traits and bit algorithms remain in use.
Floating-point classification now uses upstream compiler builtins at runtime
and during constant evaluation. The compiler audit covers quiet/signaling NaNs,
infinities, subnormals, and both zero signs. No global fast-math or finite-only
default is introduced. `<numbers>` retains long-double precision.

The upstream generic byteswap and function-override detector are restored.
Locale integer parsing uses the upstream overflow builtins again, including its
mixed signed/unsigned operands. The override detector is tested with separate
compilation, matching the libc++ archive build: a strong definition overrides
one weak function while a second remains unchanged.

The algorithm SIMD exclusion remains: an O2 runtime stress test exposes
unsupported packed-boolean bitcasts even in the ordinary algorithm path.
Locale parsing also uses a fixed 32-lane search when these utilities are enabled.
The native vector-width value of one is not enough to make those paths safe.
`bitset::count()` restores the small-bitset fast path
using a native storage-word mask instead of `_BitInt`.

The obsolete `__ishru_1_fast`/`__ishrs_1_fast` compatibility aliases are removed;
the compiler uses the existing `__ishru_1`/`__ishrs_1` entry points.

The compiler limitations still requiring libc++ customizations are:

- `_BitInt` overloads remain excluded: eZ80 Clang advertises
  `__BITINT_MAXWIDTH__` while rejecting `_BitInt` for this target. Small-bitset
  popcount uses the native-word equivalent instead.
- Algorithm SIMD utilities remain disabled because packed vector-boolean
  bitcasts are not supported, including the locale parser's fixed 32-lane search.

Other retained adaptations describe the CE data model or runtime interfaces.
For example, `chrono::years` and `chrono::months` need exact integer periods:
the upstream floating-point expression exceeds 24-bit `int` and loses precision
with the CE's 32-bit `double`. Those are separate from compiler limitations.

## Validation

The archive builds with eZ80 Clang 22.1.8. All 85 toolchain test projects
and the installed examples build against a fresh SDK in compressed and
uncompressed matrix modes. The float64 arithmetic test always uses compression
because its raw program exceeds one variable. All 131 CEmu autotest suites pass
in each matrix mode on the TI-83 Premium CE Edition Python 5.3.6 ROM.
Public-header syntax checks pass in C++17, C++20, and C++23, and project standard
overrides are verified.

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
Validation uses local Clang 22.1.8 builds with fixes through `8dd8b5a90f8c`,
with the optimization series through `dc51f004de33` for the complete suite.
All 51 backend tests pass before the optimization series and all 88 pass with
it. The five focused libc++/bit suites also pass with a library rebuilt by the
compiler before the optimization series. Physical-calculator validation has
not been performed.

The `stdbit` suite also exercises signed/unsigned 24- and 48-bit byteswap,
48-bit leading/trailing counts, bit width, floor/ceil, popcount, and randomized
rotations. Its constexpr checks cover 48-bit traits and both byteswap widths.
Target-specific compatibility blocks use compiler/width guards; the raw
upstream import commit provides the baseline for auditing every CE change.

The compiler-audit regressions add a 588-pair floating-point comparison matrix
covering all 16 predicate results, with an independent integer-rank reference.
`libcxx_builtins` covers mixed signed/unsigned overflow at 8/16/24/32/48/64 bits,
bitset counts at zero, full-word and partial-word boundaries, and algorithm
results at every mismatch offset. The same suite passes at O2 with SIMD
utilities disabled. `libcxx_overrides` tests assembler aliases and weak-symbol
interposition without LTO, matching the library build. The existing float64
arithmetic test retains all 108 direct volatile-operand comparison expressions.
Its raw program exceeds one variable, so this test explicitly stays compressed
even in the uncompressed CI matrix. The compressed original passes both CEmu
checks with the compiler before and after the optimization series (17,369 and
16,968 bytes respectively).
