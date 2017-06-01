; Created by Matt "MateoConLechuga" Waltz

	ifndef STARTUP_MODULE
	define STARTUP_MODULE
;-------------------------------------------------------------------------------
; Standard CE startup module definitions and references
;-------------------------------------------------------------------------------
	.assume	adl=1

	.ref	_main
	.ref	__low_bss

	.def	_errno
	.def	_init
	.def	_exit
	.def	__errsp

	define	.header,space=ram
	define	.launcher,space=ram
	define	.libs,space=ram
	define	.exit,space=ram
	define	.startup,space=ram

_errno  equ 0D008DCh

;-------------------------------------------------------------------------------
; Standard CE startup module code
;-------------------------------------------------------------------------------
	segment .header
	db	239
	db	123
	db	0		; Magic byte recognition for C programs
_init:

;-------------------------------------------------------------------------------
	segment .startup

	.def	__exit

	call	0020848h	; _RunInicOff, assumes iy=flags
	di
	ld	hl,__low_bss
	ld	bc,010DE2h      ; maximum size of BSS+Heap
	call	00210DCh        ; _MemClear, handles __low_bss of 0 which is nice
	push	iy
	ld	hl,0E00005h
	push	hl
	ld	a,(hl)
	push	af
	ld	(hl),3          ; reduce flash wait states (because of rtl)
	call	0004F4h         ; usb_DisableTimers
	ld	(__errsp+1),sp  ; save the stack from death
	call	_main
__exit:
__errsp:
	ld	sp,0
	pop	af
	pop	de
	ld	(de),a          ; restore flash wait states
	pop	iy              ; restore iy for OS
	push	hl		; exit code
	call	0004F0h         ; usb_ResetTimers

;-------------------------------------------------------------------------------
	segment .exit

	.ref	__exit

	pop	hl              ; exit code
	ret

_exit:
	pop	hl
	pop	hl
	jr	__exit

;-------------------------------------------------------------------------------
	segment code
;-------------------------------------------------------------------------------
; End Standard Startup Module
;-------------------------------------------------------------------------------

	endif
	end

