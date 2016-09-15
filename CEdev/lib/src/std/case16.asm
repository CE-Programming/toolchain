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
	.def	__case16

__case16       equ 000114h

