.. _usbdrvce_h:

usbdrvce.h
==========

.. code-block:: c

    #include <usbdrvce.h>

The :code:`usbdrvce` library is used for interacting with the USB peripheral in either host or device mode.

Currently this library is a work-in-progress, so some functionality may not behave as expected.
In particular, the following items are known to not work:

- All timer-related functions
- Isochronous transfers

Because of these limitations, future library versions may create backwards-incompatible changes - however the likelihood of this is rather low as long as you use the library in a reasonable manner.

.. tip::

    Be sure to look at the provided examples for guidance on how to use this library correctly.
    Hopefully in the future this page will include more documentation as the library becomes more complete.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: usbdrvce.h
   :project: CE C/C++ Toolchain
