.. _tice_h:

tice.h
======

.. code-block:: c

    #include <tice.h>

This header includes defines for OS memory and hardware ports, and prototypes for OS routines.

.. contents:: :local:
   :depth: 3

Hardware Cursor
---------------

The LCD controller supports generating a single cursor (basically a sprite).
The cursor can be enabled in any color-depth mode, has its own two-color
palette fully independent of GraphX's palette, supports transparency and
inverting effects (which can generate colors outside the GraphX palette), 
has full hardware clipping,
and can be either 32 by 32 or 64 by 64 pixels in size.
If the cursor's size is set to 32, you can load up to four cursor images into
the LCD controller at once, and switch between them instantly with a single,
fast function call.

Cursor image data are packed as two bits-per-pixel.
Unfortunately, the cursor's bitmap data are laid out as 32-bit little-endian
words, resulting in a strange byte order.
(It makes perfect sense for 32-bit CPUs.)

TODO: `convimg` support for cursor images

API Documentation
-----------------

.. doxygenfile:: tice.h
   :project: CE C/C++ Toolchain
