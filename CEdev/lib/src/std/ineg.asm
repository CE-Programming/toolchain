; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer/short NEG.
; Input:
;	Operand1: 
;		  hl : 24/16 bit
;
; Output:
;	Result:   hl : 24/16 bit ( 0 - hl)
; Registers Used:
;	a,de
;-------------------------------------------------------------------------
	.assume adl=1
	 
	.def	__ineg,__sneg

__ineg         equ 000160h
__sneg         equ 00022Ch