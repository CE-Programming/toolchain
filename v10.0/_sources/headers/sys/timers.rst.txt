.. _timers_h:

sys/timers.h
============

.. code-block:: c

    #include <sys/timers.h>

This header includes defines for the CE's hardware timers.
There are two possible timing ("clock") sources: a 32768 Hz crystal with similar accuracy to the clock found in any
smartphone or wristwatch, and the CPU's main 48 MHz clock with likely much inferior accuracy.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: sys/timers.h
   :project: CE C/C++ Toolchain
