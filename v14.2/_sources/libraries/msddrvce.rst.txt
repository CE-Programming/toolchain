.. _msddrvce_h:

msddrvce.h
==========

.. code-block:: c

    #include <msddrvce.h>

The **msddrvce** library implements routines for writing and reading data to/from Mass Storage Devices (MSD).
Common MSDs include flash drives, SD cards, hard drives, and similar block-level storage devices.
Both synchronous and asynchronous block read/write functions are provided by this library.

.. contents:: :local:
   :depth: 3

Known Limitations
-----------------

- The maximum drive size is 2TiB.
- Only drives utilizing 512 byte logical blocks are supported.

Supported Devices
-----------------

The following table lists drives have been verified to work when used with a standard OTG adapter connector.
Other devices may also work but may not have been tested.
The **msd_bandwidth** program found in the msddrvce examples directory can be used to determine if the device is suitable, and additionally tests the bandwidth for reading/writing blocks on the device.
It is recommended to use SanDisk or Kingston drives for best results.

+--------------------------------------------+-----------+---------------+--------------+
| MSD Device                                 | VID:PID   | Write KiB/sec | Read KiB/sec |
+============================================+===========+===============+==============+
| Kingston DataTraveler 32GB                 | 0951:1666 | 261           | 273          |
+--------------------------------------------+-----------+---------------+--------------+
| SanDisk Ultra 32GB                         | 0781:5581 | 215           | 272          |
+--------------------------------------------+-----------+---------------+--------------+
| SanDisk Cruzer Glide 32GB                  | 0781:5575 | 248           | 273          |
+--------------------------------------------+-----------+---------------+--------------+
| SanDisk Cruzer Micro 16GB                  | 0781:5406 | 260           | 269          |
+--------------------------------------------+-----------+---------------+--------------+
| SanDisk EasyStore 64GB                     | 0781:5597 | 248           | 273          |
+--------------------------------------------+-----------+---------------+--------------+
| PNY Attache 16GB                           | 154b:00ee | 65            | 262          |
+--------------------------------------------+-----------+---------------+--------------+
| PNY Turbo 32GB                             | 154b:00ed | 172           | 272          |
+--------------------------------------------+-----------+---------------+--------------+
| KIOXIA TransMemory 32GB                    | 30de:6544 | 95            | 272          |
+--------------------------------------------+-----------+---------------+--------------+
| Micro Center 32GB                          | 13fe:6300 | 150           | 271          |
+--------------------------------------------+-----------+---------------+--------------+
| Phison USB 2.0 64GB (Generic Drive)        | 13fe:4300 | 102           | 262          |
+--------------------------------------------+-----------+---------------+--------------+

API Documentation
-----------------

.. doxygenfile:: msddrvce.h
   :project: CE C/C++ Toolchain
