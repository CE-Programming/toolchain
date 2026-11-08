.. _srldrvce_h:

srldrvce.h
==========

.. code-block:: c

    #include <srldrvce.h>

The :code:`srldrvce` library adds support for reading and writing serial devices in host mode, as well as emulating a serial device in device mode.
This library is built on top of the :code:`usbdrvce` library - data that is not serial in nature such as pictures, video, and audio may be more suited to using the :code:`usbdrvce` library directly.

Currently this library is a work-in-progress, so some functionality may not behave as expected.
This means that future library versions may create backwards-incompatible changes - however the likelihood of this is rather low as long as you use the library in a reasonable manner.

.. tip::

    Be sure to look at the provided examples for guidance on how to use this library correctly.
    Hopefully in the future this page will include more documentation as the library becomes more complete.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: srldrvce.h
   :project: CE C/C++ Toolchain
