; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long AND.
; Input:
;	Operand1: 
;		  ehl : 32 bit
;
;	Operand2: 
;		  abc : 32 bit
;
; Output:
;	Result:   ehl : 32 bit
; Registers Used:

;-------------------------------------------------------------------------
	.def __land
	.assume adl=1

__land		equ 0001A4h
