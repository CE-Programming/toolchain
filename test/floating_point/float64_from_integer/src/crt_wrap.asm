	assume	adl=1

;-------------------------------------------------------------------------------

	section	.text

	public	_clear_fe_cur_env
_clear_fe_cur_env:
	ld	a, (___fe_cur_env)
	and	a, -125	; feclearexcept(FE_ALL_EXCEPT)
	ld	(___fe_cur_env), a
	ret

	public	_get_fe_cur_env
_get_fe_cur_env:
	ld	a, (___fe_cur_env)
	ret

;-------------------------------------------------------------------------------

	section	.text

	public	_CRT_uitod, _CRT_itod

_CRT_uitod:
	ld	hl, 3
	add	hl, sp
	ld	hl, (hl)
	jp	__uitod

_CRT_itod:
	ld	hl, 3
	add	hl, sp
	ld	hl, (hl)
	jp	__itod

;-------------------------------------------------------------------------------

	extern	__ultod
	extern	__ltod
	extern	___fe_cur_env

	extern	__uitod
	extern	__itod
