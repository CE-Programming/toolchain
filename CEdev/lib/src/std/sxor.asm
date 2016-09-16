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
	.def __sxor
	.assume adl=1

__sxor		equ 000268h
