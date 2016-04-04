; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short Multiply Signed/Unsigned
;	Note:	When multipying two n-bit values, the low-order n-bits
;		of the product are the same, whether or not the values
;		are considered signed or unsigned.
; Input:
;	Operand1: 
;		  BC : 16 bits
; 
;	Operand2: 
;		  HL : 16 bits
;
; Output:
;	Result:   HL : 16 bits
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__smulu,__smuls

__smuls:
__smulu:
	push	af
	push	bc
	push	de
	ld	d,b
	ld	e,l		;DE = first product operands (B,L)
	ld	b,h		;BC = second product operands (H,C)
	ld	h,c		;HL = third product operands (C,L)
	mlt	bc
	mlt	de
	mlt	hl
	ld	a,h		;get high-order product of low-order bytes
	add	a,c		;include low-order product of low/high-order bytes
	add	a,e		;ditto (ignore high-order product)
	ld	h,a		;H = total
	pop	de
	pop	bc
	pop	af
	ret

