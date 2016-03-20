; (c) Copyright 2007-2008 Zilog, Inc.

	.assume ADL=1
	SEGMENT code

	XREF _strlen
	XDEF _strchr

;   char *strchr(char *s,int c)
_strchr        equ 0000C4h

	END
