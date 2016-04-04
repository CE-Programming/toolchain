; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
;-------------------------------------------------------------------------
; <string.h>
; char * strstr(char *s1, char *s2);
;-------------------------------------------------------------------------
	.assume ADL=1
	SEGMENT code
	XDEF _strstr
_strstr:
	ld 	hl, 6
	add hl, sp
	ld	iy, (hl)	; bc = s2
	dec hl
	dec hl
	dec hl
	ld  de, (hl)	; de = s1
_L0:
	xor	a,a
	sbc	hl,hl
	add	hl,de
	cp	a,(hl)
	jr	z,_L3		; *s1 == '\0'
	ld	bc,iy
	inc	de
_L1:
	ld	a,(bc)
	or	a,a
	jr	z,_L2		; *s2 == '\0'
	cp	a,(hl)		; *s1 == *s2
	inc hl			; s1 ++
	inc bc			; s2 ++
	jr	z,_L1
	jr	_L0
_L2:
	ex	de,hl
	dec hl
	ret
_L3:
	sbc	hl,hl
	ret

	END

