	assume	adl=1

	section	.text

	public	_char_to_digit

; char char_to_digit(char c)
_char_to_digit:
	; returns [0, 9] when ['0', '9']
	; returns [10, 35] when ['A', 'Z'] or ['a', 'z']
	; otherwise returns -1
	ld	iy, 3
	add	iy, sp
;-------------------------------------------------------------------------------
	ld	a, (iy)
	sub	a, 48
	cp	a, 10
	jr	c, .check_digit
	; Convert an alphabetic digit, case-insensitive
	sub	a, 65 - 48
	res	5, a
	add	a, 10
.check_digit:
	cp	a, 36
	ret	c
	ld	a, -1
	ret
