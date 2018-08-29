## LibLoad Setup

Libraries are contained within a single appvar, and consist of 4 main sections: the header, the functions, any dependencies, and finally the code itself.

## The Header

A header begins with 2 idendifying bytes:

```asm
$C0,$C0
```

This simply lets us know that the following data is a valid library.

These bytes are then followed by the library version byte; for example, this would represent version 4:

```asm
$04
```

## The Functions

Functions are also stored in the library binary as entries in a vector table. A sample vector table looks like this:

(Note that assembled code is on the left, while the original file is shown on the right)

```asm
0F 00 00 -   export _function_1_label
1D 00 00 -   export _function_2_label
```

The preceding bytes simply represent the offset in the library where the function is located.

## Dependencies

This is where it gets kind of fun. Since dependencies are a part of the library in order to have an address to jump to, dependencies are simply the outputted jump table when assembling a library.

A sample library with a single dependency on LIB1 will look like this:

```asm
C0 4C 49 42
31 00 -  -   db 0C0h,"LIB1",0
01 -  -  -   db 1
-  -  -  -  _function_1:
C3 00 00 00  jp 0
-  -  -  -  _function_2:
C3 03 00 00  jp 3
```

**Important note:** Dependencies are also considered code. Thus, function offsets are calculated from the start of the dependency table, **not** the end of it.

## The Code

The code of the library is simply whatever the developer decides to add to the library. Some examples include file I/O, and many other things.

## Relocation

When the assembler encounters a relative location, the address is stored in the relocation table, which is then placed after the code section.

After the relocation information is two special data words: one which holds an offset pointer to the start of the dependency table, and one that holds the size of the library if it were to be extraceted to RAM.

This size consists of the dependencies & code portions; no header, functions, or anything else is included in calculations.

## LibLoad Process

The process taken by LibLoad is briefly summarized in the following flowchart:

(For a more detailed description, continue reading below)

![LibLoad](flowchart.png "Absoulte madness")

## The Launcher

The launcher portion of code is simply a routine that exists within the program that can jump to the first byte of the LibLoad appvar. During this process, LibLoad assumes control over the executing program in order to run its own code.

Here is an example of such launcher code:

```asm
__libloadlauncher:
	ld	hl,__libloadappvar
	call	_Mov9ToOP1
	ld	a,21
	ld	(OP1),a
__findlibload:
	call	_ChkFindSym
	jp	c,__notfound
	call	_ChkInRam
	jp	nz,__inarc
	call	_PushOP1
	call	_Arc_Unarc
	call	_PopOP1
	jr	__findlibload
__inarc:
	ex	de,hl
	ld	de,9
	add 	hl,de
	ld	e,(hl)
	add	hl,de
	inc	hl
	inc	hl
	inc	hl
	ld	de,__relocationstart
	jp	(hl)
__notfound:
	call	_ClrScrn
	call	_HomeUp
	ld	hl,__missingappvar
	call	_PutS
	call	_NewLine
	jp	_GetKey
__relocationstart:
; place library jump locations and headers here
;...

;
; PROGRAM CODE GOES HERE ->
;

; data segments
__missingappvar:
	db	"Need"
__libloadappvar:
	db	" LibLoad",0
```
