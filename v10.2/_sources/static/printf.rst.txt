.. _printf:

Using printf Functions
======================

What's the deal with printf?
----------------------------

The `printf` and related functions (`sprintf`, `vsprintf`, etc.) are based on a relatively `small implementation <https://github.com/CE-Programming/toolchain/blob/master/src/std/shared/nanoprintf.c>`_.
However, they contribute around 8 KiB to the resultant program.
It is highly recommended to not use `printf` and related functions at all because of this.
If you insist on using these functions, this page details how to do so in the next section.

Alternatively, a limited `sprintf` implementation is baked into the OS which doesn't add any extra size to the resultant program.
Only the 'c', 'd', 'u', 'x', and 's' format specifiers will probably work.
To disable all other printf functions and use this `sprintf` implementation, add the following line to the Makefile:

.. code-block:: makefile

    HAS_PRINTF := NO

If you just need to convert a float to a string, which the OS sprintf does not support, you can utilize the following `float2str` function instead.

.. code-block:: c

    void float2str(float value, char *str)
    {
        real_t tmp_real = os_FloatToReal(value);
        os_RealToStr(str, &tmp_real, 8, 1, 2);
    }


Using the printf functions
--------------------------

All the `printf` and related functions are defined in the standard `stdio.h` header, and can be used just as they would in any normal C program.

The output of character text is done via the `outchar` function, which is a special toolchain function that by default prints to the OS homescreen.
It's prototype looks like this:

.. code-block:: c

    void outchar(char character);

Reimplement this function in your program in any source file to change how characters are printed.
For example, a horrid implementation of this function might look like the one below, which just prints to the OS homescreen.

.. code-block:: c

    void outchar(char character)
    {
        char str[2] = { character, '\0' };

        os_PutStrFull(str);
    }

As an additional note, the `outchar` function is used by the standard `putchar` and `puts` functions -- even if you have disabled the other printf functions, these two will still work as expected.
