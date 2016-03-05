; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Signed Byte Modulus
; Input:
;	Operand1: 
;		  A : 8 bit dividend (numerator)
;
;	Operand2: 
;		  C : 8 bit divisor (denominator)
;
; Output:
;	Result:   A : 8 bit modulus
; Registers Used:
;	
;-------------------------------------------------------------------------
	.def	_memset_fast
	.assume adl=1

_memset_fast:
	push	ix
	ld	ix,6
	add	ix,sp
	ld	de,(ix)
	ld	hl,(ix)
	ld	bc,(ix+06)
	ld	a,(ix+03)
	inc	de
	ld	(hl),a
	ldir
	ld	hl,(ix)
	pop	ix
	ret