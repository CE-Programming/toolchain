.. _vars_h:

ti/vars.h
=========

.. code-block:: c

    #include <ti/vars.h>

The TI-84 Plus CE's early-90s roots result in it managing files and data quite differently from modern computers.
Some data in the OS, such as stat vars, are permanently allocated to a fixed location in RAM;
other data, such as user programs and strings, are not assigned a fixed location.
The operating system's equivalent to a "file" is called a variable, and they come in many types.
The locations of dynamic variables are tracked in a structure called the VAT (Variable Allocation Table).

The VAT has the novel property that it is stored completely in reverse and must be parsed backwards.
This means that no C structs are available to represent VAT entries, because C can't (easily) deal with reverse-ordered structs.
As a further complication, archived variables store a copy of their VAT entry in the archive, and *that* copy is *not* reversed.

Every variable type deals with its size differently.
The size is not stored in the VAT entry, but is instead stored with the variable's data.
But :code:`real_t` has no explicit size; the OS infers the size.
Meanwhile, lists store the number of elements and matrices store the number of rows and columns, so you have to compute the size.
(Don't forget that lists--but not matrices--can be either real or complex.)
Most other types use a simple size word.
The :ref:`fileioc library <fileioc_h>` masks all of this wackiness for you, but the OS also includes many helpful C functions.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/vars.h
   :project: CE C/C++ Toolchain
