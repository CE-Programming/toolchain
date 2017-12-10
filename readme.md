# CE C Programming Toolchain/SDK -  [![Build Status](https://travis-ci.org/CE-Programming/toolchain.svg)](https://travis-ci.org/CE-Programming/toolchain)

The CE C Software Development Kit incorporates a wide variety of tools and documentation in order to build programs in C natively for the TI-84 Plus CE / TI-83 Premium CE calculators series.

## Getting Started

It is recommended that you grab the latest release from [here](https://github.com/CE-Programming/toolchain/releases/latest) if you are looking to get started. Feel free to also bookmark the [wiki pages](https://github.com/CE-Programming/toolchain/wiki), as they will become quite helpful.

Included you will find examples using the ['Standard' CE C Libraries](https://github.com/CE-Programming/libraries/releases/latest). These provide efficient and easy support for graphics, file I/O, keypad input, etc. Be sure to grab them if you plan to use them. The [header documentation](https://ce-programming.github.io/toolchain/files.html) will let you know about the available functions.

## Help

You can join us on the EFNet IRC server, on the `#ez80-dev` channel, if you have any questions ([webchat link](http://chat.efnet.org:9090/?nick=sdk-user&channels=%23ez80-dev&Login=Login)).

## Building on linux and macOS

These steps are only if you wish to help with development of the toolchain. 

On Linux and macOS, [wine](https://www.winehq.org) is required for building.

Clone the repo: (Note the `--recursive` option)

```
git clone --recursive https://github.com/CE-Programming/toolchain.git
```

Then use:

```
cd toolchain
make
make install
```

By default, `make install` will install into the home (~/CEdev) directory.

This is configurable with `make install PREFIX={DIFFERENT_LOCATION}`

If you wish to view a list of available makefile rules, type: `make help`

To build a release, use: `make dist`

## Building on Windows

If you are using Windows, [MinGW](http://www.mingw.org) is required for building.
You will just need `mingw32-base` and `mingw32-gcc-g++`

Clone the repo: (Note the `--recursive` option)

```
git clone --recursive https://github.com/CE-Programming/toolchain.git
```

Then use:

```
cd toolchain
mingw32-make
mingw32-make install
```

By default, `mingw32-make install` will install into the root drive (C:\\CEdev) directory.

This is configurable with `mingw32-make install PREFIX={DIFFERENT_LOCATION}`

If you wish to view a list of available makefile rules, type: `mingw32-make help`

To build a release, use: `mingw32-make dist`

For releases, [NSIS](https://sourceforge.net/projects/nsis/) is required for Windows. Because of limitations of the current software; the special *Large strings* build is needed. You can find it [here](http://nsis.sourceforge.net/Special_Builds). Note also that you must configure your path variable to point to the NSIS installation directory.

