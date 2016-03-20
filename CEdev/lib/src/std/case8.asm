; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; CASE branch resolution.
;
; Input:
;	Operand3: 
;		  hl : 24 bit value to match in table
; 
; Output:
;
; Registers Used:
; 
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__case8

__case8        equ 000124h

