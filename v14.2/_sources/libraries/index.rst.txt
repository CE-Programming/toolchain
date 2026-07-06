.. _libraries:

CE Library Headers
==================

The CE Libraries are used to aid in rapid development by implementing optimized routines for graphics, fonts, file I/O, keypad input, USB access and more.
The libraries are delivered as AppVars that reside in the calculator's archive, and are dynamically linked at runtime by the :code:`LibLoad` library.
This helps to reduce the size of most programs, and ensures that programs can take advantage of library bug fixes and improvements without needing to be modified or recompiled.

The libraries can be downloaded here: `tiny.cc/clibs <https://github.com/CE-Programming/libraries/releases/latest>`__.

Common libraries:

.. toctree::
    :maxdepth: 1
    :glob:

    graphx
    fontlibc
    fileioc
    keypadc
    lcddrvce
    libload

USB Libraries:

.. toctree::
    :maxdepth: 1
    :glob:

    usbdrvce
    srldrvce
    msddrvce
    fatdrvce

Click any of the above links to navigate to the library's documentation.
