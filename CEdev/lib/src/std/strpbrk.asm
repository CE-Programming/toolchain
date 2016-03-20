; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strpbrk.asm"
	.ASSUME ADL=1
	SEGMENT code
	
;   char *strpbrk(char *s1,char *s2)
_strpbrk       equ 0000E4h

	XREF _strchr:ROM
	XREF _strlen
	XDEF _strpbrk
	END

