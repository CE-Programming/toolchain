.. _contributing:

Contributing to the CE Toolchain
================================

If you are brave enough to contribute source to the CE Toolchain, this page is for you!

Creating PRs for review
-----------------------

Pull Requests (PRs) should branch from git ``master``.
Before creating a PR, it may be a good idea to get some feedback from IRC/Discord first.
This will increase the chances of your PR being merged in a timely fashion.
Please do not make large PRs - it is better to make smaller changes in different PRs.

For information on how to fork a repo and create a PR using GitHub, see the `forking documentation <https://docs.github.com/en/free-pro-team@latest/github/getting-started-with-github/fork-a-repo>`_.

Building the CE Toolchain
-------------------------

Linux and macOS
~~~~~~~~~~~~~~~

Get the `ez80 LLVM compiler <https://github.com/jacobly0/llvm-project/wiki>`_.
Make sure that ``ez80-clang`` and ``ez80-link`` are reachable by the system's PATH environment variable.

Get the `fasmg assembler <https://flatassembler.net/download.php>`_.
The download is located near the bottom of the page.
Extract the ``fasmg.x64`` executable to the same location as the compiler.
Rename it to just ``fasmg``.

Clone the repo:

.. code-block:: bash

    git clone https://github.com/CE-Programming/toolchain.git
    cd toolchain
    git submodule update --init --recursive

Build and install the toolchain:

.. code-block:: bash

    make
    make install

By default, the toolchain is installed into the home (``~/CEdev``) directory.

This is configurable with :code:`make install PREFIX=[LOCATION]`

Windows
~~~~~~~

Get `MSYS2 <https://www.msys2.org/>`_ and use the `MinGW64` environment.

The only required pacakge is `mingw-w64-x86_64-toolchain <https://packages.msys2.org/groups/mingw-w64-x86_64-toolchain>`_.
Make sure the ``C:\msys64\mingw64\bin`` directory is in the system's PATH environment variable.

Get the `ez80 LLVM compiler <https://github.com/jacobly0/llvm-project/wiki>`_.
Make sure that ``ez80-clang.exe`` and ``ez80-link.exe`` are reachable by the system's PATH environment variable.

Get the `fasmg assembler <https://flatassembler.net/download.php>`_.
The download is located near the bottom of the page.
Extract the ``fasmg.exe`` executable to the same location as the compiler.

Clone the repo:

.. code-block:: bash

    git clone https://github.com/CE-Programming/toolchain.git
    cd toolchain
    git submodule update --init --recursive

Build and install the toolchain:

.. code-block:: bash

    mingw32-make
    mingw32-make install

By default, the toolchain is installed into the root (``C:\CEdev``) directory.

This is configurable with :code:`mingw32-make install PREFIX=[LOCATION]`
