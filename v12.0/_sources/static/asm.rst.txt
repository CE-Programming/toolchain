.. _asm:

Assembly Routines
=================

Assembly routines can be linked into a C/C++ program by putting them into the same **src** directory that your C/C++ sources are in, but with an **.asm** extension.
These can be placed in any subdirectory of **src** just like C/C++ sources.

Assembly Files
--------------

.. _asm-consts:

Constants
^^^^^^^^^

The top of the file is a good place defining constants or including other files that define constants.
These will be availabe throughout the rest of the file, but not in other files.
You can define a constant by saying :code:`my_constant := 42`.
You can include common constants in multiple files by defining them in a file named, say, **file.inc** and putting :code:`include 'file.inc'` in every file that needs them.
You should not generally put any labels, code, or data here.
If you try to reference a label defined here, you will get an :code:`Error: variable term used where not expected.` linker error which means you are trying to resolve an address that doesn't belong to any section.
See :ref:`asm-section` to fix this problem.

.. _asm-assume:

Assume
^^^^^^

You should add a :code:`assume adl=1` before trying to emit any code, which ensures that you get 24-bit eZ80 instructions.
If you end an assembly file with :code:`assume adl=0` (which is the eZ80's 16-bit Z80 compatibility mode), it will propogate to another random assembly file.
All toolchain and compiler-generated sources make sure to reset the mode at the top of the file and end the file in the same mode, but if one of your sources end in Z80 mode, then any other one of your sources might begin in Z80 mode, so it is safer to put the :code:`assume` line in every file.

.. _asm-section:

Section
^^^^^^^

Now that we are in the correct mode, we need to tell the linker where to put things.
We use :code:`section .text` for code, :code:`section .data` for variables, and :code:`section .rodata` for constant data.
Currently these are all placed in RAM, so which section you choose to switch to is much less important than how often you switch sections, even if you are switching to the same section you are already in.
This is because every time you start a new, or restart the same, section, the linker gets a new opportunity to delete a block of dead code/data.
Because of this, the correct time to switch sections is usually every time you start a new function or variable.
You should not let execution fall off the end of a block because you won't know if that block will be included or deleted from the output, however you can if you say :code:`require _symbol` of some public or private symbol defined in the next section to ensure that if the current block is included, then that will force the next block to also be included.
To define a symbol in a block that can be referenced from other blocks, you should do :code:`private _symbol` or :code:`public _symbol` right before its definition.
If it is private then it is only able to be referenced from the same file and no :ref:`extern <asm-extern>` should be used.
If it is public then it can be referenced within the same file without :ref:`extern <asm-extern>` just like private symbols, but public symbols can also be referenced from other files and even C/C++!
The public assembly symbol named :code:`_symbol` is accessible in C by the global name :code:`symbol`, assuming it is properly declared, with your asm symbol acting as the definition.

.. _asm-extern:

Extern
^^^^^^

At the end of the file is a good place to list every external symbol that you might depend on like :code:`extern _symbol`.
This includes both public symbols defined in another assembly file and global symbols from C, prefixed with an underscore like usual.
Lastly, you should not let execution fall off the end of a file because the next file that gets assembled is unpredictable and you could end up anywhere!
Block ordering can only be relied on within a single file, and only for blocks belonging to the same section.

Linking ASM routines to C/C++
-----------------------------

If an assembly function needs to be called from C, a separate header file should define a extern C global prototype.
In C this looks like a normal function or global declaration, and in C++ it's the same thing but in an :code:`extern "C" {}` block.

Below is an example C prototype followed by the assembly implementation:

:code:`asm_func.h`

.. code-block:: c

    void asm_func(int arg);

:code:`asm_func.asm`

.. code-block::

    	assume	adl=1
    
    	section	.text
    
    	public	_asm_func
    _asm_func:
    	pop	hl
    	pop	de
    	push	de	; de = arg
    	push	hl
    
    	push	de
    	call	_external_func
    	pop	de
    
    	ret
    
    	extern	_external_func

:code:`asm_func.c`

.. code-block::

    int external_func(int arg) {
        printf("external_func called with %d\n", arg);
        return 4321;
    }
    
    void test() {
        int arg = 1234;
        printf("calling asm_func with %d\n", arg);
        int ret = asm_func(arg);
        printf("asm_func returned %d\n", ret);
    }

Preserve
^^^^^^^^

Assembly routines must preserve the :code:`IX` and :code:`SP` registers.
All other registers are free for use.

Arguments
^^^^^^^^^

Arguments are pushed from last to first corresponding to the C prototype.
In eZ80, 3 bytes are always pushed to the stack regardless of the actual size.
However, the assembly function must be careful to only use the valid bytes that are pushed.
For example, if a *short* type is used, the upper byte of the value pushed on the stack will contain arbitrary data.
This table lists the locations relative to *sp* from within the called funciton.
Note that :code:`sp + [0,2]` contains the return address.

+------------+------------+----------------------+
| C/C++ Type | Size       | Stack Location       |
+============+============+======================+
| char       | 1 byte     | sp + [3]             |
+------------+------------+----------------------+
| short      | 2 bytes    | sp + [3,4]           |
+------------+------------+----------------------+
| int        | 3 bytes    | sp + [3,5]           |
+------------+------------+----------------------+
| long       | 4 bytes    | sp + [3,6]           |
+------------+------------+----------------------+
| (u)int48_t | 6 bytes    | sp + [3,8]           |
+------------+------------+----------------------+
| long long  | 8 bytes    | sp + [3,10]          |
+------------+------------+----------------------+
| float      | 4 bytes    | sp + [3,6]           |
+------------+------------+----------------------+
| double     | 4 bytes    | sp + [3,6]           |
+------------+------------+----------------------+
| pointer    | 3 bytes    | sp + [3,5]           |
+------------+------------+----------------------+

Returns
^^^^^^^

This table lists which registers are used for return values from a function.
The type's sign does not affect the registers used, but may affect the value returned.
The LSB is located in the register on the far right of the expression, e.g. ``E:HL`` indicates register ``L`` stores the LSB.

+------------+-------------------+
| C/C++ Type | Return Register   |
+============+===================+
| char       | A                 |
+------------+-------------------+
| short      | HL                |
+------------+-------------------+
| int        | UHL               |
+------------+-------------------+
| long       | E:UHL             |
+------------+-------------------+
| (u)int48_t | UDE:UHL           |
+------------+-------------------+
| long long  | BC:UDE:UHL        |
+------------+-------------------+
| float      | E:UHL             |
+------------+-------------------+
| double     | E:UHL             |
+------------+-------------------+
| pointer    | UHL               |
+------------+-------------------+
