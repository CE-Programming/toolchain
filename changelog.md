# Change Log

## [Unreleased](https://github.com/CE-Programming/toolchain/tree/HEAD)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v7.0...HEAD)

# [v7.0](https://github.com/CE-Programming/toolchain/releases/tag/v7.0) (2017-02-17)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.95...v7.0)

### Toolchain
  - Rework entire toolchain setup and hierarchy ([`559dd1c`](https://github.com/CE-Programming/toolchain/commit/559dd1c) - [MattWaltz](https://github.com/MattWaltz))
  - Doxygen header files ([`4402637`](https://github.com/CE-Programming/toolchain/commit/4402637) - [MattWaltz](https://github.com/MattWaltz))

### Libraries

#####  GRAPHX
  - Added gfx_FloodFill ([`60006ac`](https://github.com/CE-Programming/toolchain/commit/60006ac) - [MattWaltz](https://github.com/MattWaltz))
  - Added gfx_ScaleSprite ([`7618598`](https://github.com/CE-Programming/toolchain/commit/7618598) - [MattWaltz](https://github.com/MattWaltz))
  - Added gfx_SetFontHeight ([`4402637`](https://github.com/CE-Programming/toolchain/commit/4402637) - [MattWaltz](https://github.com/MattWaltz))
  - Optimized ClipDraw helper function ([`82e5d5a`](https://github.com/CE-Programming/toolchain/commit/82e5d5a) - [MattWaltz](https://github.com/MattWaltz))
  - Optimized gfx_AllocSprite ([`2c12310`](https://github.com/CE-Programming/toolchain/commit/2c12310) - [Runer112](https://github.com/Runer112))

# [v6.999](https://github.com/CE-Programming/toolchain/releases/tag/v6.999) (2017-02-17)

[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.95...v6.999)

### Toolchain
  - Add scripts to build/clean libraries and examples easily ([`61d915f`](https://github.com/CE-Programming/toolchain/commit/61d915f) - [MattWaltz](https://github.com/MattWaltz))
  - Move spasm to /bin rather than /lib/src/include ([`61d915f`](https://github.com/CE-Programming/toolchain/commit/61d915f) - [MattWaltz](https://github.com/MattWaltz))
  - Fix graphx demo 11 readme ([`3017951`](https://github.com/CE-Programming/toolchain/commit/3017951) - [Runer112](https://github.com/Runer112))
  - Add Changelog file ([`0595378`](https://github.com/CE-Programming/toolchain/commit/0595378)+[`544e75f`](https://github.com/CE-Programming/toolchain/commit/544e75f) - [MattWaltz](https://github.com/MattWaltz)+[Adriweb](https://github.com/Adriweb))
  - Restrict LF EOL conversions to text files ([`c19b360`](https://github.com/CE-Programming/toolchain/commit/c19b360) - [Adriweb](https://github.com/Adriweb))

# [v6.95](https://github.com/CE-Programming/toolchain/releases/tag/v6.95) (2017-02-10)
[Full commit list](https://github.com/CE-Programming/toolchain/compare/v6.91...v6.95)

### Toolchain
  - Improve build system and misc. cleanup ([`63ff603`](https://github.com/CE-Programming/toolchain/commit/63ff603)+[`4b3f137`](https://github.com/CE-Programming/toolchain/commit/4b3f137) - [MattWaltz](https://github.com/MattWaltz)+[Runer112](https://github.com/Runer112))
  - Modify `cstartup.asm` to disable usb timers and reset them on exit ([`63ff603`](https://github.com/CE-Programming/toolchain/commit/63ff603)+[`03809e5`](https://github.com/CE-Programming/toolchain/commit/03809e5) - [MattWaltz](https://github.com/MattWaltz))
  - Characters `0x01`-`0x1F` are considered printable rather than control ([`de96c7a`](https://github.com/CE-Programming/toolchain/commit/de96c7a) - [Runer112](https://github.com/Runer112))
  - CR EOL purge ([`15a573e`](https://github.com/CE-Programming/toolchain/commit/15a573e) - [Runer112](https://github.com/Runer112))
  - Minor documentation fixes

### Libraries

#####  GRAPHX
  - Optimize gfx\_Darken (about 25% faster) and gfx\_Lighten (about 19% faster) ([`9e7835a`](https://github.com/CE-Programming/toolchain/commit/9e7835a) - [Runer112](https://github.com/Runer112))
  - Optimize _SetColor and _SetTransparentColor ([`fc43abb`](https://github.com/CE-Programming/toolchain/commit/fc43abb) - [Runer112](https://github.com/Runer112))
  - Optimize _SetTextXY (#47) ([`6643e90`](https://github.com/CE-Programming/toolchain/commit/6643e90) - [Runer112](https://github.com/Runer112))
  - Add support for width/height of tiles not powers of 2 ([`93930fb`](https://github.com/CE-Programming/toolchain/commit/93930fb)+[`78be69c`](https://github.com/CE-Programming/toolchain/commit/78be69c) - [MattWaltz](https://github.com/MattWaltz))
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

