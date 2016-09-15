; (c) Copyright 2007-2008 Zilog, Inc.

	.assume ADL=1
	SEGMENT code

	XREF _strlen:ROM
	XDEF _strcspn
	
;   size_t strcspn(char *s1, char *s2)
_strcspn       equ 0000D0h

	END

