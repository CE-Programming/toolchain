.. _debugging:

Debugging Features
==================

The toolchain offers the ability to debug your programs using the `CEmu emulator <https://ce-programming.github.io/CEmu>`_.

Add :code:`#include <debug.h>` to a source file, and use :code:`make debug` instead of :code:`make` to build a debug program.
You may need to run :code:`make clean` beforehand in order to ensure all source files are rebuilt.

Printing to the console
-----------------------

Printing is a classic debugging technique. :code:`dbg_printf()` allows you to print variables and strings to the CEmu console.
It uses the `standard printf format specifiers <http://www.cplusplus.com/reference/cstdio/printf/>`_.

Here are some examples:

.. code-block:: c

    int var = 10;
    unsigned code = 3;

    dbg_printf("Initialized some things...\n");
    dbg_printf("var value: %d\n", var);
    dbg_printf("PROGRAM ABORTED (code = %u)\n", code);

To view the output of these functions within `CEmu <https://ce-programming.github.io/CEmu>`_, enable the console using **Docks > Console**.

debug.h
=======

.. code-block:: c

    #include <debug.h>

API Documentation
-----------------

.. doxygenfile:: debug.h
   :project: CE C/C++ Toolchain
