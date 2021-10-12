.. _fatdrvce_h:

fatdrvce.h
==========

.. code-block:: c

    #include <fatdrvce.h>

The **fatdrvce** library implements routines for working with a FAT32 based filesystem.
The library can be integrated with **msddrvce** in order to access devices such as a flash drive.

.. contents:: :local:
   :depth: 3

Known Limitations
-----------------

The following lists the known limitations of the library.

- Filesystem must use 512 byte logical blocks.
- Filesystem must be formatted as FAT32 (currently no support for FAT12, FAT16, or exFAT)
- Long name support is not yet implemented.

API Documentation
-----------------

.. doxygenfile:: fatdrvce.h
   :project: CE C Toolchain
