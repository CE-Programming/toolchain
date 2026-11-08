.. _contributing:

Contributing to the CE Toolchain
================================

If you are brave enough to contribute source to the CE Toolchain, this page is for you!

Creating PRs for review
-----------------------

Pull Requests (PRs) should branch from git :code:`master`.
Before creating a PR, it is a good idea to get some feedback either from IRC or by creating a relevant issue.
This will increase the chances of your PR being merged in a timely fashion.
Please do not make large PRs; it is better to make smaller changes in different PRs.

For information on how to fork a repo and create a PR using GitHub, see the `forking documentation <https://docs.github.com/en/free-pro-team@latest/github/getting-started-with-github/fork-a-repo>`_.

Building the CE Toolchain
-------------------------

Linux and macOS
~~~~~~~~~~~~~~~

Get the `ez80-clang LLVM compiler <https://github.com/jacobly0/llvm-project/wiki>`_.
Make sure the compiler is located in the system's PATH environment variable.

Get the `fasmg assembler <https://flatassembler.net/download.php>`_.
The download is located near the bottom of the page.
Extract the `fasmg.x64` executable for your operating system to either the same place
as `ez80-clang`, or in the system's PATH environment variable.
Rename it to just `fasmg`.

Clone the repo:

.. code-block:: bash

    git clone --recurse-submodules https://github.com/CE-Programming/toolchain.git

Build and install the toolchain:

.. code-block:: bash

    cd toolchain
    make -j
    make install -j

By default, the toolchain is installed into the home (`~/CEdev`) directory.

This is configurable with :code:`make install PREFIX=[LOCATION]`

Finally, copy the previously downloaded `fasmg` and `ez80-clang` executables to the installed `CEdev/bin` directory.

Windows
~~~~~~~

Get `MinGW <https://osdn.net/projects/mingw/>`_.
The only required pacakges are `mingw32-base` and `mingw32-gcc-g++`.
Make sure the `MinGW\\bin` directory is in the system's PATH environment variable.

Get the `ez80-clang LLVM compiler <https://github.com/jacobly0/llvm-project/wiki>`_.
Make sure the compiler is located in the system's PATH environment variable.

Get the `fasmg assembler <https://flatassembler.net/download.php>`_.
The download is located near the bottom of the page.
Extract the `fasmg` executable for your operating system to either the same place
as `ez80-clang`, or in the system's PATH environment variable.

Clone the repo:

.. code-block:: bash

    git clone --recurse-submodules https://github.com/CE-Programming/toolchain.git

Build and install the toolchain:

.. code-block:: bash

    cd toolchain
    mingw32-make -j
    mingw32-make install -j

By default, the toolchain is installed into the root (C:\\CEdev) directory.

This is configurable with :code:`mingw32-make install PREFIX=[LOCATION]`

Finally, copy the previously downloaded `fasmg` and `ez80-clang` executables to the installed `CEdev\\bin` directory.
