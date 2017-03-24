	.def	_isascii
	.assume adl=1
	
; original source
; int isascii(int c) {
; 	return c >= 0 && c < 128;
; }

_isascii:
	pop	de
	pop	hl
	push	hl
	push	de
	
	ld	de,-128
	add	hl,de
	sbc	hl,hl
	inc	hl
	ret
