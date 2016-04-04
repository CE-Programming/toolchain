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
	segment	CODE
	.assume adl=1
	.def	__fsub
	.ref	__fadd

__fsub:
	push	af
	ld	a,e
	xor	a,80H	 	;Change op2 sign.
	ld	e,a
	pop	af
	call	__fadd		;Add the two.
	push	af
	ld	a,e
	xor	a,80H	 	;restore op2 sign.
	ld	e,a
	pop	af
	ret	

