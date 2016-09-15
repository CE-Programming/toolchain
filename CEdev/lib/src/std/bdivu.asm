; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Unsigned Byte Division. 
; Input:
;	Operand1: 
;		  B : 8 bit dividend (numerator x)
;
;	Operand2: 
;		  C : 8 bit divisor (denominator y)
;
; Output:
;	Result:   A : 8 bit quotient
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def	__bdivu
	.assume adl=1
__bdivu:
	push	bc
	push	hl
	ld	h,b
	xor	a,a
	ld	b,8		;i = 8 (bit counter)
loop:
	sla	h
	rla
	jr	c,over
	cp	a,c
	jr	c,under
over:
	sub	a,c
	inc	h
under:
	djnz	loop
	;;
	;; Quotient in h
	;; Remainder in a
	;;
	ld	a,h
	pop	hl
	pop	bc
	ret

