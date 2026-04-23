.. _real:

ti/real.h
=========

.. code-block:: c

    #include <ti/real.h>

Surprisingly, the TI-84 Plus CE is actually sold to students as a calculator and not a gaming console.
TI actually even implemented an entire highly-accurate floating-point package!

TI's floating-point routines use binary-coded decimal, in which each hexadecimal nibble represents one decimal digit.
Each :code:`real_t` has 14 digits (7 bytes) in the significand, an 8-bit exponent which the OS limits to +/- 99, and a sign byte.
They provide precision similar to a standard :code:`double` on a PC, albeit with a smaller exponent range.
Using :code:`real_t` is much slower than :code:`float` because of the vastly greater precision.
(Remember that the C SDK implements :code:`double` as :code:`float`, which is allowed by the C standard.)

The SDK calls them :code:`real_t` because :code:`float` is already taken.
The OS floating-point routines also support complex numbers quite well and transparently, but SDK support is not implemented.

A C++ wrapper is available as :code:`<ti/real>` but no documentation has been written.
Please see the examples in the :code:`standalone` folder and consult the header itself.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/real.h
   :project: CE C/C++ Toolchain
