; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Set flag for comparison of 32-bit scalar with constant value zero
; Input:
;	Operand1: E:HL register
;
; Output:
;	Result:  f register
;
; Registers Used:
;	None
;-------------------------------------------------------------------------
	.def __lcmpzero
	.assume adl=1

__lcmpzero	equ 0001B0h
