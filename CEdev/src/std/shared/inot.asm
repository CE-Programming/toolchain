; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer/Short NOT.
; Input:
;	Operand1: 
;		  hl : 24/16 bit
;
; Output:
;	Result:   hl : 24/16 bit
; Registers Used:
;-------------------------------------------------------------------------
	.def __inot,__snot
	.assume adl=1

__inot         equ 000164h
__snot         equ 000230h
