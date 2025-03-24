.. _boot_sprintf:

boot_sprintf
======================

.. code-block:: c

    #include <boot_sprintf.h>

The OS comes with an implementation of ANSI C89 `sprintf`, which can reduce the size of a program by ~8 KiB. However, it is very limited in functionality. It does not support width specifiers, and it won't accept :code:`long` or :code:`float` arguments.

The following type specifiers are supported :code:`%s %c %d %i %u %o %x %X %p %n`, alongside the flags :code:`-+ #0*` in addition to the width field.

All length modifiers :code:`hh h l ll j z t L` and floating point specifiers :code:`%f %g %e %a` are **not** supported.

Additionally, each individual argument will write no more than 255 characters each. This means that any strings written with :code:`%s` will be truncated after 255 characters.

The :code:`<boot_sprintf.h>` header provides `boot_sprintf`. `boot_snprintf` and `boot_asprintf` are also provided as macros

.. code-block:: c

    int boot_sprintf(char *restrict buffer, const char *restrict format, ...)

    int boot_snprintf(char *buffer, size_t count, const char *restrict format, ...)

    int boot_asprintf(char **restrict p_buffer, const char *restrict format, ...)

Because the OS does not provide `vsprintf`, `boot_snprintf` and `boot_asprintf` are implemented as macros. This means that :code:`...` or :code:`__VA_ARGS__` will be evaluated twice when the macro is expanded. `sprintf` is traditionally "unsafe" because a maximum output length cannot be specified, which can cause buffer overflows. By writing to an unmapped memory address :code:`0xE40000`, `boot_sprintf` can safely write up to ~786000 bytes which can then be used to determine the length of the output.

replacing printf functions
----------------------------

To disable all other printf functions with `boot_sprintf`, `boot_snprintf`, and `boot_asprintf`, add the following line to the Makefile. More information `here <https://ce-programming.github.io/toolchain/static/printf.html>`

.. code-block:: makefile

    HAS_PRINTF = NO

.. warning::

    :code:`std::snprintf` and :code:`std::asprintf` will cause errors if :code:`HAS_PRINTF = NO`

boot_asprintf
----------------------------

`boot_asprintf` functions similarly to `asprintf <https://www.man7.org/linux/man-pages/man3/asprintf.3.html>`_. It will automatically allocate a buffer containing the output from `boot_sprintf`. The buffer shall be deallocated with :code:`free`. The returned buffer will be :code:`NULL` if an allocation or formatting error occurs.

boot_snprintf
----------------------------

`boot_snprintf` is similar to `snprintf`, except that it returns an empty string if the result of `boot_sprintf` won't fit inside the buffer. Otherwise passing in :code:`boot_snprintf(NULL, 0, format, args)` can be used to query the length of the output without writing to a buffer.

The truncating behavior of C99 `snprintf` can be replicated with `boot_asprintf`

.. code-block:: c
    char buf[20];
    char* temp;
    boot_asprintf(&temp, format, ...);
    if (temp != NULL) {
        strncpy(buf, temp, sizeof(buf));
        buf[sizeof(buf) - 1] = '\0'; // null terminate the end of the buffer
        free(temp);
    }

printf and fprintf
----------------------------
`printf` and `fprintf` can be replicated by using `boot_asprintf` and `fputs`

.. code-block:: c
    char* output;
    boot_asprintf(&output, format, ...);
    if (output != NULL) {
        // fprintf(stdout, ...) == printf(...)
        fputs(stdout, output);
        free(output);
    }
