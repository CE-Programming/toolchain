.. _faq:

Frequently Asked Questions
==========================

I Found A Bug, Help!?
---------------------

Nice work, now create an `issue report here <https://github.com/CE-Programming/toolchain/issues>`_ with details on what caused the crash.
Uploading a zip of your code and/or a minimal reproducible example is very appreciated, and will make bug fixes faster.

What versions of C/C++ are supported?
-------------------------------------

The CE Toolchain supports the latest LLVM/Clang toolchain, and the status of each language can be found at the respective links: `C <https://clang.llvm.org/c_status.html>`_, `C++ <https://clang.llvm.org/cxx_status.html>`_

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

Linking Assembly Source Files
-----------------------------

Assembly routines can be linked into a C/C++ program provided the following conditions are met:

- The file's extension is **.asm**. It can be placed at any depth in the sources directory.
- The routine should have a C/C++ prototype if it used externally.
- The assembly routine must be prefixed with an underscore, and have a corresponding `public` entry in the assembly file.
- Any external functions called from the assembly source must be listed as being `extern`.

Below is an example assembly source file that relies on an external function:

.. code-block:: asm

    	public	_asm_func

    _asm_func:
    	pop	hl
    	pop	de
    	push	de
    	push	hl
	call	_external_func
    	ret

    	extern	_external_func

The C prototype is shown below:

C File:

.. code-block:: c

    void asm_func(int a);

Arguments
~~~~~~~~~

Arguments are pushed from last to first corresponding to the C prototype.
In eZ80, 3 bytes are always pushed to the stack regardless of the actual size.
However, the assembly function must be careful to only use the valid bytes that are pushed.
For example, if a *short* type is used, the upper byte of the value pushed on the stack will contain arbitrary data.
This table lists the locations relative to *sp* from within the called funciton.

+------------+------------+----------------------+
| C Type     | Size       | Stack Location       |
+============+============+======================+
| char       | 1 byte     | sp + [3]             |
+------------+------------+----------------------+
| short      | 2 bytes    | sp + [3:4]           |
+------------+------------+----------------------+
| int        | 3 bytes    | sp + [3:5]           |
+------------+------------+----------------------+
| long       | 4 bytes    | sp + [6]: sp + [3:5] |
+------------+------------+----------------------+
| float      | 4 bytes    | sp + [6]: sp + [3:5] |
+------------+------------+----------------------+
| double     | 4 bytes    | sp + [6]: sp + [3:5] |
+------------+------------+----------------------+
| pointer    | 3 bytes    | sp + [3:5]           |
+------------+------------+----------------------+


Returns
~~~~~~~

This table lists which registers are used for return values.
The type's sign does not affect the registers used, but may affect the value returned.

.. note::

    | **xx**: Byte must contain valid data.
    | **??**: Byte contents don't matter.

+------------+------------+-------------------+
| C Type     | Register   | Register Contents |
+============+============+===================+
| char       | A          | xx                |
+------------+------------+-------------------+
| short      | HL         | ?? xx xx          |
+------------+------------+-------------------+
| int        | HL         | xx xx xx          |
+------------+------------+-------------------+
| long       | E:HL       | xx: xx xx xx      |
+------------+------------+-------------------+
| float      | E:HL       | xx: xx xx xx      |
+------------+------------+-------------------+
| double     | E:HL       | xx: xx xx xx      |
+------------+------------+-------------------+
| pointer    | HL         | xx xx xx          |
+------------+------------+-------------------+
