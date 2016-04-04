; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer/short NEG.
; Input:
;	Operand1: 
;		  hl : 24/16 bit
;
; Output:
;	Result:   hl : 24/16 bit ( 0 - hl)
; Registers Used:
;	a,de
;-------------------------------------------------------------------------
	.assume adl=1
	 
	.def	__ineg
	.def	__sneg

__ineg:
__sneg:
	push	de
	ex	de,hl
	or	a,a
	sbc	hl,hl
	sbc	hl,de
	pop	de
	ret	
