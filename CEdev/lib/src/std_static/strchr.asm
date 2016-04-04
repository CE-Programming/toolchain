; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strchr.asm"
	.assume ADL=1
	SEGMENT code

;   char *strchr(char *s,int c)
_strchr:
	ld		hl,	3
	add		hl,	sp
	ld		bc,	(hl)
	inc		hl
	inc		hl
	inc		hl
	ld		e,	(hl)	;assumed e register has not been changed by _strlen
	push	bc
	call	_strlen
	push	hl
	pop		bc
	inc		bc			;NULL terminating char also included in the search
	pop		hl
	ld		a,	e
	cpir
	dec		hl
	ret		z			;if found return HL

_notfound:
	or		a,	a
	sbc		hl,	hl
	ret


	XREF _strlen
	XDEF _strchr
	END
