; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; CASE branch resolution.
;
; Input:
;	Operand3: 
;		  hl : 24 bit value to match in table
; 
; Output:
;	Returns to case label
; Data at Return Address:
;	DW   numCases               0
;	DW24 startValue             2
;	DW24 Lab1                   5
;	DW24 Lab2                   8
;	...
;	DW24 defaultLab             5+3*numCases
;
; Registers Used:
; 
;-------------------------------------------------------------------------
	.def __seqcase
	.assume adl=1

__seqcase	equ 000210h