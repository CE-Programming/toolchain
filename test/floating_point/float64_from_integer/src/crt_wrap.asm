	assume	adl=1

	section	.text

	public	_CRT_utod, _CRT_itod

_CRT_utod:
	ld	hl, 3
	add	hl, sp
	ld	hl, (hl)
	jp	__utod

_CRT_itod:
	ld	hl, 3
	add	hl, sp
	ld	hl, (hl)
	jp	__itod

	extern	__utod
	extern	__itod
