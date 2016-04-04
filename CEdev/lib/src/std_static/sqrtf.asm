;--------------------------------------------------------------
;
;	  	IEEE Single precision square root
;		Copyright 2003-2008 Zilog, Inc.
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
; INPUTS:
;	Operand1: 
;		  (stack) : 32 bit IEEE format
;
; OUTPUTS:
;	Result: 
;		  EuHL : 32 bit IEEE format result
;
; ALGORITHM:
;	This algorithm is very similar to that used for binary
;	division;  readers should be familiar with that
;	algorithm of repetitive compare/subtract, and shift.
;	This algorithm uses the same concepts, except that the
;	number compared/subtracted is 2*x+1, where 'x' is the
;	developing result.  Briefly, if 'y' is the input parameter,
;	and 'x' is the result developed (and subtracted out) so
;	far, then 'y - x^2' is the residual value.  If the residual
;	is greater than '2*x + 1', then we subtract that out,
;	and add one to x;  this means that the new residual is
;	'y - (x+1)^2'.  Repetitively applied with shifting, 'x^2'
;	approaches the value of 'y'.
;
; Registers Used:
;	AF,BC,D
;
;--------------------------------------------------------------

	segment	code

	.assume adl=1
	.ref	__fpupop1, __fppack
	.def	_sqrtf

_sqrtf:
	push	ix
	ld	ix,0
	add	ix,sp
	ld	bc,(ix+6)	;get argument
	ld	a,(ix+9)
	call	__fpupop1	;unpack argument
	jr	z,exit1

	push	bc
	pop	ix		;get mantissa
	ld	hl,0		;initialize high-order mantissa
	srl	a		;compute new exponent
	jr	c,nadjust	;skip if old exponent was odd

	add	ix,ix		;adjust argument
	adc	hl,hl
nadjust:
	adc	a,63		;normalize exponent
	ld	c,a		;save exponent
	add	ix,ix		;shift argument left
	adc	hl,hl
	dec	hl		;subtract initial root
	ld	a,0		;initialize overflow
	ld	de,1		;initialize result
	ld	b,23		;set loop count
loop1:
	ex	de,hl
	add	hl,hl		;shift result left
	ex	de,hl
	add	ix,ix		;shift argument left
	adc	hl,hl
	rla			;catch overflow
	add	ix,ix		;shift argument left
	adc	hl,hl
	rla			;catch overflow
	sbc	hl,de		;result exceeds residual ?
	sbc	a,0
	jr	c,under		;no, skip

	inc	de		;add in possible result bit
	sbc	hl,de		;result exceeds residual ?
	sbc	a,0
	jr	nc,common	;yes, skip

	add	hl,de		;reverse 2nd subtract
	adc	a,0
	dec	de		;remove result bit
under:
	add	hl,de		;reverse 1st subtract
	adc	a,0
common:	
	djnz	loop1

	or	a,a		;clear carry
	sbc	hl,de		;result exceeds residual ?
	sbc	a,0		;carry = 0 if rounding
	sbc	hl,hl		;0 if no carry, else -1
	inc	hl		;1 if rounding, else 0
	ld	a,0		;initialize overflow
	add	hl,de		;add rounding
	adc	a,0
	ld	e,c		;get exponent
	ld	d,0		;set sign positive
	push	hl
	pop	bc
exit1:
	call	__fppack
	push	bc
	pop	hl
	ld	e,a
	pop	ix
	ret

