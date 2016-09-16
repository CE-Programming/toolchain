; (c) Copyright 1999-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long OR.
; Input:
;	Operand1: 
;		 ehl  : 32 bit
;
;	Operand2: 
;		  abc : 32 bit
;
; Output:
;	Result:   ehl : 32 bit
; Registers Used:
;	
;-------------------------------------------------------------------------
	.def __lor
	.assume adl=1

__lor		equ 0001D8h
