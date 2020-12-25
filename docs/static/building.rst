.. _building:

Building the CE C Toolchain
===========================

If you are brave enough to contribute source to the CE C Toolchain, this page is for you!

Linux and macOS
---------------

Get the `ez80-clang LLVM compiler <https://github.com/jacobly0/llvm-project/wiki>`_.
Make sure the compiler is located in the system's PATH enviornment variable.

Clone the repo:

.. code-block:: bash

    git clone --recurse-submodules https://github.com/CE-Programming/toolchain.git

Build and install the toolchain:

.. code-block:: bash

    cd toolchain
    make
    make install

By default, the toolchain is installed into the home (`~/CEdev`) directory.

This is configurable with :code:`make install PREFIX=[LOCATION]`

Windows
-------

Get `MinGW <http://www.mingw.org>`_.
The only required pacakges are `mingw32-base` and `mingw32-gcc-g++`.
Make sure the `MinGW/bin` directory is in the system's PATH enviornment variable.

Get the `ez80-clang LLVM compiler <https://github.com/jacobly0/llvm-project/wiki>`_.
Make sure the compiler is located in the system's PATH enviornment variable.

Clone the repo:

.. code-block:: bash

    git clone --recurse-submodules https://github.com/CE-Programming/toolchain.git

Build and install the toolchain:

.. code-block:: bash

    cd toolchain
    mingw32-make
    mingw32-make install

By default, the toolchain is installed into the root (C:\\CEdev) directory.

This is configurable with :code:`mingw32-make install PREFIX=[LOCATION]`

