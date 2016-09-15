; (c) Copyright 2007-2008 Zilog, Inc.

	.assume ADL=1
	SEGMENT code

	XDEF _strcmp

;   int strcmp(register char *s1, register char *s2)
_strcmp        equ 0000C8h

	END

