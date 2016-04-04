; (c) Copyright 2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Set flag for comparison of 16-bit scalar with constant value zero
; Input:
;	Operand1: HL register
;
; Output:
;	Result:  f register
;
; Registers Used:
;	None
;-------------------------------------------------------------------------
 
	.def	__scmpzero
	.assume adl=1

__scmpzero:
	push hl
	push de
	
	ld d,%0
	ld e,%0
	or a,a
	sbc.s hl,de
	
	pop de
	pop hl
	ret
