; (c) Copyright 2001-2008 Zilog Inc.
;-------------------------------------------------------------------------
; Signed Byte Division. 
; Input:
;	Operand1: 
;		  B : 8 bit dividend (numerator)
;
;	Operand2: 
;		  C : 8 bit divisor (denominator)
;
; Output:
;	Result:   A : 8 bit quotient
; Registers Used:
;	d, e
;-------------------------------------------------------------------------
	.def	__bdivs
	.ref	__bdivu
	.assume adl=1

__bdivs:
	push	bc
	;;
	;; Check the sign
	;; 
	xor	a,a
	sub a,b
	jp m,_L0
	ld b,a
_L0:
	xor	a,a
	sub a,c
	jp m,_L1
	ld c,a
_L1:

	call	__bdivu
	;;
	;; Check the sign of the quotient
	;; 
	pop	bc
	push hl
	ld	l,a
	ld	a,b
	xor	a,c
	ld	a,l
	jp	p,_L2
	neg
_L2:
	pop	hl

	ret	

