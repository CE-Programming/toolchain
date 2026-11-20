.include "ti84pce.inc"

.assume adl=1

.equ LIBRARY_HEADER_SIZE, 3

; The host packer combines these sections with .text and its ELF relocations.
.macro library name, version, magic1=0xc0, magic2=0xc1
	.pushsection .libload.header
	.db \magic1, \magic2, \version, "\name", 0
	.popsection
	.text
.Llibrary_base:
.endm

.macro lib_export target
	.pushsection .libload.exports
	.dw \target - .Llibrary_base
	.asciz "\target"
	.popsection
.endm

; Walk the dependency's export list in ABI order and emit the requested slots.
.macro lib_dependency name, version
	.set .Lexport_index, 0
	.db 0xc0, "\name", 0, \version
.endm

.macro lib_import target
	.ifdef import_\target
\target:
		jp .Lexport_index * 3
	.endif
	.set .Lexport_index, .Lexport_index + 1
.endm

.macro assert test:vararg
	.if !(\test)
		.error "Assertion failed: \test"
	.endif
.endm
