	assume	adl = 1

	section	.text

; if a function call is emitted (hence not constant folded), it will conflict with one of these functions

	public	__fpclassifyf
	public	__fpclassifyl
	public	__issignalingf
	public	__isnanf
	public	__isinff
	public	__isfinitef
	public	__isnormalf
	public	__issubnormalf
	public	__iszerof
	public	__issignalingl
	public	__isnanl
	public	__isinfl
	public	__isfinitel
	public	__isnormall
	public	__issubnormall
	public	__iszerol
	public	__signbitf
	public	__signbitl

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
