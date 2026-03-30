	.assume	adl=1

	.section	.text

	.global	_T_CMPLXF
	.type	_T_CMPLXF, @function
	.global	_T_CMPLX
	.type	_T_CMPLX, @function
	.global	_T_CMPLXL
	.type	_T_CMPLXL, @function

	.global	_T_creal
	.type	_T_creal, @function
	.global	_T_crealf
	.type	_T_crealf, @function
	.global	_T_creall
	.type	_T_creall, @function

	.global	_T_cimag
	.type	_T_cimag, @function
	.global	_T_cimagf
	.type	_T_cimagf, @function
	.global	_T_cimagl
	.type	_T_cimagl, @function

	.global	_T_conj
	.type	_T_conj, @function
	.global	_T_conjf
	.type	_T_conjf, @function
	.global	_T_conjl
	.type	_T_conjl, @function

	.global	_T__addsc3
	.type	_T__addsc3, @function
	.global	_T__subsc3
	.type	_T__subsc3, @function
	.global	_T__mulsc3
	.type	_T__mulsc3, @function
	.global	_T__divsc3
	.type	_T__divsc3, @function

	.global	_T__adddc3
	.type	_T__adddc3, @function
	.global	_T__subdc3
	.type	_T__subdc3, @function
	.global	_T__muldc3
	.type	_T__muldc3, @function
	.global	_T__divdc3
	.type	_T__divdc3, @function

_T_CMPLXF:
	jp	_CMPLXF
_T_CMPLX:
	jp	_CMPLX
_T_CMPLXL:
	jp	_CMPLXL

_T_creal:
	jp	_creal
_T_crealf:
	jp	_crealf
_T_creall:
	jp	_creall

_T_cimag:
	jp	_cimag
_T_cimagf:
	jp	_cimagf
_T_cimagl:
	jp	_cimagl

_T_conj:
	jp	_conj
_T_conjf:
	jp	_conjf
_T_conjl:
	jp	_conjl

_T__addsc3:
	jp	___addsc3
_T__subsc3:
	jp	___subsc3
_T__mulsc3:
	jp	___mulsc3
_T__divsc3:
	jp	___divsc3

_T__adddc3:
	jp	___adddc3
_T__subdc3:
	jp	___subdc3
_T__muldc3:
	jp	___muldc3
_T__divdc3:
	jp	___divdc3

	.extern	_CMPLXF
	.extern	_CMPLX
	.extern	_CMPLXL

	.extern	_creal
	.extern	_crealf
	.extern	_creall

	.extern	_cimag
	.extern	_cimagf
	.extern	_cimagl

	.extern	_conj
	.extern	_conjf
	.extern	_conjl

	.extern	___addsc3
	.extern	___subsc3
	.extern	___mulsc3
	.extern	___divsc3

	.extern	___adddc3
	.extern	___subdc3
	.extern	___muldc3
	.extern	___divdc3
