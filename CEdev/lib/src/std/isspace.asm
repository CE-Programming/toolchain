	.def	_isspace
	.ref	___maptab
	.assume adl=1

; original source
; int isspace(int c) {
; 	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(WS));
; }

_isspace:
	pop	hl
	pop	de
	push	de
	push	hl
	or	a,a
	sbc	hl,hl
	ld	a,e
	and	a,128
	ret	nz
	ex	de,hl
	ld	de,___maptab
	add	hl,de
	ld	a,(hl)
	and	a,64
	sbc	hl,hl
	ld	l,a
	ret
