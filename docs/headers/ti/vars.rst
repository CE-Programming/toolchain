.. _vars:

ti/vars.h
=========

.. code-block:: c

    #include <ti/vars.h>

The TI-84 Plus CE's roots early-90s roots result in it managing files and data quite differently than how modern computers do.
Some data in the OS, such as stat vars, are permanently allocated a fixed location in RAM;
other data, such as user programs and strings, are not assigned a fixed location.
The operating system's equivalent to a "file" is called a variable, and they come in many types.
The locations of dynamic variables are tracked in a structure called the VAT (Variable Allocation Table).

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/vars.h
   :project: CE C/C++ Toolchain
