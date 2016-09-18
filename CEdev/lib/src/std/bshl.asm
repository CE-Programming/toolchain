; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Byte Shift Left
; Input:
;	Operand1: 
;                 A : 8 bit number to shift
;	Operand2: 
;                 B : 8 bit shift count
;
; Output:
;       Result:   A : 8 bit 
; Registers Used:
;       flags
;-------------------------------------------------------------------------
	.def __bshl
	.assume adl=1

__bshl		equ 000100h
