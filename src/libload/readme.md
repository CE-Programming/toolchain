## LibLoad
LibLoad is a loader that makes it possible to share libraries between different programs, and enforces library versioning.

## Installing
To install LibLoad on your calculator, simply send `LibLoad.8xv` to your calculator using TI Connect CE or TILP.

## Download
You can find the latest version of LibLoad here: https://github.com/CE-Programming/libraries/releases/latest

### Building LibLoad
With the eZ80 GNU binutils and a host C compiler on PATH, run this from the toolchain checkout:

    make -C src/libload

This builds `libload.8xv` and its `libload.lib` export descriptor. Run `make libs`
from the repository root to build the full library bundle.
