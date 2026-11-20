; A setter declares its count before GAS sees its forward patch sites.
; The numbered symbols stay local to the assembler. The group name also
; denotes the first patch site for code that reads the current value.
.macro smcEach name, count, first, emit, args:vararg
	.equ .Lsmc_count\name, \count
	.set .Lsmc_next\name, 1
	.set .Lsmc_index\@, \first
	.altmacro
	.rept \count - \first + 1
		\emit \name, %.Lsmc_index\@, \args
		.set .Lsmc_index\@, .Lsmc_index\@ + 1
	.endr
	.noaltmacro
.endm

.macro smcDefineSite name, index, width
	.equ .Lsmc_site\name\()_\index, . - \width
.endm

.macro smcSite name, width
	.if .Lsmc_next\name > .Lsmc_count\name
		.error "Too many SMC sites for \name"
	.endif
	.if .Lsmc_next\name == 1
		.equ \name, . - \width
	.endif
	.altmacro
	smcDefineSite \name, %.Lsmc_next\name, \width
	.noaltmacro
	.set .Lsmc_next\name, .Lsmc_next\name + 1
.endm

.macro smcByte name
	smcSite \name, 1
.endm

.macro smcWord name
	smcSite \name, 3
.endm

.macro smcOffset name, index
	.dw .Lsmc_site\name\()_\index - . - 2
.endm

.macro smcStore name, index, reg
	ld (.Lsmc_site\name\()_\index), \reg
.endm

; Encode a list of forward distances to bytes patched by _SetSmcBytes.
.macro setSmcBytes name, count
	call	_SetSmcBytes
	.db	\count
	smcEach \name, \count, 1, smcOffset
.endm

.macro setSmcBytesFast name, count
	pop	de			; de = return vector
	ex	(sp), hl		; l = byte
	ld	a, l
	ld	hl, \name
	ld	c, (hl)
	ld	(hl), a
	smcEach \name, \count, 2, smcStore, a
	ld	a, c			; a = old byte
	ex	de, hl			; hl = return vector
	jp	(hl)
.endm

.macro setSmcBytesInline name, count
	smcEach \name, \count, 1, smcStore, a
.endm

.macro setSmcWordsInline name, count
	smcEach \name, \count, 1, smcStore, hl
.endm
