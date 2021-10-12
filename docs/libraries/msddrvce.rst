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
The **msd_bandwidth** program found in the msddrvce examples directory can be used to determine if the device is suitable.
This program can also be used to test the bandwidth for reading/writing blocks on the device, given in the below table:

+--------------------------------------------+-------------+---------------+--------------+
| MSD Device                                 | USB Version | Write KiB/sec | Read KiB/sec |
+============================================+=============+===============+==============+
| Kingston DataTraveler 32GB                 | 3.2 (Gen 1) | 244.25        | 253.84       |
+--------------------------------------------+-------------+---------------+--------------+
| PNY Turbo 32GB                             | 3.0         | 163.12        | 254.56       |
+--------------------------------------------+-------------+---------------+--------------+
| PNY Attache 16GB                           | 2.0         | 85.16         | 244.70       |
+--------------------------------------------+-------------+---------------+--------------+
| PNY Elite-X Fit 64GB                       | 3.1         | 131.71        | 252.86       |
+--------------------------------------------+-------------+---------------+--------------+
| onn. USB 2.0 Flash Drive 16 GB             | 2.0         | 190.16        | 251.98       |
+--------------------------------------------+-------------+---------------+--------------+
| Sandisk Ultra 32GB                         | 3.0         | 222.57        | 253.29       |
+--------------------------------------------+-------------+---------------+--------------+
| Sandisk Cruzer Glide 32B                   | 2.0         | 232.94        | 252.94       |
+--------------------------------------------+-------------+---------------+--------------+
| Cheap unamed drive                         | 2.0         | 210.00        | 252.35       |
+--------------------------------------------+-------------+---------------+--------------+

API Documentation
-----------------

.. doxygenfile:: msddrvce.h
   :project: CE C Toolchain
