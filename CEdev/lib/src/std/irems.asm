; (c) Copyright 1999-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer Modulus Signed.
; Input:
;	Operand1: 
;		  HL : 24 bits (dividend)
;
;	Operand2: 
;		  BC : 24 bits (divisor)
;
; Output:
;	Result:   HL : 24 bit
; Registers Used:
;	de,af
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__irems
	.ref	__iremu

__irems        equ 00016Ch

