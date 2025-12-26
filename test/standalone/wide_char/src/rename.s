	.assume	adl=1

	.section	.rodata

	.global	_PTR_000000
_PTR_000000:
	db	$00, $00, $00

	.global	_PTR_FFFFFF
_PTR_FFFFFF:
	db	$FF, $FF, $FF

	.global	_T_wmemset
	.global	_T_wmemcpy
	.global	_T_wmemmove
	.global	_T_wmemcmp
	.global	_T_wmemchr
	.global	_T_wcslen
	.global	_T_wcsnlen

_T_wmemset:
	jp 	_wmemset
_T_wmemcpy:
	jp 	_wmemcpy
_T_wmemmove:
	jp 	_wmemmove
_T_wmemcmp:
	jp 	_wmemcmp
_T_wmemchr:
	jp 	_wmemchr
_T_wcslen:
	jp 	_wcslen
_T_wcsnlen:
	jp 	_wcsnlen

	.extern	_wmemset
	.extern	_wmemcpy
	.extern	_wmemmove
	.extern	_wmemcmp
	.extern	_wmemchr
	.extern	_wcslen
	.extern	_wcsnlen
