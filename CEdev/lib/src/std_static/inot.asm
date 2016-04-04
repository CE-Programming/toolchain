; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer/Short NOT.
; Input:
;	Operand1: 
;		  hl : 24/16 bit
;
; Output:
;	Result:   hl : 24/16 bit
; Registers Used:
;-------------------------------------------------------------------------
	.assume adl=1
	 
	.def	__inot
	.def	__snot
__inot:
__snot:
	push	de
	ex	de,hl
	scf
	sbc	hl,hl
	or	a,a
	sbc	hl,de
	pop	de
	ret

