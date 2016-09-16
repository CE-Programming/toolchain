; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long NOT.
; Input:
;	Operand1: 
;		  eHL : 32 bit
;
; Output:
;	Result:   eHL : 32 bit
; Registers Used:
;	None
;-------------------------------------------------------------------------
	.def __lnot
	.assume adl=1

__lnot		equ 0001D4h
