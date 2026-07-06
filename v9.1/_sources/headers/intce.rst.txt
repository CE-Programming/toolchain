.. _intce_h:

intce.h
=======

.. code-block:: c

    #include <intce.h>

This header includes defines and prototypes for working with user interrupts.

.. warning::

    As of hardware revision I, user interrupt vectors are no longer supported.
    Some functions will no longer work on the newer hardware, and are labeled as such.
    Feel free to send TI a strongly worded email about this limitation.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: intce.h
   :project: CE C Toolchain
