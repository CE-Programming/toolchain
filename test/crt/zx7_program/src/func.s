	.assume	adl=1

	.global	_disable_compile_time_evaluation
	.type	_disable_compile_time_evaluation, @function

_disable_compile_time_evaluation:
	ld	hl, 42
	ret
