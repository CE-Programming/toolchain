.. _sprintf_h:

ti/sprintf.h
============

.. code-block:: c

    #include <ti/sprintf.h>

The OS comes with an implementation of ANSI C89 `sprintf`, which can reduce the size of a program by ~8 KiB. However, it is very limited in functionality. It does not support length modifiers, and it won't accept :code:`long` or :code:`float` arguments.

boot_sprintf
------------

The following type specifiers are supported :code:`%s %c %d %i %u %o %x %X %p %n`. The minimum field width :code:`*`, precision :code:`.*`, alongside :code:`-+#0` and the space flag are also supported. However, the precision :code:`.*` field is ignored for integers.

All length modifiers :code:`hh h l ll j z t L` and floating point specifiers :code:`%f %g %e %a` are **not** supported.

Additionally, each individual argument will write no more than 255 characters each. This means that any strings written with :code:`%s` will be truncated after 255 characters.

:code:`<ti/sprintf.h>` provides `boot_sprintf`, `boot_snprintf`, and `boot_asprintf`, in addition to `boot_vsprintf`, `boot_vsnprintf`, and `boot_vasprintf` which accept a `va_list`.

.. code-block:: c

    int boot_sprintf(char *restrict buffer, const char *restrict format, ...)
    int boot_vsprintf(char *restrict buffer, const char *restrict format, va_list args)

    int boot_snprintf(char *restrict buffer, size_t count, const char *restrict format, ...)
    int boot_vsnprintf(char *restrict buffer, size_t count, const char *restrict format, va_list args)

    int boot_asprintf(char **restrict p_buffer, const char *restrict format, ...)
    int boot_vasprintf(char **restrict p_buffer, const char *restrict format, va_list args)

`sprintf` is traditionally "unsafe" because a maximum output length cannot be specified, which can cause buffer overflows. By writing to an unmapped memory address :code:`0xE40000`, `boot_sprintf` can safely write up to ~786000 bytes which can then be used to determine the length of the output.

Replacing printf functions
--------------------------

To replace all other printf functions with the `boot_sprintf` functions, add the following line to the Makefile. More information :ref:`here <printf>`.

.. code-block:: makefile

    HAS_PRINTF = NO

boot_vsprintf
-------------

Because the OS does not provide `vsprintf`, `boot_vsprintf` is implemented by counting the number of arguments in the format string, and then copying the arguments from `va_list` onto the stack so they can be passed into `boot_sprintf`.

boot_asprintf
-------------

`boot_asprintf` functions similarly to `asprintf <https://www.man7.org/linux/man-pages/man3/asprintf.3.html>`_. It will automatically allocate a buffer containing the output from `boot_sprintf`. The buffer shall be deallocated with :code:`free`. The returned buffer will be :code:`NULL` if an allocation or formatting error occurs.

boot_snprintf
-------------

`boot_snprintf` is similar to `snprintf`, except that it returns an empty string if the result of `boot_sprintf` won't fit inside the buffer. Otherwise passing in :code:`boot_snprintf(NULL, 0, format, args)` can be used to query the length of the output without writing to a buffer.

The truncating behavior of C99 `snprintf` can be replicated with `boot_asprintf`

.. code-block:: c

    char buf[20];
    char *temp;
    boot_asprintf(&temp, format, ...);
    if (temp != NULL) {
        strncpy(buf, temp, sizeof(buf));
        buf[sizeof(buf) - 1] = '\0'; // null terminate the end of the buffer
        free(temp);
    }

printf and fprintf
------------------
`printf` and `fprintf` can be replicated by using `fputs`

.. code-block:: c

    char output[50];
    boot_snprintf(output, format, ...);
    // fprintf(stdout, ...) == printf(...)
    fputs(stdout, output);
