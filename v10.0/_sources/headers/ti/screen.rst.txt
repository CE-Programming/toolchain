.. _screen:

ti/screen.h
===============

.. code-block:: c

    #include <ti/screen.h>

Programs that don't need fancy graphics can use TI's screen routines instead of :code:`<graphx.h>`.

If you want to print text to the homescreen and have it support automatic scrolling,
then cursor locations are based on a character grid.
Most of the text routines work this way.
In particular, :code:`os_GetStringInput` and :code:`os_PutStr*` work this way.

However, you can also draw text to arbitrary pixel locations using either the large or small font.
Those routines have :code:`Font` in their name and also let you use color.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/screen.h
   :project: CE C/C++ Toolchain
