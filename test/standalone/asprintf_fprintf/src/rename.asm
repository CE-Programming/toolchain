	assume	adl = 1

	section	.text

	public	_T_memset, _T_memcpy, _T_memcmp, _T_memccpy, _T_mempcpy
	public	_T_strlen, _T_strcmp, _T_stpcpy
	public	_T_bzero

_T_memset := _memset
_T_memcpy := _memcpy
_T_memcmp := _memcmp
_T_memccpy := _memccpy
_T_mempcpy := _mempcpy

_T_strlen := _strlen
_T_strcmp := _strcmp
_T_stpcpy := _stpcpy

_T_bzero := _bzero

	extern	_memset, _memcpy, _memcmp, _memccpy, _mempcpy
	extern	_strlen, _strcmp, _stpcpy
	extern	_bzero
