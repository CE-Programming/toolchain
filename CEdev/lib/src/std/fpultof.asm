;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	Unsigned long to IEEE Single precision.
;
; INPUTS:
;		abc:	32-bit unsigned long
;
; OUTPUTS:
;		abc:	IEEE Single precision.
;
;--------------------------------------------------------------
	.def __ultof
	.assume	adl=1

__ultof		equ 000280h
