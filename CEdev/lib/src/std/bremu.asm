; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Unsigned Byte Modulus
; Input:
;	Operand1: 
;                 A : 8 bit dividend (numerator)
;
;	Operand2: 
;                 C : 8 bit divisor (denominator)
;
; Output:
;	Result:   A : 8 bit modulus
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def	__bremu
	.assume adl=1

__bremu:
	push	bc
	push	hl
	ld	h,a
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
	pop	hl
	pop	bc
	ret

