.. _hooks:

ti/hooks.h
==========

.. code-block:: c

    #include <ti/hooks.h>

Hooks allow software to override the OS's normal behavior to integrate more seemlessly with the OS.
For example, the Inequalz app uses hooks to override most of the normal graphscreen behavior.
Unfortunately, TI's hooks API assumes only apps will want to use hooks,
so they can only reliably be used by normal programs while they are still running.
If you want a hook to continue to operate after your program exits,
you'll need to make an app or use terrible hacky workarounds.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/hooks.h
   :project: CE C/C++ Toolchain
