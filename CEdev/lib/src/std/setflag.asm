; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Set Sign flag for signed comparison
;	s <-- s xor v
; Input:
;	Operand1: f register
;
; Output:
;	Result:  updated f register
;
; Registers Used:
;	None
;-------------------------------------------------------------------------
;	if ( V == 0)
;		S = S xor 0 -> S = S
;	if ( V != 0)
;		S = S xor V
;-------------------------------------------------------------------------
	.def __setflag
	.assume adl=1

__setflag	equ 000218h
