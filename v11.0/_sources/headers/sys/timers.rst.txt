.. _timers_h:

sys/timers.h
============

.. code-block:: c

    #include <sys/timers.h>

This header includes defines for the CE's 3 hardware timers.
It is discouraged from directly modifying the timers themseleves, and instead use the standard C `clock()` fuction.
These functions provide direct maniplution of the hardware timers.
Keep in mind that using them may cause the `clock()` and related functions to not work correctly.
This header also includes functions such as `sleep()` and `delay()` which are based around `clock()`'s functionality and are always safe to use.

There are two possible timing ("clock") sources: a 32768 Hz crystal with similar accuracy to the clock found in any smartphone or wristwatch, and the CPU's main 48 MHz clock with likely much inferior accuracy.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: sys/timers.h
   :project: CE C/C++ Toolchain
