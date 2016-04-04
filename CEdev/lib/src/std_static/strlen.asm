; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strlen.asm"
	.assume ADL=1
	SEGMENT code

;   size_t strlen(char *s)
_strlen:
	ld	hl,	3
	add	hl,	sp
	ld	hl,	(hl)
	xor	a,	a
	ld	bc, 0
	cpir
	or	a,	a
	sbc	hl,	hl
	scf
	sbc	hl,	bc
	ret

	XDEF _strlen
	END

