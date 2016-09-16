; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Shift Left
; Input:
;	Operand1: 
;                 AuBC : 32 bit value to be shifted
;
;	Operand2: 
;                 L : number of bits to shift
;
; Output:
;	Result:   AuBC : 32 bit result
; Registers Used:
;	flags
;-------------------------------------------------------------------------
	.def __lshl
	.assume adl=1

__lshl		equ 0001E4h
