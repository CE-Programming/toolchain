; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strlen.asm"
	.assume ADL=1
	SEGMENT code

;   size_t strlen(char *s)
_strlen        equ 0000D4h

	XDEF _strlen
	END

