.. _asm:

Assembly Files
==============

Assembly files can be linked into a C/C++ program by putting them into the same **src** directory that your C/C++ sources are in.
Use a **.S** extension if you want the compiler's preprocessor to run on the file first, or use a **.s** extension if the assembly file does not need to be preprocessed.

The use of inline assembly is supported, but highly discouraged as future changes to the compiler may render the inline assembly incompatible, and it reduces the readablity of the code.

Assembler
---------

The CE Toolchain uses the GNU Assembler (GAS) to assemble source files.
Historically the fasmg assembler was used, but is no longer supported to allow for better cross-platform support and linking performance.

Documentation for the GNU Assembler: https://www.sourceware.org/binutils/docs/as/index.html

Specific Z80/ez80 directives: https://www.sourceware.org/binutils/docs/as/Z80-Directives.html

.. _asm-assume:

Assume
^^^^^^

You should add a :code:`.assume ADL=1` before trying to emit any code, which ensures that you get 24-bit eZ80 instructions.

.. _asm-section:

Sections
^^^^^^^^

The CE Toolchain uses :code:`.section .text` for code, :code:`.section .data` for variables, and :code:`.section .rodata` for constant data.
Every time you start a new section (such as :code:`.section .text.function`), the linker has an opportunity to delete a block of dead code/data.
Because of this, the correct time to switch sections is usually every time you start a new function or variable.
To define a symbol in a block that can be referenced from other blocks, you should do :code:`.local _symbol` or :code:`.global _symbol` right before its definition.
If it is local then it is only able to be referenced from the same file and no :ref:`.extern <asm-extern>` should be used.
If it is global then it can be referenced within the same file without :ref:`.extern <asm-extern>` just like local symbols, but global symbols can also be referenced from other files and even C/C++!
The gllobal assembly symbol named :code:`_symbol` is accessible in C by the global name :code:`symbol` (note the leading underscore), assuming it is properly declared, with your asm symbol acting as the definition.

.. _asm-extern:

Extern
^^^^^^

At the end of the file is a good place to list every external symbol that you might depend on like :code:`.extern _symbol`.
This includes both global symbols defined in another assembly file and global symbols from C, prefixed with an underscore.
Block ordering can only be relied on within a single file, and only for blocks belonging to the same section.

Linking ASM routines to C/C++
-----------------------------

If an assembly function needs to be called from C, a separate header file should define a extern C global prototype.
In C this looks like a normal function or global declaration, and in C++ it's the same thing but in an :code:`extern "C" {}` block.

Below is an example C prototype followed by the assembly implementation:

:code:`asm_func.h`

.. code-block:: c

    void asm_func(int argument);

:code:`asm_func.asm`

.. code-block::

    	.assume	adl=1

    	.section	.text._asm_func
    	.global	_asm_func
    	.type	_asm_func, @function

    _asm_func:
    	pop	hl
    	pop	de
    	push	de	; de = arg
    	push	hl
    
    	push	de
    	call	_external_func
    	pop	de
    
    	ret

    	.extern	_external_func

:code:`asm_func.c`

.. code-block::

    int external_func(int arg)
    {
        printf("external_func called with %d\n", arg);
        return 4321;
    }
    
    void test(void)
    {
        int arg = 1234;
        printf("calling asm_func with %d\n", arg);
        int ret = asm_func(arg);
        printf("asm_func returned %d\n", ret);
    }

ABI Arguments
^^^^^^^^^^^^^

Arguments are pushed from last to first corresponding to the C prototype.
In eZ80, 3 bytes are always pushed to the stack regardless of the actual size.
However, the assembly function must be careful to only use the valid bytes that are pushed.
For example, if a *short* type is used, the upper byte of the value pushed on the stack will contain arbitrary data.
This table lists the locations relative to *sp* from within the called funciton.
Note that :code:`sp + [0,2]` contains the return address.

Assembly routines must preserve the :code:`IX` and :code:`SP` registers.
All other registers are free for use.

+-------------+------------+----------------------+
| C/C++ Type  | Size       | Stack Location       |
+=============+============+======================+
| char        | 1 byte     | sp + [3]             |
+-------------+------------+----------------------+
| short       | 2 bytes    | sp + [3,4]           |
+-------------+------------+----------------------+
| int         | 3 bytes    | sp + [3,5]           |
+-------------+------------+----------------------+
| long        | 4 bytes    | sp + [3,6]           |
+-------------+------------+----------------------+
| (u)int48_t  | 6 bytes    | sp + [3,8]           |
+-------------+------------+----------------------+
| long long   | 8 bytes    | sp + [3,10]          |
+-------------+------------+----------------------+
| float       | 4 bytes    | sp + [3,6]           |
+-------------+------------+----------------------+
| double      | 4 bytes    | sp + [3,6]           |
+-------------+------------+----------------------+
| long double | 8 bytes    | sp + [3,10]          |
+-------------+------------+----------------------+
| pointer     | 3 bytes    | sp + [3,5]           |
+-------------+------------+----------------------+

ABI Returns
^^^^^^^^^^^

This table lists which registers are used for return values from a function.
The type's sign does not affect the registers used, but may affect the value returned.
The LSB is located in the register on the far right of the expression, e.g. ``E:HL`` indicates register ``L`` stores the LSB.

+-------------+-------------------+
| C/C++ Type  | Return Register   |
+=============+===================+
| char        | A                 |
+-------------+-------------------+
| short       | HL                |
+-------------+-------------------+
| int         | UHL               |
+-------------+-------------------+
| long        | E:UHL             |
+-------------+-------------------+
| (u)int48_t  | UDE:UHL           |
+-------------+-------------------+
| long long   | BC:UDE:UHL        |
+-------------+-------------------+
| float       | E:UHL             |
+-------------+-------------------+
| double      | E:UHL             |
+-------------+-------------------+
| long double | BC:UDE:UHL        |
+-------------+-------------------+
| pointer     | UHL               |
+-------------+-------------------+
