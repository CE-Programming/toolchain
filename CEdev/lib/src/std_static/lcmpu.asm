; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Unsigned Comparison
; Input:
;	Operand1: 
;		  EHL : 32 bits
;		  
;	Operand2: 
;		  ABC : 32 bits
;
; Output:
;	Result:   F : S,V flags from EHL - ABC
; Registers Used:
;	None
;-------------------------------------------------------------------------

	segment	code

	.assume adl=1
	.def	__lcmpu, __lcmps

__lcmps:
__lcmpu:
        push    hl
        or      a,a             ;clear carry
        sbc     hl,bc
	ld	h,a
	ld	a,e
	jr	nz,lownz

	sbc	a,h
	ld	a,h
	jr	common
lownz:
	sbc	a,h
	ld	a,h
	push	af
	pop	hl		;L = flags
        res     6,l		;Z = 0 (meaning non-zero), all others untouched
	push	hl
	pop	af

common:
	pop	hl
	ret

