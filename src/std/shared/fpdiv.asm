;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Single precision division
;
; INPUTS:
;	Operand1: 
;		  AuBC : 32 bit IEEE format
;
;	Operand2: 
;		  EuHL : 32 bit IEEE format divisor
;
; OUTPUTS:
;	Result:   AuBC : 32 bit IEEE Quotient.
; Registers Used:
;	flags
;
;--------------------------------------------------------------
	.def __fdiv
	.assume adl=1

__fdiv		equ 000278h
