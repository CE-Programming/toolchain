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

The CE Toolchain uses LLVM/Clang v17.
The status of each language feature support can be found at the respective links: `C <https://clang.llvm.org/c_status.html>`_, `C++ <https://clang.llvm.org/cxx_status.html>`_

What is the C/C++ Runtime Memory Layout?
----------------------------------------

The CE has a limited amount of memory.

- The stack is roughly 4KiB.
- The code/data/rodata sections can be up to 64KiB.
- The bss/heap occupy a shared 60KiB region of memory and grow into each other.

The following graphic breaks down the address space.

.. image:: images/mem_layout.png
   :align: center

My code used to compile?!
-------------------------

But now I get a bunch of warnings and errors.
    The LLVM compiler being used is able to catch many more coding issues than the previous ZDS compiler.
    These are real issues that should be resolved.

But now my assembly files don't compile.
    The CE Toolchain switched to using the GNU Assembler (GAS) in version 15.0.0.
    This means that assembly files will need to be ported from the fasmg syntax to the GAS syntax.
    More information can be found in the :ref:`Assembly Files <asm>` page.
