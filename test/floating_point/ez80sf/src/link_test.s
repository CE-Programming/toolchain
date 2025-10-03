	assume	adl=1

;-------------------------------------------------------------------------------

	section	.text

	public	_link_test

_link_test:
	ld	hl, __fpabs
	ld	hl, __fpsub
	ld	hl, __fpadd
	ld	hl, __fpcbrt
	ld	hl, __fpcmpu
	ld	hl, __fpcmpo
	ld	hl, __fpcmp
	ld	hl, __fpcopysign
	ld	hl, __fpcopy
	ld	hl, __fpdiv
	ld	hl, __fpmin
	ld	hl, __fpmax
	ld	hl, __fpmul
	ld	hl, __fpneg
	ld	hl, __fprem
	ld	hl, __fpround
	ld	hl, __fpsqrt
	ld	hl, __fptol
	ld	hl, __fptoul
	ld	hl, __fptoll
	ld	hl, __fptoull
	ld	hl, __fpfloor
	ld	hl, __fpceil
	ld	hl, __fptrunc
	ld	hl, __fppop1
	ld	hl, __fppop2
	ld	hl, __fppack
	ld	hl, __fppack.normalize
	ld	hl, __fppack.normalized
	ld	hl, __fppack2
	ld	hl, __fppack2.normalize
	ld	hl, __fppack2.normalized
	ld	hl, __ltofp
	ld	hl, __ultofp
	ld	hl, __lltofp
	ld	hl, __ulltofp

	; ld	hl, __fptod
	; ld	hl, __dtofp

	or	a, a
	sbc	hl, hl
	ret

	extern	__fpabs
	extern	__fpsub
	extern	__fpadd
	extern	__fpcbrt
	extern	__fpcmpu
	extern	__fpcmpo
	extern	__fpcmp
	extern	__fpcopysign
	extern	__fpcopy
	extern	__fpdiv
	extern	__fpmin
	extern	__fpmax
	extern	__fpmul
	extern	__fpneg
	extern	__fprem
	extern	__fpround
	extern	__fpsqrt
	extern	__fptol
	extern	__fptoul
	extern	__fptoll
	extern	__fptoull
	extern	__fpfloor
	extern	__fpceil
	extern	__fptrunc
	extern	__fppop1
	extern	__fppop2
	extern	__fppack
	extern	__fppack.normalize
	extern	__fppack.normalized
	extern	__fppack2
	extern	__fppack2.normalize
	extern	__fppack2.normalized
	extern	__ltofp
	extern	__ultofp
	extern	__lltofp
	extern	__ulltofp

	extern	__fptod
	extern	__dtofp
