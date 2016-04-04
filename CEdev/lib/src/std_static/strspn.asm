; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strspn.asm"
	.ASSUME ADL=1
	SEGMENT code

;   size_t strspn(char *s1,char *s2)
_strspn:
	ld	iy, 0
	add iy, sp
	ld  bc, (iy+6)
	push bc
	call _strlen
	ex	(sp), hl		; (iy-3) = strlen(s2)

	ld	de, (iy+3)		; de = s1

;   	  while (*p) {
_wloop:
	ld	a, (de)
	or	a, a
	jr	z, _done
	ld	hl, (iy+6)
	ld	bc, (iy-3)
;   	    if (!strchr(s2,*p))
;   	      return(p - s1);
	cpir
;   	    ++p;
	inc de
	jr	z, _wloop
	scf

_done:
;   	  return(p - s1);
	ld	hl, (iy+3)
	ex  de, hl
	sbc	hl, de

	ld	sp, iy
	ret	

	XREF _strchr:ROM
	XREF _strlen
	XDEF _strspn
	END

