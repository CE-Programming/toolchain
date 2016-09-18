;--------------------------------------------------------------
;
;			Code Generation Helper
;		    For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Single precision sub
; Input:
;	Operand1: 
;		  abc : 32 bit IEEE single precision
;
;	Operand2: 
;		  ehl : 32 bit IEEE single precision
;
; Output:
;	Result:   abc : 32 bit IEEE single precision (abc - ehl)
; Registers Used:

;-------------------------------------------------------------------------
	.def __fsub
	.ref __fadd
	.assume adl=1

__fsub		equ 000290h
