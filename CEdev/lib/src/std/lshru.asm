; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Shift Right Unsigned
; Input:
;	Operand1: 
;                 AuBC : 32 bit value to be shifted by L
; 
;	Operand2: 
;                 L   : number of bits to shift
;
; Output:
;	Result:   AuBC : 32 bit 
; Registers Used:
;	flags
;-------------------------------------------------------------------------
	.def __lshru
	.assume adl=1

__lshru		equ 0001ECh
