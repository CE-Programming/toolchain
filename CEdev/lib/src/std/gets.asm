; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
	FILE	".\gets.asm"
	.ASSUME	ADL=1
	SEGMENT CODE

; gets - get a string from stdin
;
; Inputs:
;	string - address of string
;
; Returns:
;	pointer to string or NULL

;char *gets (char *string) 
_gets:
	ld		hl,	3
	add		hl,	sp
	ld		hl,	(hl)
	push	hl				;for returning string ptr
	push	hl				;ptemp = string

_loop:
	call	_getch
	ld		a,	l
	cp		a,	%a			;linefeed character
	jr		z,	_done
	pop		hl
	ld		(hl),	a
	inc		hl
	push	hl				;*(ptemp++) = getchar()
	jr		_loop

_done:
	pop		hl
	ld		(hl), 0			;*(ptemp) = EOS
	pop		hl
	ret


	XREF _getch:ROM
	XDEF _gets
