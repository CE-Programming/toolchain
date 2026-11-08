.. _faq:

Frequently Asked Questions
==========================

I Found A Bug, Help!?
---------------------

Please create an `issue report here <https://github.com/CE-Programming/toolchain/issues>`_ with details on what caused the crash.
Uploading a zip of your code and/or a minimal reproducible example is very appreciated (and is usually required).
Including the output of the :code:`make V=1` command outputs more verbose information that helps diagnose the issue.

What versions of C/C++ are supported?
-------------------------------------

The CE Toolchain supports the latest LLVM/Clang toolchain - the status of each language can be found at the respective links: `C <https://clang.llvm.org/c_status.html>`_, `C++ <https://clang.llvm.org/cxx_status.html>`_

What is the C/C++ Runtime Memory Layout?
----------------------------------------

The CE has a limited amount of memory.

- The stack is roughly 4KiB.
- The code/data/rodata sections can be up to 64KiB.
- The bss/heap occupy a shared 60KiB region of memory and grow into each other.

The following graphic breaks down the address space.

.. image:: images/mem_layout.png
   :align: center

How can I use fasmg on a non-x86 processor?
-------------------------------------------

`Fasmg <https://flatassembler.net/docs.php?article=fasmg>`_ is a macro assembler used for assembling and linking project source files.
The project is written in x86 assembly, which means it cannot be run directly on non-x86 processors (such as ARM).
To mitigate this, the `QEMU <https://www.qemu.org>`_ project can be used to emulate the x86 processor in user-mode so that it can be
used directly. If you use a Debian-based system such as Ubuntu or Linux Mint, you can install QEMU using the following command:

.. code-block:: bash

    sudo apt install qemu-user

Next, open the file :code:`CEdev/meta/makefile.mk` in the toolchain install directory and locate the following line:

.. code-block:: makefile

    FASMG = $(call NATIVEPATH,$(BIN)/fasmg)

Add the text "qemu-x86_64" directly after the equal sign, shown below.
Now, fasmg will execute in user mode under QEMU, allowing it to successfully complete the assembly and linking steps.

.. code-block:: makefile

    FASMG = qemu-x86_64 $(call NATIVEPATH,$(BIN)/fasmg)

My code used to compile?!
-------------------------

But now the linker says :code:`Error: variable term used where not expected`.
    You probably have assembly code that was not placed in a linker section, see :ref:`Assembly Constants <asm>`.

But now I get a bunch of warnings and errors.
    The LLVM compiler being used is able to catch many more coding issues than the previous ZDS compiler.
    These are real issues that should be resolved.
