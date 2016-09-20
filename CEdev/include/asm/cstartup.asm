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

	call	0020848h	; _RunInicOff
	di
	ld	hl,__low_bss
	ld	bc,010DE2h      ; maximum size of BSS+Heap
	call	00210DCh        ; _MemClear
	push	iy
	ld	hl,0E00005h
	push	hl
	ld	a,(hl)
	push	af
	ld	(hl),2          ; reduce flash wait states (because of rtl)
	ld	hl,(0F20030h)   ; save timer control state
	push	hl
	ld	(__errsp+1),sp  ; save the stack from death
	call	_main
_exit:
__errsp:
	ld	sp,0
	pop	hl
	ld	(0F20030h),hl   ; restore timer control state
	pop	af
	pop	hl
	ld	(hl),a    ; restore flash wait states
	pop	iy              ; restore iy for OS
	ret
;-------------------------------------------------------------------------------
	segment	code
;-------------------------------------------------------------------------------
; End Standard Startup Module
;-------------------------------------------------------------------------------

	endif
	end
