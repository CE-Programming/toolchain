; (c) Copyright 1999-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Modulus Signed.
; Input:
;	Operand1: 
;		  EHL : 32 bits (dividend)
;
;	Operand2: 
;		  ABC : 32 bits (divisor)
;
; Output:
;	Result:   EHL : 32 bit
; Registers Used:
;	de,af
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__lrems
	.ref	__lremu, __lneg
	
__lrems        equ 0001DCh

