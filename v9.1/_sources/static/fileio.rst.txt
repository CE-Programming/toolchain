.. _fileio:

Using File I/O Functions
========================

What are File I/O Functions?
----------------------------

File I/O functions are any of the standard `fopen`, `fgets`, `fread`, and related file functions.
These functions are meant to perform OS-level file access for reading and writing.
However, the CE doesn't expose any sort of standard UNIX or similar file capabilities.

To mitigate this, the CE C Toolchain includes these functions as wrappers around the :ref:`fileioc library <fileioc_h>`.
This allows native access to AppVars for read and write operations.

For :code:`stdin`, :code:`stdout`, and :code:`stderr` file streams, the default implementation uses the `getchar` and `putchar` functions respectively.

Using Custom File I/O
---------------------

If you do not wish to have the file I/O functions backed by the :ref:`fileioc library <fileioc_h>`, you can instead redefine the functions that you need in any source file.
The new functions will override the default implementation.

Additionally, the makefile needs to be updated accordingly.
Add the below lines to the makefile to enable the custom file operations:

.. code-block:: makefile

    HAS_CUSTOM_FILE := YES
    CUSTOM_FILE_FILE := stdio_file.h

The option **CUSTOM_FILE_FILE** should be set to the name of the file which redefines the :code:`FILE` structure used by the standard file I/O functions.
Additionally, it should redefine :code:`stdin`, :code:`stdout`, and :code:`stderr`, however if your program doesn't require these this isn't necessary.

An example *stdio_file.h* might look like this:

.. code-block:: c

    #ifndef STDIO_FILE_H
    #define STDIO_FILE_H

    typedef struct
    {
        unsigned char slot;
        unsigned char eof;
        unsigned char err;
    } FILE;
    #define FOPEN_MAX  5
    #define stdin      ((FILE*)1)
    #define stdout     ((FILE*)2)
    #define stderr     ((FILE*)3)

    #endif

Be sure to clean the project via :code:`make clean` if the implementation changes from the default and project files need to be rebuilt to use the updates.
