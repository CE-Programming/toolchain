;--------------------------------------------------------------
;
;		Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Single precision compare.
;
; INPUTS:
;
;	Operand1: 
;		  EuHL : 32 bit IEEE format
;
;	Operand2: 
;		  AuBC : 32 bit IEEE format
;
;
; OUTPUTS:	FLAGS based on Op1 - Op2
;
;--------------------------------------------------------------
	segment	CODE
	.assume adl=1
	.def	__fcmp
	.ref	__lcmps

__fcmp:
	call	__lcmps
	jr	z,exit1		; sign doesn't matter if equal

	push	bc
	push	af
	pop	bc		; C = flags
	ld	a,b
	and	a,e
	ld	a,c		; A = flags
	jp	p,skip1		; not both negative

	xor	a,80h		; invert sign bit
skip1:
	bit	2,a		; overflow bit set ?
	jr	z,skip2		; - no, skip

	xor	a,80h		; invert sign bit
skip2:
	ld	c,a
	push	bc
	pop	af
	pop	bc
exit1:
	ret

