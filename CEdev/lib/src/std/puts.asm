; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
	FILE	".\puts.asm"
	.ASSUME	ADL=1
	SEGMENT CODE

; puts - put a string to stdout
;
; Inputs:
;	string - address of string
;
; Returns:
;	Non-zero if an error occurs, else zero

;int puts(char *str) 
_puts:
	ld		hl,	3
	add		hl,	sp
	ld		hl,	(hl)
	push	hl				;ptr

_loop:
	pop		hl				;ptr
	ld		a,	(hl)
	or		a,	a
	jr		z,	_done
	inc		hl
	push	hl				;ptr++
	ld		b,	a
	or		a,	a
	sbc		hl,	hl
	ld		l,	b
	push	hl				;hl = char to write
	call	_putch
	pop		hl
	jr		_loop

_done:
	ld		hl,	%a
	push	hl
	call	_putch			;putch('\n')
	ld		hl,	%d
	push	hl
	call	_putch			;putch('\r')
	pop		hl
	pop		hl
	or		a,	a
	sbc		hl,	hl			;return 0
	ret


	XREF _putch:ROM
	XDEF _puts
