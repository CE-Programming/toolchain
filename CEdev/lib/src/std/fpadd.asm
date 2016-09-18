;--------------------------------------------------------------
;
;			Code Generation Helper
;		    For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Single precision add
;
; INPUTS:	AuBC		OP1.
;		EuHL		OP2.
;
; OUTPUTS:	AuBC		Sum.
;
; Returns the result of adding the absolute values of the single-precision
; floating-point values OP1 and OP2.  If Sign of result is 1, the sum is
; negated before being returned.
;
;--------------------------------------------------------------
	.def __fadd
	.assume adl=1

__fadd		equ 000270h
