; (c) Copyright 2007-2008 Zilog, Inc.
	FILE	".\strrchr.asm"
	.ASSUME ADL=1
	SEGMENT code

;   char *strrchr(char *s,int c)
_strrchr       equ 0000E8h

	XREF _strlen:ROM
	XDEF _strrchr
	END

