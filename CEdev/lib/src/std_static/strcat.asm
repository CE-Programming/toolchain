; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strcat.asm"
	.assume ADL=1
	SEGMENT code
;   char *strcat(char *s1,char *s2)
_strcat:
	ld		hl,	3
	add		hl,	sp
	ld		bc,	(hl)
	push	bc				;store s1
	inc		hl
	inc		hl
	inc		hl
	ld		de,	(hl)
	ld		a,	(de)
	or		a,	a
	jr		z,	_done		;if !*s2 then done

	push	bc
	pop		hl
	xor		a,	a
_loop1:
	cpi
	jr		nz,	_loop1
	dec		hl				;hl = s1+strlen(s1)

	ex		de,	hl			;de = s1+strlen(s1) | hl = s2

	xor		a,	a
_loop2:
	cp		a,	(hl)
	jr		z,	_fillzero
	ldi
	jr		_loop2

_fillzero:
	ld		(de),	a
_done:
	pop		hl				;restore s1
	ret

	
	XREF _strlen:ROM
	XDEF _strcat
	END

