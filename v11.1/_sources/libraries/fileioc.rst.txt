.. _fileioc_h:

fileioc.h
=========

.. code-block:: c

    #include <fileioc.h>

The :code:`fileioc` library provides access to OS variables such as AppVars, Programs, Lists, and Strings.

AppVars are special types of variables that can be used to store any arbitrary data, and are utilized by the CE toolchain to provide data storage beyond what can be compiled into a program.
AppVars may store things like save states, sprites, and user configurations.
Because the program context is destroyed when a program returns to the OS, AppVars can be used to store data between program launches.

The OS stores variables in either RAM or archive (aka flash) memory.
RAM memory is volatile and is cleared whenever the calculator is reset, whereas archive memory provides a more permanent storage for variables.
However, variables can only be written to while in RAM as the calculator's security measures do not provide a way to directly write to the archive.
The function :code:`ti_SetArchiveStatus` can be used to move a variable between the archive and RAM.

The function :code:`ti_Open` and :code:`ti_OpenVar` can be used to access AppVars and other OS variables respectively.
They return an opaque :code:`handle` value that is passed to the other functions available in the library.

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: fileioc.h
   :project: CE C/C++ Toolchain
