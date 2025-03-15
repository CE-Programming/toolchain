	assume	adl=1

	section	.text

	public	_T_CMPLXF, _T_CMPLX, _T_CMPLXL
	public	_T_creal, _T_crealf, _T_creall
	public	_T_cimag, _T_cimagf, _T_cimagl
	public	_T_conj, _T_conjf, _T_conjl

_T_CMPLXF := _CMPLXF
_T_CMPLX := _CMPLX
_T_CMPLXL := _CMPLXL

_T_creal := _creal
_T_crealf := _crealf
_T_creall := _creall

_T_cimag := _cimag
_T_cimagf := _cimagf
_T_cimagl := _cimagl

_T_conj := _conj
_T_conjf := _conjf
_T_conjl := _conjl

	extern	_CMPLXF, _CMPLX, _CMPLXL
	extern	_creal, _crealf, _creall
	extern	_cimag, _cimagf, _cimagl
	extern	_conj, _conjf, _conjl
