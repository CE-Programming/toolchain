.. _timers_h:

sys/timers.h
============

.. code-block:: c

    #include <sys/timers.h>

This header includes defines for the CE's 3 hardware timers.
It is discouraged from directly modifying the timers themseleves, and instead use the standard C `clock()` fuction.
This is because the toolchain uses the timers in the following way:

  * Timer 1 is used for `clock()` and related functions like `sleep()`.
  * Timer 2 is used by the :ref:`usbdrvce library <usbdrvce_h>`.
  * Timer 3 is used by the TI-OS USB stack and shouldn't be touched in most every case.

Directly manipulating the hardware timers may cause the above functions and/or libraries to not work correctly.
However, for example if you aren't using usbdrvce it is possible to use Timer 2 in your application.

There are two possible timing ("clock") sources: a 32768 Hz crystal with similar accuracy to the clock found in any smartphone or wristwatch, and the CPU's main 48 MHz clock with likely much inferior accuracy.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: sys/timers.h
   :project: CE C/C++ Toolchain
