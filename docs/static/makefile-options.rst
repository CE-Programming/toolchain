.. _makefile_options:

Makefile Options
================

The projects's Makefile controls different features and settings for the output program, and additionally can be added to for custom build structres if needed.
This section highlights the avaible options.

To edit these options, open the `makefile` file inside the project's folder in a text editor.

NAME
----

This is the name of the program variable that will be stored on the calculator.

.. code-block:: makefile

    NAME ?= PRGM

ICON
----

Icons make a more polished program that can be displayed in shells such as `Cesium <https://github.com/mateoconlechuga/cesium/releases/latest>`_.

Place a 16x16 PNG image in the same directory as the makefile with the name of whatever `ICON` is defined as, e.g. `iconc.png`.

.. code-block:: makefile

    ICON ?= iconc.png

DESCRIPTION
-----------

Change `DESCRIPTION` to the program's description. It is recommended to keep this under 25 characters.

The description will be displayed in shells such as `Cesium <https://github.com/mateoconlechuga/cesium/releases/latest>`_.


.. code-block:: makefile

    DESCRIPTION ?= "My awesome program"

COMPRESSED
----------

Programs can tend to be quite large from a variety of factors such as sprites, bloated code, or other issues.
The toolchain offers the ability to compress programs into a self-extracting executable.
This does not change the execution size, but rather the executable's storage size.

To enable this feature, open the project's makefile and edit the line:

.. code-block:: makefile

    COMPRESSED ?= YES

ARCHIVED
--------

Programs can be built to be stored in the archive rather than RAM.
To enable this feature, open the project's makefile and change the line:

.. code-block:: makefile

    ARCHIVED ?= YES

OPT_MODE
--------

This is the optimization level used for compiling the program.
The default clang optimizations flags are avaible here, e.g. -O(1|2|3|s|z|fast). 

.. code-block:: makefile

    OPT_MODE ?= -Oz

EXTRA_CFLAGS
------------

These flags are passed to the clang compiler.

.. code-block:: makefile

    EXTRA_CFLAGS ?= -Wall -Wextra

