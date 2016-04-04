; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strcpy.asm"
	.assume ADL=1
	SEGMENT code

;   char * strcpy(void * d, void * s)
_strcpy:
	ld		hl,	6
	add		hl,	sp
	ld		bc,	(hl)
	dec		hl
	dec		hl
	dec		hl
	ld		de,	(hl)	;assumed de has not been changed in _strlen
	push	de
	push	bc
	call	_strlen
	push	hl
	pop		bc
	inc		bc
	pop		hl
	ldir
	pop		hl
	ret

	XREF _strlen
	XDEF _strcpy
	END

