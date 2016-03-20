;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Negate.
;
; INPUTS:
;		AuBC:	32-bit IEEE Single Precision.
;
; OUTPUTS:
;		AuBC:	32-bit IEEE Single Precision.
;
;--------------------------------------------------------------
	segment	CODE
	
	.assume adl=1
	.def	__fneg
	
__fneg         equ 00028Ch
	
	end

