.. _fatdrvce_h:

fatdrvce.h
==========

.. code-block:: c

    #include <fatdrvce.h>

The fatdrvce library implements routines for writing and reading data to/from Mass Storage Devices (MSD).
Functions for interfacing with the FAT filesystem involve the majority of the library, however raw MSD sector access is provided.
Currently only drives that are formatted with FAT32 and use the Master Boot Record (MBR) partition format are supported.

In addition, only drives with 512 byte hardware sectors are supported; however most drives on the market utilize an "emulation" interface where drives with 4096 byte sectors are able to operate in legacy mode.

.. contents:: :local:
   :depth: 3

Supported Drives
----------------

The following drives have been verified to work (or not work) when used with a standard OTG adapter connector.
A test program found in the fatdrvce examples directory can be used to determine if the drive is suitable, and additionally provide read and write bandwidth metrics.
Note that the measurements provided here are for the raw MSD performance.
FAT access incures additional pentalties for filesystem access.
For best FAT performance, increase the cluster size as much as possible.

+--------------------------------------------+-------------+-----------+---------------+--------------+
| MSD USB Drive                              | USB Version | Validated | Write KiB/sec | Read KiB/sec |
+============================================+=============+===========+===============+==============+
| Kingston DataTraveler 32GB                 | 3.2 (Gen 1) | Pass      | 285.40        | 285.45       |
+--------------------------------------------+-------------+-----------+---------------+--------------+
| PNY Turbo 32GB                             | 3.0         | Pass      | 184.13        | 285.41       |
+--------------------------------------------+-------------+-----------+---------------+--------------+
| PNY Attache 16GB                           | 2.0         | Pass      | 100.65        | 280.43       |
+--------------------------------------------+-------------+-----------+---------------+--------------+
| PNY Elite-X Fit 64GB                       | 3.1         | Pass      | 144.51        | 285.44       |
+--------------------------------------------+-------------+-----------+---------------+--------------+
| onn. USB 2.0 Flash Drive 16 GB             | 2.0         | Pass      | 282.78        | 284.81       |
+--------------------------------------------+-------------+-----------+---------------+--------------+
| Drives found at college fairs              | 2.0         | Pass      | 145.39        | 285.40       |
+--------------------------------------------+-------------+-----------+---------------+--------------+
| Sandisk Ultra 32GB                         | 3.0         | Failed    | Unknown       | Unknown      |
+--------------------------------------------+-------------+-----------+---------------+--------------+
| Sandisk Cruzer Glide 32B                   | 2.0         | Failed    | Unknown       | Unknown      |
+--------------------------------------------+-------------+-----------+---------------+--------------+

Known Limitations
-----------------

The following lists the known limitations of the library.

- Drive must support 512 byte hardware sectors.
- Drive must be formatted as FAT32 (currently no support for FAT12, FAT16, or exFAT)
- Drive must use MBR partitioning (GPT should be backwards-compatible though)
- Long name support is not yet implemented.

API Documentation
-----------------

.. doxygenfile:: fatdrvce.h
   :project: CE C Toolchain
