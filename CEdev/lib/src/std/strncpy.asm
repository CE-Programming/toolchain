; (c) Copyright 2007-2008 Zilog, Inc.

	.ASSUME ADL=1
	SEGMENT code

;   char *strncpy(char *dst,char *src,size_t n)
_strncpy       equ 0000E0h

	XREF _strlen
	XDEF _strncpy
	END

