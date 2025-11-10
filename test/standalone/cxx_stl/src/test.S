	.assume	adl=1

	.section	.text

	.global	_ti_outchar

_ti_outchar:
	pop	de
	ex	(sp), hl
	push	de
	ld	iy, $d00080	; ti.flags
	ld	a, l
	cp	a, 32
	jp	nc, $207B8	; ti.PutC
	cp	a, 10
	jp	z, $0207F0	; ti.NewLine
	ret
