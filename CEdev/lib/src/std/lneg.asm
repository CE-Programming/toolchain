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
	
__lneg         equ 0001D0h

