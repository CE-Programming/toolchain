;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the  Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	Unpack IEEE op2 of dyadic operations.
;
; INPUTS:	EuHL:	32 bits
;
;		E EEEEEEEH HHHHHHHHHHHHHHHLLLLLLLL
;		S EEEEEEEE FFFFFFFFFFFFFFFFFFFFFFF
;		0 1      8 9                    31
; 
; OUTPUTS:	uHL:		Mantissa
;		E:		Exponent
;		D:		Sign Bit
;		ZERO FLAG	Set if op was zero.
; 
; MODIFIES:
;		flags
;--------------------------------------------------------------

	segment	code

	.def	__fpupop2
	.assume adl=1

__fpupop2:
	push	ix
	ld	ix,0
	add	ix,sp
	push	hl
	add	hl,hl		;carry = high-order bit
	set	7,(ix-1)	;set high-order bit of mantissa
	pop	hl		;restore modified mantissa
	rl	e		;compute exponent, carry = sign
	ld	d,0
	push	af
	jr	nz,nzero	;skip if exponent non-zero

	ld	hl,0		;clear mantissa
	or	a,a		;clear carry
nzero:
	rl	d		;set 1 if negative operand
	pop	af
	pop	ix
	ret

