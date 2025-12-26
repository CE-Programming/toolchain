	.assume	adl=1

	.section	.text

	.global	_T_CMPLXF, _T_CMPLX, _T_CMPLXL
	.global	_T_creal, _T_crealf, _T_creall
	.global	_T_cimag, _T_cimagf, _T_cimagl
	.global	_T_conj, _T_conjf, _T_conjl

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

	.extern	_CMPLXF, _CMPLX, _CMPLXL
	.extern	_creal, _crealf, _creall
	.extern	_cimag, _cimagf, _cimagl
	.extern	_conj, _conjf, _conjl
