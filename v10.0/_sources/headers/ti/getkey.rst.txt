.. _getkey:

ti/getkey.h
===========

.. code-block:: c

    #include <ti/getkey.h>

For programs that interact with the OS's user interface, you may want to use processed keystrokes instead of raw scancodes.
The :code:`os_GetKey` routine handles 2nd and alpha presses, and can even show menus.

TI-83 Premium CE
----------------

No research has been done on how the TI-83 Premium CE is different here.
However, you should be aware that on the TI-83 Premium CE, :code:`os_GetKey` may return values not included in this list.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/getkey.h
   :project: CE C/C++ Toolchain
