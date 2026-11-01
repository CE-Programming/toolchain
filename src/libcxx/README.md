# libc++ for the CE toolchain

This experimental port is based on ZERICO2005/toolchain's `libcxx_22` branch
at `63b8cce1a2e90591a12df2928178c072ddde3741`, rebased onto toolchain master
at `283292dd2fcf4516a724be42470e7fa273da409c`.

The original imports use LLVM `llvmorg-22.1.4`. The vendored libc++ headers
and sources, libc++abi sources and headers, and libunwind headers are updated
to the official LLVM `llvmorg-22.1.8` tag (commit
`ca7933e47d3a3451d81e72ac174dcb5aa28b59d1`), retaining the CE adaptations.
Only `include/__config`, `include/__tree`, and `include/optional` changed
upstream between these releases in the imported paths.

Build with eZ80 Clang 22 and GNU binutils using `make libcxx`. Installation
recursively copies the headers, including libc++'s internal directories.
The configuration disables exceptions, RTTI, threads, filesystem support,
random-device support, Unicode, and the time-zone database.

This remains an experimental port, not a claim of full standard-library
support. Inherited limitations include integer-width conversion warnings,
incomplete locale and wide-character runtime support, and disabled 24-bit
byteswap and 48-bit `<bit>` test cases.

Validation with eZ80 Clang 22.1.8: the libc++ archive and all 84 toolchain
test projects build. CEmu passes the `libcxx_cmath`, `libcxx_stl`, `stdbit`,
`concepts`, and `fileno` autotests on a TI-83 Premium CE Edition Python
5.3.6 ROM with the standard CE libraries loaded.  
The STL test covers heap-backed containers and strings, ownership, optional
values, and extraction of the first equivalent multimap/multiset element.
