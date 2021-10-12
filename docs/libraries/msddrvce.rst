.. _msddrvce_h:

msddrvce.h
==========

.. code-block:: c

    #include <msddrvce.h>

The **msddrvce** library implements routines for writing and reading data to/from Mass Storage Devices (MSD).
Common MSDs include flash drives, SD cards, hard drives, and similar block-level storage devices.
Both synchronous and asynchronous block read/write functions are provided by this library.

.. note::

    Only drives utilizing 512 byte logical blocks and Master Boot Record (MBR) partition formats are currently supported.

.. contents:: :local:
   :depth: 3

Supported Devices
-----------------

The following drives have been verified to work (or not work) when used with a standard OTG adapter connector.
The **msd_bandwidth** program found in the msddrvce examples directory can be used to determine if the drive is suitable, and additionally provide read and write bandwidth metrics.

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

API Documentation
-----------------

.. doxygenfile:: msddrvce.h
   :project: CE C Toolchain
