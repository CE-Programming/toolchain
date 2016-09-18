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
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	ld	a,e
	ld	hl,8388608
	ld	e,63
	push	bc
	push	hl
	call	__fcmp
	pop	bc
	pop	hl
	jp	m,l_1
	ld	e,a
	ld	a,191
	call	__fcmp
	jp	p,l_2

l_1:	ld	hl,4
	ld	(_errno),hl
	ld	l,h
	ld	e,h
	ret

l_2:	push	de
	push	hl
	call	_asin
	ld	bc,13176795
	ld	a,63
	call	__fsub
	ld	hl,bc
	ld	e,a
	ret
