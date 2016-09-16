; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Unsigned Comparison
; Input:
;	Operand1: 
;		  EHL : 32 bits
;		  
;	Operand2: 
;		  ABC : 32 bits
;
; Output:
;	Result:   F : S,V flags from EHL - ABC
; Registers Used:
;	None
;-------------------------------------------------------------------------
	.def __lcmpu
	.assume adl=1

__lcmpu		equ 0001ACh
