.. _debugging:

Debugging
=========

The toolchain offers the ability to debug your programs using the emulator `CEmu <https://ce-programming.github.io/CEmu>`_.

Add :code:`#include <debug.h>` to a source file, and use :code:`make debug` instead of :code:`make` to build a debug program.
You may need :code:`make clean` in order to ensure all source files are rebuilt.

Printing to the console
-----------------------

Printing is a classic debugging technique. :code:`dbg_sprintf()` allows you to print variables and strings to the CEmu console.
It uses these `format specifiers <http://www.cplusplus.com/reference/cstdio/printf/>`_.

Here are some examples:

.. code-block:: c

    int var = 10;
    unsigned code = 3;
    dbg_sprintf(dbgout, "Initialized some things...\n");
    dbg_sprintf(dbgout, "var value: %d\n", var);
    dbg_sprintf(dbgerr, "PROGRAM ABORTED (code = %u)\n", code);

To view the output of these functions within `CEmu <https://ce-programming.github.io/CEmu>`_, enable the console using **Docks > Console**.

