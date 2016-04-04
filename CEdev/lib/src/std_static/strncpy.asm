; (c) Copyright 2007-2008 Zilog, Inc.

	.ASSUME ADL=1
	SEGMENT code

;   char *strncpy(char *dst,char *src,size_t n)
_strncpy:
	ld		iy, 0
	add 	iy, sp
	sbc		hl,	hl
	ld		de, (iy+9)
	adc		hl,	de
	jr		z,	_done
	ld		bc,	(iy+6)
	push 	bc
	call 	_strlen
	or		a,	a
	sbc		hl,	de
	jr		nc,	_L1
	adc		hl,	de
	ld		bc,	hl
	ex		de,	hl
	xor		a,	a
	sbc		hl,	de
	jr		z,	_L2
	ex		(sp),hl
	scf
	jr		_L3
	
_L1:
	ld		bc,	(iy+9)
_L2:	
	pop		hl
_L3:
	ld		de,	(iy+3)
	ldir
	jr		nc,	_done
	ex		de,	hl
	pop		bc
	
_loop:	
	ld		(hl),a
	cpi
	jp		pe,	_loop
	
_done:
	ld		hl, (iy+3)
	ret

	
	XREF _strlen
	XDEF _strncpy
	END

