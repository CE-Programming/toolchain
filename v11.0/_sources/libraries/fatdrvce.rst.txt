.. _fatdrvce_h:

fatdrvce.h
==========

.. code-block:: c

    #include <fatdrvce.h>

The **fatdrvce** library implements routines for working with a FAT32 based filesystem.
The read and write functions are implemented as user-provided callbacks, allowing for any underlying storage to be used.

.. contents:: :local:
   :depth: 3

Typical Usage
-------------

This library can be integrated with **msddrvce** in order to access physical devices such as a flash drive.

For best performance, the "cluster allocation size" should be set to the maximum allowed.
On Linux this can be accomplished with the following command:

.. code-block:: bash

    mkfs.vfat -s 128 -S 512 -v /dev/<drive partition, e.g. sda1>

Known Limitations
-----------------

- The filesystem must use 512 byte logical blocks.
- The filesystem must be formatted as FAT32 (no support for FAT12, FAT16, or exFAT)
- Long name support is not currently implemented.

API Documentation
-----------------

.. doxygenfile:: fatdrvce.h
   :project: CE C/C++ Toolchain
