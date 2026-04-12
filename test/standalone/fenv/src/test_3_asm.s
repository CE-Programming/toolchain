	.assume	adl=1

	.section	.text

	.global	_test_3_asm
	.type	_test_3_asm, @function

; int test_3_asm(void)
_test_3_asm:
	ld	hl, -3
	call	__frameset

	; preserve current rounding mode
	call	_fegetround
	ld	(ix - 3), hl

	; compare it to the real deal
	ld	a, (___fe_cur_env)
	cp	a, l
	jr	nz, .L.fail_1

	; set a new and different rounding mode
	ld	a, l
	xor	a, 1
	ld	l, a
	push	hl
	call	_fesetround
	pop	bc

	; return value should be zero
	add	hl, bc
	or	a, a
	sbc	hl, bc
	jr	nz, .L.fail_2

	; see if changes were made correctly
	call	_fegetround
	ld	bc, (ix - 3)
	ld	a, c
	xor	a, 1
	ld	c, a

	or	a, a
	sbc	hl, bc
	add	hl, bc
	jr	nz, .L.fail_3

	; restore current rounding mode
	ld	a, (ix - 3)
	ld	(___fe_cur_env), a

	; passed tests
	ld	hl, 0
.L.finish:
	ld	sp, ix
	pop	ix
	ret

.L.fail_1:
	ld	hl, 1000
	jr	.L.finish

.L.fail_2:
	ld	hl, 2000
	jr	.L.finish

.L.fail_3:
	ld	hl, 3000
	jr	.L.finish

	.extern	__frameset
	.extern	__fe_cur_env
	.extern	_fegetround
	.extern	_fesetround
