	.assume	adl = 1

	.section	.text

	.global	_T_memset, _T_memcpy, _T_memmove, _T_memcmp, _T_memccpy, _T_mempcpy, _T_memrchr, _T_memmem, _T_memrmem
	.global	_T_strlen, _T_strcmp, _T_strncmp, _T_stpcpy, _T_stpncpy, _T_strlcat, _T_strchrnul, _T_strrstr
	.global	_T_bzero

_T_memset:
	jp	_memset
_T_memcpy:
	jp	_memcpy
_T_memmove:
	jp	_memmove
_T_memcmp:
	jp	_memcmp
_T_memccpy:
	jp	_memccpy
_T_mempcpy:
	jp	_mempcpy
_T_memrchr:
	jp	_memrchr
_T_memmem:
	jp	_memmem
_T_memrmem:
	jp	_memrmem

_T_strlen:
	jp	_strlen
_T_strcmp:
	jp	_strcmp
_T_strncmp:
	jp	_strncmp
_T_stpcpy:
	jp	_stpcpy
_T_stpncpy:
	jp	_stpncpy
_T_strlcat:
	jp	_strlcat
_T_strchrnul:
	jp	_strchrnul
_T_strrstr:
	jp	_strrstr

_T_bzero:
	jp	_bzero

	.section	.rodata._NULL_ptr

	.global	_NULL_ptr
_NULL_ptr:
	db	$00, $00, $00

	.extern	_memset, _memcpy, _memmove, _memcmp, _memccpy, _mempcpy, _memrchr, _memmem, _memrmem
	.extern	_strlen, _strcmp, _strncmp, _stpcpy, _stpncpy, _strlcat, _strchrnul, _strrstr
	.extern	_bzero
