; Created by Matt "MateoConLechuga" Waltz

	ifndef STARTUP_MODULE
	define STARTUP_MODULE
;-------------------------------------------------------------------------------
; Minimized CE startup module definitions and references
;-------------------------------------------------------------------------------
	.assume	adl=1

	.ref	__low_bss
	.ref	_main

	.def	_errno
	.def	_init
	.def	_exit
	.def	__exit

	define	.header,space=ram
	define	.icon,space=ram
	define	.launcher,space=ram
	define	.libs,space=ram
	define	.startup,space=ram

_errno     equ 0D008DCh

;-------------------------------------------------------------------------------
; Standard CE startup module code
;-------------------------------------------------------------------------------
	segment .header
	db	239
	db	123
	db	0		; Magic byte recognition for C programs
_init:
	ifdef	ICON
	.ref	__program_description_end
	jp	__program_description_end
	endif
	
	segment .launcher
	segment .libs

;-------------------------------------------------------------------------------
	segment .startup

	call	0020848h	; _RunInicOff
	di
	ld	hl,__low_bss
	ld	bc,010DE2h      ; maximum size of BSS+Heap
	call	00210DCh        ; _MemClear
	push	iy
	ld	(__errsp+1),sp  ; save the stack from death
	call	_main
_exit:
__exit:
__errsp:
	ld	sp,0
	pop	iy              ; restore iy for OS
	ret
;-------------------------------------------------------------------------------
	segment code
;-------------------------------------------------------------------------------
; End Minimized Startup Module
;-------------------------------------------------------------------------------

	endif
	end
