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
	.def __lneg
	.assume adl=1
	
__lneg		equ 0001D0h
