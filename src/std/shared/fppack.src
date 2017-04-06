;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	Pack IEEE operand of dyadic operations.
;
; INPUTS:		
;		AuBC:		2s-comp mantissa+fraction (9+23 bit)
;		E:		Exponent.
;		D:		Sign.
;
; OUTPUTS:	AuBC:		32 bit IEEE float.
; 
;		A AAAAAAB  BBBBBBBBBBBBBBCCCCCCCCC
;		S EEEEEEE  FFFFFFFFFFFFFFFFFFFFFFF
;		0 1     8  9                     31
; MODIFIES:	
;	flags
;--------------------------------------------------------------
	.def __fppack
	.assume adl=1

__fppack	equ 00026Ch
