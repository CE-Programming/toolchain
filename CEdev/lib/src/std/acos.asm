	.ref __frameset0
	.ref __fcmp
	.ref __fsub
	.ref _asin
	.ref _errno
	.def _acos
	.assume adl=1
	
; #define pio2  1.57079632679490
;
; double acos(double arg) {
; 	if((arg > 1.) || (arg < -1.)) {
; 		errno = EDOM;
; 		return(0.);
; 	}
; 	return(pio2 - asin(arg));
; }

_acos:
	call	__frameset0
	ld	hl,8388608
	ld	e,63
	ld	bc,(ix+6)
	ld	a,(ix+9)
	push	bc
	push	hl
	call	__fcmp
	pop	bc
	pop	hl
	jp	m,l_1
	ld	e,(ix+9)
	ld	a,191
	call	__fcmp
	jp	p,l_2

l_1:	ld	bc,4
	ld	(_errno),bc
	xor	a,a
	sbc	hl,hl
	jr	l_3

l_2:	ld	c,(ix+9)
	ld	b,0
	push	bc
	ld	bc,(ix+6)
	push	bc
	call	_asin
	ld	sp,ix
	ld	bc,13176795
	ld	a,63
	call	__fsub
	ld	hl,bc

l_3:	ld	e,a
	pop	ix
	ret
