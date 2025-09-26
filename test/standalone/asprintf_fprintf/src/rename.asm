	assume	adl = 1

	section	.text

	public	_T_memset, _T_memcpy, _T_memmove, _T_memcmp, _T_memccpy, _T_mempcpy, _T_memrchr
	public	_T_strlen, _T_strcmp, _T_strncmp, _T_stpcpy
	public	_T_bzero

_T_memset := _memset
_T_memcpy := _memcpy
_T_memmove := _memmove
_T_memcmp := _memcmp
_T_memccpy := _memccpy
_T_mempcpy := _mempcpy
_T_memrchr := _memrchr

_T_strlen := _strlen
_T_strcmp := _strcmp
_T_strncmp := _strncmp
_T_stpcpy := _stpcpy

_T_bzero := _bzero

	section	.rodata

	public	_NULL_ptr
_NULL_ptr:
	db	$00, $00, $00

	extern	_memset, _memcpy, _memmove, _memcmp, _memccpy, _mempcpy, _memrchr
	extern	_strlen, _strcmp, _strncmp, _stpcpy
	extern	_bzero
