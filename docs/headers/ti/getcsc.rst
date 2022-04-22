.. _getcsc:

ti/getcsc.h
===========

.. code-block:: c

    #include <ti/getcsc.h>

Naturally, TI's operating system also has its own keyboard driver.
You can easily use it instead of the :code:`keypadc` library, and is particularly suited to non-game programs.

The OS's interrupt handler handles the keyboard driver and caches a scancode when it detects a key press.
You can use this scancode directly without any translation of 2nd and alpha through the :code:`os_GetCSC` function.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/getcsc.h
   :project: CE C/C++ Toolchain
