; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long ADD.
; Input:
;	Operand1: 
;                 ehl : 32 bit
;
;	Operand2: 
;                 abc : 32 bit
;
; Output:
;	Result:   ehl : 32 bit
; Registers Used:

;-------------------------------------------------------------------------
	.def __ladd, __ladd_b
	.assume adl=1

__ladd_b       equ 0001A0h
__ladd         equ 00019Ch
