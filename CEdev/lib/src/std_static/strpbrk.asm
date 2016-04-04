; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strpbrk.asm"
	.ASSUME ADL=1
	SEGMENT code
;   char *strpbrk(char *s1,char *s2)
_strpbrk:
	ld	iy, 0
	add iy, sp
	ld  bc, (iy+6)
	push bc
	call _strlen
	ex	(sp), hl		; (iy-3) = strlen(s2)	

	ld	de, (iy+3)		; de = s1

_wloop:
	ld	a, (de)
	or	a, a
	jr	z, _notfound
	ld	hl, (iy+6)
	ld	bc, (iy-3)
	cpir
	inc de
	jr	nz, _wloop

_found:
	ex  de, hl
	dec hl
	jr 	_done

_notfound:
	ld 	hl, 0

_done:
	ld	sp, iy
	ret

	XREF _strchr:ROM
	XREF _strlen
	XDEF _strpbrk
	END

