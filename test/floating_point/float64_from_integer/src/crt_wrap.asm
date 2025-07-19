	assume	adl=1

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

	public	_CRT_utod, _CRT_itod
if 0

_CRT_utod:
	ld	hl, 3
	add	hl, sp
	ld	hl, (hl)
	jp	__utod

_CRT_itod:
	ld	hl, 3
	add	hl, sp
	ld	hl, (hl)
	jp	__itod

else

_CRT_utod:
	ld	hl, 3
	add	hl, sp
	ld	hl, (hl)
	ld	e, 0
	jp	__ultod

_CRT_itod:
	ld	hl, 3
	add	hl, sp
	ld	hl, (hl)
	push	hl
	add	hl, hl
	sbc	hl, hl
	ld	e, l	; sign extend UHL to E:UHL
	pop	hl
	jp	__ltod
end if

	extern	__utod
	extern	__itod
	extern	__ultod
	extern	__ltod
	extern	___fe_cur_env
