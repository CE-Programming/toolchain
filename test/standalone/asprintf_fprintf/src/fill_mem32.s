	.assume	adl = 1

	.section	.text

	.global	_fill_mem32

; void fill_mem32(void *dst, size_t bytes, uint32_t pattern)
_fill_mem32:
	ld	iy, 0
	add	iy, sp
	ld	de, (iy + 3)
	ld	hl, (iy + 6)
	ld	bc, 4
	sbc	hl, bc
	; return if bytes <= pattern_size
	ret	c
	ret	z
	push	hl
	; copy pattern once
	lea	hl, iy + 9
	ldir
	pop	bc
	; now copy (bytes - pattern_size)
	ld	hl, (iy + 3)
	ldir
	ret
