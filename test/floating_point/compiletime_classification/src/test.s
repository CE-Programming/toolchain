	.assume	adl = 1

	.section	.text

; if a function call is emitted (hence not constant folded), it will conflict with one of these functions

	.global	__fpclassifyf
	.global	__fpclassifyl
	.global	__issignalingf
	.global	__isnanf
	.global	__isinff
	.global	__isfinitef
	.global	__isnormalf
	.global	__issubnormalf
	.global	__iszerof
	.global	__issignalingl
	.global	__isnanl
	.global	__isinfl
	.global	__isfinitel
	.global	__isnormall
	.global	__issubnormall
	.global	__iszerol
	.global	__signbitf
	.global	__signbitl

__fpclassifyf:
__fpclassifyl:
__issignalingf:
__isnanf:
__isinff:
__isfinitef:
__isnormalf:
__issubnormalf:
__iszerof:
__issignalingl:
__isnanl:
__isinfl:
__isfinitel:
__isnormall:
__issubnormall:
__iszerol:
__signbitf:
__signbitl:
	ret
