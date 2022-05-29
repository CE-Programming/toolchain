.. _tokens_h:

ti/tokens.h
===========

.. code-block:: c

    #include <ti/tokens.h>

TI's operating system does not use ASCII (or Unicode) for user input.
Instead, all text entered is in a tokenized format,
where something like :code:`If` or :code:`poissoncdf(` is stored as a one or two byte code instead of the individual letters.
If you want to process string, program, or equation variables, you'll need to be able to handle tokens,
which this header helps you do.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/tokens.h
   :project: CE C/C++ Toolchain
