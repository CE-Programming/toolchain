.. _error_h:

ti/error.h
==========

.. code-block:: c

    #include <ti/error.h>

Exceptions in languages like Python provide a structured way of handling rare error conditions.
TI calls their implementation of this idea error handlers.

When the OS encounters an unsusal condition such as divide-by-zero or out-of-memory, it looks for an active error handler.
If no active error handlers exist, the OS will display the :code:`ERR:` screen.
If an active error handler does exist, it gets control instead of showing the :code:`ERR:` screen.

Unlike exception handlers, TI's error handlers do not differentiate between error codes; the same error handler is called for all errors.
However, error handlers do support nesting.
If an handler decides that it can't handle an error, it can rethrow it.

.. warning::

    When a TI error handler is invoked, C++ destructors **are not** run *even if the handler is outside the current scope!*
    Therefore, you must be very careful with object creation while an error handler is active.

Similarly, although the toolchain supports C++, it does *not* support C++ exceptions, and TI error handlers are not a substitute for C++ exceptions.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/error.h
   :project: CE C/C++ Toolchain
