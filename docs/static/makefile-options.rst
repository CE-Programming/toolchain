.. _makefile_options:

.. toctree::
  :titlesonly:

Makefile Options
================

The project's makefile controls different features and settings for the output program.
Additional rules can be added to build different components as well.

To edit these options, open the :code:`makefile` file inside the project's folder in a text editor.

Output Configuration
--------------------

.. rubric:: NAME

This is the name of the program that will be stored on the calculator.

.. code-block:: makefile

    NAME = PRGM

.. rubric:: ICON

Icons make a more polished program that can be displayed in shells such as `Cesium <https://github.com/mateoconlechuga/cesium/releases/latest>`_.

Icons are a 16x16 pixel image - provide the relative path to the image from the makefile via the :code:`ICON` option.

.. code-block:: makefile

    ICON = icon.png

.. rubric:: DESCRIPTION

Change :code:`DESCRIPTION` to the program's description.
It is recommended to keep this under 25 characters.

The description will be displayed in shells such as `Cesium <https://github.com/mateoconlechuga/cesium/releases/latest>`_.

.. code-block:: makefile

    DESCRIPTION = "My awesome program"

.. rubric:: COMPRESSED

Programs can tend to be quite large from a variety of factors such as sprites, bloated code, or other issues.
The toolchain offers the ability to compress programs into a self-extracting executable.
This does not change the execution size, but rather the executable's storage size.

To enable this feature, open the project's makefile and edit the line:

.. code-block:: makefile

    COMPRESSED = YES

.. rubric:: ARCHIVED

Programs can be built to be stored in the archive rather than RAM.
To enable this feature, open the project's makefile and change the line:

.. code-block:: makefile

    ARCHIVED = YES

.. rubric:: OUTPUT_MAP

Outputs a <name>.map file into the :code:`bin` directory that includes section, variable, and function addressing/size information of the compiled program.
To speed up linking this step can be disabled.
Default: :code:`YES`.

.. code-block:: makefile

    OUTPUT_MAP = YES

Compiler Configuration
----------------------

.. rubric:: CFLAGS / CXXFLAGS

These flags are passed to the compiler.
:code:`CFLAGS` is used for C source files, :code:`CXXFLAGS` is used for C++ source files.

.. code-block:: makefile

    CFLAGS = -Wall -Wextra -Oz
    CXXFLAGS = -Wall -Wextra -Oz

.. rubric:: LTO

This option enables link-time optimization.
Depending on the program this can reduce the output size.
Default: :code:`YES`.

.. code-block:: makefile

    LTO = YES

.. rubric:: PREFER_OS_CRT

Prefer the builtin OS CRT (Compiler-Run-Time) functions if they exist.
This can help to decrease the output size in some circumstances, as a select number of CRT functions will execute from flash.
Default: :code:`NO`.

.. code-block:: makefile

    PREFER_OS_CRT = NO

.. rubric:: PREFER_OS_LIBC

Prefer the builtin OS LIBC functions if they exist.
This can help to decrease the output size in some circumstances, as a select number of LIBC functions will execute from flash.
Default: :code:`YES`.

.. code-block:: makefile

    PREFER_OS_LIBC = YES

Miscellaneous Configuration
---------------------------

.. rubric:: DEPS

Add any files that you want to be built by the toolchain to this variable.
Define rules for the files after including the main CEdev makefile.

.. code-block:: makefile

    DEPS = $(BINDIR)/levelpack.bin

    include $(shell cedev-config --makefile)

    $(BINDIR)/levelpack.bin:
    	$(call MKDIR,$(@D))
    	echo "levelpack" > $(BINDIR)/levelpack.bin

