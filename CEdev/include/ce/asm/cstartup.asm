; Created by Matt "MateoConLechuga" Waltz

	ifndef STARTUP_MODULE
	define STARTUP_MODULE
;-------------------------------------------------------------------------------
; Standard CE startup module definitions and references
;-------------------------------------------------------------------------------
	xref	__low_bss
	xref	_main
	
	xdef	_errno
	xdef	_exit
	xdef	_init
	
	.assume	ADL = 1

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
	xref	__program_description_end
	jp	__program_description_end
	endif
	
	segment .launcher
	segment .libs

;-------------------------------------------------------------------------------
	segment .startup

	di
	call	0020848h	; _RunInicOff
	ld	hl,0E00005h
	ld	a,(hl)
	ld	(__saves+1),a
	ld	(hl),2          ; reduce flash wait states (because of rtl)
	ld	hl,__low_bss
	ld	bc,010DE2h      ; maximum size of BSS+Heap
	call	00210DCh        ; _MemClear

	ld	(__errsp+1),sp
	call	_main
_exit:
	ld	hl,0E00005h
__saves:
	ld	(hl),0
__errsp:
	ld	sp,0
	ld	iy,0D00080h      ; Restore IY for OS
	ret
;-------------------------------------------------------------------------------
	segment	code
;-------------------------------------------------------------------------------
; End Standard Startup Module
;-------------------------------------------------------------------------------

	endif
	end
