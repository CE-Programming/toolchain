	assume	adl=1

	section	.rodata

	public	_PTR_000000
_PTR_000000:
	db	$00, $00, $00

	public	_PTR_FFFFFF
_PTR_FFFFFF:
	db	$FF, $FF, $FF

	section	.text

	public	_T_wmemset, _T_wmemcpy, _T_wmemmove, _T_wmemcmp, _T_wmemchr
	public	_T_wcslen, _T_wcsnlen

_T_wmemset := _wmemset
_T_wmemcpy := _wmemcpy
_T_wmemmove := _wmemmove
_T_wmemcmp := _wmemcmp
_T_wmemchr := _wmemchr

_T_wcslen := _wcslen
_T_wcsnlen := _wcsnlen

	extern	_wmemset, _wmemcpy, _wmemmove, _wmemcmp, _wmemchr
	extern	_wcslen, _wcsnlen
