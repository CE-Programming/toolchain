; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strspn.asm"
	.ASSUME ADL=1
	SEGMENT code

;   size_t strspn(char *s1,char *s2)
_strspn        equ 0000ECh

	XREF _strchr:ROM
	XREF _strlen
	XDEF _strspn
	END

