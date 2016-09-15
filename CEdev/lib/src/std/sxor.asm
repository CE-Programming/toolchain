;-------------------------------------------------------------------------
; Short XOR.
; Input:
;	Operand1: 
;		  bc : 16 bit
;
;	Operand2: 
;		  hl : 16 bit
;
; Output:
;	Result:   hl : 16 bit
; Registers Used:
;	a
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__sxor

__sxor         equ 000268h
	
