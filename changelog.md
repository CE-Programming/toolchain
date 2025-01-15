# Change Log

## [Unreleased](https://github.com/CE-Programming/toolchain/compare/v12.1...master)

# [v12.1](https://github.com/CE-Programming/toolchain/releases/tag/v12.1) (2024-10-26)

* **New features**
  * Added convbin support for bundles by @mateoconlechuga
  * Added isblank function by @mateoconlechuga
  * Added _fpclassifyf and _isnormalf by @@ZERICO2005

* **Bugfixes**
  * Fixed _isinf function by @runer112
  * Fixed __ftoll ABI and left shift amount by @calc84maniac
  * Fixed graphx line clipping issue (#353) by @mateoconlechuga
  * Fixed msd_Close msddrvce freezing issue (#477) by @mateoconlechuga
  * Fixed multiple issues with inchar/outchar and fget/fput functions by @mateoconlechuga

* **Improvements**:
  * Optimized all isxxxxx ctype.h functions by @calc84maniac / @mateoconlechuga
  * The `inchar` function now returns `int` to support EOF by @mateoconlechuga

# [v12.0](https://github.com/CE-Programming/toolchain/releases/tag/v12.0) (2024-10-6)

* **New features**
  * Added optimized 48-bit runtime routines by @calc84maniac / @fundudeone
  * Added strftime implementation by @mateoconlechuga
  * Fixed off-by-one localtime day calculation (#469) by @mateoconlechuga
  * Added flip and rotate options for tilesets to convimg by @mateoconlechuga
  * Added support for different memory allocators by @mateoconlechuga

* **Bugfixes**
  * Exit functions are no longer read-only by @commandblockguy
  * Fixed off-by-one localtime day calculation (#469) by @mateoconlechuga
  * Fixed clipped text respecting multiple transparent colors (#353) by @mateoconlechuga
  * Fixed stop token in os_RunPrgm by @mateoconlechuga
  * Fixed initializer_list definition by @jacobly0
  * Fixed write crash in fileioc (#461) by @mateoconlechuga
  * Fixed floating point multiply bug by @calc84maniac
  * Fixed incorrect sign compare in __lcmpzero by @calc84maniac
  * Fixed bug in fatdrvce that could corrupt the root directory when creating a file by @mateoconlechuga
  * Fixed ldexpf behaviour for NaN and Inf by @ZERICO2005
  * Fixed duplicated OS_TOK_STAT_F define by @adriweb
  * Fixed some repository submodule issues by @myclevorname
  * Fixed color quantization for unique colors in convimg by @mateoconlechuga
  
* **Improvements**:
  * Fixes/improvements for str[n]casecmp by @calc84maniac
  * Fixes/improvements for GetStringInput by @calc84maniac
  * Fix skipping of large USB transfers by @jacobly0
  * Ensure interface is set in MSDDRVCE by @mateoconlechuga
  * Optimize 24-bit and 32-bit and/or/xor operations by @calc84maniac
  * Optimize malloc implementation by @calc84maniac
  * CI macos improvements by @adriweb
  * Greatly optimized the fatdrvce fat_SetFileBlockOffset function by @mateoconlechuga
  * Enforce fatdrvce to only support uppercase filenames by @mateoconlechuga
  * Added prefix and suffix options for convimg by @JonasVdS18

# [v11.2](https://github.com/CE-Programming/toolchain/releases/tag/v11.2) (2023-8-24)

* **New features**
  * Add back dedicated timer functions by @mateoconlechuga
  * Use timer 1 for clock and related functions by @mateoconlechuga

* **Bugfixes**
  * Fix sprintf/vsprintf/snprintf/vsprintf bounds checking by @mateoconlechuga
  * Fixes for convimg (palette generation) by @mateoconlechuga

* **Improvements**:
  * Add framerate limiting example by @commandblockguy
  * Ensure tools are compiled statically by @mateoconlechuga
  * Improve macOS deployment tools by @adriweb
  * Minor documentation improvements by @mateoconlechuga

# [v11.1](https://github.com/CE-Programming/toolchain/releases/tag/v11.1) (2023-5-19)

* **New features**
  * Changes fatdrvce API to make it easier to use by @mateoconlechuga
  * Adds `os_GetTokenInput` to get tokenized input from the OS by @mateoconlechuga
  * Support hex string for fixed colors in convimg by @mateoconlechuga

* **Bugfixes**
  * Fixes `os_GetStringInput` to support more menus by @mateoconlechuga
  * Add some pointer checks to usbdrvce examples by @adriweb
  * Change `OS_MATRIX_ELEMENT` to row-major by @Nikhil-42
  * Fix 1-wide `gfx_Rectangle_NoClip` calls by @runer112
  * Numerous fixes in both convbin and convimg by @mateoconlechuga

* **Improvements**:
  * Add comments for symbols to grahpx source code by @TIny-Hacker
  * Improve error for long variable names by @mateoconlechuga
  * Add VS Code IDE documentation by @commandblockguy
  * Add names to some anonymous structures by @adriweb
  * Update fasmg-ez80 support by @jacobly0
  * Add more info about system values by @adriweb
  * Allow for overriding of source file extensions by @mateoconlechuga
  * Default example binaries to archive by @LogicalJoe

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v11.0...v11.1)

# [v11.0](https://github.com/CE-Programming/toolchain/releases/tag/v11.0) (2022-12-06)

* **New features**
  * Add usbdrvce library for interfacing with the USB port by @jacobly0
  * Add srldrvce library for interfacing with serial-based devices by @commandblockguy
  * Add msddrvce and fatdrvce libraries for interfacing with mass storage devices by @mateoconlechuga
  * Add fileioc library `ti_ArchiveHasRoomVar` function by @mateoconlechuga
  * Update convimg to support more conversion options by @mateoconlechuga

* **Bugfixes**
  * Fix fileioc library `ti_ArchiveHasRoom` function by @mateoconlechuga
  * Ensure spaces aren't provided in the program name by @mateoconlechuga
  * Fix convimg option `max-entries` by @mateoconlechuga
  * Fix defines for OS_VAR_Z and OS_VAR_THETA by @commandblockguy

* **Improvements**:
  * Optimize utility function in fileioc by @jacobly0
  * Optimize 24-bit right shift for much lower maximum runtime by @calc84maniac
  * Improve macOS codesigning and nightly builds by @adriweb
  * Update documentation for `os_GetCSC` and `os_GetKey` by @RealStoneSword
  * Optimize `__ishl` for bounded execution time for larger shifts by @calc84maniac

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v10.2...v11.0)

# [v10.2](https://github.com/CE-Programming/toolchain/releases/tag/v10.2) (2022-08-10)

* **New features**
  * Add `os_Eval` and `os_EvalVar` for direct evalution of equations by @mateoconlechuga.
  * Add automated DMG code signing / notarization for nightly macOS builds by @adriweb.
  * Updated and improved `convfont` support with text-based fonts by @drdnar.
  * Added comments for 8XP programs in `convbin` by @mateoconlechuga.
  * Added transparent pixel support in `convimg` by @mateoconlechuga.

* **Bugfixes**
  * Fix comparison of int32_t and int64_t by @runer112.
  * Fix `printf` when printing certain floating point values by @mateoconlechuga.
  * Fix printing of `int32_t` by @jacobly0.
  * Fix `gfx_FloodFill` issue on bottom on screen wrapping by @mateoconlechuga.
  * Change the type of CLOCKS_PER_SECOND to match clock_t by @commandblockguy.
  * Compiler fix for missing register class check by @jacobly0.

* **Improvements**:
  * Deprecate `TI_REAL_TYPE` and `ti_Ans` style of macros by @mateoconlechuga.
  * Deprecate `sk_key_t` and `ti_var_t` typedefs by @mateoconlechuga.
  * General documentation updates and improvements.

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v10.1...v10.2)

# [v10.1](https://github.com/CE-Programming/toolchain/releases/tag/v10.1) (2022-06-03)

* **New features**
  * Adds `byteswap.h` header file as standard.
  * Added `zx0` compression option for generating compressed programs via `convbin`.
  * Added `zx0` compression option for images converted with `convimg`.
  * Added optional LibLoad library support via `LIBLOAD_OPTIONAL` makefile option.

* **Bugfixes**
  * Fixes invalid jump targets generated by the compiler.
  * Fixes strcasecmp compilation.
  * Fixes `make debug` when LTO is enabled.

* **Improvements**:
  * Moves C++ includes to separate include directory to ensure no C include overlap.
  * Implement optimized `lbswap` and `llbswap` by @runer112 in https://github.com/CE-Programming/toolchain/pull/386

* **Documentation**:
  * Documentation updates and improvements, mainly to makefile options

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v10.0...v10.1)

# [v10.0](https://github.com/CE-Programming/toolchain/releases/tag/v10.0) (2022-05-25)

* **New features**:
  * Implement 64-bit math support. By @runer112 in https://github.com/CE-Programming/toolchain/pull/354
  * LTO (link-time optimization) is now available and enabled by default - it may help generating smaller binaries.
  * `make test` is available for the examples to launch the _autotest_ if available, which uses a now-shipped CLI-based CEmu with the autotester.
  * A "nightly" automated release is now available for each new commit on the master branch, thanks to @mateoconlechuga
  * `alloca` is now available. By @mateoconlechuga and @jacobly0
  * More/Better support for C++ in various headers
  * Ellipse and filled ellipse routines added to GraphX by @PeterTillema

* **Bugfixes**:
  * A few bugs in the **ez80-clang** compiler were fixed by @jacobly0
  * A few bugs in the tooling _(convimg, convbin...)_ and libload were fixed by @mateoconlechuga
  * Pop arguments after calling `_asin` by @PeterTillema in https://github.com/CE-Programming/toolchain/pull/352
  * Implement `strrchr` since the static zilog one was broken. By @jacobly0
  * **std**: Fix various standard defines. By @jacobly0
  * Fix `NULL` argument to `strtok` (fix https://github.com/CE-Programming/toolchain/issues/348) by @commandblockguy
  * **FileIOC**: Fix return value for ti_RclVar. By @commandblockguy
  * Switch addresses of `os_RealAsinRad` and `os_RealAcosRad` by @arjvik in https://github.com/CE-Programming/toolchain/pull/358

* **Improvements**:
  * Optimize and add static math functions. By @runer112 in https://github.com/CE-Programming/toolchain/pull/354
  * Complete refactor of the headers to simplify and better split features. By @drdnar in https://github.com/CE-Programming/toolchain/pull/378
  * Better code generation possible with more section-ing (`section	.text` has to be added in ASM files before code, now)
  * Two examples/templates are now [available as template repos](https://github.com/CE-Programming/?type=template#org-repositories), make it easier to start developing. Thanks @commandblockguy

* **Documentation**:
  * Lots of improvements and details added, following the various refactors listed above, but also typos, clarifications, etc.
  (By @drdnar mainly, but also @runer112, @tari, @mateoconlechuga, @Dragon-Hatcher, @Chr1sDev, @PeterTillema, @mrwompwomp, @Aulimaitar, @HexCodeFFF)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v9.2.2...v10.0)

# [v9.2.2](https://github.com/CE-Programming/toolchain/releases/tag/v9.2.2) (2021-09-21)

  - Fix an edge case when creating multiple appvars with convimg
  - Prevent fileioc from crashing if the user provides an invalid slot

# [v9.2.1](https://github.com/CE-Programming/toolchain/releases/tag/v9.2.1) (2021-09-11)

  - Patch for edge case where `delay()` and `usleep()` functions may freeze
  - Minor documentation updates

# [v9.2](https://github.com/CE-Programming/toolchain/releases/tag/v9.2) (2021-09-09)

  - Deprecate `timer_GetLow` and `ti_CloseAll` functions
  - Remove pixelShadow from BSS to fix issue [#298](https://github.com/CE-Programming/toolchain/issues/298)
  - Bug fixes for convimg and convbin programs
  - Add more missing C++ headers and add typeinfo support (thanks [jacobly](https://github.com/jacobly0))
  - Added `clock`, `sleep`, `usleep`, `msleep`, `ticksleep`, and other clock related functions (thanks [Runer112](https://github.com/runer112))
  - Added `os_RunPrgm` function for running programs on the calculator
  - Added `boot_TurnOn` function which turns on the hardware
  - Implementation and improvements to C++ for `static_assert` and `quick_exit` (thanks [jacobly](https://github.com/jacobly0))
  - Updates to fasmg linker files; fasmg now uses 64 bit release on Linux
  - Pressing [on] doesn't throw an error on exit anymore (thanks [commandblockguy](https://github.com/commandblockguy))
  - Fix bug when compiling icon source file
  - Remove Windows installer program and use batch file instead (thanks [DrDnar](https://github.com/drdnar))
  - General core makefile improvements
  - Makefile now handles recursive search better and extra source files
  - Linux releases have binaries marked as executable
  - Documentation is now versioned based on release
  - Linker bug when using debug mode resolved
  - Test toolchain with compression enabled and disabled, as well as remove convimg build artifacts
  - Added `cedev-config` program to handle miscellaneous toolchain things
  - Documentation improvements (thanks [Michael0x18](https://github.com/Michael0x18))
  - Added general coding guidelines and working with Git documentation

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v9.1...v9.2)

# [v9.1](https://github.com/CE-Programming/toolchain/releases/tag/v9.1) (2021-01-16)

  - Update fasmg (fix linker bug that could unnecessarily require a library)
  - Update ez80-clang (fix compiler bug where taking the address of stack variables in simple functions was broken)
  - Improve CI

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v9.0...v9.1)

# [v9.0](https://github.com/CE-Programming/toolchain/releases/tag/v9.0) (2020-12-26)

**Major release!** 🥂 <img src="https://llvm.org/img/DragonSmall.png" title="llvm" align="right">

Starting with this version, the toolchain is now based on LLVM, an open-source retargetable compiler infrastructure. The [backend](https://github.com/jacobly0/llvm-project) was created by [Jacobly](https://github.com/jacobly0) and the compiler (named clang, which you may see as `ez80-clang` in the toolchain) is now able produce eZ80 assembly from C/C++ source files. This is a major milestone as it allows the CE toolchain to move away from using the legacy Zilog ZDS compiler, which is closed-source, proprietary, only worked on Windows, and contained numerous bugs. Thanks to LLVM, later standards of the C and C++ specifications are supported (you're not stuck with C89 anymore!), code optimization actually works, and the compiler is able to run natively across multiple platforms.

  - Lots of cleanup and improvements to the standard includes and headers in general, made possible by the compiler change mentioned above.
  - Various changes and improvements to the fasmg linker (written by [Jacobly](https://github.com/jacobly0) as well)
  - Some "hacks" like `_OS` and `_asm` aren't needed anymore, they are now gone.
  - Debug info is now produced in the Dwarf format (and source-level debugging support within CEmu is getting closer to being ready!)
  - The [convimg](https://github.com/mateoconlechuga/convimg) project has been updated to support a new YAML format that is easier for beginners and tooling. The previous toolchain release (v8.8) also used a YAML format, however some slight modifications were made in order to make it standard-compliant. Example `convimg.yaml` conversion files can be found in the examples.
  - New **fileioc** function: `ti_SetGCBehavior` to set routines to run before and after a garbage collect would be triggered.
  - New **keypadc** defines: many keypad key defines corresponding to the TI-83 Premium CE keypad were added for easier coding
  - New **usb.h** function: `usb_BatteryCharging` to check if the battery is currently charging.
  - New **time.h** headers and functions: standard features. See [commit](https://github.com/CE-Programming/toolchain/commit/87e62890df312624a792156dadae1f82100652d2) for details.
  - New **tice.h** defines and macros: easier ways to control timers. See [commit](https://github.com/CE-Programming/toolchain/commit/d0d2f6c65fadadf12229e3125ea10995af498e8f) for details.
  - Revamped v/s/printf functions, now available if needed thanks to a light third-party library, see [docs](https://ce-programming.github.io/toolchain/static/printf.html).
  - New C++ header-only "library" for easily manipulating "TI real" numbers (see [this PR](https://github.com/CE-Programming/toolchain/pull/258)), making some math operations easier. See examples.
  - `abort()` doesn't generate code that would make CEmu open its debugger anymore - you can use the specific debug functions for that now.
  - Various optimizations in library functions
  - Various makefile improvements and cleanup (bugfixes, portability...)
  - Improved autotests for the examples
  - fasmg got a speed boost thanks to CALM instructions.
  - Documentation improved and revamped. Available on [online here](http://ce-programming.github.io/toolchain/), which replaces the repo's wiki
  - The build/CI infrastructure was migrated from Travis to Github Actions.

These massive internal changes *do* mean that some programs might not compile right away anymore, but don't worry, it shouldn't be too difficult to fix your code. Check out the [v9.0 release note](https://github.com/CE-Programming/toolchain/tree/v9.0) for migration tips.

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v8.8...v9.0)


# [v8.8](https://github.com/CE-Programming/toolchain/releases/tag/v8.8) (2020-01-19)

 - Documentation fixes and headers cleanup
 - Fix `gfx_TilePtr` and `gfx_TilePtrMapped`
 - Expose more OS functions (see `tice.h`)
 - Add LCD cursor defines
 - MMIO defines are all volatile
 - Submodules update
 - "development library" generation
 - Examples folders hierarchy improved
 - Prepare makefile for future changes
 - Fix warnings

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v8.7...v8.8)

# [v8.7](https://github.com/CE-Programming/toolchain/releases/tag/v8.7) (2019-08-25)

 - Documentation fixes
 - Fix `gfx_Begin` signature
 - Fix `gfx_RotateSpriteC`
 - Fix `ti_Str0` value and add missing `ti_Str9`
 - Fix `gfx_SetCharData` (#221)
 - Improve build
 - Add `ti_ArchiveHasRoom`

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v8.6...v8.7)

# [v8.6](https://github.com/CE-Programming/toolchain/releases/tag/v8.6) (2019-06-30)

 - New libray: FontLib by DrDnar
 - Add `kb_IsDown` keypadc macro
 - Add `gfx_CopyRectangle`
 - Add `os_TestFlagBitsFast`
 - Fix `gfx_GetClipRegion`
 - Fix `getstringinput`
 - Fix `strncasecmp`
 - Fix `ti_SetArchiveStatus` ignoring archived argument
 - Improve comments and `printTextSmall` function
 - Improve `gfx_Wait`
 - Improve CI
 - Improve build files in general, more parallel and portability support
 - More documentation

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v8.5...v8.6)

# [v8.5](https://github.com/CE-Programming/toolchain/releases/tag/v8.5) (2018-10-31)

 - LibLoad and linker improvements
 - AppVeyor CI support
 - Fix `ti_RclVar`
 - Improve and fix tests in general
 - Optimize a few graphx routines (SetPalette, SetClipRegion, RLETSprite)
 - Add `os_NewLine`
 - Fix MMIO defines (size/volatility) in tice.h
 - Add 32-bit "atomic" load functions and stopwatch example

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v8.4...v8.5)

# [v8.4](https://github.com/CE-Programming/toolchain/releases/tag/v8.4) (2018-08-23)

 - Fix fileioc bug not bypassing archived header in ti_SetArchiveStatus
 - LibLoad optimizations
 - Documentation fixes and improvements
 - GraphX optimizations
 - Replace NSIS by Inno for Windows installer
 - Add a better GraphX template
 - Improve some build-related stuff

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v8.3...v8.4)

# [v8.3](https://github.com/CE-Programming/toolchain/releases/tag/v8.3) (2018-07-25)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v8.2...v8.3)

### Toolchain
  - Misc. build improvements and fixes ([MateoConLechuga](https://github.com/MateoConLechuga) + [Runer112](https://github.com/Runer112) + [Adriweb](https://github.com/Adriweb))
  - Travis config file cleanup ([Adriweb](https://github.com/Adriweb))
  - New macros and features related to fasmg ([Jacobly](https://github.com/jacobly0))
  - Added dbg_ClearConsole ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Compression-related APIs fixes and updates ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Misc. code cleanup ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Some documentation updates ([TIAnonyme0](https://github.com/TIAnonyme0) + [Runer112](https://github.com/Runer112))
  - Submodules updates for [ConvPNG](https://github.com/mateoconlechuga/convpng) and [fasmg](https://github.com/jacobly0/fasmg-ez80) ([MateoConLechuga](https://github.com/MateoConLechuga) + [Jacobly](https://github.com/jacobly0))

### Libraries

#### GRAPHX
  - Minimized waiting by gfx_SwapDraw, added gfx_Wait ([Runer112](https://github.com/Runer112))
  - Improved behavior of length argument to gfx_PrintInt and gfx_PrintUInt ([Runer112](https://github.com/Runer112))
  - Many small optimizations ([Runer112](https://github.com/Runer112) + [Jacobly](https://github.com/jacobly0))

#### FILEIOC
  - Added ti_DetectAny, ti_GetName, ti_Rename, and ti_RenameVar ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Added ti_GetVATPtr ([PeterTillema](https://github.com/PeterTillema))
  - Fixed ti_GetC for empty variables ([PeterTillema](https://github.com/PeterTillema))
  - Fixed variable creation erroneously opening closed slots ([Runer112](https://github.com/Runer112))
  - Fixed ti_DetectAny type access ([PeterTillema](https://github.com/PeterTillema))

# [v8.2](https://github.com/CE-Programming/toolchain/releases/tag/v8.2) (2018-03-24)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v8.1...v8.2)

### Toolchain
  - Add full screen image example ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Improved os_GetStringInput ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Fixed a Windows build issue for src/std/linked ([Runer112](https://github.com/Runer112))
  - Blitting demo instead of buffering demo ([Runer112](https://github.com/Runer112))
  - Use latest-stable CEmu for Travis auto-tests ([Adriweb](https://github.com/Adriweb))

### Libraries
  - Optimized a couple GraphX routines ([grosged](https://github.com/grosged) + [Runer112](https://github.com/Runer112))

# [v8.1](https://github.com/CE-Programming/toolchain/releases/tag/v8.2) (2018-02-19)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v8.0...v8.1)

### Toolchain
  - Improved several autotests ([Runer112](https://github.com/Runer112))
  - Build fix for Windows regarding icon handling ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Misc. build and Travis fixes/improvements ([Adriweb](https://github.com/Adriweb))
  - Submodules updates for [ConvPNG](https://github.com/mateoconlechuga/convpng/compare/dcf9131...d74720e) and [fasmg](https://github.com/jacobly0/fasmg-ez80/compare/acf0c68...fc5a4fc) ([MateoConLechuga](https://github.com/MateoConLechuga) + [Jacobly](https://github.com/jacobly0))

### Libraries
  - Optimized multiple routines from GraphX and FileIO ([grosged](https://github.com/grosged) + [Runer112](https://github.com/Runer112))

# [v8.0](https://github.com/CE-Programming/toolchain/releases/tag/v8.0) (2018-01-30)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v7.4.2...v8.0)

### Toolchain
  - Replace ZDS assembler with fasmg-ez80 ([Jacobly](https://github.com/jacobly0))
  - Replace ZDS linker/librarian with fasmg-ez80 ([Jacobly](https://github.com/jacobly0)))
  - Integrate fasmg-ez80 into toolchain ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Library translation to fasmg-ez80 format ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Add more tests and header file cleanup ([Adriweb](https://github.com/Adriweb))

### Libraries
  - Optimize gfx_FillScreen() and gfx_ZeroScreen() ([Runer112](https://github.com/Runer112))
  - Fix gfx_FillTriangle() and gfx_FillTriangle_NoClip() ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Add gfx_SetCharData() and os_GetStringInput() ([MateoConLechuga](https://github.com/MateoConLechuga))

# [v7.4.2](https://github.com/CE-Programming/toolchain/releases/tag/v7.4.2) (2017-08-13)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v7.4.1...v7.4.2)

### Toolchain
  - Misc. code fixes ([Adriweb](https://github.com/Adriweb))
  - Fix environment variable setting and paths on the windows installer ([MateoConLechuga](https://github.com/MateoConLechuga))

# [v7.4.1](https://github.com/CE-Programming/toolchain/releases/tag/v7.4.1) (2017-08-10)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v7.4...v7.4.1)

### Toolchain
  - Better Travis settings for docs deployment ([Adriweb](https://github.com/Adriweb))
  - Tested-functions-list tool ([Adriweb](https://github.com/Adriweb))
  - Deprecate support for mode 2 interrupts and related things ([MateoConLechuga](https://github.com/MateoConLechuga))

### Libraries
  - Minor header fixes (missing includes) in GraphX and FileIOC ([Adriweb](https://github.com/Adriweb))
  - Code optimizations in GraphX ([PeterTillema](https://github.com/PeterTillema))

# [v7.4](https://github.com/CE-Programming/toolchain/releases/tag/v7.4) (2017-07-25)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v7.3...v7.4)

### Toolchain
  - Various Makefile fixes (windows spaces, subdirectories...) ([MateoConLechuga](https://github.com/MateoConLechuga))
  - More and better documentation ([MateoConLechuga](https://github.com/MateoConLechuga)+[Runer112](https://github.com/Runer112)+[Jacobly](https://github.com/jacobly0))
  - ConvPNG updates to use W/H defines ([MateoConLechuga](https://github.com/MateoConLechuga))

### Libraries

#####  GRAPHX
  - Fixed gfx_RLETSprite where width != height, and in a right clip case - ([`5c84e9b`](https://github.com/CE-Programming/toolchain/commit/5c84e9b) - [Runer112](https://github.com/Runer112))
  - Add gfx_RotateScaleSprite and related functions + docs ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Improve line routine implementation ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Fix the new gfx_Begin and some bad macro usages ([Jacobly](https://github.com/jacobly0))

# [v7.3](https://github.com/CE-Programming/toolchain/releases/tag/v7.3) (2017-07-04)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v7.2...v7.3)

### Toolchain
  - Automated testing through Travis ([Adriweb](https://github.com/Adriweb))
  - Fixed C++-compatibility-related things ([Adriweb](https://github.com/Adriweb))
  - Fixed/improved autotester files ([Adriweb](https://github.com/Adriweb)+[MateoConLechuga](https://github.com/MateoConLechuga))
  - Improved Makefile ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Misc. fixes and optimizations ([MateoConLechuga](https://github.com/MateoConLechuga)+[Runer112](https://github.com/Runer112)+[Jacobly](https://github.com/jacobly0))
  - Fixed some docs and examples ([MateoConLechuga](https://github.com/MateoConLechuga))
  - More demos ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Fixed bss and cstarted-related things ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Added millisecond delay function ([`ae19350`](https://github.com/CE-Programming/toolchain/commit/ae19350) - [Runer112](https://github.com/Runer112))
  - Improved (pseudo)random number generation ([`b6c1929`](https://github.com/CE-Programming/toolchain/commit/b6c1929) - [Runer112](https://github.com/Runer112))
  - Overall misc. cleanup and documentation ([Runer112](https://github.com/Runer112))

### Libraries

#####  GRAPHX
  - Clipped sprites fixes ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Code optimizations ([MateoConLechuga](https://github.com/MateoConLechuga)+[Runer112](https://github.com/Runer112)+[Jacobly](https://github.com/jacobly0))
  - ConvPNG-related updates ([MateoConLechuga](https://github.com/MateoConLechuga))
  - ConvTile-related updates ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Renaming: gfx_sprite_t from gfx_image_t ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Fixed green LSB in default palette colors ([`be9fea4`](https://github.com/CE-Programming/toolchain/commit/be9fea4) - [Runer112](https://github.com/Runer112))
  - Added fast (RLE) transparent sprite type, gfx_rletsprite_t, and functions: gfx_AllocRLETSprite, gfx_MallocRLETSprite, gfx_UninitedRLETSprite, gfx_RLETSprite, gfx_RLETSprite_NoClip, gfx_ConvertFromRLETSprite, gfx_ConvertToRLETSprite, gfx_ConvertToNewRLETSprite, gfx_ConvertMallocRLETSprite ([`e26bf07`](https://github.com/CE-Programming/toolchain/commit/e26bf07) - [Runer112](https://github.com/Runer112))
  - Fixed drawing unclipped sprites with odd width ([`5a4cc95`](https://github.com/CE-Programming/toolchain/commit/5a4cc95) - [Runer112](https://github.com/Runer112))


# [v7.2](https://github.com/CE-Programming/toolchain/releases/tag/v7.2) (2017-05-06)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v7.1...v7.2)

### Toolchain
  - Implicit `prgm_CleanUp` by default - ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Examples cleanup - ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Fix some example screenshots - ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Routines optimizations - ([MateoConLechuga](https://github.com/MateoConLechuga)+[Runer112](https://github.com/Runer112))

### Libraries

#####  FILEIOC
  - Misc. fixes - ([MateoConLechuga](https://github.com/MateoConLechuga)+[Runer112](https://github.com/Runer112)+[PeterTillema](https://github.com/PeterTillema))


# [v7.1](https://github.com/CE-Programming/toolchain/releases/tag/v7.1) (2017-04-30)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v7.0...v7.1)

### Toolchain
  - Compatibility headers and better include paths - ([Adriweb](https://github.com/Adriweb))
  - Travis CI integration - ([Adriweb](https://github.com/Adriweb))
  - Example screenshots - ([Adriweb](https://github.com/Adriweb))
  - Improved documentation - ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Misc. fixes - ([MateoConLechuga](https://github.com/MateoConLechuga))
  - Fix Windows install - ([MateoConLechuga](https://github.com/MateoConLechuga))

### Libraries

#####  GRAPHX
  - Bug. fixes - ([MateoConLechuga](https://github.com/MateoConLechuga)+[PeterTillema](https://github.com/PeterTillema))
  - Optimizations - ([MateoConLechuga](https://github.com/MateoConLechuga))


# [v7.0](https://github.com/CE-Programming/toolchain/releases/tag/v7.0) (2017-04-07)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.95...v7.0)

### Toolchain
  - Rework entire toolchain setup and hierarchy ([`559dd1c`](https://github.com/CE-Programming/toolchain/commit/559dd1c) - [MateoConLechuga](https://github.com/MateoConLechuga))
  - Doxygen header files ([`4402637`](https://github.com/CE-Programming/toolchain/commit/4402637) - [MateoConLechuga](https://github.com/MateoConLechuga))

### Libraries

#####  GRAPHX
  - Added gfx_FloodFill ([`60006ac`](https://github.com/CE-Programming/toolchain/commit/60006ac) - [MateoConLechuga](https://github.com/MateoConLechuga))
  - Added gfx_ScaleSprite ([`7618598`](https://github.com/CE-Programming/toolchain/commit/7618598) - [MateoConLechuga](https://github.com/MateoConLechuga))
  - Added gfx_SetFontHeight ([`4402637`](https://github.com/CE-Programming/toolchain/commit/4402637) - [MateoConLechuga](https://github.com/MateoConLechuga))
  - Optimized ClipDraw helper function ([`82e5d5a`](https://github.com/CE-Programming/toolchain/commit/82e5d5a) - [MateoConLechuga](https://github.com/MateoConLechuga))
  - Optimized gfx_AllocSprite ([`2c12310`](https://github.com/CE-Programming/toolchain/commit/2c12310) - [Runer112](https://github.com/Runer112))

# [v6.999](https://github.com/CE-Programming/toolchain/releases/tag/v6.999) (2017-02-17)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.95...v6.999)

### Toolchain
  - Add scripts to build/clean libraries and examples easily ([`61d915f`](https://github.com/CE-Programming/toolchain/commit/61d915f) - [MateoConLechuga](https://github.com/MateoConLechuga))
  - Move spasm to /bin rather than /lib/src/include ([`61d915f`](https://github.com/CE-Programming/toolchain/commit/61d915f) - [MateoConLechuga](https://github.com/MateoConLechuga))
  - Fix graphx demo 11 readme ([`3017951`](https://github.com/CE-Programming/toolchain/commit/3017951) - [Runer112](https://github.com/Runer112))
  - Add Changelog file ([`0595378`](https://github.com/CE-Programming/toolchain/commit/0595378)+[`544e75f`](https://github.com/CE-Programming/toolchain/commit/544e75f) - [MateoConLechuga](https://github.com/MateoConLechuga)+[Adriweb](https://github.com/Adriweb))
  - Restrict LF EOL conversions to text files ([`c19b360`](https://github.com/CE-Programming/toolchain/commit/c19b360) - [Adriweb](https://github.com/Adriweb))

# [v6.95](https://github.com/CE-Programming/toolchain/releases/tag/v6.95) (2017-02-10)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.91...v6.95)

### Toolchain
  - Improve build system and misc. cleanup ([`63ff603`](https://github.com/CE-Programming/toolchain/commit/63ff603)+[`4b3f137`](https://github.com/CE-Programming/toolchain/commit/4b3f137) - [MateoConLechuga](https://github.com/MateoConLechuga)+[Runer112](https://github.com/Runer112))
  - Modify `cstartup.asm` to disable usb timers and reset them on exit ([`63ff603`](https://github.com/CE-Programming/toolchain/commit/63ff603)+[`03809e5`](https://github.com/CE-Programming/toolchain/commit/03809e5) - [MateoConLechuga](https://github.com/MateoConLechuga))
  - Characters `0x01`-`0x1F` are considered printable rather than control ([`de96c7a`](https://github.com/CE-Programming/toolchain/commit/de96c7a) - [Runer112](https://github.com/Runer112))
  - CR EOL purge ([`15a573e`](https://github.com/CE-Programming/toolchain/commit/15a573e) - [Runer112](https://github.com/Runer112))
  - Minor documentation fixes

### Libraries

#####  GRAPHX
  - Optimize gfx\_Darken (about 25% faster) and gfx\_Lighten (about 19% faster) ([`9e7835a`](https://github.com/CE-Programming/toolchain/commit/9e7835a) - [Runer112](https://github.com/Runer112))
  - Optimize _SetColor and _SetTransparentColor ([`fc43abb`](https://github.com/CE-Programming/toolchain/commit/fc43abb) - [Runer112](https://github.com/Runer112))
  - Optimize _SetTextXY (#47) ([`6643e90`](https://github.com/CE-Programming/toolchain/commit/6643e90) - [Runer112](https://github.com/Runer112))
  - Add support for width/height of tiles not powers of 2 ([`93930fb`](https://github.com/CE-Programming/toolchain/commit/93930fb)+[`78be69c`](https://github.com/CE-Programming/toolchain/commit/78be69c) - [MateoConLechuga](https://github.com/MateoConLechuga))
  - Fix bug with tile index 255


# [v6.91](https://github.com/CE-Programming/toolchain/releases/tag/v6.91) (2017-01-20)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.9...v6.91)

# [v6.9](https://github.com/CE-Programming/toolchain/releases/tag/v6.9) (2016-12-28)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.8...v6.9)

# [v6.8](https://github.com/CE-Programming/toolchain/releases/tag/v6.8) (2016-12-28)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.7...v6.8)

# [v6.7](https://github.com/CE-Programming/toolchain/releases/tag/v6.7) (2016-12-21)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.6...v6.7)

# [v6.6](https://github.com/CE-Programming/toolchain/releases/tag/v6.6) (2016-12-18)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.5...v6.6)

# [v6.5](https://github.com/CE-Programming/toolchain/releases/tag/v6.5) (2016-12-12)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.3...v6.5)

**Closed issues:**

- obj dir something something [\#43](https://github.com/CE-Programming/toolchain/issues/43)

# [v6.3](https://github.com/CE-Programming/toolchain/releases/tag/v6.3) (2016-11-24)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.2...v6.3)

**Fixed bugs:**

- demo2 doesn't compile [\#42](https://github.com/CE-Programming/toolchain/issues/42)

# [v6.2](https://github.com/CE-Programming/toolchain/releases/tag/v6.2) (2016-11-23)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.1...v6.2)

# [v6.1](https://github.com/CE-Programming/toolchain/releases/tag/v6.1) (2016-11-19)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.0...v6.1)

**Implemented enhancements:**

- More C standard functions [\#38](https://github.com/CE-Programming/toolchain/issues/38)
- Clipped text printing routines [\#26](https://github.com/CE-Programming/toolchain/issues/26)

**Merged pull requests:**

- optimised \_PrintUInt & \_FillScreen [\#40](https://github.com/CE-Programming/toolchain/pull/40) (Grosged)
- faster ScaledSprite\_NoClip & Sprite\_NoClip [\#39](https://github.com/CE-Programming/toolchain/pull/39) (Grosged)
- optimisation of imuls|imulu \(8,5% faster\) [\#37](https://github.com/CE-Programming/toolchain/pull/37) (Grosged)
- suggest a faster FillCircle\_NoClip routine [\#34](https://github.com/CE-Programming/toolchain/pull/34) (Grosged)

# [v6.0](https://github.com/CE-Programming/toolchain/releases/tag/v6.0) (2016-10-26)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v5.9...v6.0)

**Closed issues:**

- Cannot make examples' makefile [\#29](https://github.com/CE-Programming/toolchain/issues/29)

**Merged pull requests:**

- \_VertLine\_NoClip improvements [\#30](https://github.com/CE-Programming/toolchain/pull/30) (Grosged)
- Optimized \_TransparentPlot\_ASM for speed\* [\#28](https://github.com/CE-Programming/toolchain/pull/28) ([Runer112](https://github.com/Runer112))

# [v5.9](https://github.com/CE-Programming/toolchain/releases/tag/v5.9) (2016-10-15)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v5.8...v5.9)

# v5.8 (2016-10-04)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v5.7...v5.8)

# [v5.7](https://github.com/CE-Programming/toolchain/releases/tag/v5.7) (2016-09-21)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v5.6...v5.7)

# [v5.6](https://github.com/CE-Programming/toolchain/releases/tag/v5.6) (2016-09-20)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v5.5...v5.6)

# [v5.5](https://github.com/CE-Programming/toolchain/releases/tag/v5.5) (2016-09-10)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v5.2...v5.5)

**Fixed bugs:**

- gfx\_Shift\<\> performs improperly [\#22](https://github.com/CE-Programming/toolchain/issues/22)

**Closed issues:**

- Tilemap only renders if gfx\_tilemap\_t is local [\#25](https://github.com/CE-Programming/toolchain/issues/25)
- Clipping is broken [\#24](https://github.com/CE-Programming/toolchain/issues/24)
- SEEK\_\* are defined and implemented incorrectly [\#23](https://github.com/CE-Programming/toolchain/issues/23)

# [v5.2](https://github.com/CE-Programming/toolchain/releases/tag/v5.2) (2016-08-25)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v5.1...v5.2)

# [v5.1](https://github.com/CE-Programming/toolchain/releases/tag/v5.1) (2016-08-23)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v5.0...v5.1)

# [v5.0](https://github.com/CE-Programming/toolchain/releases/tag/v5.0) (2016-08-23)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v4.6...v5.0)

# [v4.6](https://github.com/CE-Programming/toolchain/releases/tag/v4.6) (2016-05-26)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v4.5...v4.6)

# [v4.5](https://github.com/CE-Programming/toolchain/releases/tag/v4.5) (2016-05-24)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v4.0...v4.5)

# [v4.0](https://github.com/CE-Programming/toolchain/releases/tag/v4.0) (2016-05-19)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v4.4...v4.0)

# [v4.4](https://github.com/CE-Programming/toolchain/releases/tag/v4.4) (2016-05-19)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v4.2...v4.4)

# [v4.2](https://github.com/CE-Programming/toolchain/releases/tag/v4.2) (2016-05-19)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v3.4...v4.2)

# [v3.4](https://github.com/CE-Programming/toolchain/releases/tag/v3.4) (2016-04-04)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v3.3...v3.4)

# [v3.3](https://github.com/CE-Programming/toolchain/releases/tag/v3.3) (2016-04-04)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v3.2...v3.3)

# [v3.2](https://github.com/CE-Programming/toolchain/releases/tag/v3.2) (2016-04-03)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v3.1...v3.2)

# [v3.1](https://github.com/CE-Programming/toolchain/releases/tag/v3.1) (2016-03-21)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v3.0...v3.1)

# [v3.0](https://github.com/CE-Programming/toolchain/releases/tag/v3.0) (2016-03-21)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v2.2...v3.0)

# [v2.2](https://github.com/CE-Programming/toolchain/releases/tag/v2.2) (2016-03-20)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v2.1...v2.2)

# [v2.1](https://github.com/CE-Programming/toolchain/releases/tag/v2.1) (2016-03-18)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v2.0...v2.1)

**Implemented enhancements:**

- Makefile bugs and improvements... [\#20](https://github.com/CE-Programming/toolchain/issues/20)

**Fixed bugs:**

- Makefile bugs and improvements... [\#20](https://github.com/CE-Programming/toolchain/issues/20)
- Including ti84pce.h in multiple files causes linktime warnings. [\#16](https://github.com/CE-Programming/toolchain/issues/16)

**Closed issues:**

- tice.h does not include string.h [\#21](https://github.com/CE-Programming/toolchain/issues/21)

# [v2.0](https://github.com/CE-Programming/toolchain/releases/tag/v2.0) (2016-03-06)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v1.7...v2.0)

**Implemented enhancements:**

- Improved demo0 "purity", moved template-like stuff to a template dir [\#19](https://github.com/CE-Programming/toolchain/pull/19) ([KermMartian](https://github.com/KermMartian))

**Fixed bugs:**

- executing makefile twice in succession outputs 8xp even if linking fails [\#7](https://github.com/CE-Programming/toolchain/issues/7)
- Makefile incorrectly escaped with wine 1.9.2 under Ubuntu 14.04 [\#6](https://github.com/CE-Programming/toolchain/issues/6)

# [v1.7](https://github.com/CE-Programming/toolchain/releases/tag/v1.7) (2016-02-11)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v1.6...v1.7)

**Implemented enhancements:**

- More portable deletion of build products [\#18](https://github.com/CE-Programming/toolchain/pull/18) ([elfprince13](https://github.com/elfprince13))

**Fixed bugs:**

- ti84pce.h relies on headers which it does not include [\#17](https://github.com/CE-Programming/toolchain/issues/17)
- incorrect typedef of ptrdiff\_t [\#15](https://github.com/CE-Programming/toolchain/issues/15)
- \<assert.h\> depends on \<debug.h\>, does not include it [\#14](https://github.com/CE-Programming/toolchain/issues/14)

**Closed issues:**

- \<debug.h\> should respect the NDEBUG flag used by \<assert.h\> [\#12](https://github.com/CE-Programming/toolchain/issues/12)
- abort\(\) should not be redefined in \<debug.h\> [\#11](https://github.com/CE-Programming/toolchain/issues/11)

# [v1.6](https://github.com/CE-Programming/toolchain/releases/tag/v1.6) (2016-02-06)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v1.5...v1.6)

**Closed issues:**

- dbg\_printf should not take a buffer argument. [\#13](https://github.com/CE-Programming/toolchain/issues/13)

# [v1.5](https://github.com/CE-Programming/toolchain/releases/tag/v1.5) (2016-02-06)
**Implemented enhancements:**

- Increase subdirectory portability [\#9](https://github.com/CE-Programming/toolchain/pull/9) ([elfprince13](https://github.com/elfprince13))
- These environment variables are unused [\#8](https://github.com/CE-Programming/toolchain/pull/8) ([elfprince13](https://github.com/elfprince13))

**Closed issues:**

- No bin folder present in CEDev [\#1](https://github.com/CE-Programming/toolchain/issues/1)
