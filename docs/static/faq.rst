.. _faq:

Frequently Asked Questions
==========================

Floats in sprintf and dbg_printf
--------------------------------

Floats in printf and related functions (using `%f`, `%g`, or similar), are not normally provided due to memory constraints.
They can be `temporarily` enabled by adding the following line in the makefile:

.. code-block:: makefile

    USE_FLASH_FUNCTIONS := NO

This will greatly increase the size of the binary, so it is recommended to implement a custom limited version of `%f`.
For example, this accomplishes the goal of `%f`, placing the output in a character array.

.. code-block:: c

    void float2str(float value, char *str)
    {
        real_t tmp_real = os_FloatToReal(value);
        os_RealToStr(str, &tmp_real, 8, 1, 2);
    }


Memory Layout
-------------

The CE has a limited amount of memory.
The stack is roughly 4KiB bytes in size, while the bss/heap grow into each other and consume 64KiB. The following graphic breaks down the address space.

.. image:: images/mem_layout.png
   :align: center

