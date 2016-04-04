; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long NEG.
; Input:
;	Operand1: 
;		  EuHL : 32 bit
;
; Output:
;	Result:   EuHL : 32 bit
; Registers Used:
;	flags
;-------------------------------------------------------------------------
	.assume adl=1
	 
	.def	__lneg
__lneg:
	push	af
	push	de
	ex	de,hl
	xor	a,a
	sbc	hl,hl
	sbc	hl,de
	pop	de
	sbc	a,e
	ld	e,a
	pop	af
	ret

