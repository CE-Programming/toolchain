.. _sprintf_h:

ti/sprintf.h
============

.. code-block:: c

    #include <ti/sprintf.h>

The OS comes with an implementation of ANSI C89 :code:`sprintf`, which can reduce the size of a program by ~8 KiB. However, it is limited in functionality. It does not support length modifiers and won't accept :code:`long` or :code:`float` arguments.

boot_sprintf
------------

The following type specifiers are supported: :code:`%s %c %d %i %u %o %x %X %p %n`. The minimum field width :code:`*`, precision :code:`.*`, and the :code:`-+#0` and space flags are also supported. However, the precision :code:`.*` field is ignored for integers.

All length modifiers :code:`hh h l ll j z t L` and floating-point specifiers :code:`%f %g %e %a` are **not** supported.

Additionally, each individual argument will write no more than 255 characters. This means that any strings written with :code:`%s` will be truncated after 255 characters.

:code:`<ti/sprintf.h>` provides :code:`boot_sprintf`, :code:`boot_snprintf`, and :code:`boot_asprintf`, in addition to :code:`boot_vsprintf`, :code:`boot_vsnprintf`, and :code:`boot_vasprintf`, which accept a :code:`va_list`.

.. code-block:: c

    int boot_sprintf(char *restrict buffer, const char *restrict format, ...)
    int boot_vsprintf(char *restrict buffer, const char *restrict format, va_list args)

    int boot_snprintf(char *restrict buffer, size_t count, const char *restrict format, ...)
    int boot_vsnprintf(char *restrict buffer, size_t count, const char *restrict format, va_list args)

    int boot_asprintf(char **restrict p_buffer, const char *restrict format, ...)
    int boot_vasprintf(char **restrict p_buffer, const char *restrict format, va_list args)

:code:`sprintf` is traditionally "unsafe" because a maximum output length cannot be specified, which can cause buffer overflows. By writing to an unmapped memory address :code:`0xE40000`, :code:`boot_sprintf` can safely write up to ~786000 bytes, which can then be used to determine the length of the output.

Replacing printf functions
--------------------------

To replace all other printf functions with the :code:`boot_sprintf` functions, add the following line to the Makefile. More information: :ref:`here <printf>`.

.. code-block:: makefile

    HAS_PRINTF = NO

boot_vsprintf
-------------

Because the OS does not provide :code:`vsprintf`, :code:`boot_vsprintf` is implemented by counting the number of arguments in the format string and then copying the arguments from :code:`va_list` onto the stack so they can be passed into :code:`boot_sprintf`.

boot_asprintf
-------------

:code:`boot_asprintf` functions similarly to :code:`asprintf <https://www.man7.org/linux/man-pages/man3/asprintf.3.html>`_. It automatically allocates a buffer containing the output from :code:`boot_sprintf`. The buffer should be deallocated with :code:`free`. The returned buffer will be :code:`NULL` if an allocation or formatting error occurs.

boot_snprintf
-------------

:code:`boot_snprintf` is similar to :code:`snprintf`, except that it returns an empty string if the result of :code:`boot_sprintf` won't fit inside the buffer. Otherwise, passing in :code:`boot_snprintf(NULL, 0, format, args)` can be used to query the length of the output without writing to a buffer.

The truncating behavior of C99 :code:`snprintf` can be replicated with :code:`boot_asprintf`.

.. code-block:: c

    char buf[20];
    char *temp;
    boot_asprintf(&temp, format, ...);
    if (temp != NULL) {
        strlcpy(buf, temp, sizeof(buf));
        free(temp);
    }

printf and fprintf
------------------

:code:`printf` and :code:`fprintf` can be replicated by using :code:`fputs`.

.. code-block:: c

    char output[50];
    boot_snprintf(output, sizeof(output), format, ...);
    // fprintf(stdout, ...) == printf(...)
    fputs(output, stdout);
