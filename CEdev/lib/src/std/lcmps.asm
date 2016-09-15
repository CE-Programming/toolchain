; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Comparison
; Input:
;	Operand1: 
;                 EHL : 32 bits
;		  
;	Operand2: 
;                 ABC : 32 bits
;
; Output:
;	Result:   F : S,V flags from EHL - ABC
; Registers Used:
;	None
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__lcmps

__lcmps        equ 0001A8h
